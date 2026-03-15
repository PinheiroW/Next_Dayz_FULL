/**
 * alpPluginNDresources.c
 * * RESOURCE INFRASTRUCTURE PLUGIN - Módulo ND_MISSIONS (Resources)
 * Gerencia a configuração global de poços de água e postos de combustível.
 */

class alpPluginNDresources extends alpPlugin
{
	protected ref alpResourcesSetting alp_ResourcesSetting;

	// --- Ciclo de Vida e Limpeza ---

	void ~alpPluginNDresources()
	{
		delete alp_ResourcesSetting;					
	}

	override void Init() 
	{
		// Lógica Lado Servidor: Preparação de Arquivos e Pastas
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{
			// Criação de diretórios base para persistência de recursos
			if (!FileExist(ALP_RESOURCES_FOLDER)) MakeDirectory(ALP_RESOURCES_FOLDER);	
			if (!FileExist(ALP_WELLS_FOLDER))     MakeDirectory(ALP_WELLS_FOLDER);	
			if (!FileExist(ALP_FUELS_FOLDER))     MakeDirectory(ALP_FUELS_FOLDER);	

			// Carregamento do arquivo de configuração JSON
			JsonFileLoader<alpResourcesSetting>.JsonLoadFile(ALP_RESOURCES_FILE, alp_ResourcesSetting);		
			
			if (!alp_ResourcesSetting)			
			{
				alp_ResourcesSetting = new alpResourcesSetting();
				JsonFileLoader<alpResourcesSetting>.JsonSaveFile(ALP_RESOURCES_FILE, alp_ResourcesSetting);				
			}
		}	
	}

	// --- Sincronização RPC (Network) ---

	/**
	 * Disparado quando um jogador se conecta para sincronizar as configurações de recursos.
	 */
	override void OnConnectManaged(PlayerBase player)
	{	
		ScriptRPC rpc = GetND().GetInitRPC(GetID());					
		WriteOnConnectRPC(rpc);
		GetND().SendGameRPC(rpc, player);
	}	
	
	/**
	 * Escreve os dados de configuração no buffer RPC.
	 */
	void WriteOnConnectRPC(ref ScriptRPC rpc)
	{
		rpc.Write(alp_ResourcesSetting);
	}
	
	/**
	 * Lógica Lado Cliente: Recebe e aplica as configurações do servidor.
	 */
	override void ReadInitRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		ctx.Read(alp_ResourcesSetting);		
	}		

	// --- Getters de Configuração ---

	/**
	 * Retorna as opções gerais de recursos.
	 */
	alpResourcesSetting GetOptions()
	{
		return alp_ResourcesSetting;
	}

	/**
	 * Retorna as configurações padrão para poços de água.
	 */
	alpDefaultWellsSetting GetDefaultWell()
	{
		return (alp_ResourcesSetting) ? alp_ResourcesSetting.Wells : null;
	}

	/**
	 * Retorna as configurações padrão para postos de combustível.
	 */
	alpDefaultFuelstationSetting GetDefaultFuelstations()
	{
		return (alp_ResourcesSetting) ? alp_ResourcesSetting.Fuelstations : null;
	}
}