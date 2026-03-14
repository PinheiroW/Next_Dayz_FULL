class alpBuildingStorage
{
	int alp_WorldID = 0;

	int GetNewWorldID()
	{
		alp_WorldID--;
		return alp_WorldID;
	}
}

ref alpBuildingStorage alp_BuildingStorage;

alpBuildingStorage GetBuildingStorage()
{
	if (!alp_BuildingStorage)
	{
		alp_BuildingStorage = new alpBuildingStorage;
	}
	return alp_BuildingStorage;
}

enum alpBUILDINGSET
{
	HAS_ALARM = 1,
	HAS_FINGERPRINTSLOCK = 2,
	HAS_LOCKPICKINGPROTECTION = 4,
	HAS_ENHANCEDDOOR = 8,
}

ref TStringArray alp_ApprovedDoors = {"doorWoodSmallOpen","doorWoodFrontOpen","doorWoodTwinOpen","doorMetalTwinOpen","doorMetalSmallOpen"};
ref TStringArray alp_ApprovedDoorsVehicles = {"doorCarSmallOpen","doorWoodSlideOpen"};

class alpBed
{
	int ID;
	string Name; // CORREÇÃO 1: Ponto e vírgula inserido (Evita Compile Error)
	vector Position;	
	//int Owner;
}

