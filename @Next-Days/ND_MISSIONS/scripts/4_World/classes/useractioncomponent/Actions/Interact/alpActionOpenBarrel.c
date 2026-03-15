/**
 * alpActionOpenBarrel.c
 * * AÇÃO DE INTERAÇÃO (ABRIR BARRIL RADIOATIVO) - Módulo ND_MISSIONS
 * Permite abrir o barril se ele não estiver trancado e estiver fechado.
 */

class alpActionOpenBarrel: ActionInteractBase
{
	void alpActionOpenBarrel()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target ) return false;

		alp_Radioactive_Barrel ntarget;
		// OTIMIZAÇÃO: Cast direto para a classe específica do mod
		if ( Class.CastTo(ntarget, target.GetObject()) )
		{
			// Só permite abrir se NÃO estiver trancado e estiver atualmente FECHADO
			if ( !ntarget.IsLocked() && !ntarget.IsOpen() )
			{
				return true;
			}
		}

		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Target ) return;

		alp_Radioactive_Barrel ntarget;
		// Executa a abertura no servidor com validação de segurança
		if ( Class.CastTo(ntarget, action_data.m_Target.GetObject()) )
		{
			if ( !ntarget.IsOpen() )
			{
				ntarget.Open();
			}
		}
	}
};