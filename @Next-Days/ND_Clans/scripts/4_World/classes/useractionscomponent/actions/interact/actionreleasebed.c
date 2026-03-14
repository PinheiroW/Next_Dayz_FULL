class alpActionReleaseBed: ActionInteractBase
{
	void alpActionReleaseBed()
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
		return "#pp_release_bed";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// CORREÇÃO 1: Failsafe contra Null Pointer Crash no carregamento do Mod Core
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
				
				if ( pp )
				{
					int bedIndex = building.GetOccupiedBedID( target.GetCursorHitPos() );		
					
					if ( bedIndex >= 0 )
					{
						// CORREÇÃO 2: Bypass Front-end resolvido.
						// Agora verifica se o jogador é autorizado a mexer nas camas deste PP.
						int pID = player.GetPlayerID();
						int cID = player.GetClanID();
						
						if ( pp.IsAuthorizedToClaimBed(pID, cID) )
						{
							return true;
						}
					}						
				}
			}			
		}
		
		return false;
	}
	
	// CORREÇÃO 3: Substituição do OnEnd (perigoso para banco de dados) pelo OnExecuteServer (Estável)
	override void OnExecuteServer( ActionData action_data )		
	{
		// CORREÇÃO 4: Proteção dupla de memória no Servidor
		if ( !action_data.m_Target || !action_data.m_Player ) return;

		BuildingBase building;
		if ( Class.CastTo(building, action_data.m_Target.GetParent()) )
		{
			// CORREÇÃO 5: Revalidação Backend rígida para impedir spoofing de rede (RPC Exploits)
			alp_PlotPole pp = alpClansPlugin.GetPlotPole( building.GetOwnerID() );
			if ( !pp || !pp.IsAuthorizedToClaimBed(action_data.m_Player.GetPlayerID(), action_data.m_Player.GetClanID()) ) return;

			int bedIndex = building.GetOccupiedBedID(action_data.m_Target.GetCursorHitPos() ); 

			if ( bedIndex >= 0 )
			{
				// CORREÇÃO 6: Null Check na classe Hive antes de forçar o I/O
				if ( action_data.m_Player.GetPlayerHive() )
				{
					action_data.m_Player.GetPlayerHive().ReleaseClaimedBed( building.GetOwnerID(), building.GetStringID(), bedIndex );
				}
				
				building.ReleaseBed( bedIndex );
			}
		}
	}
};