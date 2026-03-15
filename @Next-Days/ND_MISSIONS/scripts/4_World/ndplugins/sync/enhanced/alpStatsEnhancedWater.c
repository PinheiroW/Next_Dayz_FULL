/**
 * alpStatsEnhancedWater.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o nível percentual de hidratação (água) do jogador.
 */

class alpStatsEnhancedWater extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada à hidratação.
	 */
	void alpStatsEnhancedWater(PlayerBase player)
	{
		// alp_Type define o destino dos dados na HUD (Ícone de Água/Sede)
		alp_Type = alpRPelementsEnahnced.WATER;
	}

	/**
	 * Calcula o valor de hidratação no servidor.
	 * Retorna true se houver alteração para disparar a sincronização RPC.
	 */
	override protected bool GetValueServer(out float value)
	{
		// Verificação de segurança para o objeto do jogador
		if (!alp_Player) return false;

		// Converte o valor bruto de água em escala percentual (0.0 - 100.0)
		alp_Value = (alp_Player.GetStatWater().Get() / alp_Player.GetStatWater().GetMax()) * 100;
		
		// Otimização: Sincroniza apenas se o valor mudou desde o último tick
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Valor inalterado, mantém cache e evita tráfego de rede
		value = alp_LastValue;
		return false;
	}

	/**
	 * Define que esta estatística pertence ao conjunto de atributos vitais do jogador.
	 */
	override bool IsPlayerStats()
	{
		return true;
	}	
}