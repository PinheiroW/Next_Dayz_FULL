/**
 * alpActionServerConsoleUnlock.c
 * * AÇÃO DE INTERAÇÃO (LOGIN/DESBLOQUEIO DE CONSOLE) - Módulo ND_MISSIONS
 * Permite o acesso ao terminal utilizando o cartão de acesso correto.
 */

class alpActionServerConsoleUnlock: ActionInteractBase
{
	void alpActionServerConsoleUnlock()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override void CreateConditionComponents()  
	{
		// O cartão não pode estar arruinado para ser lido pelo console
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return "#alp_action_console_login";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;
		
		// O jogador deve estar mirando no leitor de cartões (Componente 1)
		if ( target.GetComponentIndex() != 1 ) return false;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Valida se o alvo é um console e se o item em mãos é um cartão de acesso
		if ( Class.CastTo(console, target.GetObject()) && Class.CastTo(card, item) )
		{
			// Condições para desbloquear:
			// 1. O console deve estar atualmente TRANCADO.
			// 2. Não pode estar destruído.
			// 3. O ID de segurança do cartão deve ser igual ao do console.
			if ( console.IsLockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() )
			{
				if ( card.GetKeyID() == console.GetAccesCardID() )
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Target ) return;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Revalidação de segurança no servidor
		if ( Class.CastTo(console, action_data.m_Target.GetObject()) && Class.CastTo(card, action_data.m_MainItem) )
		{
			if ( card.GetKeyID() == console.GetAccesCardID() )
			{
				// Desbloqueia o terminal (False = Unlock)
				console.LockALP( false );
			}
		}
	}
};