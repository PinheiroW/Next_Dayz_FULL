/**
 * @class   alpCholera
 * @brief   Gerencia a cobrança e a cura da Cólera (Água contaminada) no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Segurança de Rede
 */
class alpCholera extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia de configuração financeira
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().Cholera;
	}
	
	override void CureDisease()
	{
		// 2. Proteção vital do objeto do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Tratamentos médicos de doenças/agentes devem ser estritamente no Servidor
		if (GetGame().IsServer())
		{
			// 4. Limpeza segura do Agente da Cólera
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.CHOLERA, 0 );
			}
				
			// 5. Desativação segura dos sintomas (vômito, perda de água)
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHOLERA))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_CHOLERA);
				}		
			}
		}
	}
}