/**
 * alpStatsIsInTradeZone.c
 * * STAT SYNC COMPONENT - Módulo ND_MISSIONS (Sync)
 * Gerencia a sincronização binária (1-bit) do status de presença em Zona de Comércio.
 */

class alpStatsIsInTradeZone extends alpStatsBase
{
	/**
	 * Construtor: Inicializa o tipo de estatística e define a economia de bits.
	 */
	void alpStatsIsInTradeZone(PlayerBase player)
	{
		// alp_Type identifica esta flag no dicionário de sincronização RPC
		alp_Type = alpRPelements.ISINTRADERZONE;
		
		// Otimização: Apenas 1 bit (0 ou 1) para representar a presença na zona
		NUM_OF_BITS = 1;
	}
	
	/**
	 * Atualiza o valor local buscando o estado atual no componente de Roleplay do jogador.
	 */
	override void Update()
	{
		if (alp_Player && alp_Player.GetRP())
		{
			// Consulta o estado armazenado no alpRP.c
			alp_Value = alp_Player.GetRP().IsInTradeZone();
		}
	}
	
	/**
	 * Aplica um novo valor à estatística e atualiza logicamente o status no jogador.
	 * @param value: 0 (Fora da Zona) ou 1 (Dentro da Zona).
	 */
	override void SetValue(int value)
	{
		alp_Value = value;
		
		// Sincroniza a alteração com o componente de Roleplay para efeitos de UI/Lógica
		if (alp_Player && alp_Player.GetRP())
		{
			alp_Player.GetRP().SetInTradeZone(value);
		}
	}	
}