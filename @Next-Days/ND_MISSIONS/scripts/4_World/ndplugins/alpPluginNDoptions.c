/**
 * alpPluginNDoptions.c
 * * GLOBAL OPTIONS & INITIALIZATION - Módulo ND_MISSIONS
 * Gerencia a inicialização de sistemas globais, como a economia do banco.
 */

class alpPluginNDoptions extends alpPlugin
{
	// Reservado para futuras implementações de configurações globais
	// protected ref alpOptionsND alp_OptionsND;

	/**
	 * Inicializa os componentes globais do servidor.
	 */
	override void Init() 
	{
		// Lógica Lado Servidor
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{	
			// Inicializa o Balanço do Banco (Carregamento de JSONs e Moedas)
			// Crucial para que o sistema de Trader e ATM funcione.
			alpBANK.InitServerSide();
			
			/* Nota: O bloco abaixo está reservado para carregamento de 
			   opções globais customizadas do mod Next-Days.
			*/
			/*
			if (!FileExist(ALP_ROOTFOLDER + ALP_OPTIONS))
			{ 
				alp_OptionsND = new alpOptionsND;
				JsonFileLoader<alpOptionsND>.JsonSaveFile(ALP_ROOTFOLDER + ALP_OPTIONS, alp_OptionsND);
			}
			else 
			{
				JsonFileLoader<alpOptionsND>.JsonLoadFile(ALP_ROOTFOLDER + ALP_OPTIONS, alp_OptionsND);	
			}
			*/
		}
	}
	
	/*
	// --- Sincronização RPC (Reservado) ---

	override void OnConnectManaged(PlayerBase player)
	{	
		if (GetGame().IsServer())
		{	
			ScriptRPC rpc = GetND().GetInitRPC(GetID());					
			rpc.Write(alp_OptionsND);
			GetND().SendGameRPC(rpc, player);
		}
	}	

	override void ReadInitRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		ctx.Read(alp_OptionsND);		
	}	
	
	alpOptionsND GetOptions()
	{
		return alp_OptionsND;
	}	
	*/
}