/**
 * @class   alpPoisoningChemical2
 * @brief   Gerencia a cobrança e a cura da Contaminação Química Nível 2 no Next Days
 * Auditado em: 2026 - Foco em Correção de Sintaxe, Failsafes e Segurança de Rede
 */
// 1. Nome da classe corrigido (Removido o typo 'Chemica1_2')
class alpPoisoningChemical2 extends alpDisease
{
	override float GetFee()
	{
		// 2. Failsafe financeiro contra falhas na cadeia do Trader
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().ChemicalPoisoningL2;
	}
	
	override void CureDisease()
	{
		// 3. Proteção vital do objeto do Jogador (Prevenção de Crash se ele morrer no menu)
		if (!alp_Player) return;

		// 4. Segurança: A remoção de agentes letais DEVE ocorrer apenas no Servidor
		if (GetGame().IsServer())
		{
			// Limpeza segura do Agente Químico (Gás)
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.CHEMICAL_POISON, 0 );
			}
			
			// Desativação segura do Sintoma Nível 2 (Vômito de sangue/dano contínuo)
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION2))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_CONTAMINATION2);
				}		
			}
		}
	}
}