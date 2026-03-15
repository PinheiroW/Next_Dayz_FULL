/**
 * @class   alpStatsEnhancedHuntingProgres
 * @brief   Sincroniza a porcentagem de progresso para o próximo nível de Caça
 * Auditado em: 2026 - Foco em Estabilidade de Cálculo e Performance
 */
class alpStatsEnhancedHuntingProgres extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedHuntingProgres(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.HUNTINGPROGRES;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. DEFESA CONTRA PONTEIROS NULOS
		if (!alp_Player || !alp_Player.GetStatPerkHunting() || !alp_Player.GetStatPerkHuntingProgress())
		{
			value = 0;
			return false;
		}

		int level = alp_Player.GetStatPerkHunting().Get();
		int levelCap = GetND().GetRP().GetPerkHuntingLevelCup();
		
		if (level < levelCap)
		{
			float requiredExp = alp_Player.GetRP().GetHuntingRequiredExp(level + 1);
			
			// 2. PROTEÇÃO CONTRA DIVISÃO POR ZERO
			if (requiredExp > 0)
			{
				float currentExp = alp_Player.GetStatPerkHuntingProgress().Get();
				// Arredondamos para 1 casa decimal para suavidade no HUD e economia de rede
				alp_Value = Math.Round((currentExp / requiredExp) * 100); 
			}
			else
			{
				alp_Value = 0;
			}
		}
		else
		{
			alp_Value = 100; // Nível máximo atingido
		}
		
		// 3. LOGICA DE ATUALIZAÇÃO (DELTA)
		if (alp_Value != alp_LastValue)
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