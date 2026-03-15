/**
 * @class   alpTirednessMdfr
 * @brief   Gerencia o consumo de fadiga baseado em metabolismo e condições externas
 * Auditado em: 2024 - Foco em Segurança de Configuração e Integridade de Dados
 */
class alpTirednessMdfr: ModifierBase
{
	ref HumanMovementState m_MovementState = new HumanMovementState();
	
	override void Init()
	{
		m_TrackActivatedTime    = false;
		m_ID                    = rModifiers.MDF_TIREDNESS;
		m_TickIntervalInactive  = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive    = DEFAULT_TICK_TIME_ACTIVE;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		// Verifica se o sistema de perks está disponível antes de ler a opção
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPerksOptions())
		{
			return GetND().GetRP().GetPerksOptions().EnableFatigue;
		}
		return false;
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false; // Sempre ativo enquanto a opção EnableFatigue for true
	}

	/**
	 * @brief Calcula multiplicadores de cansaço baseados no estado do jogador
	 */
	protected float GetFatigueMdfALP(PlayerBase player, float fatigue)
	{
		if (!player || !GetND() || !GetND().GetRP() || !GetND().GetRP().GetFatigue())
			return fatigue;

		auto config = GetND().GetRP().GetFatigue();

		// Multiplicador por doença
		if (player.HasDisease()) 
		{
			fatigue *= config.FatigueSickMultiplier;
		}

		// Multiplicador por temperatura (Frio)
		float heat_comfort = player.GetStatHeatComfort().Get();
		if (heat_comfort <= PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)		
		{
			fatigue *= config.FatigueHeatMultiplier;
		}

		return fatigue;
	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;

		player.GetMovementState(m_MovementState);
			
		// 1. Obtém velocidade metabólica baseada no movimento (Ex: parado, andando, correndo)
		float fatigueBase = alpUF.GetTirednessMetabolicSpeed(m_MovementState.m_iMovement);
		
		// 2. Aplica os modificadores de estado (Doença, Temperatura)
		float finalFatigue = GetFatigueMdfALP(player, fatigueBase);
		
		// 3. Aplica o consumo no Stat de Fadiga (subtrai, pois cansaço aumenta a exaustão)
		// Nota: Certifique-se que o StatFatigue está registrado no PlayerBase
		if (player.GetStatFatigue())
		{
			// O valor é negativo para reduzir a reserva de energia/fadiga disponível
			player.GetStatFatigue().Add(-(finalFatigue * deltaT));
		}
	}
};