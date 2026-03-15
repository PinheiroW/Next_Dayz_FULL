/**
 * alpNDbase.c
 * * NÚCLEO DE GERENCIAMENTO (CORE) - Módulo ND_MISSIONS
 * Gerencia o ciclo de vida de plugins, sincronização de tempo e persistência global.
 */

ref alpND_base alp_ND_base;

// Singleton Accessor
alpND_base GetGameND()
{
	if (!alp_ND_base)
	{
		alp_ND_base = new alpND_base();
	}
	return alp_ND_base;
}

class alpND_base 
{
	// --- INSTÂNCIA E VARIÁVEIS ---
	string alp_CLIENT_DATA = "$profile:next-days.json";
	int m_ServerTimeDelta;

	static ref array<string> alp_PlayerRegister;
	static ref map<int, int> RegisteredPrivateMissions = new map<int, int>;
	
	protected bool alp_IsVersionValid;
	protected bool alp_IsFirstServerRun;	
	protected ref alpPlayersID alp_PlayersID;
	
	// Plugins Containers
	protected ref map<int, ref alpPluginBase> alp_ActivePlugins;	
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_START;				
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_UPDATE;				
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_FINISH;	
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONCONNECT;
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONRPC;

	// Missions & Quests
	protected ref array<ref alpMissionBase> alp_RegisteredMissions;
	protected ref map<string, ref alpOptionsMS_templates> alp_RegisteredMissionsTemplate;
	protected ref array<ref alpRegisteredQuest> alp_ActiveQuests;

	void alpND_base()
	{
		alp_ActivePlugins 				= new map<int, ref alpPluginBase>;
		alp_RegPlugins_EVENT_START 		= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_UPDATE 	= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_FINISH 	= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONCONNECT 	= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONRPC 		= new array<ref alpPluginBase>;
		
		alp_RegisteredMissions 			= new array<ref alpMissionBase>;
		alp_RegisteredMissionsTemplate 	= new map<string, ref alpOptionsMS_templates>;
		alp_ActiveQuests 				= new array<ref alpRegisteredQuest>;
	}

	// --- GERENCIAMENTO DE PLUGINS ---

	void RegisterPlugin(alpPluginBase plugin, int id)
	{
		if (plugin)
		{
			alp_ActivePlugins.Set(id, plugin);
			if (plugin.IsEvent(alpPluginEvent.START)) 		alp_RegPlugins_EVENT_START.Insert(plugin);
			if (plugin.IsEvent(alpPluginEvent.UPDATE)) 		alp_RegPlugins_EVENT_UPDATE.Insert(plugin);
			if (plugin.IsEvent(alpPluginEvent.FINISH)) 		alp_RegPlugins_EVENT_FINISH.Insert(plugin);
			if (plugin.IsEvent(alpPluginEvent.ONCONNECT)) 	alp_RegPlugins_EVENT_ONCONNECT.Insert(plugin);
			if (plugin.IsEvent(alpPluginEvent.ONRPC)) 		alp_RegPlugins_EVENT_ONRPC.Insert(plugin);
		}
	}

	// OTIMIZAÇÃO: Getters com verificação de segurança
	alpPluginNDnotf GetPluginNotf() {
		if (alp_ActivePlugins.Contains(ALP_RPC_PLUGIN_NOTF))
			return alpPluginNDnotf.Cast(alp_ActivePlugins.Get(ALP_RPC_PLUGIN_NOTF));
		return null;
	}

	alpPluginNDmissionsSystem GetPluginMS() {
		if (alp_ActivePlugins.Contains(ALP_RPC_GAME))
			return alpPluginNDmissionsSystem.Cast(alp_ActivePlugins.Get(ALP_RPC_GAME));
		return null;
	}

	// --- CICLO DE VIDA (EVENTS) ---

	void OnUpdate(float timeslice)
	{
		foreach (alpPluginBase plugin : alp_RegPlugins_EVENT_UPDATE)
		{
			if (plugin) plugin.OnUpdate(timeslice);
		}
	}

	void OnRPC(PlayerBase player, int rpc_type, ParamsReadContext ctx)
	{
		foreach (alpPluginBase plugin : alp_RegPlugins_EVENT_ONRPC)
		{
			if (plugin) plugin.OnRPC(player, rpc_type, ctx);
		}
	}

	// --- SISTEMA DE TEMPO E PERSISTÊNCIA ---

	int GetTimeStamp()
	{
		if (!GetGame()) return 0;
		int time = GetGame().GetTime();
		if (GetGame().IsClient())
		{
			time += m_ServerTimeDelta;
		}
		return time;
	}

	void SetServerTimeDelta(int time) 
	{
		if (GetGame())
			m_ServerTimeDelta = time - GetGame().GetTime();
	}

	void SaveRegisteredPrivateMissions()
	{
		alpClientData data = new alpClientData(GetTimeStamp()); // CORREÇÃO: Uso de GetTimeStamp unificado
		data.RegisteredPrivateMissions = RegisteredPrivateMissions;		
		JsonFileLoader<alpClientData>.JsonSaveFile(alp_CLIENT_DATA, data);
	}

	void LoadRegisteredPrivateMissions()
	{
		// CORREÇÃO: Lógica de existência de arquivo corrigida (!FileExist -> FileExist)
		if (FileExist(alp_CLIENT_DATA)) 
		{ 	
			alpClientData data;					
			JsonFileLoader<alpClientData>.JsonLoadFile(alp_CLIENT_DATA, data);

			if (data) 
			{
				int actualdate = GetTimeStamp() - 1;
				int saveddate = data.date;
				
				// Se o arquivo for do mesmo ciclo (restart), carrega as missões
				if (actualdate <= saveddate)
				{
					RegisteredPrivateMissions = data.RegisteredPrivateMissions;
				}
			}
		}
	}

	// --- QUESTS E MISSÕES ---

	int GetActiveQuestCurrency(int npc)
	{
		int questID = -1;
		if (alp_ActiveQuests)
		{
			for (int i = 0; i < alp_ActiveQuests.Count(); i++)
			{								
				if (alp_ActiveQuests.Get(i) && alp_ActiveQuests.Get(i).NPC == npc)
				{
					questID = alp_ActiveQuests.Get(i).CurrencyID;
					break;
				}
			}			
		}		
		return questID;
	}
}