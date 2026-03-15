/**
 * alpStatsEnhancedPlayerBalance.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o saldo bancário do jogador de forma otimizada.
 */

class alpStatsEnhancedPlayerBalance extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada ao saldo financeiro.
	 */
	void alpStatsEnhancedPlayerBalance(PlayerBase player)
	{
		// alp_Type define o destino dos dados na HUD (Saldo do Jogador)
		alp_Type = alpRPelementsEnahnced.PLAYER_BALANCE;
	}

	/**
	 * Obtém o valor do saldo bancário no servidor.
	 * Retorna true se houver alteração para disparar a sincronização RPC.
	 */
	override protected bool GetValueServer(out float value)
	{
		// Verificação de segurança para acesso aos componentes de RP e Banco
		if (!alp_Player || !alp_Player.GetRP() || !alp_Player.GetRP().GetCart()) 
			return false;

		// Obtém o saldo atual do banco vinculado ao carrinho do jogador
		alp_Value = (float) alp_Player.GetRP().GetCart().GetBankBalance();
		
		// Otimização: Sincroniza apenas se o saldo mudou desde a última verificação
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Valor inalterado, mantém cache e economiza tráfego de rede
		value = alp_LastValue;
		return false;
	}

	/**
	 * Define que esta estatística é essencial para funcionalidades de comércio (Trader).
	 */
	override bool IsTraderStats()
	{
		return true;
	}	
}