/**
 * @class   alpWoundInfection1 e alpWoundInfection2
 * @brief   Gerencia a cobrança, cura e prevenção da Infecção de Feridas no Next Days
 * Auditado em: 2026 - Foco em Segurança de Dicionários (Maps), Failsafes e Rede
 */

class alpWoundInfection1 extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe financeiro
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().WoundInfectionL1;
	}
	
	override void CureDisease()
	{
		// 2. Proteção vital do objeto do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Cura de agentes e manipuladores de modificadores restrita ao Servidor
		if (GetGame().IsServer())
		{
			// Limpa o Agente Infeccioso
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.WOUND_AGENT , 0 );
			}
			
			if (alp_Player.GetModifiersManager())
			{
				// Remove os sintomas do Nível 1 (Dor)
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_WOUND_INFECTION1))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_WOUND_INFECTION1);
				}			
				
				// Aplica o "Buff" de desinfecção (Protege contra reinfecção imediata)
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_DISINFECTION))
				{
					alp_Player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_DISINFECTION );
				}
				alp_Player.GetModifiersManager().ActivateModifier( eModifiers.MDF_DISINFECTION );		
			}
		}
	}
	
	override bool IsEnable()
	{
		// 4. Failsafe Massivo da UI: Garante que os dados RPG existam
		if (!alp_Player || !alp_Player.GetRP() || !alp_Player.GetRP().alp_MedicList) 
		{
			return false;
		}
		
		// 5. Busca Segura no Dicionário
		alpDisease infectionLevel2 = alp_Player.GetRP().alp_MedicList.Get( alpDiseases.WOUNDINFECTION_2 );
		
		// Se o Estágio 2 existe E o jogador está com ele, não mostra o tratamento do Estágio 1
		if ( infectionLevel2 && infectionLevel2.IsInfected() )
		{
			return false;
		}
		
		return true;
	}	
}

class alpWoundInfection2 extends alpDisease
{
	override float GetFee()
	{
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().WoundInfectionL2;
	}

	override void CureDisease()
	{
		if (!alp_Player) return;

		if (GetGame().IsServer())
		{
			if (alp_Player.m_AgentPool)
			{
				alp_Player.m_AgentPool.SetAgentCount( eAgents.WOUND_AGENT , 0 );
			}
			
			if (alp_Player.GetModifiersManager())
			{
				// Remove os sintomas do Nível 2 (Dano contínuo / Febre alta)
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_WOUND_INFECTION2))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_WOUND_INFECTION2);
				}	
				
				// Aplica o "Buff" de desinfecção
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_DISINFECTION))
				{
					alp_Player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_DISINFECTION );
				}
				alp_Player.GetModifiersManager().ActivateModifier( eModifiers.MDF_DISINFECTION );	
			}
		}
	}
}