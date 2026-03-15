/**
 * alpStatsBase.c
 * * SYNC SYSTEM BASE - Módulo ND_MISSIONS (Sync)
 * Define a estrutura fundamental para estatísticas sincronizadas via bitmask.
 */

/**
 * Identificadores únicos para cada elemento de sincronização de Roleplay.
 * A ORDEM NESTE ENUM É CRÍTICA PARA A INTEGRIDADE DOS DADOS.
 */
enum alpRPelements
{
	STAMINA,
	RAD_RESIST,
	TOXIC_RESIST,
	REPUTATION,
	REPUTATION_ROLE,
	HUNTING,
	ISINTRADERZONE,
	ISALLOWDAMAGE,
	ISRAINED,
	DISEASES,	
	TDCY_TIREDNESS,
	COUNT
}

class alpStatsBase
{
	// --- Variáveis de Estado e Configuração ---
	protected int        alp_Value;    // Valor atual da estatística
	protected int        alp_Range;    // Intervalo/Escala (se aplicável)
	protected int        alp_Type;     // Tipo vinculado ao enum alpRPelements
	protected int        NUM_OF_BITS;  // Quantidade de bits ocupados na rede
	protected PlayerBase alp_Player;   // Referência ao jogador dono da estatística

	// --- Inicialização ---

	void alpStatsBase(PlayerBase player)
	{
		alp_Player = player;
	}

	/**
	 * Método virtual para ser sobrescrito pelas classes filhas.
	 * Responsável por buscar o dado atualizado no motor do jogo ou componentes de RP.
	 */
	void Update()
	{
	}

	// --- Getters e Setters ---

	int GetType()
	{
		return alp_Type;
	}

	int GetNumberOfBits()
	{
		return NUM_OF_BITS;
	}	

	void SetValue(int value)
	{
		alp_Value = value;
	}	

	/**
	 * Retorna o valor da estatística.
	 * No servidor, gatilha uma atualização forçada antes de retornar.
	 */
	int GetValue()
	{
		if ( GetGame() && GetGame().IsServer() )
		{
			Update();
		}
		
		return alp_Value;
	}

	int GetRange()
	{
		return alp_Range;
	}

	// --- Lógica de Rede (Bitmask) ---

	/**
	 * Calcula a máscara de bits necessária para extrair ou injetar o valor na rede.
	 * Ex: 1 bit = 0x1, 8 bits = 0xFF.
	 */
	int GetCompareMask()
	{
		// Fórmula: (2^n) - 1
		int mask = Math.Pow(2, GetNumberOfBits()) - 1;
		return mask;
	}	
}