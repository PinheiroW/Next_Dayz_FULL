/**
 * actionconsume.c
 * * AÇÃO CONTÍNUA (CONSUMIR ITEM) - Módulo ND_MISSIONS
 * Impede que o jogador consuma alimentos ou bebidas enquanto estiver usando uma máscara restritiva.
 */

modded class ActionConsume
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO: Proteção primária para garantir que a entidade do jogador é válida neste frame
		if (!player) 
		{
			return false;
		}
		
		// OTIMIZAÇÃO E SEGURANÇA: Previne Null Pointer Exception ao consultar opções globais num loop de condição
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPlayerOptions())
		{
			if (GetND().GetRP().GetPlayerOptions().MaskPreventConsume)
			{
				EntityAI mask = player.FindAttachmentBySlotName("Mask");
				
				// LÓGICA MANTIDA: Se há máscara e ela NÃO é uma exceção (ex: bandana), bloqueia a ação
				if (mask && !IsExceptionsALP(mask))
				{
					return false;
				}
			}
		}

		// Retorna ao comportamento padrão da Enfusion caso a máscara não seja restritiva ou não exista
		return super.ActionCondition(player, target, item);
	}
}; // Adicionado ponto e vírgula obrigatório