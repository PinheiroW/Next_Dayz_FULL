/**
 * @class   alpPoisoning
 * @brief   Gerencia a cobrança e a cura da Intoxicação Alimentar no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Segurança de Rede
 */
class alpPoisoning extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia de configuração financeira
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().FoodPoisoning;
	}
	
	override void CureDisease()
	{
		// 2. Proteção vital do objeto do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Tratamentos de agentes patogênicos DEVEM ocorrer apenas no Servidor
		if (GetGame().IsServer())
		{
			// 4. Limpeza segura do Agente de Intoxicação Alimentar
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.FOOD_POISON, 0 );
			}
			
			// Nota: Diferente da Cólera, a intoxicação no DayZ costuma sumir 
			// naturalmente assim que o agente é zerado, não exigindo remoção forçada de Modificador aqui.
		}			
	}
}