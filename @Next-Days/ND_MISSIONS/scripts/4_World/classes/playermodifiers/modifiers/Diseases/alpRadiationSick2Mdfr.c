/**
 * alpRadiationSick2Mdfr.c
 * * MODIFICADOR DE DOENÇA DE RADIAÇÃO (ESTÁGIO 2) - Módulo ND_MISSIONS
 * Controla os sintomas moderados, chance de infecção, vômito e desidratação.
 */

class alpRadiationSick2Mdfr: ModifierBase
{
	static const int WATER_DRAIN_FROM_VOMIT  = 450;
	static const int ENERGY_DRAIN_FROM_VOMIT = 310;	
	
	override void Init()
	{
		m_ID 					= rModifiers.MDF_ALPRADIATIONSICK2;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L2 && player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L3 );
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;
		
		player.IncreaseDiseaseCount();
		
		// OTIMIZAÇÃO: Null check para garantir a estabilidade do servidor
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.L2);
		}
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override void OnDeactivate(PlayerBase player)
	{
		if (!player) return;
		
		player.DecreaseDiseaseCount();
		
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.NONE);
		}
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L3 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;
		
		// Dreno de hidratação contínuo e acelerado (nível de sprint)
		float metabolic_speed = PlayerConstants.METABOLIC_SPEED_WATER_SPRINT;
		player.GetStatWater().Add( (-metabolic_speed * deltaT) );
					
		// Chances de sintomas baseadas em tick
		float vomit 	= 0.995;
		float infection = 0.950;

		// Risco de gerar agentes de ferimento (Infecção)
		if (Math.RandomFloat01() >= infection) 
		{
			player.m_AgentPool.AddAgent(eAgents.WOUND_AGENT, m_TickIntervalActive);
		}	
		
		// Risco de gerar sintoma de vômito
		if (Math.RandomFloat01() >= vomit) 
		{
			SymptomBase symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
				
			if (symptom)
			{
				symptom.SetDuration(5);
			
				// CORREÇÃO: Uso de 'player' ao invés de 'm_Player' para precisão de referência
				if (player.GetStatWater().Get() > WATER_DRAIN_FROM_VOMIT)
					player.GetStatWater().Add(-1 * WATER_DRAIN_FROM_VOMIT);
					
				if (player.GetStatEnergy().Get() > ENERGY_DRAIN_FROM_VOMIT)
					player.GetStatEnergy().Add(-1 * ENERGY_DRAIN_FROM_VOMIT);
			}
		}				
	}
}