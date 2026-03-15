/**
 * GamePlay.c
 * * EXTENSÃO DE INTERFACE E IDENTIDADE - Módulo ND_MISSIONS
 * Define ganchos para o HUD e armazena metadados únicos do jogador (ID e Reputação).
 */

modded class Hud
{
	// Método stub para ser sobrescrito na camada de interface (5_Mission)
	void SendMessageALP(int type, string text, vector pos = "0 0 0") {}
}; // Adicionado ponto e vírgula obrigatório

modded class PlayerIdentity
{
	// Variáveis de estado para persistência e sincronização de dados do jogador
	int m_PlayerUniqueID;
	int m_PlayerReputationLevel;
	
	void SetPlayerUniqueID(int id)
	{
		m_PlayerUniqueID = id;
	}

	int GetPlayerUniqueID()
	{
		return m_PlayerUniqueID;
	}

	void SetPlayerLevel(int id)
	{
		m_PlayerReputationLevel = id;
	}

	int GetPlayerLevel()
	{
		return m_PlayerReputationLevel;
	}
}; // Adicionado ponto e vírgula obrigatório