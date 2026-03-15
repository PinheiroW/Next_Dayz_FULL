/**
 * @class   alpAnabolicMdfr
 * @brief   Modificador de efeito anabolizante (Next Days)
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Performance
 */
class alpAnabolicMdfr: ModifierBase
{
	const int ANABOLIC_LIFETIME = 300; // 5 Minutos
	float m_RegenTime;
	
	override void Init()
	{
		m_TrackActivatedTime    = true;
		m_ID                    = rModifiers.MDF_ANABOLIC;
		m_TickIntervalInactive  = 3;
		m_TickIntervalActive    = 1; // Tick rápido para processar regeneração
		m_IsPersistent          = true;
		m_RegenTime             = ANABOLIC_LIFETIME;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return false; // Ativado via script (item consumível)
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;

		// Integração com o sistema RPG (Flag de estado)
		if (player.GetRP())
		{
			// Caso precise de uma flag específica no futuro, descomente e ajuste:
			// player.GetRP().SetAnabolicActive(true);
		}

		if (player.GetNotifiersManager())
		{
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
		}
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override void OnDeactivate(PlayerBase player)
	{
		if (!player) return;

		if (player.GetNotifiersManager())
		{
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
		}
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		return (GetAttachedTime() >= m_RegenTime);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!player) return;

		// Aplica regeneração leve enquanto o anabolizante estiver ativo
		// Otimizado para não processar se a saúde já estiver no máximo
		float health = player.GetHealth("GlobalHealth", "Health");
		if (health < 100)
		{
			player.AddHealth("", "Health", 0.05); 
		}

		float blood = player.GetHealth("GlobalHealth", "Blood");
		if (blood < 5000)
		{
			player.AddHealth("", "Blood", 2.0);
		}
	}
};