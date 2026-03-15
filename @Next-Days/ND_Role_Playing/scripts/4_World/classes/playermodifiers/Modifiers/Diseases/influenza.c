/**
 * @class   InfluenzaMdfr
 * @brief   Gerencia a gripe vanilla com integração ao sistema RPG e Imunidade
 * Auditado em: 2024 - Foco em Integridade de Contadores e Segurança de Ponteiros
 */
modded class InfluenzaMdfr: ModifierBase
{
	const int AGENT_THRESHOLD_ACTIVATE = 300;
	const int AGENT_THRESHOLD_DEACTIVATE = 200;
	
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID 					= eModifiers.MDF_INFLUENZA;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override string GetDebugText()
	{
		return ("Activate threshold: " + AGENT_THRESHOLD_ACTIVATE + "| " + "Deativate threshold: " + AGENT_THRESHOLD_DEACTIVATE);
	}
	
	override protected bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		return (player.GetSingleAgentCount(eAgents.INFLUENZA) >= AGENT_THRESHOLD_ACTIVATE);
	}

	override protected void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		if (player)
		{
			// CORREÇÃO: Incrementa o contador para manter paridade com OnDeactivate
			player.IncreaseDiseaseCount();

			auto rp = player.GetRP();
			if (rp)
			{
				rp.SetDisease(alpDiseases.INFLUENZA);
			}
		}
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		if (!player) return;

		// Otimização: Cache do ModifiersManager
		ModifiersManager manager = player.GetModifiersManager();
		if (manager)
		{
			// Se já estiver imune, reseta o tempo da imunidade desativando e reativando
			if (manager.IsModifierActive(rModifiers.MDF_IMMUNITY_INFLUENZA))
			{
				manager.DeactivateModifier(rModifiers.MDF_IMMUNITY_INFLUENZA);
			}
			manager.ActivateModifier(rModifiers.MDF_IMMUNITY_INFLUENZA);
		}
				
		player.DecreaseDiseaseCount();
		
		auto rp = player.GetRP();
		if (rp)
		{
			rp.UnsetDisease(alpDiseases.INFLUENZA);
		}
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if (!player) return true;
		return (player.GetSingleAgentCount(eAgents.INFLUENZA) <= AGENT_THRESHOLD_DEACTIVATE);
	}
}