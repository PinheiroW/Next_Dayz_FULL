/**
 * alpActionCloseBarrel.c
 * * USER INTERACTION (CLOSE RADIOACTIVE BARREL) - Módulo ND_MISSIONS
 * Gerencia o fechamento físico de barris radioativos, validando estados de trava.
 */

class alpActionCloseBarrel : ActionInteractBase
{
	void alpActionCloseBarrel()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override string GetText()
	{
		return "#close";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target) return false;

		alp_Radioactive_Barrel barrel;
		// Tenta converter o objeto alvo para a classe de barril do mod
		if (Class.CastTo(barrel, target.GetObject()))
		{
			// Condição: O barril deve estar ABERTO e não pode estar trancado
			if (barrel.IsOpen() && !barrel.IsLocked())
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
		// Executa a transição lógica para FECHADO no servidor para fins de sincronização
		if (Class.CastTo(barrel, action_data.m_Target.GetObject()))
		{
			if (barrel.IsOpen())
			{
				barrel.Close();
			}
		}
	}
};