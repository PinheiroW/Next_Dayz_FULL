/**
 * alpStatsEnhancedTraderBalance.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o saldo do jogador no sistema de Trader.
 */

class alpStatsEnhancedTraderBalance extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada ao saldo do Trader.
	 */
	void alpStatsEnhancedTraderBalance(PlayerBase player)
	{
		// alp_Type define o destino dos dados na interface do Trader
		alp_Type = alpRPelementsEnahnced.TRADER_BALANCE;
	}

	/**
	 * Obtém o valor do saldo do Trader no servidor.
	 * Retorna true se houver alteração significativa para disparo da sincronização RPC.
	 */
	override protected bool GetValueServer(out float value)
	{
		// Verificação de segurança para o objeto do jogador e o sistema de Trader
		if (!alp_Player || !GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader()) 
			return false;

		// Obtém o saldo atualizado do jogador no sistema de Trader
		alp_Value = (float) GetND().GetMS().GetTrader().GetTraderBalance(alp_Player);
		
		// Otimização: Sincroniza apenas se o saldo mudou desde o último tick
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Valor inalterado, mantém o cache e evita o uso desnecessário da rede
		value = alp_LastValue;
		return false;
	}

	/**
	 * Define que esta estatística pertence exclusivamente ao contexto de comércio.
	 */
	override bool IsTraderStats()
	{
		return true;
	}	
}