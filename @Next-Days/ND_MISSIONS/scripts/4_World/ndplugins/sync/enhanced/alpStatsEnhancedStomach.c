/**
 * alpStatsEnhancedStomach.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza o volume percentual do estômago do jogador.
 */

class alpStatsEnhancedStomach extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada ao volume gástrico.
	 */
	void alpStatsEnhancedStomach(PlayerBase player)
	{
		// alp_Type define o destino dos dados na HUD (Ícone de Estômago/Digestão)
		alp_Type = alpRPelementsEnahnced.STOMACH;
	}

	/**
	 * Calcula o preenchimento do estômago no servidor.
	 * Retorna true se houver alteração significativa para disparo da sincronização RPC.
	 */
	override protected bool GetValueServer(out float value)
	{
		// Verificação de segurança para o objeto do jogador e componente de estômago
		if (!alp_Player || !alp_Player.m_PlayerStomach) 
			return false;

		// Converte volume bruto em escala percentual baseada no limite máximo (LVL3)
		// BT_STOMACH_VOLUME_LVL3 é a constante nativa do DayZ para estômago cheio
		alp_Value = (alp_Player.m_PlayerStomach.GetStomachVolume() / PlayerConstants.BT_STOMACH_VOLUME_LVL3) * 100;
		
		// Otimização: Sincroniza apenas se o volume mudou desde o último tick
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		
		// Valor inalterado, mantém o cache e evita tráfego desnecessário
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