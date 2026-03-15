/**
 * alpActionOpenBarrel.c
 * * USER INTERACTION (OPEN RADIOACTIVE BARREL) - Módulo ND_MISSIONS
 * Gerencia a abertura física de barris radioativos baseada em estados de trava e visibilidade.
 */

class alpActionOpenBarrel: ActionInteractBase
{
	void alpActionOpenBarrel()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target) return false;

		alp_Radioactive_Barrel barrel;
		// Validação de tipo específica para barris radioativos do mod Next-Days
		if (Class.CastTo(barrel, target.GetObject()))
		{
			// Só permite a abertura se o objeto NÃO estiver trancado e se estiver FECHADO
			if (!barrel.IsLocked() && !barrel.IsOpen())
			{
				return true;
			}
		}

		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return;

		alp_Radioactive_Barrel barrel;
		// Processa a transição de estado no servidor para replicação na rede
		if (Class.CastTo(barrel, action_data.m_Target.GetObject()))
		{
			if (!barrel.IsOpen())
			{
				barrel.Open();
			}
		}
	}
};