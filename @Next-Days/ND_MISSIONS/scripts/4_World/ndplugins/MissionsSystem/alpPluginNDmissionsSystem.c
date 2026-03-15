/**
 * alpPluginNDmissionsSystem.c
 * * MISSION SYSTEM MASTER CONTROLLER - Módulo ND_MISSIONS
 * Gerencia o ciclo de vida global, economia de veículos, traders e sincronização RPC.
 */

class alpPluginNDmissionsSystem extends alpPlugin
{
	// --- Estatísticas e Limites Globais ---
	static ref map<string, int> m_MissionGroup = new map<string, int>;
	static int CarsCount = 0;
	static ref map<string, int> VehicleTypes = new map<string, int>;
	static ref array<FuelStation> FuelStations = new array<FuelStation>;
	
	// --- Configurações e Opções ---
	ref array<ref alpProtectionItem> alp_ProtectionBonuses;
	ref map<string, ref alpProtectionItem> alp_ProtectionBonusesMaped;
	ref alpOptionsMSradiation alp_optionsMSradiation; 
	ref alpOptionsMStrader alp_optionsMStrader; 
	
	// --- Coleções de Missões ---
	protected ref alpMissionList alp_List;
	ref map<int, ref alpMission> alp_Missions;
	ref map<string, ref array<ref alpMission>> alp_MissionsByName;
	ref alpMissionPosition alp_MissionRegistr;	

	// --- Economia e Itens ---
	ref map<string, ref alpLoot> alp_LootMap;
	ref map<string, ref alpVehicles> alp_VehiclesMap;	
	ref map<string, autoptr Param3<int, string, int>> alp_AllItemsByTag;
	ref alpTraderCore alp_TraderCore;
	ref array<string> alp_HideItems;
	ref array<string> alp_HideItemsType;	
	
	// --- Dados Geográficos e Quests ---
	ref map<string, ref array<ref array<float>>> m_RegisteredPositions;
	ref array<int> alp_ActiveQuestsID; 	

	// --- Time Stamp Central ---
	static int alp_Hour;
	static int alp_Minute;
	static int alp_Second;

	// --- Inicialização do Plugin ---

	override void Init() 
	{
		alp_Missions       = new map<int, ref alpMission>;
		alp_MissionsByName = new map<string, ref array<ref alpMission>>;
		alp_HideItems      = new array<string>;
		alp_HideItemsType  = new array<string>;
	
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{
			alp_ActiveQuestsID = new array<int>;	
			m_RegisteredPositions = new map<string, ref array<ref array<float>>>; 

			// Carregamento de Configurações (Radiação, Trader, Proteção)
			JsonFileLoader<autoptr alpOptionsMSradiation>.JsonLoadFile(ALP_MISSIONS_RADIATION_FILE, alp_optionsMSradiation);	
			if (!alp_optionsMSradiation) alp_optionsMSradiation = new alpOptionsMSradiation();
			
			if (!FileExist(ALP_MISSIONSYSTEM_PROTECTION))
				JsonFileLoader<array<ref alpProtectionItem>>.JsonSaveFile(ALP_MISSIONSYSTEM_PROTECTION, alp_ProtectionBonuses);
			else
				JsonFileLoader<array<ref alpProtectionItem>>.JsonLoadFile(ALP_MISSIONSYSTEM_PROTECTION, alp_ProtectionBonuses);
				
			MapProtectionConfig(alp_ProtectionBonuses);							
			
			// Carregamento de Listas de Missões, Loot e Veículos
			if (!FileExist(ALP_MISSIONS_FOLDER)) MakeDirectory(ALP_MISSIONS_FOLDER);
			alp_List = new alpMissionList();
			JsonFileLoader<autoptr alpMissionList>.JsonLoadFile(ALP_MISSIONSYSTEM_FILE, alp_List);	
			
			alp_MissionRegistr = new alpMissionPosition;
			
			array<ref alpLoot> loots;			
			JsonFileLoader<array<ref alpLoot>>.JsonLoadFile(ALP_MISSIONSYSTEM_LOOT, loots);	
			alp_LootMap = new map<string, ref alpLoot>;	
			if (loots) {
				foreach (alpLoot loot : loots) alp_LootMap.Insert(loot.title, loot);
			}

			array<ref alpVehicles> vehicles;	
			JsonFileLoader<array<ref alpVehicles>>.JsonLoadFile(ALP_MISSIONSYSTEM_VEHICLES, vehicles);		
			alp_VehiclesMap = new map<string, ref alpVehicles>;	
			if (vehicles) {
				foreach (alpVehicles vehicle : vehicles) alp_VehiclesMap.Insert(vehicle.title, vehicle);
			}
			
			// Trader Core Init
			if (!FileExist(ALP_MISSIONS_TRADER_FOLDER)) MakeDirectory(ALP_MISSIONS_TRADER_FOLDER);
			JsonFileLoader<autoptr alpOptionsMStrader>.JsonLoadFile(ALP_MISSIONS_TRADER_FILE, alp_optionsMStrader);	
			if (!alp_optionsMStrader) alp_optionsMStrader = new alpOptionsMStrader();
		}	
		
		if (GetGame().IsClient())
		{
			alp_optionsMSradiation = new alpOptionsMSradiation();
			alp_optionsMStrader    = new alpOptionsMStrader();			
		}			
	}

	// --- Gerenciamento de Ciclo de Vida (Update) ---

	override void OnUpdate(float timeslice) 
	{
		alp_UpdateTime += timeslice;

		if (GetGame().IsServer())
		{
			// Ticks de 3 segundos para missões (Economia de CPU)
			if (alp_UpdateTime > 3)
			{
				GetHourMinuteSecondUTC(alp_Hour, alp_Minute, alp_Second);
				foreach(alpMission mission : alp_Missions)
				{
					mission.ManageMission(alp_UpdateTime);
				}	
				alp_UpdateTime = 0;
			}
		}
		
		if (GetGame().IsClient())
		{
			// Ticks de 1 segundo para detecção de proximidade (UI/Mapa)
			if (alp_UpdateTime > 1)
			{
				foreach(alpMission missionClient : alp_Missions)
				{
					if (missionClient) missionClient.ClientTouch(alp_UpdateTime);
				}	
				alp_UpdateTime = 0;				
			}
			
			// Tick rápido (0.2s) para radiação local
			alp_TickCheckRadiation += timeslice;
			if (alp_TickCheckRadiation > 0.2)
			{
				PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());			
				if (player) player.GetRP().SetLocalRadiation();
				alp_TickCheckRadiation = 0;
			}
		}	
	}

	// --- Métodos de Auxílio e Estatísticas ---

	static int GetCurrentTime() 
	{
		// Cálculo do Timestamp em segundos para sincronização de eventos
		return (alp_Hour * 3600) + (alp_Minute * 60) + alp_Second;
	}

	static void AddVehicleToStat(string name)
	{
		CarsCount++;
		int count;
		if (VehicleTypes.Find(name, count)) count += 1;
		else count = 1;
		VehicleTypes.Set(name, count);
	}

	static void RemoveVehicleFromStat(string name)
	{
		CarsCount--;
		int count;
		if (VehicleTypes.Find(name, count)) {
			count -= 1; // Corrigido para reduzir o tipo específico
			VehicleTypes.Set(name, count);					
		} 
	}
}