modded class BuildingBase
{
	float DOORS_HEALTH = 1;
	
	int m_LastOwnerID;	
	
	ref map<string,ref alpBed> alp_AllBeds;	
	ref map<string,float> alp_DoorsDamage;
	ref alpEstateSetting m_Estate;
	
	protected int alp_ID;
	
	int m_OwnerID;
	int m_ClanID;
	int m_KeyID;
	int m_Setting;
	int m_ClaimedBeds;
	int m_ValidThru;
	int m_Permission;
	
	int m_DaysRemain;
	
	void BuildingBase()
	{
		if ( CanBeBought() ) 
		{ 
			RegisterNetSyncVariableInt("m_OwnerID");
			RegisterNetSyncVariableInt("m_ClanID");
			RegisterNetSyncVariableInt("m_KeyID");
			RegisterNetSyncVariableInt("m_Setting");
			RegisterNetSyncVariableInt("m_ClaimedBeds");
			RegisterNetSyncVariableInt("m_ValidThru");				
			RegisterNetSyncVariableInt("m_Permission");		
					
			if (GetGame().IsServer() && GetGame().IsMultiplayer() ) 
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.LoadDataALP, 1);	
			}
			if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
			{
				ClientData.AddEstate( this );	
			}
			
			if ( m_DamageZoneMap )
			{
				alp_DoorsDamage = new map<string,float>;
		
				for (int d = 0; d < m_DamageZoneMap.Count(); d++)
				{
					string zone = m_DamageZoneMap.GetKey(d);					
					alp_DoorsDamage.Set( zone, DOORS_HEALTH );				
				}		
			}			
			
			alp_AllBeds = new map<string,ref alpBed>;
			
			autoptr TStringArray selections = new TStringArray;
			GetSelectionList( selections );										
			
			int id = 0;
			foreach( string s : selections )
			{	
				if ( s.IndexOf("beds") != -1 || s.IndexOf("chairs") != -1 )
				{
					autoptr alpBed bed = new alpBed;
					bed.ID = id;
					bed.Name = s;					
					bed.Position = GetSelectionPositionMS( s ) + "0.9 0.2 0";	
					alp_AllBeds.Set(s,bed);			
					id++;			
					if (id > 32)
					{
						break;
					}	
				}
			}				
		}
	}	
	
	void ~BuildingBase()
	{
		// CORREÇÃO 2: ClientData é exclusivo do Client. Forçado o check isolado para evitar Server Crash.
		if ( CanBeBought() && GetGame() && GetGame().IsClient() ) 
		{
			ClientData.RemoveEstate( this );	
		}		
		
		delete alp_AllBeds;
		delete alp_DoorsDamage;
	}	

	bool CanBeBought(){ return false; }	
	
	int GetDaysRemain(){ return VerificationProtection(); }	
	
	int VerificationProtection()
	{		
		int year, month, day, days;
		GetYearMonthDayUTC(year, month, day);			
	    days = year * 365 + month * 30 + day;					
		days = m_ValidThru - days;		
		return days;
	}	
	
	alpEstateSetting GetEstate(){ return m_Estate; }
	
	int GetWorldID()
	{	
		if ( !alp_ID )
		{
			int low;
			int high;
			GetNetworkID(low,high);
			alp_ID = low; 
		}						
		return alp_ID;
	}
	
	string GetStringID()
	{
		vector pos = GetPosition();
		return pos[0].ToString() + ":" + pos[1].ToString() + ":" + pos[2].ToString();
	}			
	
	void LoadDataALP()
	{		
		m_Estate = alpBBHIVE.Get( GetStringID(), GetType() );		
		
		// CORREÇÃO 3: Failsafe Crítico de Banco de Dados. Impede NPE Crash se o banco retornar vazio.
		if (!m_Estate) return;
		
		m_OwnerID = m_Estate.OwnerID;
		m_ClanID = m_Estate.ClanID;
		m_KeyID = m_Estate.KeyID;
		m_Setting = m_Estate.Setting;
		m_ClaimedBeds = m_Estate.ClaimedBeds;
		m_ValidThru = m_Estate.ValidThru;
		m_Permission = m_Estate.Permission;
		
		if ( IsEstateProtected() )
		{
			if  ( GetDaysRemain() > 0 ) 
			{
				m_LastOwnerID = m_Estate.OwnerID;
				if (GetGame().IsClient()) ClientData.AddEstate( this ); // Blindado para o Client
				LockAllBaseDoors();
			} 
			else 
			{
				SetEstateValues( new Param7<int,int,int,int,int,int,int>(0,0,0,0,0,0,0) );
				m_Estate.Clear();
				alpBBHIVE.Save();
			}
		} 
				
		if ( GetND() && GetND().GetClans() && GetND().GetClans().GetLocking() && GetND().GetClans().GetLocking().EnableLocking && GetCountOfDoorsALP() ) 
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitLockedDoors, 500 );
		}		
		SetSynchDirty();
	}
	
	bool IsEstateProtected() 
	{
		return m_OwnerID;
	}
	
	void SavaDataALP()
	{
		if (!m_Estate) return;

		m_OwnerID = m_Estate.OwnerID;
		m_ClanID = m_Estate.ClanID;
		m_KeyID = m_Estate.KeyID;
		m_Setting = m_Estate.Setting;
		m_ClaimedBeds = m_Estate.ClaimedBeds;
		m_ValidThru = m_Estate.ValidThru;
		m_Permission = m_Estate.Permission;
				
		if (m_LastOwnerID != m_OwnerID ) 
		{
			// CORREÇÃO 4: Typo '==' alterado para atribuição '='. A variável agora salva.
			m_LastOwnerID = m_OwnerID; 
			// CORREÇÃO 5: Isolamento estrito de UI/Client.
			if (GetGame().IsClient()) ClientData.AddEstate( this ); 
		}

		if (m_OwnerID)
		{
			alpBBHIVE.RegisterEstate( GetStringID(), m_Estate ); 
		}
		alpBBHIVE.Save();
		
		SetSynchDirty();
	}	
	
	void SyncEstateValues(PlayerBase player)
	{
		if ( m_OwnerID && player && GetND() && GetND().GetClans() ) 
		{
			Param7<int,int,int,int,int,int,int> values = new Param7<int,int,int,int,int,int,int>(m_OwnerID,m_ClanID,m_KeyID,m_Setting,m_ClaimedBeds,m_ValidThru,m_Permission);

			ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
			rpc.Write( ALP_RPC_PLUGIN_CLANS.SYNC_PLOTPOLE );	
			rpc.Write( GetWorldID() );
			rpc.Write( values );
			GetND().SendGameRPC( rpc, player );			
		}
	}
	
	void SetEstateValues(Param7<int,int,int,int,int,int,int> values ) 
	{
		if ( values ) 
		{
			m_OwnerID = values.param1;
			m_ClanID = values.param2;
			m_KeyID = values.param3;
			m_Setting = values.param4;
			m_ClaimedBeds = values.param5;
			m_ValidThru = values.param6;			
			m_Permission = values.param7;	
		}
	}
	
	void UpdateEstateSetting(PlayerBase player, int owner, int clan, int key, int setting , int validto, int permission )
	{
		SetOwnerID( owner );
		SetClanID( clan );
		SetKeyID( key );
		SetHouseALP( setting );
		SetValidToALP( validto );
		SetClanPermission( permission );
		
		SyncEstateValues(player);		
		SavaDataALP();		
	}
	
	void UpdateClanSetting(int clanID, int clanPermisison )
	{
		SetClanID(clanID);
		SetClanPermission(clanPermisison);
		SavaDataALP();		
	}
	
	void SetOwnerID(int id)
	{
		if (m_Estate) m_Estate.OwnerID = id;
		m_OwnerID = id;
	}		
	void SetClanID(int id)
	{
		if (m_Estate) m_Estate.ClanID = id;
		m_ClanID = id;
	}	
	void SetClanPermission(int id)
	{
		if (m_Estate) m_Estate.Permission = id;
		m_Permission = id;
	}	
	void SetKeyID(int id)
	{
		if (m_Estate) m_Estate.KeyID = id;
		m_KeyID = id;
	}	
	void SetHouseALP(int setting)
	{
		if (m_Estate) m_Estate.Setting = setting;
		m_Setting = setting;
	}
	void SetValidToALP(int validto )
	{
		if ( validto > m_ValidThru )
		{
			if (m_Estate) m_Estate.ValidThru = validto;
			m_ValidThru = validto;		
		}
	}			
	
	int GetClanPermission(){ return m_Permission; }	
	int GetHouseSetting(){ return m_Setting; }	
	int GetOwnerID(){ return m_OwnerID; } 
	int GetClanID(){ return m_ClanID; }
	int GetKeyID(){ return m_KeyID; }		
	
	bool IsEnabledFingerPringLock(){ return alpBUILDINGSET.HAS_FINGERPRINTSLOCK & m_Setting; }		
	bool CanUseFingerPrints(){ return m_Permission & alpCLAN_PERMISSION.CAN_USE_FINGERPRINTS; }
	bool HasAlarmALP(){ return alpBUILDINGSET.HAS_ALARM & m_Setting; }	
	bool HasLockProtection(){ return alpBUILDINGSET.HAS_LOCKPICKINGPROTECTION & m_Setting; }	
	bool HasEnhancedDoors(){ return alpBUILDINGSET.HAS_ENHANCEDDOOR & m_Setting; }		
	
	int GetBedID(vector position)
	{
		int id = -1;
		if (!alp_AllBeds) return id;

		for(int i = 0; i < alp_AllBeds.Count(); i++)
		{
			if ( vector.Distance( position, ModelToWorld( alp_AllBeds.GetElement(i).Position ) ) < 1.0 && !IsBedClaimed(i) )
			{				
				id = i;
				break;
			} 		
		}			
		return id;	
	}	
	
	int GetOccupiedBedID(vector position)
	{
		int id = -1;
		if (!alp_AllBeds) return id;

		for(int i = 0; i < alp_AllBeds.Count(); i++)
		{
			if ( vector.Distance( position, ModelToWorld( alp_AllBeds.GetElement(i).Position ) ) < 1.0 && IsBedClaimed(i) )
			{			
				id = i;
				break;
			} 		
		}
		return id;	
	}		
	
	vector GedBedLocation(int index)
	{
		if (!alp_AllBeds || index < 0 || index >= alp_AllBeds.Count()) return "0 0 0";
		return ModelToWorld( alp_AllBeds.GetElement(index).Position );
	}
	
	bool ClaimBed(int id , int pID )
	{
		if (!m_Estate) return false;
		int index = id;
		// CORREÇÃO 6: Isolamento seguro de conversão de bitmask
		int bitMask = Math.Round(Math.Pow(2, id));
		m_Estate.ClaimedBeds = m_Estate.ClaimedBeds | bitMask;
		m_ClaimedBeds = m_Estate.ClaimedBeds;
		m_Estate.RoomMates[index] = pID;
		SavaDataALP();
		return true;
	}	

	void ReleaseBed(int id )
	{
		if (!m_Estate) return;
		int index = id;
		int bitMask = Math.Round(Math.Pow(2, id));		
		m_Estate.ClaimedBeds = ~bitMask & m_Estate.ClaimedBeds;	
		m_ClaimedBeds = m_Estate.ClaimedBeds;	
		m_Estate.RoomMates[index] = 0;
		SavaDataALP();		
	}	

	void ReleaseOldBed(int id, int playerID )
	{
		if ( GetEstate() && GetEstate().ReleaseOldBed(id, playerID) ) 
		{
			m_ClaimedBeds = m_Estate.ClaimedBeds;
			SavaDataALP();	
		}	
	}		
	
	bool IsBedClaimed( int id )
	{
		int bitMask = Math.Round(Math.Pow(2, id));
		return (m_ClaimedBeds & bitMask) != 0;
	}		

	void LockAllDoors(float chance = 1 )
	{
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetLocking()) return;

		int count = GetCountOfDoorsALP();		
		float lockedRatio = GetND().GetClans().GetLocking().RatioLockedDoors;		
		int countLocked = count * lockedRatio;
		int locked = 0;
		int i;
		for (i = 0 ; i < count ; i++ )
		{			
			if ( IsDoorLocked(i) ) locked++;
		}

		if ( countLocked > locked )
		{
			for (i = 0 ; i < count ; i++ )
			{
				if ( countLocked <= locked ) break;
					
				if (CanOpenTheDoor(i))
				{
					if ( chance >= Math.RandomFloat01() )
					{
						if ( IsDoorOpen(i) ) CloseDoor(i);														
						if ( !IsDoorLocked(i) )
						{
							locked++;
							LockDoor(i);
						}
					}
				}
				else
				{
					locked++;
				}				
			}			
		}
	}
	
	void LockAllBaseDoors()
	{
		int count = GetCountOfDoorsALP();
		for (int i = 0 ; i < count ; i++ )
		{			
			if ( IsDoorOpen(i) ) CloseDoor(i);								
			if ( !IsDoorLocked(i) ) LockDoor(i);			
		}	
	}
	
	void UnlockAllDoors()
	{
		int count = GetCountOfDoorsALP();
		for (int i = 0 ; i < count ; i++ )
		{
			if (CanOpenTheDoor(i))
			{
				if ( IsDoorLocked(i) ) UnlockDoor(i);
			}
		}
	}	
	
	bool CanOpenTheDoor(int index)
	{
		string path_base = "" + CFG_VEHICLESPATH + " " + GetType() + " Doors";
		string doors;
		if (GetGame().ConfigIsExisting(path_base))
		{
			GetGame().ConfigGetChildName(path_base,index, doors );			
			path_base = path_base + " " + doors + " soundOpen";			
			doors = GetGame().ConfigGetTextOut( path_base );		
			if ( alp_ApprovedDoors.Find( doors ) >= 0 ) return true;

			if ( GetND() && GetND().GetClans() && GetND().GetClans().GetLocking() && GetND().GetClans().GetLocking().IncludingVehiclesWrecks && alp_ApprovedDoorsVehicles.Find( doors ) >= 0 )
			{
				return true;
			}			
		}			
		return false;							
	}
	
	void InitLockedDoors()
	{	
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetLocking()) return;

		bool forceUnlock = GetND().GetClans().GetLocking().ForcerUnlockAllDoors;		
		float chance = GetND().GetClans().GetLocking().ChanceToLockDoorAfterRestart;		
		
		if ( !forceUnlock && chance && !alp_IsMissionStructure )
		{				
			LockAllDoors(chance);
		}			
		if ( forceUnlock && !alp_IsMissionStructure )
		{
			UnlockAllDoors();
		}
	}
	
	override string GetDisplayName()
	{
		string name = super.GetDisplayName();	
		if ( name == STRING_EMPTY ) name = GetType();
		return name;
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{	
		// CORREÇÃO 7: Failsafe para eventos de Raids (Evita Crash se o mod core falhar durante PvP)
		if (CanBeBought() && GetGame() && GetGame().IsServer() && GetND() && GetND().GetClans() && GetND().GetClans().GetBases() && GetND().GetClans().GetBases().EnableNextDaysRaidMechanics )
		{
			if ( GetOwnerID() )
			{
				if ( damageType == DT_EXPLOSION )
				{
					float allowedDamage = 0;
					int ammoType = GetAmmoType(ammo);
					if ( ammoType )
					{				
						allowedDamage = GetDamageMultiplier( ammoType ) * DOORS_HEALTH;
					}
					SetDoorsHealth( allowedDamage );
				} 
				else 
				{
					float damage = damageResult.GetDamage(dmgZone,"Health");	
					float health = GetHealth(dmgZone,"Health");	
					
					health += damage;
					SetHealth(dmgZone,"Health",health);	
				}
			}
		} 
		else 
		{
			super.EEHitBy(damageResult,  damageType,  source,  component,  dmgZone,  ammo,  modelPos,  speedCoef);
		}
	}
	
	int GetAmmoType(string ammo )
	{
		switch (ammo)
		{
			case "alp_DynamiteExplosion": return alpAMMOTYPE.L2;		
			case "Plastic_Explosive_Ammo": return alpAMMOTYPE.L1;		
		}
		return 0;
	}
	
	void SetDoorsHealth(float damage )
	{
		if ( alp_DoorsDamage )
		{
			string name;
			float last_health, health, maxhealth;
			for(int i = 0; i < alp_DoorsDamage.Count(); i++)
			{
				name = alp_DoorsDamage.GetKey(i);
				health = GetHealth01(name,"Health");
				last_health = alp_DoorsDamage.GetElement(i);

				if ( health != last_health )
				{
					last_health -= damage;
				
					if ( last_health > 0 )
					{
						alp_DoorsDamage.Set( name  , last_health );	
						
						maxhealth =  GetMaxHealth(name,"Health");	
						maxhealth *= last_health;						
						SetHealth(name,"Health",maxhealth);										
					}					
					else
					{
						if ( IsDoorLocked(i) )
						{
							UnlockDoor( i );
							OpenDoor(i);
						}

						alp_DoorsDamage.Set( name  , DOORS_HEALTH );	
					}					
				}
			}
		}	
	}

	int alp_LastAttack;
	
	float GetDamageMultiplier(int ammoType)
	{
		float coef;	

		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetBases()) return 1.0;

		if ( GetND().GetClans().IsPlayerInGame( m_OwnerID ) || ( m_ClanID > 0 && GetND().GetClans().IsClanInGame( m_ClanID ) ) ) 
		{
			int currentTime = GetGame().GetTime() - (180 * 1000);	
			if ( alp_LastAttack > currentTime )
			{	
				GetND().GetClans().SendAlertMessage( GetPosition(), m_OwnerID , m_ClanID );				
				alp_LastAttack = GetGame().GetTime();
			}									
			if ( HasEnhancedDoors() )
			{
				coef = GetND().GetClans().GetBases().Raid_TNT_OwnerIsON_Building_Door_Tier2;
			}
			else 
			{
				coef = GetND().GetClans().GetBases().Raid_TNT_OwnerIsON_Building_Door_Tier1;
			}		
		} 
		else 
		{
			if ( HasEnhancedDoors() )
			{
				coef = GetND().GetClans().GetBases().Raid_TNT_OwnerIsOFF_Building_Door_Tier2;
			}
			else
			{
				coef = GetND().GetClans().GetBases().Raid_TNT_OwnerIsOFF_Building_Door_Tier1;			
			}				
		}
		return coef;
	}

	int GetCountOfDoorsALP()
	{
		int count = 0;		
		string path_base = "" + CFG_VEHICLESPATH + " " + GetType() + " Doors";
		if (GetGame().ConfigIsExisting(path_base))
		{
			count = GetGame().ConfigGetChildrenCount(path_base);
		}	
		return count;
	}
	
	float GetVolumeALP()
	{
		float volume;
		vector minMax[2];		
		if ( GetCollisionBox(minMax) )
		{
			vector dir = minMax[1] - minMax[0];
			if ( dir[0] == 0 ) dir[0] = 2;
			if ( dir[1] == 0 ) dir[1] = 2;			
			if ( dir[2] == 0 ) dir[2] = 2;					
						
			volume = dir[0] * dir[1] * dir[2];
		}
		return volume;	
	}
};

enum alpAMMOTYPE
{
	L0,
	L1,
	L2
}