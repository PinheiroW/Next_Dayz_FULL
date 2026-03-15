/**
 * Tetracyclineantibiotics.c
 * * MODDED ENTITY (ANTIBIÓTICOS) - Módulo ND_MISSIONS
 * Estende o uso da Tetraciclina para tratar estágios iniciais de envenenamento por radiação.
 */

modded class TetracyclineAntibiotics : Edible_Base
{
	/**
	 * Chamado ao consumir o medicamento.
	 * Adiciona a lógica de cura de radiação (Estágios 1, 2 e 3).
	 */
	override void OnConsume(float amount, PlayerBase consumer)
	{
		if ( consumer && consumer.GetModifiersManager() )
		{
			// Cura o Estágio 1 de Radiação
			if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
			{
				consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
			}		
	
			// Cura o Estágio 2 de Radiação
			if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
			{
				consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
			}		

			// Cura o Estágio 3 de Radiação
			if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
			{
				consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
			}						
		}
		
		// Executa a cura padrão do jogo (Cólera, etc.)
		super.OnConsume(amount, consumer);
	}
}

/*
    Nota de Design - Níveis de Radiação (Referência):
    L0 = 200  | L1 = 500  | L2 = 1000 
    L3 = 3000 | L4 = 6000 (Crítico - Antibióticos não funcionam mais)
*/