/**
 * @class   alpStatsEnhancedToxicResistanceProgres
 * @brief   Sincroniza a porcentagem de progresso para o próximo nível de Resistência Tóxica
 * Auditado em: 2026 - Foco em Estabilidade de Operação e Eficiência de Banda
 */
class alpStatsEnhancedToxicResistanceProgres extends alpStatsBaseEnhanced
{
	void alpStatsEnhancedToxicResistanceProgres(PlayerBase player)
	{
		alp_Type = alpRPelementsEnahnced.TOXIC_RESISTPROGRES;
	}
	
	override protected bool GetValueServer(out float value)
	{
		// 1. BLINDAGEM: Verifica se o player e os componentes de Stat estão instanciados
		if (!alp_Player || !alp_Player.GetStatPerkToxicResistance() || !alp_Player.GetStatPerkToxicResistanceProgress())
		{
			value = 0;
			return false;
		}

		int level = alp_Player.GetStatPerkToxicResistance().Get();
		int levelCap = GetND().GetRP().GetPerkToxicResistanceLevelCup();

		if (level < levelCap)
		{
			float requiredExp = alp_Player.GetRP().GetToxicResistanceRequiredExp(level + 1);
			
			// 2. SEGURANÇA MATEMÁTICA: Proteção contra divisão por zero
			if (requiredExp > 0)
			{
				float currentExp = alp_Player.GetStatPerkToxicResistanceProgress().Get();
				// Arredondamento para 1% de precisão (evita spam de rede)
				alp_Value = Math.Round((currentExp / requiredExp) * 100);
			}
			else
			{
				alp_Value = 0;
			}
		}
		else
		{
			// Nível máximo atingido: barra sempre em 100%
			alp_Value = 100;
		}
		
		// 3. DELTA CHECK: Só envia dados se o valor arredondado mudar
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