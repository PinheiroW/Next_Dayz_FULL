modded class alpPlayerHive 
{
	void SetClaimedBed(int pp, string house, int index)
	{
		auto store = GetStore();
		if (!store) return;

		int ppID = store.Base_Owner;
		string hID = store.Base_House;
		int old_index = store.Base_Bed;
		
		if ( ppID )
		{
			// Libera a cama antiga se houver
			int pID = GetPlayer().GetPlayerID();		
			alpClansPlugin.ReleaseBed( ppID, hID, old_index, pID );
		}
		
		store.Base_Owner = pp;
		store.Base_House = house;
		store.Base_Bed = index;
		Save();
	}

	void ReleaseClaimedBed(int pp, string house, int index)
	{
		auto store = GetStore();
		if (!store) return;

		int ppID = store.Base_Owner;
		string hID = store.Base_House;
		int old_index = store.Base_Bed;
		
		if ( ppID == pp && hID == house && index == old_index )
		{
			store.Base_Owner = 0;
			store.Base_House = "";
			store.Base_Bed = 0;
			Save();
		}				
	}	

	vector GetBedLocation()
	{
		vector pos = "0 0 0";
		auto store = GetStore();
		if (!store) return pos;
		
		int ownerID = store.Base_Owner;
		string houseID = store.Base_House;
		int bedID = store.Base_Bed;	
		
		PlayerBase player = GetPlayer();
		if (!player) return pos;

		int pID = player.GetPlayerID();
		int clanID = store.ClanID;

		if ( ownerID )
		{	
			pos = alpClansPlugin.GetBedLocation( ownerID, houseID, bedID, pID, clanID );
			
			if (pos == "0 0 0")
			{
				store.Base_Owner = 0;
				store.Base_House = "";
				store.Base_Bed = 0;
				Save();			
			}
		}
		return pos;
	}
	
	override void OnConnect()
	{
		super.OnConnect();
	
		if (GetGame() && GetGame().IsServer())
		{
			PlayerBase player = GetPlayer();
			if (!player) return;

			// CORREÇÃO 1: Failsafe para evitar NPE Crash no acesso aos Plugins
			if (!GetND() || !GetND().GetClans()) return;

			auto clansPlugin = GetND().GetClans();
			bool enhancedSpawn = clansPlugin.GetSpawn().EnableEnhancedSpawnSettings;			
			bool equipmentChanged = false;
			
			int reputationLevel = player.GetStatPerkReputation().Get();
			
			// CORREÇÃO 2: Substituição de autoptr obsoleto
			array<string> messages = new array<string>;
			
			if ( IsActiveDeathEvent() ) 
			{
				if ( enhancedSpawn )
				{
					equipmentChanged = true;
					if ( GetStore().IsNewborn )
					{
						GetStore().IsNewborn = false;
						
						auto spawnMgmt = clansPlugin.GetSpawnManagement();
						if (spawnMgmt)
						{
							alpSpawnSetNewborn spawnsetnewborn = spawnMgmt.GetNewbornSet();					
							if (spawnsetnewborn)
							{							
								EquipPlayer( spawnsetnewborn.Equipments, spawnsetnewborn.lootMaxCount);
								foreach(string m : spawnsetnewborn.Messages) messages.Insert(m);	
								
								if ( spawnsetnewborn.Water ) player.GetStatWater().Set( spawnsetnewborn.Water );
								if ( spawnsetnewborn.Energy ) player.GetStatEnergy().Set( spawnsetnewborn.Energy );
							}
						}
					}
					else
					{
						auto spawnMgmtRel = clansPlugin.GetSpawnManagement();
						if (spawnMgmtRel)
						{
							alpSpawnSetPlayer spawnset = spawnMgmtRel.GetSpawnSet(reputationLevel);
							if (spawnset)
							{	
								EquipPlayer( spawnset.Equipments, spawnset.lootMaxCount );
								foreach(string m2 : spawnset.Messages) messages.Insert(m2);	
								
								if ( spawnset.Water ) player.GetStatWater().Set( spawnset.Water );
								if ( spawnset.Energy ) player.GetStatEnergy().Set( spawnset.Energy );
							}
						}
					}
				}

				if ( clansPlugin.GetSpawn().EnableSpawnInBase )
				{
					vector spawnPos = GetBedLocation();
					if ( spawnPos != "0 0 0")
					{
						if ( clansPlugin.CanSpawnInBase( player.GetPlayerID() ) )
						{
							spawnPos[1] = spawnPos[1] + 0.5; 
							player.SetPosition( spawnPos );						
						}
					}				
				}
				DeactiveEvent( ALP_SPAWN_EVENT.DEATH );
			}
			else if ( player.IsPlayerSpawn() && enhancedSpawn && GetStore().IsNewborn )
			{
				GetStore().IsNewborn = false;
				equipmentChanged = true;
				
				auto spawnMgmtWipe = clansPlugin.GetSpawnManagement();
				if (spawnMgmtWipe)
				{
					alpSpawnSetNewborn spawnsetnewborn2 = spawnMgmtWipe.GetNewbornSet();					
					if (spawnsetnewborn2)
					{						
						EquipPlayer( spawnsetnewborn2.Equipments, spawnsetnewborn2.lootMaxCount);
						foreach(string m3 : spawnsetnewborn2.Messages) messages.Insert(m3);	
						if ( spawnsetnewborn2.Water ) player.GetStatWater().Set( spawnsetnewborn2.Water );
						if ( spawnsetnewborn2.Energy ) player.GetStatEnergy().Set( spawnsetnewborn2.Energy );
					}
				}
			}
						
			if ( equipmentChanged && messages.Count() > 0 )
			{
				int timeOffset = 500;
				int messageStart = 6000;
				for (int i = 0; i < messages.Count(); i++)
				{
					int timeMessage = messageStart + (timeOffset * i);
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.SendSpawnMessage, timeMessage, false, messages.Get(i));
				}
				player.SetSynchDirty();
			}			
		}			
	}

	void SendSpawnMessage(string message)
	{
		if (GetND() && GetND().GetNotf())
		{
			GetND().GetNotf().SendPersonalMessage( message, GetPlayer() );	
		}
	}	
	
	override void SaveCommonStats()
	{
		super.SaveCommonStats();
		auto store = GetStore();
		if (store) store.Event = store.Event | ALP_SPAWN_EVENT.DEATH;
	}	
	
	bool IsActiveDeathEvent()
	{
		auto store = GetStore();
		if (!store) return false;
		return store.Event & ALP_SPAWN_EVENT.DEATH;
	}
	
	bool IsActiveEvent(int type)
	{
		auto store = GetStore();
		if (!store) return false;
		return store.Event & type;
	}
	
	void DeactiveEvent(int type)
	{
		auto store = GetStore();
		if ( store && IsActiveEvent( type ) )
		{
			store.Event = ~type & store.Event;
		}
	}
	
	override void OnFirstConnect()
	{
		super.OnFirstConnect();
		if (alp_StoreValues) alp_StoreValues.IsNewborn = true;		
	}
	
	void EquipPlayer(array<ref alpLootCargo> equipments, int maxCount = 0 )
	{
		PlayerBase player = GetPlayer();
		if (!player || !equipments) return;

		player.ClearInventory();
		
		// CORREÇÃO 3: Otimização de Performance (Referência de mapa fora do loop)
		if (!GetND() || !GetND().GetMS()) return;
		auto lootMap = GetND().GetMS().alp_LootMap;

		int count = 0;
		foreach (alpLootCargo cargoMan : equipments)
		{
			if (!cargoMan) continue;

			alpLoot lootMan = null;
			if (lootMap) lootMan = lootMap.Get(cargoMan.title);
				
			if (lootMan) 
			{
				alpMission.SpawnCargo( player, lootMan, cargoMan.chance);
			}
			else
			{
				alpMission.SpawnEntityInCargo(player, cargoMan.title, cargoMan.chance );
			}								
			
			count++; 												
			if ( maxCount > 0 && count >= maxCount ) break;
		}			
	}
}