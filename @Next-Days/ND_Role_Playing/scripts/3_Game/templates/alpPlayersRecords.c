/**
 * @class   alpPlayerRecords
 * @brief   Estrutura de dados para estatísticas persistentes do jogador
 * Auditado em: 2024 - Foco em Integridade de Dados e Persistência
 */
class alpPlayerRecords
{
	// Versão da estrutura de dados do registro
	int DataVersion = 1;

	string GUID;
	string Name;
	float  Reputation;
	
	int    KilledPlayers;
	int    SkinnedPlayers;
	int    KilledZombies;
	int    KilledAnimals;

	// Construtor para inicialização segura
	void alpPlayerRecords(string id = "", string name = "", float rep = 0)
	{
		GUID = id;
		Name = name;
		Reputation = rep;
		
		// Inicialização explícita de contadores
		KilledPlayers = 0;
		SkinnedPlayers = 0;
		KilledZombies = 0;
		KilledAnimals = 0;
	}
}