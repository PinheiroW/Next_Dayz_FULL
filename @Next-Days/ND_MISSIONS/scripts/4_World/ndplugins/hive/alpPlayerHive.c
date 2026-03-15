/**
 * alpPlayerHive.c
 * * HIVE PERSISTENCE SYSTEM - Módulo ND_MISSIONS
 * Gerencia o ciclo de vida dos dados do jogador (Load/Save/Sync) via arquivos JSON.
 */

class alpPlayerHive 
{
	string alp_Guid;
	PlayerBase alp_Player;
	protected ref alpStoreValues alp_StoreValues;
	
	/**
	 * Construtor: Inicializa ou carrega os dados do jogador com base no GUID.
	 */
	void alpPlayerHive(PlayerBase player)
	{
		alp_Player = player;
		
		if (GetGame().IsServer())
		{
			alp_Guid = alp_Player.GetIdentity().GetPlainId();	
			
			// Tenta carregar o arquivo existente
			JsonFileLoader<alpStoreValues>.JsonLoadFile( ALP_RP_FOLDER + alp_Guid + ".json", alp_StoreValues );
			
			// Se o arquivo não existir, cria um novo perfil (Primeiro Acesso)
			if (!alp_StoreValues)
			{
				alp_StoreValues = new alpStoreValues();
				OnFirstConnect();
				Save();
			}
			
			// Garante que o PlayerID esteja sincronizado com a identidade do DayZ
			alp_Player.alp_PlayerID = GetPlayerID();
			alp_Player.GetIdentity().SetPlayerUniqueID( GetPlayerID() );
			
			OnConnect();
			Save();	
		}
		else
		{
			// No lado do cliente, apenas aguarda a sincronização via RPC
			alp_StoreValues = new alpStoreValues();
		}
	}

	// --- Métodos de Persistência ---

	void Save()
	{
		if (GetGame().IsServer() && alp_StoreValues)
		{
			JsonFileLoader<alpStoreValues>.JsonSaveFile( ALP_RP_FOLDER + alp_Guid + ".json", alp_StoreValues );
		}
	}

	void OnConnect()
	{
		// Sincroniza os dados salvos com o cliente assim que a conexão é estabelecida
		SendToClientAll();
	}

	/**
	 * Configurações para o primeiro acesso do jogador no servidor.
	 */
	void OnFirstConnect()
	{
		alp_StoreValues.Name = alp_Player.GetIdentity().GetName();
		alp_StoreValues.GUID = alp_Player.GetIdentity().GetPlainId();		
		alp_StoreValues.PlayerID = GetND().GetNewPlayerID();
		
		// Inicializa a conta bancária
		alpBANK.SetBankAccountOnConnect( alp_Player , alp_StoreValues.PlayerID );	
		
		// Entrega o bônus inicial (Gift) se configurado no sistema
		int gift[3] = GetND().GetMS().GetOptoinsTrader().GiftToNewPlayer;
		if (gift && gift[1] != 0)
		{
			int balance = gift[1];
			if (balance > 0)
			{
				alpBANK.AddBalanceToAccount(alp_StoreValues.PlayerID, gift[0], balance, alp_Player);
			}
		}
	}

	// --- Comunicação RPC ---

	void SendToClientAll()
	{
		// Envia todo o pacote de StoreValues para o cliente do jogador
		GetScriptRPC_allSync().Send(alp_Player, ALP_RPC_PLAYER, true, alp_Player.GetIdentity());
	}

	protected ScriptRPC GetScriptRPC_allSync()
	{
		ScriptRPC rpc = new ScriptRPC();	
		rpc.Write( ALP_RPC_PLAYER_TYPE.HIVE_SYNC_ALL );
		rpc.Write( alp_StoreValues );
		return rpc;
	}

	// --- Getters ---

	alpStoreValues GetStore() { return alp_StoreValues; }
	int GetPlayerID() { return alp_StoreValues.PlayerID; }
	PlayerBase GetPlayer() { return alp_Player; }
}