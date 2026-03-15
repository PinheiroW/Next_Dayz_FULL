/**
 * alpStatsEnhancedFood.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o nível percentual de energia (comida) do jogador.
 */

class alpStatsEnhancedFood extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada à energia/comida.
	 */
	void alpStatsEnhancedFood(PlayerBase player)
	{
		// alp_Type define o destino dos dados na HUD (Ícone de Comida)
		alp_Type = alpRPelementsEnahnced.FOOD;
	}

	/**
	 * Calcula o valor de energia no servidor.
	 * Retorna true se houver alteração significativa para disparo de sincronização.
	 */
	override protected bool GetValueServer(out float value)
	{
		if (!alp_Player) return false;

		// Converte calorias brutas em escala percentual (0.0 - 100.0)
		float currentEnergy = alp_Player.GetStatEnergy().Get();
		float maxEnergy     = alp_Player.GetStatEnergy().GetMax();
		
		alp_Value = (currentEnergy / maxEnergy) * 100;
		
		// Otimização: Apenas sincroniza se o valor mudou desde o último tick
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Sem alteração, mantém o valor antigo e evita tráfego de rede
		value = alp_LastValue;
		return false;
	}

	/**
	 * Define que esta estatística é inerente ao personagem do jogador.
	 */
	override bool IsPlayerStats()
	{
		return true;
	}	
}