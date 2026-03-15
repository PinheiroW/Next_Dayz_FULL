/**
 * @class   alpStatsEnhancedTemperature
 * @brief   Sincroniza a temperatura corporal com suporte a febre dinâmica
 * Auditado em: 2026 - Foco em Realismo Térmico e Fluidez de HUD
 */
class alpStatsEnhancedTemperature extends alpStatsBaseEnhanced
{
	float alp_LastTemp = -1;
	bool  alp_HasFever;
	
	void alpStatsEnhancedTemperature(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.TEMPERATURE;
	}
	
	override protected bool GetValueServer(out float value)
	{
		if (!alp_Player) return false;

		alp_Value = GetTemperatureValue();	
		
		// Delta check com pequena margem para evitar spam de rede por decimais irrelevantes
		if ( Math.AbsFloat(alp_Value - alp_LastValue) > 0.1 )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		value = alp_LastValue;
		return false;
	}

	float GetTemperatureValue()
	{
		// 1. SEMPRE BASEAR NA TEMPERATURA REAL DO MOTOR DO JOGO
		float currentStatTemp = alp_Player.GetStatTemperature().Get();
		
		// 2. LÓGICA DE FEBRE COMO MODIFICADOR
		if (alp_Player.GetModifiersManager() && alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_FEVER))
		{
			if (!alp_HasFever)
			{
				alp_HasFever = true;
				// Sorteia um incremento de febre (ex: +2.0°C a +4.0°C acima do normal)
				alp_LastTemp = Math.RandomFloatInclusive(2.0, 4.0);
			}
			
			// Retorna a temperatura real + o bônus da febre
			return currentStatTemp + alp_LastTemp;
		}
		else
		{
			// 3. RESET QUANDO CURADO
			if (alp_HasFever)
			{
				alp_HasFever = false;
				alp_LastTemp = -1;
			}
			
			return currentStatTemp;
		}
	}

	override bool IsPlayerStats()
	{
		return true;
	}
}