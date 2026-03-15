/**
 * alpStatsEnhancedHealth.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o nível percentual de saúde global do jogador.
 */

class alpStatsEnhancedHealth extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada à saúde global.
	 */
	void alpStatsEnhancedHealth(PlayerBase player)
	{
		// alp_Type define o destino dos dados na HUD (Barra de Vida Principal)
		alp_Type = alpRPelementsEnahnced.HEALTH;
	}

	/**
	 * Calcula o valor de saúde global no servidor.
	 * Retorna true se houver alteração para disparar a sincronização RPC.
	 */
	override protected bool GetValueServer(out float value)
	{
		if (!alp_Player) return false;

		// Converte saúde absoluta em escala percentual (0.0 - 100.0)
		float currentHealth = alp_Player.GetHealth("GlobalHealth", "Health");
		float maxHealth     = alp_Player.GetMaxHealth("GlobalHealth", "Health");
		
		alp_Value = (currentHealth / maxHealth) * 100;
		
		// Otimização: Apenas sincroniza se o valor mudou desde o último tick
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Valor inalterado, mantém o cache e evita tráfego de rede
		value = alp_LastValue;
		return false;
	}

	/**
	 * Define que esta estatística pertence ao personagem do jogador.
	 */
	override bool IsPlayerStats()
	{
		return true;
	}	
}