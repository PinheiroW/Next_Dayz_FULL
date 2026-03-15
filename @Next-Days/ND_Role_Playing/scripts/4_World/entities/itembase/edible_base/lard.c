/**
 * @class   Lard
 * @brief   Modifica a Banha para permitir utilidades de sobrevivência (fogo) no Next Days
 * Auditado em: 2026 - Foco em Expansão de Utilidade de Itens
 */
modded class Lard extends Edible_Base
{
	override void SetActions()
	{
		// 1. Mantém as ações originais (Comer, Cozinhar, etc.)
		super.SetActions();
		
		// 2. Adiciona utilidade de ignição/criação de fogo em ambientes internos
		// Isso permite usar a gordura animal como combustível inicial (Roleplay de sobrevivência)
		AddAction(ActionCreateIndoorFireplace);
		AddAction(ActionCreateIndoorOven);
		
		/** * @note Se desejar que a banha também seja usada para lubrificar armas 
		 * ou tratar couro (Hunting Perk), novas ações devem ser inseridas aqui.
		 */
	}
}