/**
 * @class   alpStatsTendencyTiredness
 * @brief   Sincroniza tendência e gravidade do cansaço para o HUD
 * Auditado em: 2026 - Foco em Bitmasking e Estabilidade de HUD
 */
class alpStatsTendencyTiredness extends alpStatsBase
{
	protected int TENDENCY_MASK = 7;           // Primeiros 3 bits (0-7)
	protected int SERIOUSNESS_BIT_OFFSET = 3;  // Offset para gravidade
	
	int alp_ValueLast = -99999;
	protected PluginPlayerStatus m_ModulePlayerStatus;
	
	void alpStatsTendencyTiredness(PlayerBase player)
	{
		alp_Type = alpRPelements.TDCY_TIREDNESS;
		NUM_OF_BITS = 6; // 3 bits para tendência + 3 para gravidade
		
		// 1. PROTEÇÃO DE LADO: Só busca o plugin se estivermos no Cliente
		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			m_ModulePlayerStatus = PluginPlayerStatus.Cast(GetPlugin(PluginPlayerStatus));
		}
	}
	
	override void Update()
	{
		// 2. REATIVAÇÃO DO SISTEMA: Busca o valor real do cansaço do jogador
		if (alp_Player && alp_Player.GetStatTiredness())
		{
			// Nota: O valor aqui deve vir processado como bitmask (Tendência + Gravidade)
			// vindo da lógica do componente StatTiredness.
			alp_Value = alp_Player.GetStatTiredness().Get();
		}
	}
	
	override void SetValue(int value)
	{
		alp_Value = value;
		
		// 3. ATUALIZAÇÃO SEGURA: Só tenta atualizar o HUD no Cliente
		if (m_ModulePlayerStatus && IsValueChanged())
		{
			UpdateHUD();
		}
	}	

	bool IsValueChanged()
	{
		return (alp_Value != alp_ValueLast);
	}
	
	void UpdateHUD()
	{
		alp_ValueLast = alp_Value;
		
		// Decodificação dos bits (Bitmasking)
		int seriousness = alp_Value >> SERIOUSNESS_BIT_OFFSET;
		int tendency = TENDENCY_MASK & alp_Value;		
		
		// Lógica de tendência (Up/Down/Stable)
		if (tendency > 3) 
		{
			tendency = -(tendency - 3);
		}		
		
		// 4. NOTIFICAÇÃO: Chave customizada NTFKEY_ALPTIREDNESS deve estar registrada no PluginPlayerStatus
		m_ModulePlayerStatus.DisplayTendency(NTFKEY_ALPTIREDNESS, tendency, TranslateLevelToStatus(seriousness));
	}
	
	int TranslateLevelToStatus(int level)
	{
		// 5. MAPEAMENTO DE CORES DO HUD:
		// 1-2: Branco/Cinza | 3: Amarelo | 4: Laranja | 5: Vermelho
		switch (level)
		{
			case DSLevels.WARNING:  return 3; // Amarelo
			case DSLevels.CRITICAL: return 4; // Laranja
			case DSLevels.BAD:      return 5; // Vermelho
		}
		return 1; // Normal / Branco
	}
}