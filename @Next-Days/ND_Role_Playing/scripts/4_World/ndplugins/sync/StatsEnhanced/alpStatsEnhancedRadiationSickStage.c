/**
 * @class   alpStatsEnhancedRadiationSickStage
 * @brief   Sincroniza o estágio atual da doença de radiação (L1 a L5)
 * Auditado em: 2026 - Foco em Estabilidade de Instanciação e Performance
 */
class alpStatsEnhancedRadiationSickStage extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedRadiationSickStage(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.RADIATIONSICKSTAGE;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. BLINDAGEM: Verifica se o player e o módulo RP existem
		if (!alp_Player || !alp_Player.GetRP())
		{
			value = 0;
			return false;
		}

		// 2. OTIMIZAÇÃO: Acesso direto ao valor para evitar overhead de função
		// Convertemos para int para garantir que o estágio seja um número "limpo"
		int currentStage = alp_Player.GetRP().GetRadiationSickStage();
		
		// 3. LOGICA DE ATUALIZAÇÃO (DELTA)
		if (currentStage != (int)alp_LastValue)
		{
			alp_LastValue = currentStage;
			value = (float)currentStage;
			return true;
		}
		
		return false;
	}

	// 4. LIMPEZA: Removido GetRadSickStage() para simplificar a classe, 
	// a menos que seja necessário para overrides futuros.
		
	override bool IsPlayerStats()
	{
		return true;
	}
}