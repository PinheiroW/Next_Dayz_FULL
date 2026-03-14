class alpActionManagePlotPole : ActionInteractBase
{
	void alpActionManagePlotPole()	
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask        = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;		
	}

	// Boa Prática: OBRIGATÓRIO declarar os Components mesmo que a ActionCondition tenha override profundo
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTCursor;
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#pp_title";
	}
	
	override bool HasProgress()
	{
		return false;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// CORREÇÃO 1: Failsafe para evitar Crash de Null Pointer
		if ( !target || !target.GetObject() || !player ) return false;

		Object targetObject = target.GetObject();
		alp_PlotPole plotpole = alp_PlotPole.Cast(targetObject);
		
		if ( plotpole )
		{
			// CORREÇÃO 2: Exploit Removido! 
			// A trava IsClient() foi deletada. Agora o Servidor sempre validará a autorização do PlotPole.
			int playerID = player.GetPlayerID();
			int clanID = player.GetClanID();
			
			if ( plotpole.IsAuthorizedToAccessMenu(playerID, clanID) )
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		// CORREÇÃO 3: Blindagem de memória do jogador e alvo no Servidor
		if ( !action_data.m_Target || !action_data.m_Player ) return;

		alp_PlotPole plotpole = alp_PlotPole.Cast(action_data.m_Target.GetObject());
		
		if ( plotpole )
		{
			// CORREÇÃO 4: Revalidação de Backend (Garante segurança total contra injeções de RPC Spoofing)
			if ( !plotpole.IsAuthorizedToAccessMenu(action_data.m_Player.GetPlayerID(), action_data.m_Player.GetClanID()) ) return;

			// Failsafe do Core Mod
			if ( !GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() ) return;

			int stockID = GetStockID( action_data.m_Player.GetPosition() );		
			
			if ( action_data.m_Player.GetSyncData() )
			{
				action_data.m_Player.GetSyncData().RegisterToStats( true );		
				action_data.m_Player.GetSyncData().ForceSync();
			}
			
			GetND().GetMS().GetTrader().GiveMeStock( stockID , action_data.m_Player, true );
		}
	}

	override void OnExecuteClient( ActionData action_data )
	{
		if ( !action_data.m_Target || !action_data.m_Player ) return;

		alp_PlotPole plotpole = alp_PlotPole.Cast(action_data.m_Target.GetObject());
		
		if ( plotpole )
		{
			// CORREÇÃO 5: Prevenção massiva contra Client Crash
			if ( !GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !action_data.m_Player.GetRP() || !action_data.m_Player.GetRP().GetCart() ) return;

			int stockID = GetStockID( action_data.m_Player.GetPosition() );
		
			GetND().GetMS().GetTrader().SetNPC(stockID);						
			action_data.m_Player.GetRP().GetCart().SetNPCid( stockID );			
			
			action_data.m_Player.alp_PlotPoleManage = plotpole;
			
			if ( !GetGame().GetUIManager().FindMenu(ALP_MENU_MANAGE_PLOTPOLE) )
			{
				GetGame().GetUIManager().EnterScriptedMenu(ALP_MENU_MANAGE_PLOTPOLE, NULL);
			}
		}
	}	

	int GetStockID(vector position)
	{
		int stockID = 1;
		
		if ( !GetND() || !GetND().GetClans() || !GetND().GetClans().GetBases() ) return stockID;
		
		// CORREÇÃO 6: Otimização Pesada de Array (Fim do Memory Leak / Loop Hang)
		array<ref alpTaxedArea> territories = GetND().GetClans().GetBases().TerritoryCurrency;

		if ( territories && territories.Count() > 0 )
		{
			int count = territories.Count();
			for (int a = 0 ; a < count ; a++)
			{
				alpTaxedArea area = territories.Get(a);
				if (!area) continue;

				int p1x = area.Point1[0];
				int p2x = area.Point1[1];
				
				int p1y = area.Point2[0];
				int p2y = area.Point2[1];
				
				if ( position[0] > p1x && position[0] < p2x ) 
				{
					if ( position[2] > p1y && position[2] < p2y ) 
					{
						stockID = area.StockID;
						break;
					}
				}					
			}
		}
		return stockID;
	}	
}