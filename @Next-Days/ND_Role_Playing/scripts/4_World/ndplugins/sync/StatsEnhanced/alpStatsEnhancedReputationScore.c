/**
 * @class   alpStatsEnhancedReputationProgress
 * @brief   Sincroniza a porcentagem de progresso para o próximo nível de Reputação
 * Auditado em: 2026 - Foco em Integridade de Dados e Redução de Overhead de Rede
 */
class alpStatsEnhancedReputationProgress extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedReputationProgress(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.REPUTATIONPROGRES;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. SEGURANÇA: Verifica se o player e os componentes de Stat existem
		if (!alp_Player || !alp_Player.GetStatPerkReputation() || !alp_Player.GetStatPerkReputationProgress())
		{
			value = 0;
			return false;
		}

		// Usamos AbsInt porque o nível pode ser negativo (Bandido), mas o progresso é escalar
		int level = Math.AbsInt(alp_Player.GetStatPerkReputation().Get());
		int levelCap = GetND().GetRP().GetPerkReputationLevelCup();

		if (level < levelCap)
		{
			float requiredExp = alp_Player.GetRP().GetReputationRequiredExp(level + 1);
			
			// 2. SEGURANÇA MATEMÁTICA: Proteção contra divisão por zero
			if (requiredExp > 0)
			{
				float currentExp = Math.AbsFloat(alp_Player.GetStatPerkReputationProgress().Get());
				// Arredondamos para 1 casa decimal para feedback suave sem sobrecarregar a rede
				alp_Value = Math.Round((currentExp / requiredExp) * 100);
			}
			else
			{
				alp_Value = 0;
			}
		}
		else
		{
			alp_Value = 100; // Nível máximo atingido (Heroi ou Bandido Master)
		}
		
		// 3. DELTA CHECK: Só envia se houver mudança significativa
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