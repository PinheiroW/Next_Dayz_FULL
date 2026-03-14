/**
 * alpPluginNDmissionsSystem
 * Gerenciador de zonas de restrição de IA.
 * FIX: Inconsistência de raios no Register/Unregister.
 * OTIMIZAÇÃO: Uso de DistanceSq para ganho de performance em loops.
 */
modded class alpPluginNDmissionsSystem extends alpPlugin
{
	static ref map<int, ref alpMission> m_AiCannotSpawnInMissions = new map<int, ref alpMission>;
	
	static int m_IsLocal = 0;
	static int m_IsGlobal = 0;

	// Removido o delete manual no destrutor para evitar crashes no shutdown
	void ~alpPluginNDmissionsSystem() {}

	override void AddMissionByName(string name, alpMission mission)
	{
		super.AddMissionByName(name, mission);
		
		auto creatures = GetND().GetCreatures();
		if (mission && creatures && creatures.GetOptions())
		{
			array<string> registered = creatures.GetOptions().CannotSpawnInMissions;
			if (registered && registered.Find(name) != -1) 
			{
				mission.SetAiRestricted(true);
			}
		}
	}	
	
	static void RegisterRestrictedMission(alpMission m)
	{
		if (!m) return;
		
		int id = m.GetID();
		int radius = m.alp_DamageRadius;		
		
		// Valor padronizado: 20000
		if (radius >= 20000) 
		{
			m_IsGlobal += 1;
		} 
		else 
		{
			if (!m_AiCannotSpawnInMissions.Contains(id))
			{
				m_IsLocal += 1;
				m_AiCannotSpawnInMissions.Set(id, m);
			}
		}
	}

	static void UnRegisterRestrictedMission(alpMission m)
	{
		if (!m) return;
		
		int id = m.GetID();
		int radius = m.alp_DamageRadius;
		
		// Valor padronizado: 20000 (deve ser igual ao Register)
		if (radius >= 20000) 
		{
			m_IsGlobal -= 1;
		} 
		else 
		{
			if (m_AiCannotSpawnInMissions.Contains(id))
			{
				m_IsLocal -= 1;
				m_AiCannotSpawnInMissions.Remove(id);
			}
		}
		
		// Proteção contra números negativos
		if (m_IsGlobal < 0) m_IsGlobal = 0;
		if (m_IsLocal < 0) m_IsLocal = 0;
	}

	static bool CansSpawnAI(EntityAI ai)
	{
		if (!ai) return true;
		
		// Se houver uma restrição global (ex: evento de manutenção ou purga), nenhuma IA spawna
		if (m_IsGlobal > 0) return false;
		
		// Se não houver missões locais restritas, permite o spawn imediatamente
		if (m_IsLocal == 0) return true;

		vector ai_pos = ai.GetPosition();
		
		foreach (int id, alpMission m : m_AiCannotSpawnInMissions)
		{
			if (m)
			{
				float radius = m.alp_DamageRadius;
				// OTIMIZAÇÃO: DistanceSq é muito mais leve que Distance (evita raiz quadrada)
				float distSq = vector.DistanceSq(ai_pos, m.GetPosition());
				
				if (distSq <= (radius * radius))
				{
					return false; // IA está dentro de uma zona restrita
				}
			}
		}
		
		return true;
	}
}