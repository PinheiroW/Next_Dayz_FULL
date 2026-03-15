/**
 * ItemBase.c
 * Módulo: ND_MISSIONS
 * * Este arquivo modifica a base de todos os itens do jogo para suportar:
 * 1. Sistema de Proteção ALP (Radiação/Biológica)
 * 2. Cálculo de valor para Traders (Quantidade ALP)
 * 3. Sincronização de Contaminação
 */

enum alpPROTECTION
{
	BIOLOGICAL = 1,
	CHEMICAL   = 2,
	RADIATION  = 3
}

modded class ItemBase
{
	protected bool alp_IsMissionObject = false;
	ref alpProtectionBonuses alp_ProtectionBonuses;
	
	// --- Construtor e Sincronização ---
	void ItemBase()
	{
		// Registra a variável de agentes para que o cliente saiba se o item está contaminado
		RegisterNetSyncVariableInt("m_AttachedAgents"); 
	}	
	
	// --- Destruidor e Limpeza ---
	void ~ItemBase()
	{
		if (GetGame() && GetGame().IsServer()) 
		{
			PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
			if (player) 
			{
				// Remove o rastro de contaminação do jogador ao deletar/destruir o item
				player.RemoveContaminedItem(GetID());
			}
		}	
	}	
	
	// --- Sistema de Proteção contra Riscos Ambientais ---

	/**
	 * Retorna a eficácia da proteção baseada no estado do item.
	 * Itens arruinados não protegem nada (0.0).
	 */
	float GetHealthLevelValueALP()
	{
		float level = 1.0;
		switch (GetHealthLevel())
		{
			case 1: level = 0.75; break; // Worn
			case 2: level = 0.50; break; // Damaged
			case 3: level = 0.25; break; // Badly Damaged
			case 4: level = 0.00; break; // Ruined
		}
		return level;
	}

	/**
	 * Calcula a quantidade real do item para o sistema de economia.
	 * Suporta pilhas de munição, carregadores e consumíveis.
	 */
	float GetQuantityALP()
	{
		if (IsMagazine())
		{
			Magazine_Base mag = Magazine_Base.Cast(this);
			if (mag && mag.GetAmmoMax() > 0)
			{
				return (float)mag.GetAmmoCount() / mag.GetAmmoMax();
			}
		}		
				
		if (HasQuantity() && GetQuantityMax() > 0)				
		{
			return (float)GetQuantity() / GetQuantityMax();
		}
		
		return 1.0; 
	}

	// --- Compatibilidade com Namalsk Survival ---

#ifdef NAMALSK_SURVIVAL		
	override void SetWet(float value, bool allow_client = false)
	{
		if (!IsServerCheck(allow_client)) return;

		// Impede que álcool e desinfetantes congelem (mantenham o estado 'Wet' do motor do jogo)
		if (GetWetMax() > 1.9) 
		{
			int liquid_type = GetLiquidType();	
			if (liquid_type == LIQUID_VODKA || liquid_type == LIQUID_DISINFECTANT)
				return;
		}
		super.SetWet(value, allow_client);
	}
#endif

	// --- Funções de Estado de Missão ---

	void SetMissionObject(bool state) { alp_IsMissionObject = state; }
	bool IsMissionObject() { return alp_IsMissionObject; }
}