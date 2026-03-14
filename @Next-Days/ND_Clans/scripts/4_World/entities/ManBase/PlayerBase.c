// Script File
modded class PlayerBase
{
	// PlotPole
	ref alpAuthorize alp_Authorize;	
	alp_PlotPole alp_PlotPoleManage;
	
	int alp_ClanID = -1;
	// Nota: Verifique se alp_PlayerID está declarado no ManBase ou se precisa ser declarado aqui
	
	float alp_Time;
	const float ALP_TIMEFORCHECKMESSAGES = 1.0;		
	vector alp_LastKnownPosition = "0 0 0";	
	
	override void Init()
	{
		super.Init();
		
		RegisterNetSyncVariableInt("alp_PlayerID");	
		RegisterNetSyncVariableInt("alp_ClanID");	
		
		alp_Authorize = new alpAuthorize(this);		
	}	
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick( deltaTime );		
		
		if ( GetGame().IsClient() && IsControlledPlayer() && IsAlive() )
		{
			alp_Time += deltaTime;
			if (alp_Time >= ALP_TIMEFORCHECKMESSAGES)
			{
				alp_Time = 0; // Reset do timer
				CheckPlotPole();
			}		
		}
	}	
	
	override int GetClanID()
	{
		return alp_ClanID;
	}
		
	int GetPlayerID()
	{
		// Certifique-se que alp_PlayerID existe nesta classe ou na ManBase
		return alp_PlayerID;
	}
	
	void SetClanID(int id )
	{
		alp_ClanID = id;
	}

	bool IsAuthorized(ItemBase item)
	{
		if (!alp_Authorize) return false;
		return alp_Authorize.IsAuthorized(item);
	}
	
	bool IsAuthorized()
	{
		if (!alp_Authorize) return false;
		return alp_Authorize.IsAuthorized();
	}	
	
	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{		
		super.SetActionsRemoteTarget(InputActionMap);	
		AddAction(alpAddFriendAction);
		AddAction(alpActionClaimBed);
		AddAction(alpActionReleaseBed);
	}	

	void CheckPlotPole() // Client only
	{
		float dist;
		int pID = GetPlayerID();
		int cID = GetClanID();		
		int r;
		bool home = false;
		
		Hud hud = GetHudALP();

		foreach (EntityAI ent : ClientData.PlotPoleList)
		{
			alp_PlotPole pp = alp_PlotPole.Cast(ent);
								
			if (pp)
			{
				if (pp.alp_Radius )
				{
					dist = vector.Distance(pp.GetPosition(), GetPosition());					
					r = pp.GetRadius();					
					
					if ( pp.IsAuthorized(pID, cID) && dist <= r )
					{
						home = true;
					}
					
					if ( dist <= r && !pp.alp_AlertMessage ) 
					{
						if ( hud )
						{
							if ( pp.IsAuthorized(pID, cID) ) 
								hud.SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_welcome_home");
							else if ( !GetND().GetClans().GetBases().DisableNotfYouAreInEnemyTerritory )
								hud.SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_you_are_in_enemy_territory");
						}
						pp.alp_AlertMessage = true;	
					}
					
					if ( dist > r && pp.alp_AlertMessage) 
					{
						if ( hud )
						{
							if ( pp.IsAuthorized(pID, cID) && pp.alp_OwnerID > 0 )
								hud.SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_you_left_home");
							else if ( pp.alp_OwnerID > 0 && !GetND().GetClans().GetBases().DisableNotfYouAreInEnemyTerritory )
								hud.SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_you_left_enemy_territory");
						}
						pp.alp_AlertMessage = false;						
					}
				}
			}
		}	

		// CORREÇÃO: Null check obrigatório para o sistema de RP
		auto rp = GetRP();
		if (rp)
		{
			if (home) 
			{			
				if ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtHome ) 
					rp.SetHome( true , true );									
				else
					rp.SetHome( true , IsInVehicle() );			
			} 
			else 
			{
				if ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtSafeZone ) 
				{
					bool inTrader = false;
					if (GetSyncData()) inTrader = GetSyncData().GetElement( alpRPelements.ISINTRADERZONE ).GetValue();
					rp.SetHome( false , IsInVehicle() || inTrader );											
				} 
				else 
				{
					rp.SetHome( false , IsInVehicle() );
				}						
			}
		}
	}			
	
	Hud GetHudALP()
	{
		// CORREÇÃO: Acesso direto ao membro da classe vanilla
		return m_Hud;
	}			
	
	bool IsPossibleFillBottle()
	{
		if (m_Environment && m_Environment.IsInShelter() )
		{
			return false;
		}
		return true;
	}
}