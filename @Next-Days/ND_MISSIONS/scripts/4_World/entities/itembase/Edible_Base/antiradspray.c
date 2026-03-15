/**
 * antiradspray.c
 * * ENTIDADE DE ITEM (SPRAY DE DESCONTAMINAÇÃO) - Módulo ND_MISSIONS
 * Utilizado para remover radiação externa acumulada no corpo e vestimentas.
 */

class alp_DecontaminationSpray : Edible_Base
{
	override void InitItemVariables()
	{
		super.InitItemVariables();
		// can_this_be_combined = true; // Desativado conforme lógica original
	}
	
	/**
	 * Impede que o spray seja anexado como um acessório em slots de inventário não planejados.
	 */
	override bool CanPutAsAttachment(EntityAI parent)
	{
		return false;
	}

	override bool CanDetachAttachment(EntityAI parent)
	{
		return false;
	}
	
	/**
	 * Define a eficácia do item para sistemas de desinfecção.
	 * @return 25% da capacidade máxima por uso.
	 */
	override float GetDisinfectQuantity(int system = 0, Param param1 = null)
	{
		return (GetQuantityMax() * 0.25);
	}
	
	/**
	 * Registra as ações específicas deste item.
	 */
	override void SetActions()
	{
		super.SetActions();
		
		// Permite descontaminar a si mesmo ou outro jogador
		AddAction(ActionDecontamineTarget);
		AddAction(ActionDecontamineSelf);
	}
}