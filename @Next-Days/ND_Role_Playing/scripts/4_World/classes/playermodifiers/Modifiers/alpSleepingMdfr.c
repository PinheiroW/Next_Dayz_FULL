/**
 * @class   alpSleepingMdfr
 * @brief   Gerencia a mecânica de sono, recuperação de fadiga e riscos de exposição
 * Auditado em: 2024 - Foco em Estabilidade de Configuração e Performance
 */
class alpSleepingMdfr: ModifierBase
{
	override void Init()
	{
		m_TrackActivatedTime	= false;
		m_ID 					= rModifiers.MDF_SLEEPING;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		return player.IsPlayerSleeping();
	}

	override protected void OnActivate(PlayerBase player)
	{
		// Espaço reservado para efeitos visuais ou sons ao dormir
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		// Espaço reservado para efeitos ao acordar
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if (!player) return true;
		return !player.IsPlayerSleeping();
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;

		// 1. Obtenção segura de configurações (Failsafe)
		float restAmount = 1.0;
		float penaltyShelter = 0.5;
		float penaltyHeat = 0.5;

		if (GetND() && GetND().GetRP() && GetND().GetRP().GetFatigue())
		{
			restAmount = GetND().GetRP().GetFatigue().Resting;
			penaltyShelter = GetND().GetRP().GetFatigue().RestingPenaltyShelter;
			penaltyHeat = GetND().GetRP().GetFatigue().RestingPenaltyHeat;
		}

		bool canRegenerate = true;
		
		// 2. Verificação de Abrigo
		if (!player.IsPlayerInShelter())
		{
			restAmount *= penaltyShelter;
			canRegenerate = false; // Não regenera vida dormindo ao relento
		}
		
		// 3. Verificação de Conforto Térmico e Gerenciador de Modificadores
		float heat_comfort = player.GetStatHeatComfort().Get();
		ModifiersManager modManager = player.GetModifiersManager();
		
		if (heat_comfort <= PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
		{
			// Se estiver com frio e NÃO estiver imune, corre risco de gripe
			if (modManager && !modManager.IsModifierActive(rModifiers.MDF_IMMUNITY_INFLUENZA))
			{
				restAmount *= penaltyHeat;
				player.InsertAgent(eAgents.INFLUENZA, 1 * deltaT);
			}
		}

		// 4. Aplicação da recuperação de Fadiga (Rest)
		if (player.GetStatFatigue())
		{
			player.GetStatFatigue().Add(restAmount * deltaT);
		}

		// 5. Regeneração de Saúde (Somente em condições ideais: Abrigo + Sem Frio)
		if (canRegenerate && heat_comfort > PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
		{
			if (player.GetHealth("GlobalHealth", "Health") < 100)
			{
				player.AddHealth("", "Health", 0.05 * deltaT);
			}
		}
	}
};