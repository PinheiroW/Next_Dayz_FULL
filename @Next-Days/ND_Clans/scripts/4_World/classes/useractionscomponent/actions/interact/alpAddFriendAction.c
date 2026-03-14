class alpAddFriendAction: ActionInteractBase
{
	void alpAddFriendAction()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#ip_addfriend";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// CORREÇÃO 1: Failsafes vitais contra Null Pointer Exception (NPE Crash)
		if ( !GetND() || !GetND().GetClans() || !GetND().GetClans().GetOptions() ) return false;
		if ( !player || !player.GetRP() ) return false;

		if ( !GetND().GetClans().GetOptions().EnableClans || !player.GetRP().GetClan() )
			return false;
		
		PlayerBase ntarget = PlayerBase.Cast( target.GetObject() );

		// CORREÇÃO 2: ntarget.GetIdentity() REMOVIDO! 
		// O Client Vanilla não possui o Identity de outros jogadores. Sem essa remoção, a Action não funciona.
		if( ntarget && ntarget.IsAlive() && !ntarget.IsLiftWeapon() && ntarget.GetClanID() == -1 )
		{
			return true;
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		// CORREÇÃO 3: Blindagem de memória do jogador e do alvo no Backend
		if ( !action_data.m_Player || !action_data.m_Player.GetRP() || !action_data.m_Target ) return;

		PlayerBase ntarget = PlayerBase.Cast( action_data.m_Target.GetObject() );
		alpClanData clan = action_data.m_Player.GetRP().GetClan();
		
		// CORREÇÃO 4: A verificação rígida de Identity acontece OBRIGATORIAMENTE aqui, no Servidor.
		if (ntarget && ntarget.GetIdentity() && clan)
		{
			// Null check do sistema central antes da escrita
			if ( GetND() && GetND().GetClans() && GetND().GetNotf() )
			{
				GetND().GetClans().AddMember( ntarget, clan );
				GetND().GetNotf().SendMessage( ntarget, ALPMSTYPE.SMPERSONAL, "#ip_beenaddedtoclan " + clan.Name );
			}
		}		
	}
}