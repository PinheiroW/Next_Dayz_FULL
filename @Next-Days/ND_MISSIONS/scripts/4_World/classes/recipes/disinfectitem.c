/**
 * disinfectitem.c
 * * RECEITA DE DESINFECÇÃO MODIFICADA - Módulo ND_MISSIONS
 * Garante que a limpeza de itens preserve agentes severos (Kuru, Salmonella, Cólera e Radiação).
 */

modded class DisinfectItem extends RecipeBase
{	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight) // gets called upon recipe's completion
	{
		ItemBase ingredient1;
		ItemBase ingredient2;
		
		// Cast seguro dos ingredientes
		Class.CastTo(ingredient1, ingredients[0]);
		Class.CastTo(ingredient2, ingredients[1]);
		
		// OTIMIZAÇÃO: Validação para evitar Null Pointer Exception caso o item seja destruído/dropado no exato frame da ação
		if (!ingredient1 || !ingredient2) 
			return;

		// Deduz a quantidade de uso do desinfetante (Spray, Álcool ou Tintura)
		ingredient1.AddQuantity(-ingredient1.GetDisinfectQuantity());

		// LÓGICA DE MOD MANTIDA: Limpa o item, mas mantém doenças severas e a radiação
		ingredient2.RemoveAllAgentsExcept(eAgents.BRAIN | eAgents.SALMONELLA | eAgents.CHOLERA | alpeAgents.RADIATION);
		ingredient2.SetCleanness(1);
	}
}