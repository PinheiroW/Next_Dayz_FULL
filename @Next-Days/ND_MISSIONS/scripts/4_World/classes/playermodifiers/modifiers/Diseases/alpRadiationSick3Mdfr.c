/**
 * alpRadiationSick3Mdfr.c
 * * MODIFICADOR DE DOENÇA DE RADIAÇÃO (ESTÁGIO 3) - Módulo ND_MISSIONS
 * Controla sintomas graves: alto risco de infecção, vômitos frequentes e sangramentos espontâneos.
 */

class alpRadiationSick3Mdfr: ModifierBase
{
	static const int WATER_DRAIN_FROM_VOMIT  = 450;
	static const int ENERGY_DRAIN_FROM_VOMIT = 310;	
	
	// Array constante contendo todas as zonas corporais possíveis para geração de sangramento
	const ref array<string> BLEEDINGZONES = {
		"Head", "Neck", "Pelvis", "Spine", "LeftShoulder", "LeftArm", "LeftArmRoll", 
		"LeftForeArm", "RightShoulder", "RightArm", "RightArmRoll", "RightForeArm", 
		"LeftForeArmRoll", "RightForeArmRoll", "LeftLeg", "LeftLegRoll", "LeftUpLeg", 
		"LeftUpLegRoll", "RightLeg", "RightLegRoll", "RightUpLeg", "RightUpLegRoll", 
		"LeftFoot", "LeftToeBase", "RightFoot", "RightToeBase"
	};

	override void Init()
	{
		m_ID 					= rModifiers.MDF_ALPRADIATIONSICK3;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L3 && player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L4 );
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;
		
		player.IncreaseDiseaseCount();
		
		// OTIMIZAÇÃO: Segurança no acesso ao RP
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.L3);
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
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L4 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;

		// 1. Desidratação contínua e acelerada
		float metabolic_speed = PlayerConstants.METABOLIC_SPEED_WATER_SPRINT;
		player.GetStatWater().Add( (-metabolic_speed * deltaT) );
					
		// Probabilidades de sintomas para o Estágio 3
		float vomit 	= 0.990;
		float bleed 	= 0.998;
		float infection = 0.850;		
		
		// 2. Risco de Infecção Aguda (15% de chance por tick ativo)
		if (Math.RandomFloat01() >= infection) 
		{
			player.m_AgentPool.AddAgent(eAgents.WOUND_AGENT, m_TickIntervalActive);
		}	
		
		// 3. Vômito Severo (1% de chance por tick ativo)
		if (Math.RandomFloat01() >= vomit) 
		{
			if (player.GetSymptomManager()) // Null check preventivo
			{
				SymptomBase symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
					
				if (symptom)
				{
					symptom.SetDuration(5);
				
					// CORREÇÃO: Substituição de m_Player por player para evitar desync de escopo
					if (player.GetStatWater().Get() > WATER_DRAIN_FROM_VOMIT)
						player.GetStatWater().Add(-1 * WATER_DRAIN_FROM_VOMIT);
						
					if (player.GetStatEnergy().Get() > ENERGY_DRAIN_FROM_VOMIT)
						player.GetStatEnergy().Add(-1 * ENERGY_DRAIN_FROM_VOMIT);
				}
			}
		}

		// 4. Sangramento Espontâneo (0.2% de chance por tick ativo)
		if (Math.RandomFloat01() >= bleed)
		{
			// OTIMIZAÇÃO: Null check essencial para interagir com o gerenciador de sangue
			if (player.GetBleedingManagerServer() && BLEEDINGZONES && BLEEDINGZONES.Count() > 0)
			{
				player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(BLEEDINGZONES.GetRandomElement());
			}
		}
	}
}