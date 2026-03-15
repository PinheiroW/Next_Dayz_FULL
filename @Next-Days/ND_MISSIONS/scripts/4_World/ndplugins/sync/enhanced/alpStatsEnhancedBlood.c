/**
 * alpStatsEnhancedBlood.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o nível percentual de sangue do jogador de forma otimizada.
 */

class alpStatsEnhancedBlood extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Vincula o objeto ao jogador e define o tipo de estatística.
	 */
	void alpStatsEnhancedBlood(PlayerBase player)
	{
		// alp_Player é inicializado na classe base alpStatsBaseEnhanced
		alp_Type = alpRPelementsEnahnced.BLOOD;
	}

	/**
	 * Calcula o valor atual no servidor.
	 * Retorna true apenas se o valor mudou em relação à última verificação.
	 */
	override protected bool GetValueServer(out float value)
	{
		if (!alp_Player) return false;

		// Calcula a porcentagem de sangue (0.0 - 100.0)
		float currentBlood = alp_Player.GetHealth("", "Blood");
		float maxBlood     = alp_Player.GetMaxHealth("", "Blood");
		
		alp_Value = (currentBlood / maxBlood) * 100;
		
		// Verificação de alteração para otimização de sincronização
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Valor permanece o mesmo, nenhuma atualização necessária
		value = alp_LastValue;
		return false;
	}

	/**
	 * Identifica esta estatística como sendo vinculada diretamente ao estado do jogador.
	 */
	override bool IsPlayerStats()
	{
		return true;
	}	
}