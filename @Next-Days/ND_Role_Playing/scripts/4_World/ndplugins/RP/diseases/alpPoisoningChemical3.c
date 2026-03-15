/**
 * @class   alpPoisoningChemical3
 * @brief   Gerencia a cobrança e a cura da Contaminação Química Nível 3 (Crítico) no Next Days
 * Auditado em: 2026 - Foco em Correção de Sintaxe, Failsafes e Segurança de Rede
 */
// 1. Nome da classe corrigido (Removido o typo 'Chemica1_3')
class alpPoisoningChemical3 extends alpDisease
{
	override float GetFee()
	{
		// 2. Failsafe financeiro contra falhas de carregamento na cadeia do Trader
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().ChemicalPoisoningL3;
	}
	
	override void CureDisease()
	{
		// 3. Proteção vital do objeto do Jogador (Extremamente necessário no Nível 3)
		if (!alp_Player) return;

		// 4. Segurança: A remoção de agentes letais DEVE ocorrer apenas no Servidor
		if (GetGame().IsServer())
		{
			// Limpeza segura do Agente Químico
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.CHEMICAL_POISON, 0 );
			}
			
			// Desativação segura do Sintoma Nível 3 (Dano extremo/Inconsciência)
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION3))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_CONTAMINATION3);
				}		
			}
		}
	}
}