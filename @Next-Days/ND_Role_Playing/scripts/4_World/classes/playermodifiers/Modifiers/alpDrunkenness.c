/**
 * @class   alpDrunkennessMdfr
 * @brief   Gerencia o estado de embriaguez e seus efeitos sistêmicos
 * Auditado em: 2024 - Foco em Correção de Escopo e Estabilidade de Sintomas
 */
class alpDrunkennessMdfr: ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE 	= 100;
	static const int AGENT_THRESHOLD_DEACTIVATE = 20;
	
	static const int WATER_DRAIN_FROM_VOMIT 	= 450;
	static const int ENERGY_DRAIN_FROM_VOMIT 	= 310;		
	
	override void Init()
	{
		m_TrackActivatedTime	= false;
		m_ID 					= rModifiers.MDF_DRUNKENNESS;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		return (player.GetSingleAgentCount(alpeAgents.DRUNKENNESS) > AGENT_THRESHOLD_ACTIVATE);
	}

	override protected void OnActivate(PlayerBase player)
	{
		if (!player) return;

		if (player.GetNotifiersManager()) 
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
		
		// Mascarar animação de ferimento (efeito analgésico do álcool)
		if (player.m_InjuryHandler)
		{
			player.m_InjuryHandler.m_ForceInjuryAnimMask = player.m_InjuryHandler.m_ForceInjuryAnimMask | eInjuryAnimMask.PAIN_KILLERS;
		}

		if (player.GetRP())
			player.GetRP().SetDisease(alpDiseases.DRUNKENNESS);
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		if (!player) return;

		if (player.GetNotifiersManager()) 
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);

		if (player.m_InjuryHandler)
		{
			player.m_InjuryHandler.m_ForceInjuryAnimMask = player.m_InjuryHandler.m_ForceInjuryAnimMask & ~eInjuryAnimMask.PAIN_KILLERS;
		}

		if (player.GetRP())
			player.GetRP().UnsetDisease(alpDiseases.DRUNKENNESS);
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;
		
		// 1. Perda de água por processamento metabólico do álcool
		float water_loss = deltaT * 0.2;
		player.GetStatWater().Add(-water_loss);
		
		float drunkenness = player.GetSingleAgentCount(alpeAgents.DRUNKENNESS);

		// Jogadores inconscientes ou dormindo não sofrem sintomas ativos, mas metabolizam o álcool
		if (player.IsPlayerSleeping() || player.IsUnconscious()) return;
		
		// 2. Efeito de aquecimento (falsa sensação de calor)
		// CORREÇÃO: Variável inicializada corretamente
		float currentHC = player.GetStatHeatComfort().Get();
		float minHC = player.GetStatHeatComfort().GetMin();
		float maxHC = player.GetStatHeatComfort().GetMax();
		
		float newHC = Math.Clamp(currentHC + 0.2, minHC, maxHC);
		player.GetStatHeatComfort().Set(newHC);

		// 3. Gerenciamento de Sintomas por nível de embriaguez
		SymptomManager symptomManager = player.GetSymptomManager();
		if (!symptomManager) return;

		// Nível 1: Risadas (Laughter)
		if (drunkenness >= 250)
		{
			if (Math.RandomFloat01() < (1.0 / 15.0))
			{
				symptomManager.QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
			}
		}

		// Nível 2: Desequilíbrio/Tontura (Movement Blur/Sway - implementado via sintoma se disponível)
		if (drunkenness >= 600)
		{
			// Aqui poderia ser disparado um sintoma de visão turva
		}

		// Nível 3: Vômito Crítico
		if (drunkenness >= 900)
		{
			if (Math.RandomFloat01() < (1.0 / 20.0))
			{
				SymptomBase symptom = symptomManager.QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
				if (symptom)
				{
					symptom.SetDuration(Math.RandomIntInclusive(4, 8));
					// Penalidade severa de hidratação/energia ao vomitar
					player.GetStatWater().Add(-WATER_DRAIN_FROM_VOMIT);
					player.GetStatEnergy().Add(-ENERGY_DRAIN_FROM_VOMIT);
				}
			}
		}
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if (!player) return true;
		return (player.GetSingleAgentCount(alpeAgents.DRUNKENNESS) <= AGENT_THRESHOLD_DEACTIVATE);
	}
};