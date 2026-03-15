/**
 * @class   alpBrainDisease
 * @brief   Gerencia a cobrança e a cura da Doença do Cérebro (Kuru) no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Segurança de Nulidade
 */
class alpBrainDisease extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas de carregamento de Configs/Traders
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().BrainSick;
	}
	
	override void CureDisease()
	{
		// 2. Proteção vital do objeto do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Tratamentos médicos só devem ser processados pelo Servidor
		if (GetGame().IsServer())
		{
			// Zera os agentes da doença de forma segura
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.BRAIN, 0 );
			}
			
			// Desativa os sintomas (tremores e risadas)
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BRAIN))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BRAIN);
				}	
			}
		}
	}
}