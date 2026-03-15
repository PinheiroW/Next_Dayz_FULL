/**
 * PlayerBase.c
 * * MODDED PLAYER ENTITY - Módulo ND_MISSIONS
 * Gerencia os sistemas core: Radiação, Proteção, Trade, Logs de Hit e Comportamento.
 */

enum alpEntityType
{
	SUICIDE,
	PLAYER,
	ZOMBIE,
	ANIMAL,
	GRENADE,
}

// Classe de rastreamento de último dano recebido
class alpLastHit
{
	int alp_EntityType;
	int alp_HitTime;
	int alp_DamageType;
	string alp_Source;
	string alp_Name;
	
	void alpLastHit() { alp_DamageType = DT_CUSTOM; }
	
	void RegisterHit(int entity, int time, int type, string source = "", string name = "")
	{
		alp_EntityType = entity;
		alp_HitTime = time;
		alp_DamageType = type;
		alp_Source = source;
		alp_Name = name;
	}
	
	bool IsSuicide()
	{
		int time = GetGame().GetTime();
		int lasthit = alp_HitTime + 30000; // Janela de 30 segundos
		return (lasthit < time || alp_EntityType == alpEntityType.SUICIDE);
	}	
}

modded class PlayerBase extends ManBase
{
	protected ref alpLastHit m_alpLastHit;
	protected ref array<int> alp_ContaminedItems;
	protected bool m_IsNVGWorking;

	void PlayerBase()
	{
		m_alpLastHit = new alpLastHit();
		alp_ContaminedItems = new array<int>;
	}

	// --- Gerenciamento de Radiação e Itens Contaminados ---

	void AddContaminedItem(int id)
	{
		if (alp_ContaminedItems.Find(id) == -1)
			alp_ContaminedItems.Insert(id);
	}

	void RemoveContaminedItem(int id)
	{
		int index = alp_ContaminedItems.Find(id);
		if (index != -1)
			alp_ContaminedItems.Remove(index);
	}

	/**
	 * Retorna a soma de radiação emitida por todos os itens no inventário.
	 */
	float GetItemsRadiation()
	{
		float total = 0;
		// Lógica integrada com o sistema global de radiação
		if (GetRP()) total = GetRP().GetItemsRadiation(alp_ContaminedItems);
		return total;
	}

	// --- Controle de Combate e Zonas de Segurança ---

	override bool CanBeRestrained()
	{
		if (GetRP() && !GetRP().IsAllowedDamage()) return false;
		return super.CanBeRestrained();
	}

	override bool IsWeaponRaiseCompleted()
	{
		// Impede levantar armas em zonas de Trade
		if (GetRP() && GetRP().IsInTradeZone() && !GetRP().IsAllowedDamage()) 
			return false;
				
		return super.IsWeaponRaiseCompleted();
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		
		// Registro de Log de Dano
		if (m_alpLastHit && source)
		{
			int entityType = alpEntityType.ZOMBIE;
			if (source.IsInherited(PlayerBase)) entityType = alpEntityType.PLAYER;
			
			m_alpLastHit.RegisterHit(entityType, GetGame().GetTime(), damageType, source.GetType(), source.GetHierarchyRootPlayer().GetIdentity().GetName());
		}
	}

	// --- Utilidades de Movimento e Estado ---

	bool IsNVGWorking() { return m_IsNVGWorking; }
	void SetNVGWorking(bool state) { m_IsNVGWorking = state; }

	bool IsErectedALP()
	{
		HumanMovementState state = new HumanMovementState();
		GetMovementState(state);
		return (state.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_ERECT);
	}

	void ForceStanceALP(int id)
	{
		HumanCommandMove cm = GetCommand_Move();
		if (cm)
		{
			if (id == 0) cm.ForceStance(DayZPlayerConstants.STANCEIDX_ERECT);
			else if (id == 1) cm.ForceStance(DayZPlayerConstants.STANCEIDX_CROUCH);
			else if (id == 2) cm.ForceStance(DayZPlayerConstants.STANCEIDX_PRONE);
		}
	}
}