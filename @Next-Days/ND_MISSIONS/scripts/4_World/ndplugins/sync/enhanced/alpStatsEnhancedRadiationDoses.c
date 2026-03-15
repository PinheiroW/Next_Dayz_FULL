/**
 * alpStatsEnhancedRadiationDoses.c
 * * ENHANCED STAT SYSTEM - Módulo ND_MISSIONS
 * Monitora e sincroniza a carga radiológica acumulada no jogador.
 */

class alpStatsEnhancedRadiationDoses extends alpStatsBaseEnhanced
{
	/**
	 * Construtor: Inicializa a estatística vinculada às doses de radiação.
	 */
	void alpStatsEnhancedRadiationDoses(PlayerBase player)
	{
		// alp_Type define o destino dos dados na HUD (Contador de Doses)
		alp_Type = alpRPelementsEnahnced.RADIATIONDOSES;
	}

	/**
	 * Calcula o valor das doses acumuladas no servidor.
	 * Requer um dosímetro ativo para realizar a leitura e sincronização.
	 */
	override protected bool GetValueServer(out float value)
	{
		// Verificação de segurança: O jogador precisa ter um dosímetro para ver as doses
		if (alp_Player && alp_Player.GetRP() && alp_Player.GetRP().HasDosimeter())
		{
			// Obtém o total de radiação recebida pelo organismo
			alp_Value = (float) alp_Player.GetRP().GetRecievedRadiation();
			
			// Otimização: Sincroniza apenas se a dose acumulada mudou
			if (alp_Value != alp_LastValue)
			{
				alp_LastValue = alp_Value;
				value = alp_Value;
				return true;
			}
		}
		
		// Se não houver dosímetro ou não houver alteração, mantém o último valor e não sincroniza
		value = alp_LastValue;
		return false;
	}

	/**
	 * Identifica esta estatística como pertencente ao sistema de radiação.
	 */
	override bool IsRadiationStats()
	{
		return true;
	}
}