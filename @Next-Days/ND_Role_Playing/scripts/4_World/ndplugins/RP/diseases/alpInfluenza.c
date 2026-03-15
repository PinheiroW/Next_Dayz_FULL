/**
 * @class   alpInfluenza
 * @brief   Gerencia a cobrança e a cura da Gripe (Influenza) no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Segurança de Rede
 */
class alpInfluenza extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia de configuração financeira
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().Influenza;
	}
		
	override void CureDisease()
	{
		// 2. Proteção vital do objeto do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Tratamentos médicos de doenças/agentes devem ser estritamente no Servidor
		if (GetGame().IsServer())
		{
			// 4. Limpeza segura do Agente da Influenza
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.INFLUENZA , 0 );
			}
				
			// 5. Desativação segura dos sintomas (Tosse, febre, etc.)
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_INFLUENZA))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_INFLUENZA);
				}		
			}
		}
	}
}