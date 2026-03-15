/**
 * alpStatsIsRained.c
 * * STAT SYNC COMPONENT - Módulo ND_MISSIONS (Sync)
 * Monitora e sincroniza o estado de exposição à chuva do jogador (1-bit).
 */

class alpStatsIsRained extends alpStatsBase
{
	/**
	 * Construtor: Inicializa o tipo de estatística e define a economia de bits.
	 */
	void alpStatsIsRained(PlayerBase player)
	{
		// alp_Type identifica esta flag no dicionário de sincronização RPC
		alp_Type = alpRPelements.ISRAINED;
		
		// Otimização: Apenas 1 bit (0 ou 1) para representar o estado sob chuva
		NUM_OF_BITS = 1;
	}
	
	/**
	 * Atualiza o valor local buscando o estado climático atual no ambiente do jogador.
	 */
	override void Update()
	{
		// Verifica se o componente de ambiente do jogador está inicializado
		if ( alp_Player && alp_Player.m_Environment )
		{
			// Obtém o estado da chuva e atualiza o componente de Roleplay
			alp_Value = alp_Player.m_Environment.IsRainingALP();
			alp_Player.GetRP().SetRainedState( alp_Value );
		}
	}

	/**
	 * Aplica um novo valor à estatística e sincroniza logicamente o status no jogador.
	 * @param value: 0 (Seco/Sem Chuva) ou 1 (Exposto à Chuva).
	 */
	override void SetValue(int value)
	{
		alp_Value = value;
		
		// Sincroniza a alteração com o componente de Roleplay (usado no cálculo de radiação)
		if ( alp_Player && alp_Player.GetRP() )
		{
			alp_Player.GetRP().SetRainedState( value );
		}
	}	
}