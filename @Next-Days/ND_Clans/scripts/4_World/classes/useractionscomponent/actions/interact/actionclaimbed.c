class alpActionClaimBed: ActionInteractBase
{
	void alpActionClaimBed()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override string GetText()
	{
		return "#pp_claim_bed";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// CORREÇÃO 1: Failsafe para prevenção de Null Pointer Crash no carregamento do Core
		if ( !GetND() || !GetND().GetClans() || !GetND().GetClans().GetSpawn() ) return false;

		if ( !GetND().GetClans().GetSpawn().EnableSpawnInBase )
		{
			return false;
		}
		
		if ( target && target.GetParent() ) 
		{	
			BuildingBase building;				
			if ( Class.CastTo(building, target.GetParent() ) && building.GetOwnerID() )
			{	
				alp_PlotPole pp = alpClansPlugin.GetPlotPole( building.GetOwnerID() );
				
				// Null Check Preventivo
				if ( !pp ) return false;
				
				int pID = player.GetPlayerID();
				int cID = player.GetClanID();	
				
				// CORREÇÃO 2: Bypass resolvido. O Servidor AGORA testa a permissão obrigatoriamente.
				if ( pp.IsAuthorizedToClaimBed(pID, cID) )
				{
					int bedIndex = building.GetBedID( target.GetCursorHitPos() );	
					if ( bedIndex >= 0 )
					{
						return true;
					}						
				}
				return false;															
			}			
		}
		return false;
	}
	
	// CORREÇÃO 3: Substituição do OnEnd obsoleto pelo OnExecuteServer nativo e seguro
	override void OnExecuteServer( ActionData action_data )
	{
		// Blindagem dupla de ponteiros para evitar Server Crash
		if ( !action_data.m_Target || !action_data.m_Player ) return;

		BuildingBase building;
		if ( Class.CastTo(building, action_data.m_Target.GetParent()) )
		{
			// CORREÇÃO 4: Revalidação Backend para impedir Spoofing de RPC
			alp_PlotPole pp = alpClansPlugin.GetPlotPole( building.GetOwnerID() );
			if ( !pp || !pp.IsAuthorizedToClaimBed(action_data.m_Player.GetPlayerID(), action_data.m_Player.GetClanID()) ) return;

			int bedIndex = building.GetBedID(action_data.m_Target.GetCursorHitPos() );
			
			if ( bedIndex >= 0 )
			{
				int pID = action_data.m_Player.GetPlayerID();
				
				// CORREÇÃO 5: Null Check na classe Hive antes de forçar o I/O
				if ( action_data.m_Player.GetPlayerHive() )
				{
					action_data.m_Player.GetPlayerHive().SetClaimedBed( building.GetOwnerID(), building.GetStringID(), bedIndex );
				}
				
				building.ClaimBed( bedIndex, pID );		
			}
		}
	}
};