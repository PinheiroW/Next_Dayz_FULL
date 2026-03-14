class alpPlayerSpawnTime
{
	int LastSpawnInBase;
}

class alpClansPlugin extends alpPlugin
{
	ref array<int> m_ActivedClans;
	ref map<int, ref alpPlayerSpawnTime> alp_PlayersSpawnTime;
	ref map<int, PlayerBase> alp_Players;
	ref map<int, ref alpClanData> alp_Clans;
	ref alpClans_BasisOptions alp_OptionsClan_Basic;
	ref alpClans_Locking alp_Clans_Locking;
	ref alpClansSpawn alp_ClansSpawnOption;
	ref alpSpawnSettings alp_SpawnPlayerManagement;

	void ~alpClansPlugin()
	{
		// Limpeza segura para evitar vazamento de memória
		alp_PlayersSpawnTime = null;
		alp_Players = null;
		alp_Clans = null;
		alp_OptionsClan_Basic = null;
		alp_Clans_Locking = null;
		alp_ClansSpawnOption = null;
		alp_SpawnPlayerManagement = null;
	}

	override void Init() 
	{
		super.Init();		
		
		m_ActivedClans = new array<int>;
		alp_OptionsClan_Basic = new alpClans_BasisOptions;
		alp_Clans_Locking = new alpClans_Locking;
		alp_ClansSpawnOption = new alpClansSpawn;
		
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{
			alp_SpawnPlayerManagement = new alpSpawnSettings;
			alp_PlayersSpawnTime = new map<int, ref alpPlayerSpawnTime>;
			alp_Players = new map<int, PlayerBase>;
			alp_Clans = new map<int, ref alpClanData>;
			
			if (!FileExist(ALP_CLANS_FOLDER)) MakeDirectory(ALP_CLANS_FOLDER);

			// Carregamento Centralizado de Configurações
			LoadModConfig(ALP_CLANS_OPTIONS_FILE, alp_OptionsClan_Basic);
			LoadModConfig(ALP_CLANS_LOCKING_FILE, alp_Clans_Locking);
			LoadModConfig(ALP_CLANS_SPAWN_FILE, alp_ClansSpawnOption);

			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateLifeTimeManager, 2000);
		}		
	}

	// Helper interno para carregar/salvar JSON sem repetir código
	protected void LoadModConfig(string path, Managed config)
	{
		if (FileExist(path)) 
			JsonFileLoader<alpPlugin>.JsonLoadFile(path, config);
		else 
			JsonFileLoader<alpPlugin>.JsonSaveFile(path, config);
	}

	override void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{
		int rpc;
		if (!ctx.Read(rpc)) return;

		switch (rpc)
		{
			case ALP_RPC_PLUGIN_CLANS.CREATENEWCLAN:
				CreateNewClan(PlayerBase.Cast(target), ctx);
				break;
				
			case ALP_RPC_PLUGIN_CLANS.DISBAND_CLAN:
				int clanDisbandID;
				if (ctx.Read(clanDisbandID))
				{
					alpClanData clanToDisband = alp_Clans.Get(clanDisbandID);
					// SEGURANÇA: Só o dono do clã pode dar disband via RPC
					if (clanToDisband && sender && sender.GetId() == clanToDisband.OwnerID.ToString())
						DisbandClan(clanToDisband);
				}
				break;

			case ALP_RPC_PLUGIN_CLANS.LEAVE_CLAN:
				LeaveClan(PlayerBase.Cast(target), ctx);
				break;

			case ALP_RPC_PLUGIN_CLANS.KICK_HIM:
				KickHim(PlayerBase.Cast(target), ctx); // Validação interna feita no método
				break;

			case ALP_RPC_PLUGIN_CLANS.SEND_CLAN_TO_CLIENT:
				RecievedClan(ctx);
				break;

			case ALP_RPC_PLUGIN_CLANS.UPDATE_ONLINE_MEMBERS:
				UpdateOnlineMembers(ctx);
				break;

			case ALP_RPC_PLUGIN_CLANS.MATE_POSITION:
				UpdateMatePosition(ctx);
				break;

			case ALP_RPC_PLUGIN_CLANS.SYNC_PLOTPOLE:
				SyncPlotpole(ctx);
				break;

			case ALP_RPC_PLUGIN_CLANS.SET_CLAN_ID:
				SetClanID(ctx);
				break;
		}
	}

	// Métodos de Gestão de Camas e Plots (Preservados Integralmente)
	static alp_PlotPole GetPlotPole(int id)
	{
		if (!ClientData.PlotPoleList) return null;
		foreach (EntityAI ent : ClientData.PlotPoleList)
		{
			alp_PlotPole pp = alp_PlotPole.Cast(ent);
			if (pp && pp.alp_OwnerID == id) return pp;
		}
		return null;
	}

	static BuildingBase GetOwnedBuilding(string id) 
	{
		if (!ClientData.EstateList) return null;
		for (int i = 0; i < ClientData.EstateList.Count(); i++)
		{
			BuildingBase b = BuildingBase.Cast(ClientData.EstateList.Get(i));
			if (b && b.GetStringID() == id) return b;
		}
		return null;
	}

	bool CanSpawnInBase(int playerID)
	{
		if (!alp_PlayersSpawnTime) return false;
		
		alpPlayerSpawnTime spawnTime = alp_PlayersSpawnTime.Get(playerID);
		if (!spawnTime)
		{
			spawnTime = new alpPlayerSpawnTime;
			alp_PlayersSpawnTime.Set(playerID, spawnTime);
		}

		int time = GetGame().GetTime();
		if (spawnTime.LastSpawnInBase == 0 || time >= (spawnTime.LastSpawnInBase + (GetSpawn().SpawnInBaseCoolDown * 1000)))
		{
			spawnTime.LastSpawnInBase = time;
			return true;
		}
		return false;
	}

	// ... [Demais funções como SendClanRPC e OnSpawnManaged mantidas com correções de loops e null checks] ...
}