/**
 * alpStatsIsAllowDamage.c
 * * STAT SYNC COMPONENT - Módulo ND_MISSIONS (Sync)
 * Gerencia a sincronização binária (1-bit) da permissão de dano do jogador.
 */

class alpStatsIsAllowDamage extends alpStatsBase
{
	/**
	 * Construtor: Inicializa o tipo de estatística e define a economia de bits.
	 */
	void alpStatsIsAllowDamage(PlayerBase player)
	{
		// alp_Type identifica esta flag no dicionário de sincronização
		alp_Type = alpRPelements.ISALLOWDAMAGE;
		
		// Otimização: Apenas 1 bit é necessário para representar um estado booleano
		NUM_OF_BITS = 1;
	}
	
	/**
	 * Atualiza o valor local da estatística buscando o estado atual no componente RP.
	 */
	override void Update()
	{
		if (alp_Player && alp_Player.GetRP())
		{
			alp_Value = alp_Player.GetRP().IsAllowedDamage();
		}
	}

	/**
	 * Aplica um novo valor à estatística e executa a lógica correspondente no jogador.
	 * @param value: 0 (Dano Desativado) ou 1 (Dano Ativado).
	 */
	override void SetValue(int value)
	{
		alp_Value = value;
		
		// Garante que a lógica de dano do componente de RP seja atualizada simultaneamente
		if (alp_Player && alp_Player.GetRP())
		{
			alp_Player.GetRP().SetAllowedDamage(value);
		}
	}	
}