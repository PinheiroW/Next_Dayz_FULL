/**
 * alpRadiationSick4Mdfr.c
 * * MODIFICADOR DE DOENÇA DE RADIAÇÃO (ESTÁGIO 4) - Módulo ND_MISSIONS
 * Estágio Crítico: Sangramento severo, infecção letal, vômito e risco de inconsciência.
 */

class alpRadiationSick4Mdfr: ModifierBase
{
	static const int WATER_DRAIN_FROM_VOMIT  = 450;
	static const int ENERGY_DRAIN_FROM_VOMIT = 310;	
	
	const ref array<string> BLEEDINGZONES = {
		"Head", "Neck", "Pelvis", "Spine", "LeftShoulder", "LeftArm", "LeftArmRoll", 
		"LeftForeArm", "RightShoulder", "RightArm", "RightArmRoll", "RightForeArm", 
		"LeftForeArmRoll", "RightForeArmRoll", "LeftLeg", "LeftLegRoll", "LeftUpLeg", 
		"LeftUpLegRoll", "RightLeg", "RightLegRoll", "RightUpLeg", "RightUpLegRoll", 
		"LeftFoot", "LeftToeBase", "RightFoot", "RightToeBase"
	};

	override void Init()
	{
		m_ID 					= rModifiers.MDF_ALPRADIATIONSICK4;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L4 && player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L5 );
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;
		
		player.IncreaseDiseaseCount();
		
		// OTIMIZAÇÃO: Segurança no acesso ao RP
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.L4);
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
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L5 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;

		// 1. Desidratação contínua e acelerada
		float metabolic_speed = PlayerConstants.METABOLIC_SPEED_WATER_SPRINT;
		player.GetStatWater().Add( (-metabolic_speed * deltaT) );
					
		// Probabilidades de sintomas para o Estágio 4
		float vomit 	= 0.985;
		float bleed 	= 0.995;
		float infection = 0.750;		
		float health 	= 0.999;
				
		// 2. Infecção Aguda (25% de chance)
		if (Math.RandomFloat01() >= infection) 
		{
			player.m_AgentPool.AddAgent(eAgents.WOUND_AGENT, m_TickIntervalActive);
		}	
		
		// 3. Vômito (1.5% de chance)
		if (Math.RandomFloat01() >= vomit) 
		{
			if (player.GetSymptomManager()) 
			{
				SymptomBase symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
					
				if (symptom)
				{
					symptom.SetDuration(5);
				
					// CORREÇÃO: Uso do parâmetro local 'player'
					if (player.GetStatWater().Get() > WATER_DRAIN_FROM_VOMIT)
						player.GetStatWater().Add(-1 * WATER_DRAIN_FROM_VOMIT);
						
					if (player.GetStatEnergy().Get() > ENERGY_DRAIN_FROM_VOMIT)
						player.GetStatEnergy().Add(-1 * ENERGY_DRAIN_FROM_VOMIT);
				}
			}
		}	
		
		// 4. Sangramento Espontâneo (0.5% de chance)
		if (Math.RandomFloat01() >= bleed) 
		{
			if (player.GetBleedingManagerServer() && BLEEDINGZONES && BLEEDINGZONES.Count() > 0)
			{
				player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(BLEEDINGZONES.GetRandomElement());	
			}
		}	
		
		// 5. Inconsciência por Choque (0.1% de chance)
		// CORREÇÃO: Substituído RandomIntInclusive por RandomFloat01 para corrigir o bug de desmaio infinito
		if (Math.RandomFloat01() >= health) 
		{
			player.DecreaseHealth("", "Shock", PlayerConstants.UNCONSCIOUS_THRESHOLD);
		}						
	}
}