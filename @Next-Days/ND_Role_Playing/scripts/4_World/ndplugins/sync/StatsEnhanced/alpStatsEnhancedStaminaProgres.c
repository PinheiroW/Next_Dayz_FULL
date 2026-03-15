/**
 * @class   alpStatsEnhancedStaminaProgress
 * @brief   Sincroniza a porcentagem de progresso para o próximo nível de Stamina
 * Auditado em: 2026 - Foco em Prevenção de Falhas Matemáticas e Performance
 */
class alpStatsEnhancedStaminaProgress extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedStaminaProgress(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.STAMINAPROGRES;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. BLINDAGEM: Garante que o player e os sistemas de stat estão ativos
		if (!alp_Player || !alp_Player.GetStatPerkStamina() || !alp_Player.GetStatPerkStaminaProgress())
		{
			value = 0;
			return false;
		}

		int level = alp_Player.GetStatPerkStamina().Get();
		int levelCap = GetND().GetRP().GetPerkStaminaLevelCup();
		
		if (level < levelCap)
		{
			float requiredExp = alp_Player.GetRP().GetStaminaRequiredExp(level + 1);
			
			// 2. SEGURANÇA MATEMÁTICA: Evita divisão por zero
			if (requiredExp > 0)
			{
				float currentExp = alp_Player.GetStatPerkStaminaProgress().Get();
				// Arredondamos para evitar spam de rede com decimais inúteis
				alp_Value = Math.Round((currentExp / requiredExp) * 100);
			}
			else
			{
				alp_Value = 0;
			}
		}
		else
		{
			// Nível máximo atingido: barra 100% cheia
			alp_Value = 100;
		}
		
		// 3. DELTA CHECK: Só envia dados se a porcentagem inteira mudar
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