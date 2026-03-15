/**
 * alpRadiationSick5Mdfr.c
 * * MODIFICADOR DE DOENÇA DE RADIAÇÃO (ESTÁGIO 5 - TERMINAL) - Módulo ND_MISSIONS
 * Estágio Final: Altíssima letalidade, sangramento massivo, dano e risco de morte súbita (L6).
 */

class alpRadiationSick5Mdfr: ModifierBase
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
		m_ID 					= rModifiers.MDF_ALPRADIATIONSICK5;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L5 );
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;
		
		player.IncreaseDiseaseCount();
		
		// OTIMIZAÇÃO: Segurança no acesso ao RP
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.L5);
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
		
		// Condição de cura original (geralmente impossível sem tratamentos muito específicos do mod)
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L5 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;

		// 1. Morte Súbita (Nível 6 Atingido)
		if ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L6 )
		{
			player.SetHealth("", "", 0);
			return; // Quebra a execução para não gastar CPU calculando sintomas em um morto
		}

		// 2. Desidratação contínua
		float metabolic_speed = PlayerConstants.METABOLIC_SPEED_WATER_SPRINT;
		player.GetStatWater().Add( (-metabolic_speed * deltaT) );
					
		// Probabilidades extremas do Estágio 5
		float vomit 	= 0.970; // 3% de chance por tick
		float bleed 	= 0.800; // 20% de chance por tick
		float infection = 0.650; // 35% de chance por tick
		float health 	= 0.900; // 10% de chance por tick de sofrer dano na vida real/choque
		
		// 3. Infecção Grave
		if (Math.RandomFloat01() >= infection) 
		{
			player.m_AgentPool.AddAgent(eAgents.WOUND_AGENT, m_TickIntervalActive);
		}	
		
		// 4. Vômitos Constantes
		if (Math.RandomFloat01() >= vomit) 
		{
			if (player.GetSymptomManager())
			{
				SymptomBase symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
					
				if (symptom)
				{
					symptom.SetDuration(5);
				
					// CORREÇÃO: Uso da variável 'player'
					if (player.GetStatWater().Get() > WATER_DRAIN_FROM_VOMIT)
						player.GetStatWater().Add(-1 * WATER_DRAIN_FROM_VOMIT);
						
					if (player.GetStatEnergy().Get() > ENERGY_DRAIN_FROM_VOMIT)
						player.GetStatEnergy().Add(-1 * ENERGY_DRAIN_FROM_VOMIT);
				}
			}
		}	
		
		// 5. Sangramento Severo
		if (Math.RandomFloat01() >= bleed) 
		{
			if (player.GetBleedingManagerServer() && BLEEDINGZONES && BLEEDINGZONES.Count() > 0)
			{
				player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(BLEEDINGZONES.GetRandomElement());	
			}
		}	
		
		// 6. Dano Direto à Vida e Choque
		if (Math.RandomFloat01() >= health) 
		{
			// Preservada a lógica base do autor (Pode deduzir vida ou aplicar choque letal)
			player.DecreaseHealth("", "Shock", PlayerConstants.UNCONSCIOUS_THRESHOLD);
		}						
	}
}