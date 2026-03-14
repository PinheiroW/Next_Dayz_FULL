/**
 * NDCreatures - alpMission.c
 * Auditoria Técnica: Pró-Gamer / IA Modding Specialist
 */

modded class alpMission 
{
	// Corrigido typo: m_IsAiResctricted -> m_IsAiRestricted
	private bool m_IsAiRestricted;

	void SetAiRestricted(bool state)
	{
		m_IsAiRestricted = state;
	}
	
	override void LoadMission(alpMissionStore s)
	{
		super.LoadMission(s);

		// Executa apenas no Servidor para evitar conflitos no Cliente
		if (GetGame().IsServer() && m_IsAiRestricted) 
		{
			alpPluginNDmissionsSystem.RegisterRestrictedMission(this);
		}
	}
	
	override alpMissionBase SpawnMission(vector pos = "0 0 0", vector angle = "0 0 0", int parentID = -1)
	{
		alpMissionBase m = super.SpawnMission(pos, angle, parentID);
		
		if (GetGame().IsServer() && m)
		{
			// Verifica se já não foi registrado no LoadMission para evitar duplicidade
			if (m_IsAiRestricted) 
			{
				// O método Unregister seguido de Register garante que não haverá duplicatas na array
				alpPluginNDmissionsSystem.UnRegisterRestrictedMission(this);
				alpPluginNDmissionsSystem.RegisterRestrictedMission(this);
			}			
			return m;
		}
		return m;
	}	
	
	override void DespawnMission()
	{		
		if (GetGame().IsServer() && m_IsAiRestricted) 
		{
			alpPluginNDmissionsSystem.UnRegisterRestrictedMission(this);
		}			
		super.DespawnMission();		
	}	
}