/**
 * @class   alpRadiationDisease
 * @brief   Gerencia a cobrança escalonada e cura da Radiação no Next Days
 * Auditado em: 2026 - Foco em Segurança de SyncData, Otimização Matemática e Failsafes
 */
class alpRadiationDisease extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe financeiro contra falhas de inicialização
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().RadiationSick;
	}
	
	override void CureDisease()
	{	
		// 2. Proteção vital de ponteiros
		if (!alp_Player || !alp_Player.GetRP()) return;
		
		// 3. Segurança: Tratamentos profundos de radiação e status Ocorrem apenas no Servidor
		if (GetGame().IsServer())
		{
			// 4. Otimização: Chama a função GetRecievedRadiation() apenas uma vez
			int radiation = alp_Player.GetRP().GetRecievedRadiation();
		
			// Estágio L5 geralmente é fatal/incurável, a cura só funciona abaixo dele
			if ( radiation < ALP_RADPOISON.L5 )
			{
				if (alp_Player.m_AgentPool)
				{
					alp_Player.m_AgentPool.SetAgentCount( alpeAgents.RADIATION, 0 );
				}
		
				// Limpeza em cascata dos modificadores ativos
				if (alp_Player.GetModifiersManager())
				{
					if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
						alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
			
					if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
						alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
									
					if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
						alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
									
					if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK4))
						alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK4);
				}			
			}
		}
	}
	
	override bool CanBeCured()
	{
		// 5. Blindagem Crítica do SyncData (Evita Crashes na UI do cliente)
		if (!alp_Player || !alp_Player.GetSyncData()) return false;
		
		auto syncElement = alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.RADIATIONSICKSTAGE);
		if (!syncElement) return false; // Se o elemento de rede não existir, bloqueia a cura
		
		float value = 0;	
		syncElement.GetValue( value );
		
		// Retorna verdadeiro diretamente da expressão booleana
		return (value <= ALP_RADIATION_SICKSTAGE.L4);
	}		
	
	override float GetPrice()
	{
		// 6. Proteção espelhada para o cálculo de preço
		if (!alp_Player || !alp_Player.GetSyncData()) return 0.0;
		
		float price = super.GetPrice();	
		float value = 0;
		float ratio = 100.0; // Assume 100% como padrão (failsafe)
		
		auto syncElement = alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.RADIATIONSICKSTAGE);
		
		if ( syncElement )
		{
			syncElement.GetValue( value );
			
			// 7. Otimização de Cascata (else if): Para de processar assim que encontra a condição certa
			if (value <= ALP_RADIATION_SICKSTAGE.L1)
			{
				ratio = 20.0; // Nível 1 custa 20%
			}	
			else if (value <= ALP_RADIATION_SICKSTAGE.L2)
			{
				ratio = 40.0; // Nível 2 custa 40%
			}					
			else if (value <= ALP_RADIATION_SICKSTAGE.L3)
			{
				ratio = 80.0; // Nível 3 custa 80%
			}	
			else if (value <= ALP_RADIATION_SICKSTAGE.L4)
			{
				ratio = 100.0; // Nível 4 custa 100%
			}
		}		
			
		ratio /= 100;				
		return price * ratio;
	}	
}