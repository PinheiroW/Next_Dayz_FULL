/**
 * @class   alpStatsEnhancedRadResitProgres
 * @brief   Sincroniza a porcentagem de progresso para o próximo nível de Resistência à Radiação
 * Auditado em: 2026 - Foco em Prevenção de Divisão por Zero e Segurança de Ponteiro
 */
class alpStatsEnhancedRadResitProgres extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedRadResitProgres(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.RAD_RESISTPROGRES;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. BLINDAGEM: Verifica se o player e os componentes de Stat existem
		if (!alp_Player || !alp_Player.GetStatPerkRadiationResistance() || !alp_Player.GetStatPerkRadiationResistanceProgress())
		{
			value = 0;
			return false;
		}

		int level = alp_Player.GetStatPerkRadiationResistance().Get();
		int levelCap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();
		
		if (level < levelCap)
		{
			float requiredExp = alp_Player.GetRP().GetRadiationResistanceRequiredExp(level + 1);
			
			// 2. SEGURANÇA MATEMÁTICA: Evita divisão por zero
			if (requiredExp > 0)
			{
				float currentExp = alp_Player.GetStatPerkRadiationResistanceProgress().Get();
				// Arredondamos para evitar atualizações de rede por variações insignificantes
				alp_Value = Math.Round((currentExp / requiredExp) * 100);
			}
			else
			{
				alp_Value = 0;
			}
		}
		else
		{
			// Se atingiu o nível máximo, a barra deve ficar cheia (100%)
			alp_Value = 100;
		}
		
		// 3. FILTRO DE ATUALIZAÇÃO (Delta Check)
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