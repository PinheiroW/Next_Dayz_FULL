/**
 * alpRPGplugin.c
 * * RP SYSTEM PLUGIN - Módulo ND_MISSIONS (RP)
 * Gerencia opções de Roleplay para jogadores, veículos e integração econômica.
 */

class alpPluginNDrp extends alpPlugin
{
	// --- Configurações e Opções ---
	protected ref alpOptionsRP_Players alp_OptionsRP_Players;
	protected ref alpOptionsRP_Vehicles alp_OptionsRP_Vehicles;

	// --- Comportamento de Veículos ---
	protected ref array<ref alpVehicleBehavior> alp_OptionsRP_Vehicles_Behavior;
	protected ref map<string, ref alpVehicleBehavior> alp_OptionsRP_Vehicles_BehaviorMaped;

	// --- Limpeza de Memória ---

	void ~alpPluginNDrp()
	{
		delete alp_OptionsRP_Players;
		delete alp_OptionsRP_Vehicles;
		delete alp_OptionsRP_Vehicles_Behavior;
		delete alp_OptionsRP_Vehicles_BehaviorMaped;					
	}	

	// --- Inicialização do Plugin ---

	override void Init() 
	{
		alp_OptionsRP_Players = new alpOptionsRP_Players;
		alp_OptionsRP_Vehicles = new alpOptionsRP_Vehicles;
		alp_OptionsRP_Vehicles_BehaviorMaped = new map<string, ref alpVehicleBehavior>;		
		
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{
			if (!FileExist(ALP_RP_FOLDER)) MakeDirectory(ALP_RP_FOLDER);	
			
			// 1. Carregamento de Configurações de Jogadores
			if (!FileExist(ALP_RP_PLAYERS_FILE))
				JsonFileLoader<alpOptionsRP_Players>.JsonSaveFile(ALP_RP_PLAYERS_FILE, alp_OptionsRP_Players);
			else 
				JsonFileLoader<alpOptionsRP_Players>.JsonLoadFile(ALP_RP_PLAYERS_FILE, alp_OptionsRP_Players);
			
			// 2. Carregamento de Configurações Gerais de Veículos
			if (!FileExist(ALP_RP_VEHICLES_FILE))
				JsonFileLoader<alpOptionsRP_Vehicles>.JsonSaveFile(ALP_RP_VEHICLES_FILE, alp_OptionsRP_Vehicles);
			else 
				JsonFileLoader<alpOptionsRP_Vehicles>.JsonLoadFile(ALP_RP_VEHICLES_FILE, alp_OptionsRP_Vehicles);
				
			// 3. Gerenciamento de Propriedades Específicas de Veículos (Behavior)
			if (!FileExist(ALP_RP_VEHICLES_SETTINGS_FILE))
			{ 
				alp_OptionsRP_Vehicles_Behavior = new array<ref alpVehicleBehavior>;
				
				if (GetVehicleOptions().InitVehiclesProperties)
				{
					InitVehiclesProperties(alp_OptionsRP_Vehicles_Behavior);
				}
				JsonFileLoader<array<ref alpVehicleBehavior>>.JsonSaveFile(ALP_RP_VEHICLES_SETTINGS_FILE, alp_OptionsRP_Vehicles_Behavior);
			}
			else 
			{
				JsonFileLoader<array<ref alpVehicleBehavior>>.JsonLoadFile(ALP_RP_VEHICLES_SETTINGS_FILE, alp_OptionsRP_Vehicles_Behavior);	
			}

			// Mapeia os comportamentos para busca rápida
			for (int i = 0; i < alp_OptionsRP_Vehicles_Behavior.Count(); i++)
			{
				alpVehicleBehavior vehicle = alp_OptionsRP_Vehicles_Behavior.Get(i);
				if (vehicle)
				{
					alp_OptionsRP_Vehicles_BehaviorMaped.Set(vehicle.Name, vehicle);
				}
			}	
		}	
	}

	// --- Sincronização e Conexão (RPC) ---

	override void OnConnectManaged(PlayerBase player)
	{	
		ScriptRPC rpc = GetND().GetInitRPC(GetID());					
		WriteOnConnectRPC(rpc);
		GetND().SendGameRPC(rpc, player);
	}	
	
	void WriteOnConnectRPC(ref ScriptRPC rpc)
	{
		rpc.Write(alp_OptionsRP_Players);
		rpc.Write(alp_OptionsRP_Vehicles);
	}
	
	override void OnSpawnManaged(PlayerBase player)
	{
		// Carrega dados persistentes (RPG stats)
		player.LoadPlayerHive();
		
		// Inicializa conta bancária
		alpBANK.SetBankAccountOnConnect(player);		
	}
	
	override void ReadInitRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		ctx.Read(alp_OptionsRP_Players);		
		ctx.Read(alp_OptionsRP_Vehicles);		
	}	

	// --- Definições Padrão de Veículos ---

	/**
	 * Inicializa propriedades físicas e comportamentais para a frota do servidor.
	 */
	void InitVehiclesProperties(ref array<ref alpVehicleBehavior> properties)
	{
		// Categorias: Nome da Classe, É Blindado, HP, Multiplicadores de Dano, Preços de Seguro/Taxa
		properties.Insert(new alpVehicleBehavior("OffroadHatchback", false, 10000, 0.075, 0.075, 0.075, 150, 750, 3000));
		properties.Insert(new alpVehicleBehavior("CivilianSedan", false, 10000, 0.065, 0.065, 0.065, 150, 750, 3000));
		properties.Insert(new alpVehicleBehavior("Hatchback_02", false, 10000, 0.070, 0.070, 0.070, 150, 750, 3000));
		properties.Insert(new alpVehicleBehavior("Sedan_02", false, 10000, 0.130, 0.130, 0.130, 150, 750, 3000));
		
		// Veículos Especiais / Militares
		properties.Insert(new alpVehicleBehavior("CrSk_Land_Rover_Defender_110", true, 2500, 0.04, 0.02, 0.04, 500, 3000, 10000));
		properties.Insert(new alpVehicleBehavior("Gerph_Zil130", true, 500, 0.01, 0.0, 0.00, 1000, 5000, 10000));	
		properties.Insert(new alpVehicleBehavior("Truck_01_Covered", true, 500, 0.01, 0.0, 0.00, 1000, 5000, 10000));
	}
	
	// --- Getters ---

	alpOptionsRP_Players GetPlayerOptions() { return alp_OptionsRP_Players; }
	
	alpOptionsRP_Vehicles GetVehicleOptions() { return alp_OptionsRP_Vehicles; }
	
	alpVehicleBehavior GetVehicleProperties(string vehicle)
	{
		alpVehicleBehavior car;
		if (alp_OptionsRP_Vehicles_BehaviorMaped && alp_OptionsRP_Vehicles_BehaviorMaped.Find(vehicle, car))
		{
			return car;
		}
		return null;
	}	
}