/**
 * alpActionCloseBarrel.c
 * * AÇÃO DE INTERAÇÃO (FECHAR BARRIL RADIOATIVO) - Módulo ND_MISSIONS
 * Permite fechar o barril se ele não estiver trancado e estiver aberto.
 */

class alpActionCloseBarrel : ActionInteractBase
{
	void alpActionCloseBarrel()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override string GetText()
	{
		return "#close";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target ) return false;

		alp_Radioactive_Barrel ntarget;
		// LÓGICA MANTIDA: Tenta converter o objeto alvo para um barril radioativo
		if ( Class.CastTo(ntarget, target.GetObject()) )
		{
			// Só permite fechar se o barril estiver aberto E não estiver trancado (pelo sistema de chaves/lock)
			if ( ntarget.IsOpen() && !ntarget.IsLocked() )
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
		// Executa o comando de fechar no servidor
		if ( Class.CastTo(ntarget, action_data.m_Target.GetObject()) )
		{
			if ( ntarget.IsOpen() )
			{
				ntarget.Close();
			}
		}
	}
	
	// OnEndServer e OnEndClient foram omitidos por serem redundantes nesta ação simples
};