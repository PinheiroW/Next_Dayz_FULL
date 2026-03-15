/**
 * alpStatsBaseEnhanced.c
 * * ENHANCED SYNC SYSTEM BASE - Módulo ND_MISSIONS (Sync)
 * Classe fundamental para estatísticas de ponto flutuante com detecção de mudança.
 */

/**
 * Identificadores para elementos de sincronização aprimorada.
 * A ORDEM NESTE ENUM DEVE SER PRESERVADA PARA EVITAR ERROS DE COMUNICAÇÃO.
 */
enum alpRPelementsEnahnced
{
	HEALTH,
	BLOOD,
	WATER,
	FOOD,	
	STOMACH,
	
	RADIATIONDOSES,
	FATIGUE,
	
	TEMPERATURE,
	RADIATIONSICKSTAGE,
	
	STAMINAPROGRES,
	RAD_RESISTPROGRES,
	TOXIC_RESISTPROGRES,

	REPUTATIONPROGRES,
	HUNTINGPROGRES,
	SCORE,

	/* Reservado para implementações futuras
	SAVED_STAMINA_LEVEL,
	SAVED_STAMINA_PROGRESS,
	SAVED_RAD_RESIST_LEVEL,
	SAVED_RAD_RESIST_PROGRESS,	
	SAVED_TOXIC_RESIST_LEVEL,
	SAVED_TOXIC_RESIST_PROGRESS,	
	SAVED_REPUTATION_LEVEL,
	SAVED_REPUTATION_PROGRESS,	
	SAVED_HUNTING_LEVEL,
	SAVED_HUNTING_PROGRESS,	
	SAVED_SOFTSKILLS,
	SAVED_HARDSKILLS,
	SAVED_COLDRESIST,
	*/	

	TRADER_BALANCE,
	PLAYER_BALANCE,	
	
	COUNT
}

class alpStatsBaseEnhanced
{
	// --- Variáveis de Estado ---
	protected int        alp_Type;      // ID do enum alpRPelementsEnahnced
	protected float      alp_Value;     // Valor atual
	protected float      alp_LastValue = -99999999; // Valor anterior para detecção de delta
	protected PlayerBase alp_Player;    // Referência ao jogador

	// --- Inicialização ---

	void alpStatsBaseEnhanced(PlayerBase player)
	{
		alp_Player = player;
	}

	// --- Núcleo de Sincronização ---

	/**
	 * Retorna true se o valor atual for diferente do último valor sincronizado.
	 */
	bool GetValue(out float value)
	{
		if ( GetGame() && GetGame().IsServer() )
			return GetValueServer(value);
		else
			return GetValueClient(value);		
	}

	/**
	 * Define o valor local (utilizado principalmente no lado cliente via RPC).
	 */
	void SetValue(float value)
	{
		alp_Value = value;
	}

	/**
	 * Lógica de busca de valor no servidor. Deve ser sobrescrita pelas especializações.
	 */
	protected bool GetValueServer(out float value)
	{
		return false;
	}

	/**
	 * Lógica de detecção de mudança no lado cliente para atualização de UI.
	 */
	protected bool GetValueClient(out float value)
	{
		if ( alp_LastValue != alp_Value )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		value = alp_LastValue;
		return false;
	}

	// --- Getters e Identificação ---

	int GetType()
	{
		return alp_Type;
	}

	/**
	 * Categoriza a estatística como pertencente aos status vitais do jogador.
	 */
	bool IsPlayerStats()
	{
		return false;
	}

	/**
	 * Categoriza a estatística como pertencente ao sistema radiológico.
	 */
	bool IsRadiationStats()
	{
		return false;	
	}

	/**
	 * Categoriza a estatística como pertencente ao contexto de economia/trader.
	 */
	bool IsTraderStats()
	{
		return false;
	}
}