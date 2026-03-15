/**
 * @class   alpStatsEnhancedFatigue
 * @brief   Sincroniza a porcentagem de fadiga/cansaço (0-100%)
 * Auditado em: 2026 - Foco em Segurança Matemática e Otimização de Tráfego
 */
class alpStatsEnhancedFatigue extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedFatigue(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.FATIGUE;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. BLINDAGEM DE OBJETOS
		if (!alp_Player || !alp_Player.GetStatTiredness())
		{
			value = 0;
			return false;
		}

		float current = alp_Player.GetStatTiredness().Get();
		float max = alp_Player.GetStatTiredness().GetMax();

		// 2. PROTEÇÃO CONTRA DIVISÃO POR ZERO E NANS
		if (max <= 0)
		{
			alp_Value = 0;
		}
		else
		{
			// Calculamos a porcentagem e usamos Math.Round para evitar 
			// atualizações de rede por variações decimais ínfimas.
			alp_Value = Math.Round((current / max) * 100);
		}
		
		// 3. FILTRO DE ATUALIZAÇÃO (Delta Check)
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		return false;
	}
	
	override bool IsPlayerStats()
	{
		return true;
	}	
}