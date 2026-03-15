/**
 * ATM.c
 * * ENTIDADE DO OBJETO (CAIXA ELETRÔNICO) - Módulo ND_MISSIONS
 * Define o comportamento do objeto ATM no mundo e suas interações disponíveis.
 */

class alp_ATM extends BuildingSuper
{
	void alp_ATM()
	{
		// Construtor padrão para inicialização do objeto
	}
	
	/**
	 * Define se o motor do jogo deve tratar este objeto como um edifício completo.
	 * Retornar false otimiza a performance para objetos de interação simples.
	 */
	override bool IsBuilding()
	{
		return false;
	}
	
	/**
	 * Registra as ações que o jogador pode realizar ao olhar para este objeto.
	 */
	override void SetActions()
	{
		super.SetActions();
		
		// Adiciona a ação de abrir a interface bancária (ATM)
		AddAction(alpActionATM);
	}
}