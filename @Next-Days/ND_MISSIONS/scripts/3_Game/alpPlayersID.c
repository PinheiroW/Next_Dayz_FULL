/**
 * alpPlayersID.c
 * * GERENCIADOR DE IDENTIDADES (IDs) - Módulo ND_MISSIONS
 * Garante a atribuição de um ID numérico único e sequencial para cada novo jogador.
 */

class alpPlayersID 
{
	int LAST_PLAYER_ID;
	
	void alpPlayersID()
	{
		// CORREÇÃO: Garante que as pastas existam antes de manipular o arquivo
		if (!FileExist(ALP_RP_FOLDER_ID))
		{
			MakeDirectory(ALP_RP_FOLDER_ID);
		}

		if (!FileExist(ALP_RP_FOLDER_ID_JSON))
		{
			LAST_PLAYER_ID = 0;
			Save(); // Cria o arquivo inicial
		}
		else
		{
			// Carrega os dados existentes do arquivo para a instância atual
			JsonFileLoader<alpPlayersID>.JsonLoadFile(ALP_RP_FOLDER_ID_JSON, this);
		}
	}
	
	int GetPlayerID()
	{
		LAST_PLAYER_ID++;
		Save();
		return LAST_PLAYER_ID;
	}
	
	void Save()
	{
		// Proteção simples: só salva se o caminho estiver definido
		if (ALP_RP_FOLDER_ID_JSON != "")
		{
			JsonFileLoader<alpPlayersID>.JsonSaveFile(ALP_RP_FOLDER_ID_JSON, this);
		}
	}
}; // Adicionado ponto e vírgula obrigatório