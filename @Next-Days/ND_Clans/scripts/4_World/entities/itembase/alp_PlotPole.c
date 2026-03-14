// plot pole kit
class alp_PlotPoleKit : ItemBase
{
	int alp_PlayerID;
	
	void alp_PlotPoleKit()
	{
	}

	override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0" )
	{
		super.OnPlacementComplete( player, position, orientation );
		
		if ( GetGame().IsServer() )
		{		
			// Create TerritoryFlag
			alp_PlotPole plotpole = alp_PlotPole.Cast( GetGame().CreateObjectEx( "alp_PlotPole", GetPosition(), ECE_PLACE_ON_SURFACE ) );
			
			// CORREÇÃO 1: Failsafe / Null Check na criação do Plot Pole
			if ( plotpole )
			{
				plotpole.SetPosition( position );
				plotpole.SetOrientation( orientation );
				plotpole.alp_OwnerID = alp_PlayerID;
				plotpole.SetSynchDirty();			
				
				// make the kit invisible, so it can be destroyed from deploy UA when action ends
				HideAllSelections();
				SetIsDeploySound( true );			
			}
		}	
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}
}

enum alpCLAN_PERMISSION
{
	NONE,
	CAN_ACCES_TAX_MENU,
	CAN_PLACE,
	CAN_USE_FINGERPRINTS = 4,
	CAN_CLAIM_BED = 8,
}

// plot pole
class alp_PlotPole : ItemBase
{
	int alp_OwnerID = -1;	
	int alp_ClanID = -1;
	int alp_ClanPermission;
	
	int alp_Radius;
	int alp_ValidThru;
	bool alp_AlertMessage = false;
	
	int alp_DaysRemain;
	
	void alp_PlotPole()
	{		
		RegisterNetSyncVariableInt("alp_OwnerID");		
		RegisterNetSyncVariableInt("alp_ClanID");		
		RegisterNetSyncVariableInt("alp_ClanPermission");		
		RegisterNetSyncVariableInt("alp_Radius");		
		RegisterNetSyncVariableInt("alp_ValidThru");		

		// CORREÇÃO 2: Isolamento obrigatório do UI (Evita Crash no Servidor)
		if (GetGame().IsClient())
		{
			ClientData.AddPlotPole( this );			
		}
		
		if (GetGame().IsServer())
		{			
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater(this.SetUpPlotPole, 1000);				
		}
	}	
		
	void ~alp_PlotPole()
	{
		// CORREÇÃO 3: Isolamento obrigatório no Destrutor
		if (GetGame() && GetGame().IsClient())
		{
			ClientData.RemovePlotPole( this );			
		}
	}	
	
	int GetValidThru()
	{
		return alp_ValidThru;
	}
	
