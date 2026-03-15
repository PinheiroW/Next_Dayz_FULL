/**
 * @class   alpImmunityInfluenzaMdfr
 * @brief   Modificador de imunidade pós-gripe (Next Days)
 * Auditado em: 2024 - Foco em Segurança de Inicialização e Ponteiros
 */
class alpImmunityInfluenzaMdfr: ModifierBase
{
	float m_RegenTime;
	
	override void Init()
	{
		m_TrackActivatedTime    = true;
		m_ID                    = rModifiers.MDF_IMMUNITY_INFLUENZA;
		m_TickIntervalInactive  = DEFAULT_TICK_TIME_INACTIVE_LONG;
		m_TickIntervalActive    = DEFAULT_TICK_TIME_ACTIVE;
		m_IsPersistent          = true;
		
		// Valor padrão de segurança (ex: 600 segundos) caso a config falhe
		m_RegenTime = 600.0; 
		
		// Tenta carregar da config se disponível
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetDiseases())
		{
			m_RegenTime = GetND().GetRP().GetDiseases().ImmunityInfluenza;
		}
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		// Modificadores de imunidade geralmente são ativados via script (OnDeactivate da doença)
		// portanto, a condição de ativação automática permanece false.
		return false;
	}

	override void OnActivate(PlayerBase player)
	{
		if (player && player.GetNotifiersManager())
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
		if (player && player.GetNotifiersManager())
		{
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
		}
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();
		
		// Garante que o modificador expire após o tempo definido
		if (attached_time >= m_RegenTime)
		{
			return true;
		}
		
		return false;
	}
};