/**
 * @class   CraftFireplace
 * @brief   Modifica a receita da fogueira para aceitar dinheiro e banha como componentes
 * Auditado em: 2024 - Foco em Integridade de Inventário e Fluxo de Crafting
 */
modded class CraftFireplace extends RecipeBase
{	
	override void Init()
	{
		super.Init(); // Mantém gravetos e panos originais

		// Adiciona Dinheiro como opção (Slot 0 ou 1)
		InsertIngredient(0, "alp_Money");
		InsertIngredient(1, "alp_Money");

		// Adiciona Banha como opção
		InsertIngredient(0, "Lard");
		InsertIngredient(1, "Lard");
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		ItemBase result = ItemBase.Cast(results.Get(0));
		if (!result) return;

		for (int i = 0; i < 2; i++)
		{
			ItemBase ingredient = ingredients[i];
			if (!ingredient) continue;

			// Caso especial: Se o ingrediente for BANHA, tentamos anexar à fogueira
			if (ingredient.GetType() == "Lard")
			{
				TransferToAttachmentALP(player, result, ingredient, "LardALP");
			}
			else if (ingredient.GetQuantity() <= 0)
			{
				// Comportamento padrão: move o item inteiro se não tiver quantidade (ex: Rags unitários)
				player.ServerTakeEntityToTargetAttachment(result, ingredient);
			}
			else
			{
				// Comportamento padrão: reduz 1 da quantidade
				ingredient.AddQuantity(-1);
			}
		}
	}

	/**
	 * @brief Helper seguro para mover itens para anexos durante o craft
	 */
	protected void TransferToAttachmentALP(PlayerBase player, ItemBase target, ItemBase ingredient, string slotName)
	{
		int slotId = InventorySlots.GetSlotIdFromString(slotName);
		if (slotId == InventorySlots.INVALID) return;

		if (GetGame().IsServer())
		{
			// No servidor, usamos o comando extendido de movimentação
			player.ServerTakeEntityToTargetAttachmentEx(target, ingredient, slotId);
		}
		// Nota: O motor sincroniza automaticamente para o cliente
	}
};