/**
 * alpPluginBase.c
 * * CLASSE BASE DE PLUGINS - Módulo ND_MISSIONS
 * Define a estrutura fundamental para módulos, gerenciamento de eventos e callbacks de rede.
 */

// IDs únicos para identificação dos módulos no Core
enum alpPLUGIN_BASE_ID
{	
	OPTIONS    = 1,   // Configurações principais
	NOTF       = 2,   // Notificações
	INFO       = 4,   // Informações/Sites
	RP         = 8,   // Roleplay
	MS         = 16,  // Mission System 
	RESOURCES  = 32,  // Poços e Postos
	CLANS      = 64,  // Clans e Base Building
	CREATURES  = 128  // Animais e Criaturas
}; // Adicionado ponto e vírgula

// Flags de Eventos para registro no ciclo de vida
enum alpPLUGIN_BASE_EVENTS
{
	START        = 1,
	UPDATE       = 2,
	FINISH       = 4,
	ONCONNECT    = 8,
	ONSPAWN      = 16,
	ONDEATH      = 32,
	ONDISCONNECT = 64,
	ONRECONNECT  = 128
}; // Adicionado ponto e vírgula

// Classe de suporte para chamadas de função sincronizadas
class alpSyncItemCall
{
	Class  alp_Adresa;
	string alp_Function;
	
	void alpSyncItemCall(Class callBack, string function)
	{
		alp_Adresa = callBack;	
		alp_Function = function;
	}
	
	void Run()
	{
		if (alp_Adresa)
		{
			GetGame().GameScript.CallFunction(alp_Adresa, alp_Function, null, null);
		}
	}
}

class alpPluginBase 
{
	protected int alp_ID;
	protected bool alp_DataInitCompleted;
	protected int alp_RegisteredEvents;
	
	// CORREÇÃO: ref em vez de autoptr
	protected ref array<ref alpSyncItemCall> alp_CallsOnConnect;

	void alpPluginBase(int id)
	{
		alp_ID = id;
		Init();
	}

	void RegisterEvent(int event)
	{
		alp_RegisteredEvents = alp_RegisteredEvents | event;
	}

	void UnRegisterEvent(int event)
	{
		alp_RegisteredEvents = alp_RegisteredEvents & ~event;
	}

	bool IsEvent(int event)
	{
		return (alp_RegisteredEvents & event);
	}

	void AddCallBackOnConnect(Class callBack, string function)
	{
		if (!alp_CallsOnConnect) 
			alp_CallsOnConnect = new array<ref alpSyncItemCall>;
		
		alp_CallsOnConnect.Insert(new alpSyncItemCall(callBack, function));
	}

	void RunCallBackOnConnect()
	{
		if (alp_CallsOnConnect)
		{
			for (int i = 0; i < alp_CallsOnConnect.Count(); i++)
			{
				alpSyncItemCall call = alp_CallsOnConnect.Get(i);
				// CORREÇÃO: Verificação de segurança contra Null Pointer
				if (call)
				{
					call.Run();
				}
			}
			alp_CallsOnConnect.Clear();
		} 
	}

	// Métodos virtuais para serem sobrescritos
	void Init() {}
	void OnUpdate(float timeslice) {}
	void OnRPC(PlayerBase player, int rpc_type, ParamsReadContext ctx) {}
	void ReadInitRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx) {}	
	void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx) {}

	// Getters de estado de evento
	bool IsEventStart() { return alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.START; }
	bool IsEventUpdate() { return alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.UPDATE; }	
	bool IsEventFinish() { return alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.FINISH; }	
	bool IsEventOnConnect() { return alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONCONNECT; }	
	bool IsEventOnSpawn() { return alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONSPAWN; }	
	bool IsEventOnDeath() { return alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONDEATH; }	
}