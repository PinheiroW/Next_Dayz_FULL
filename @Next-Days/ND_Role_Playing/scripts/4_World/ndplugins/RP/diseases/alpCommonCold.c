/**
 * @class   alpCommonCold
 * @brief   Gerencia a cobrança, lógica de sobreposição e cura do Resfriado no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Proteção de Dicionários (Maps)
 */
class alpCommonCold extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia do Trader
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().Commoncold;
	}
		
	override void CureDisease()
	{
		// 2. Proteção do ponteiro do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Cura de agentes e remoção de modificadores deve ser feita no Servidor
		if (GetGame().IsServer())
		{
			// 4. Limpeza segura do Agente (Influenza é a base do resfriado no DayZ)
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.INFLUENZA , 0 );
			}
				
			// 5. Desativação segura dos sintomas (Espirros)
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_COMMON_COLD))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_COMMON_COLD);
				}		
			}
		}
	}
	
	override bool IsEnable()
	{
		// 6. Failsafe Massivo: Garante que os dados RPG existem antes de consultar a lista
		if (!alp_Player || !alp_Player.GetRP() || !alp_Player.GetRP().alp_MedicList) 
		{
			return false; // Se não carregou, desabilita a opção por segurança
		}
		
		// 7. Busca segura no Dicionário (Map)
		alpDisease fluDisease = alp_Player.GetRP().alp_MedicList.Get( alpDiseases.INFLUENZA );
		
		// Se a Gripe (Influenza) existe na lista E o jogador está infectado com ela, esconde o Resfriado
		if ( fluDisease && fluDisease.IsInfected() )
		{
			return false;
		}
		
		return true;
	}		
}