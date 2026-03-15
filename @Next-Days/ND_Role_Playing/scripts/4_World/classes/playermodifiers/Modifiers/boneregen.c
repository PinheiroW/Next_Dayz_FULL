/**
 * @class   BoneRegenMdfr
 * @brief   Gerencia a regeneração de ossos (membros) de forma otimizada
 * Auditado em: 2024 - Foco em Performance de API e Segurança de Ponteiros
 */
modded class BoneRegenMdfr: ModifierBase
{
	const int LIFETIME = 600;	
	private const float BONE_HEALTH_INCREMENT_PER_SEC = 0.1;
	
	// Lista de membros para otimização do loop
	private static const string BONE_SLOTS[] = {"RightArm", "RightHand", "LeftArm", "LeftHand", "RightLeg", "RightFoot", "LeftLeg", "LeftFoot"};
	
	override void Init()
	{
		m_TrackActivatedTime    = true;
		m_IsPersistent          = true;
		m_ID                    = eModifiers.MDF_BONE_REGEN;
		m_TickIntervalInactive  = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive    = DEFAULT_TICK_TIME_ACTIVE;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return false; // Ativado externamente (Morfina/Tala)
	}

	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override protected void OnActivate(PlayerBase player)
	{
		if (player && player.GetNotifiersManager())
		{
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
		}
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		if (player && player.GetNotifiersManager())
		{
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
		}
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		return (GetAttachedTime() >= LIFETIME);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{	
		if (!player) return;

		float increment = BONE_HEALTH_INCREMENT_PER_SEC * deltaT;
		
		// Otimização: Loop através dos slots com verificação de saúde atual
		foreach (string slot : BONE_SLOTS)
		{
			// Só aplica AddHealth se o osso estiver danificado (< 100)
			// Isso economiza chamadas pesadas ao motor de dano
			if (player.GetHealth(slot, "Health") < 100)
			{
				player.AddHealth(slot, "Health", increment);
			}
		}
	}
};