	void Disassemble()
	{
		alp_PlotPoleKit plotpole = alp_PlotPoleKit.Cast( GetGame().CreateObject( "alp_PlotPoleKit", GetPosition() ) );
		GetGame().ObjectDelete( this );
	}	
		
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionManagePlotPole);
	}	

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}		

	int GetRadius()
	{
		return alp_Radius;
	}
	
	int GetMaxRadius()
	{			
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetBases()) return 0;
		return GetND().GetClans().GetBases().PlotPoleTaxes.Get( GetND().GetClans().GetBases().PlotPoleTaxes.Count() - 1).Radius;
	}
	
	bool HasClanOwnerPermission()
	{
		return alp_ClanPermission & alpCLAN_PERMISSION.CAN_ACCES_TAX_MENU;
	}
		
	bool CanUseFingerPrints()
	{
		return alp_ClanPermission & alpCLAN_PERMISSION.CAN_USE_FINGERPRINTS;
	}
	bool CanPlaceObjects()
	{
		return alp_ClanPermission & alpCLAN_PERMISSION.CAN_PLACE;
	}	
	bool CanClaimBed()
	{
		return alp_ClanPermission & alpCLAN_PERMISSION.CAN_CLAIM_BED;
	}
	
	override bool IsBuildingALP()
	{
		return true;
	}			
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

		ctx.Write( alp_OwnerID );
		ctx.Write( alp_ClanID );
		ctx.Write( alp_ClanPermission );		
		ctx.Write( alp_Radius );
		ctx.Write( alp_ValidThru );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) ) return false;
		
		// CORREÇÃO 4: Segurança total contra corrupção do hive do banco de dados (Wipe Prevent)
		if ( !ctx.Read( alp_OwnerID ) ) return false;
		if ( !ctx.Read( alp_ClanID ) ) return false;
		if ( !ctx.Read( alp_ClanPermission ) ) return false;
		if ( !ctx.Read( alp_Radius ) ) return false;
		if ( !ctx.Read( alp_ValidThru ) ) return false;

		if ( alp_ValidThru == 0 )
		{
			alp_ValidThru = SetDateStamp();
		}						
		return true;
	}
	
	protected int SetDateStamp()
	{
		int year, month, day, stamp;
		GetYearMonthDayUTC(year, month, day);			
		stamp = year * 365 + month * 30 + day;		
		return stamp;
	}
	
	bool IsAuthorized( int pID, int cID )
	{
		if ( pID == alp_OwnerID ) return true;
		if ( CanPlaceObjects() && cID == alp_ClanID ) return true;
		return false;
	}
	
	bool IsAuthorizedToClaimBed( int pID, int cID )
	{
		if ( pID == alp_OwnerID ) return true;
		if ( CanClaimBed() && cID == alp_ClanID ) return true;
		return false;
	}	
	
	bool IsAuthorizedToAccessMenu( int pID, int cID )
	{
		if ( pID == alp_OwnerID ) return true;
		if ( HasClanOwnerPermission() && cID == alp_ClanID && cID > 0 ) return true;
		return false;
	}	
	
	void VerifyActualClanID(int pID, int cID)
	{
		if ( pID == alp_OwnerID )
		{
			m_LastClanID = cID;
			if ( cID != alp_ClanID )
			{
				m_LastClanID = alp_ClanID;
				alp_ClanID	= cID;
				alp_ClanPermission = 0;
				SetSynchDirty();
			}
		}
	}
	
	void SetUpPlotPole()
	{	
		alp_DaysRemain = VerificationProtection();

		if ( alp_DaysRemain > 0 )
		{
			if ( GetND() && GetND().GetClans() && GetND().GetClans().GetBases() && GetND().GetClans().GetBases().EnableLifeTimeManagement )
			{
				GetLifeTimeManager().AddBase( new alpLifeTimeItem( GetPosition(), alp_Radius, 1 ) );	
			}		
			GetBuildingInRadius();			
		}
		else 
		{					
			alp_Radius = 0;
		}
		SetSynchDirty();
	}
	
	int VerificationProtection()
	{		
		int year, month, day, days;
		GetYearMonthDayUTC(year, month, day);			
		days = year * 365 + month * 30 + day;					
		days = alp_ValidThru - days;		
		return days;
	}	
	
	void SetClanPermission(int setting)
	{
		int last = alp_ClanPermission;
		alp_ClanPermission = setting;
		
		if ( last != alp_ClanPermission ) 
		{
			if ( m_Buildings ) 
			{
				for ( int i = 0; i < m_Buildings.Count(); i++)
				{
					// CORREÇÃO 5: A variável estava vazia. Agora ela extrai corretamente o prédio do array!
					BuildingBase b = m_Buildings.Get(i);
					
					if ( b && b.GetOwnerID() == alp_OwnerID ) 
					{
						b.UpdateClanSetting( alp_ClanID, alp_ClanPermission );	
					}
				}
			}
		}
	}
	
	int m_LastRadius;
	int m_LastClanID;

	ref array<BuildingBase> m_Buildings;
	
	array<BuildingBase> GetBuildingInRadius() 
	{
		if ( !m_Buildings || m_LastRadius != alp_Radius || m_LastClanID != alp_ClanID ) 
		{
			m_LastRadius = alp_Radius;			
			m_Buildings = new array<BuildingBase>;		
		
			// CORREÇÃO 6: Remoção do autoptr obsoleto
			array<Object> nearest_objects = new array<Object>;
			array<CargoBase> proxy_cargos = new array<CargoBase>;		
			
			GetGame().GetObjectsAtPosition( GetPosition() , alp_Radius , nearest_objects, proxy_cargos ); 	
			
			for (int i = 0; i < nearest_objects.Count(); i++)
			{
				Object obj = nearest_objects.Get(i);
				
				if ( obj ) 
				{
					BuildingBase building; 	
					BaseBuildingBase base;
					
					if ( obj.IsBuilding() && Class.CastTo( building, obj ) && building.CanBeBought() )
					{
						if (building.GetCountOfDoorsALP())
						{
							m_Buildings.Insert(building);						
							if ( building.GetOwnerID() == alp_OwnerID && ( building.GetClanID() != alp_ClanID || building.GetClanPermission() != alp_ClanPermission ) )
							{
								building.UpdateClanSetting( alp_ClanID, alp_ClanPermission );
							}												
						}						
					} 
					else if ( Class.CastTo( base, obj ) ) 
					{
						base.SetPlotPoleID( alp_OwnerID , alp_ClanID );		
						if ( m_LastClanID != alp_ClanID )
						{
							base.SetSynchDirty();
						}					
					}
				}
			}
			m_LastClanID = alp_ClanID;			
		}	
		return m_Buildings;	
	}		
	
	BuildingBase GetBuilding(int id )
	{
		array<BuildingBase> budovy = GetBuildingInRadius();

		if ( budovy ) 
		{
			for(int i = 0; i < budovy.Count(); i++ )
			{
				BuildingBase building = budovy.Get(i);
				if (building && building.GetWorldID() == id ) 
				{
					return building;
				}
			}
		}
		return null;		
	}
	
	bool UpdateEstateOwnership(PlayerBase player, int houseID, int key, int setting )
	{	
		BuildingBase b = GetBuilding( houseID );		
		if ( b ) 
		{
			b.UpdateEstateSetting( player, GetOwnerID(), GetClanID(), key, setting, GetValidThru(), alp_ClanPermission );
			return true;
		}			
		return false;
	}
	
	bool SellEstateOwnership(PlayerBase player, int houseID, int key, int setting )
	{	
		BuildingBase b = GetBuilding( houseID );		
		if ( b ) 
		{
			b.UpdateEstateSetting( player, 0, 0, 0, 0, 0, 0);
			return true;
		}			
		return false;
	}
	
	int GetOwnerID()
	{
		return alp_OwnerID;
	}
	
	int GetClanID()
	{
		return alp_ClanID;	
	}
	
	void AddProtectionLifeTime(PlayerBase player, int d, int r)
	{
		if ( alp_Radius >= r && alp_DaysRemain > 0 )
		{
			d += alp_DaysRemain;		
		}
		
		alp_ValidThru = SetDateStamp() + d;
		
		alp_DaysRemain = VerificationProtection();
		alp_Radius = r;		

		array<BuildingBase> budovy = GetBuildingInRadius();
		if ( budovy ) 
		{
			for(int i = 0; i < budovy.Count(); i++ )
			{				
				BuildingBase b = budovy.Get(i);
				if (b && b.GetOwnerID() == GetOwnerID() ) 
				{
					b.UpdateEstateSetting( player, b.GetOwnerID(), GetClanID(), b.GetKeyID(), b.GetHouseSetting() , GetValidThru(), alp_ClanPermission );						
				}
			}
		}		
	}
	
	void DisableTerritoryProtection()
	{
		alp_ValidThru = 0;
		alp_Radius = 0;
		alp_DaysRemain = VerificationProtection();
		SetSynchDirty();
	}		
	
	int GetDaysRemain()
	{
		return VerificationProtection();
	}
	
	void ForceSetSynchDirty(PlayerBase player)
	{
		if ( !m_Buildings )
		{
			m_Buildings = GetBuildingInRadius();
		}
		
		if ( m_Buildings ) 
		{
			for(int i = 0; i < m_Buildings.Count(); i++ )
			{
				BuildingBase building = m_Buildings.Get(i);
				if ( building ) 
				{
					building.SyncEstateValues(player);
				}
			}
		}		
	}
}