/**
 * alpPlayerStoreValues.c
 * * HIVE DATA STRUCTURE - Módulo ND_MISSIONS
 * Define os campos que são salvos no arquivo JSON de cada jogador.
 */

class alpStoreValues
{
	// Identificação do Jogador
	string Name;
	string GUID;
	int    PlayerID;
	
	// Status de Eventos e Missões
	int    Event;

	/**
	 * Construtor para garantir a inicialização limpa dos dados.
	 */
	void alpStoreValues()
	{
		Name     = "";
		GUID     = "";
		PlayerID = 0;
		Event    = 0;
	}

	// Nota: BankBalance foi removido desta estrutura para ser gerenciado 
	// exclusivamente pelo sistema alpBANK, garantindo maior segurança.
}