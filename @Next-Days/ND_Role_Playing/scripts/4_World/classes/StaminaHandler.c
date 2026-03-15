/**
 * @class   StaminaHandler
 * @brief   Gerencia a integração do Perk de Stamina com o sistema de movimento vanilla
 * Auditado em: 2026 - Foco em Segurança de Divisão e Performance
 */

modded class StaminaConsumers
{
	void UpdateConsumerALP(PlayerBase player)
	{
		// 1. Failsafe robusto
		if (!player || !player.GetSyncData()) return;
		
		int level = player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
		float modifier = GetND().GetRP().GetPerkStaminaMdf( level );
		
		// Failsafe contra modificador nulo ou negativo
		if (modifier <= 0) modifier = 1.0;

		foreach(StaminaConsumer sc : m_StaminaConsumers)
		{
			// Nota: Certifique-se de que o sistema vanilla reseta esses valores 
			// antes da chamada, ou o valor será cumulativo (Over-stacking).
			sc.SetActivationThreshold( sc.GetActivationThreshold() * modifier );			
			sc.SetDrainThreshold( sc.GetDrainThreshold() * modifier );	
		}
	}	
}

modded class StaminaHandler
{
	// Adicionando um timer de debounce para evitar cálculos pesados todo frame
	protected float m_ALP_UpdateTimer = 0;

	override void Update(float deltaT, int pCurrentCommandID)
	{
		super.Update(deltaT, pCurrentCommandID);

		// 2. Otimização de Processamento (Update a cada 1 segundo em vez de todo frame)
		m_ALP_UpdateTimer += deltaT;
		if (m_ALP_UpdateTimer >= 1.0)
		{
			if ( m_Player && GetND().GetRP().GetPerksOptions().EnablePerkStamina )
			{
				UpdateStaminaProgressALP();
			}
			m_ALP_UpdateTimer = 0;
		}
	}

	protected void UpdateStaminaProgressALP()
	{
		int level = m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
		// Exemplo: Nível alto de Perk = XP de Stamina aumenta
		UpdateStaminaProggres( level * 0.1 ); 
	}

	override protected void StaminaProcessor_Ladder(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Ladder(pHumanMovementState);
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{		
			float modifier = GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			
			// 3. Proteção Crítica contra Divisão por Zero
			if (modifier <= 0) modifier = 1.0;

			if (m_StaminaDelta < 0)
			{
				m_StaminaDelta *= modifier;
			}
			else 
			{
				m_StaminaDelta /= modifier;
			}				
			
			// 4. Lógica de Escala (Case simplificado)
			switch ( pHumanMovementState.m_iMovement )
			{
				case 2: // Rápido
					UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().ClimbFast );
				break;
					
				case 1: // Lento
					if (!m_IsInCooldown)
					{
						UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().ClimbSlow );
					}
				break;
			}
		}					
	}	
};