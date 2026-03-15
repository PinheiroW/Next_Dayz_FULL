/**
 * purifywater.c
 * * RECEITA DE PURIFICAÇÃO DE ÁGUA - Módulo ND_MISSIONS
 * Garante que a purificação da água (ex: pastilhas de cloro) não remova a radiação.
 */

modded class PurifyWater extends RecipeBase
{	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		// OTIMIZAÇÃO: Validação de segurança para prevenir Null Pointer Exception
		// Garante que o array possui os itens necessários antes de tentar acessá-los
		if (!ingredients || ingredients.Count() < 2) 
			return;
			
		ItemBase ingredient2 = ingredients[1];
		
		if (ingredient2)
		{
			// LÓGICA DE MOD MANTIDA: Purifica a água de doenças comuns, mas mantém a radiação intacta
			ingredient2.RemoveAllAgentsExcept(alpeAgents.RADIATION);
		}
	}
}