/**
 * PlayerBase.c
 * * MODDED PLAYER ENTITY - Módulo ND_MISSIONS
 * Núcleo de gerenciamento do sobrevivente: Radiação, Combate em SafeZones e Logs de Hit.
 */

/**
 * Tipos de entidades para fins de registro de Killfeed/Dano.
 */
enum alpEntityType
{
	SUICIDE,
	PLAYER,
	ZOMBIE,
	ANIMAL,
	GRENADE,
}

/**
 * Classe utilitária para armazenar o contexto do último golpe recebido.
 */
class alpLastHit
{
	int alp_EntityType;
	int alp_HitTime;
	int alp_DamageType;
	string alp_Source;
	string alp_Name;
	
	void alpLastHit() 
	{ 
		alp_DamageType = DT_CUSTOM; 
	}
	
	/**
	 * Registra os dados da agressão para auditoria posterior.
	 */
	void RegisterHit(int entity, int time, int type, string source = "", string name = "")
	{
		alp_EntityType = entity;
		alp_HitTime    = time;
		alp_DamageType = type;
		alp_Source     = source;
		alp_Name       = name;
	}
	
	/**
	 * Verifica se a morte deve ser classificada como suicídio baseado no tempo do último golpe.
	 */
	bool IsSuicide()
	{
		int currentTime = GetGame().GetTime();
		// Janela de 30 segundos de persistência do agressor
		int expirationTime = alp_HitTime + 30000; 
		return (expirationTime < currentTime || alp_EntityType == alpEntityType.SUICIDE);
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

	// --- GERENCIAMENTO DE RADIAÇÃO ---

	/**
	 * Adiciona um item à lista de emissores de radiação no inventário.
	 */
	void AddContaminedItem(int id)
	{
		if (alp_ContaminedItems && alp_ContaminedItems.Find(id) == -1)
			alp_ContaminedItems.Insert(id);
	}

	/**
	 * Remove a influência radioativa de um item.
	 */
	void RemoveContaminedItem(int id)
	{
		if (!alp_ContaminedItems) return;
		int index = alp_ContaminedItems.Find(id);
		if (index != -1)
			alp_ContaminedItems.Remove(index);
	}

	/**
	 * Calcula a radiação total acumulada pelos itens transportados.
	 */
	float GetItemsRadiation()
	{
		float total = 0;
		// Integração com o plugin de RPG para somar a toxicidade dos itens
		if (GetRP()) 
			total = GetRP().GetItemsRadiation(alp_ContaminedItems);
		return total;
	}

	// --- COMPORTAMENTO EM ZONAS DE TRADE E COMBATE ---

	/**
	 * Impede que o jogador seja rendido/algemado dentro de SafeZones.
	 */
	override bool CanBeRestrained()
	{
		if (GetRP() && !GetRP().IsAllowedDamage()) 
			return false;
		return super.CanBeRestrained();
	}

	/**
	 * Bloqueia o uso de armas em áreas de comércio para garantir a ordem.
	 */
	override bool IsWeaponRaiseCompleted()
	{
		if (GetRP() && GetRP().IsInTradeZone() && !GetRP().IsAllowedDamage()) 
			return false;
				
		return super.IsWeaponRaiseCompleted();
	}

	/**
	 * Intercepta o evento de dano para registrar o agressor.
	 */
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		
		if (m_alpLastHit && source)
		{
			int entityType = alpEntityType.ZOMBIE;
			if (source.IsInherited(PlayerBase)) 
				entityType = alpEntityType.PLAYER;
			
			// Tenta extrair o nome do agressor (seja ele um NPC, Jogador ou IA)
			string attackerName = "Unknown";
			if (source.GetHierarchyRootPlayer() && source.GetHierarchyRootPlayer().GetIdentity())
				attackerName = source.GetHierarchyRootPlayer().GetIdentity().GetName();
			
			m_alpLastHit.RegisterHit(entityType, GetGame().GetTime(), damageType, source.GetType(), attackerName);
		}
	}

	// --- UTILITÁRIOS DE ESTADO E MOVIMENTAÇÃO ---

	bool IsNVGWorking() { return m_IsNVGWorking; }
	void SetNVGWorking(bool state) { m_IsNVGWorking = state; }

	/**
	 * Verifica se o personagem está na postura ereta.
	 */
	bool IsErectedALP()
	{
		HumanMovementState state = new HumanMovementState();
		GetMovementState(state);
		return (state.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_ERECT);
	}

	/**
	 * Força uma postura específica via comando de movimento.
	 * @param id: 0 (Ereto), 1 (Agachado), 2 (Deitado).
	 */
	void ForceStanceALP(int id)
	{
		HumanCommandMove moveCmd = GetCommand_Move();
		if (moveCmd)
		{
			switch(id)
			{
				case 0: moveCmd.ForceStance(DayZPlayerConstants.STANCEIDX_ERECT); break;
				case 1: moveCmd.ForceStance(DayZPlayerConstants.STANCEIDX_CROUCH); break;
				case 2: moveCmd.ForceStance(DayZPlayerConstants.STANCEIDX_PRONE); break;
			}
		}
	}
}