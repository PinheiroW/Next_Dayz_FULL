/**
 * actioneatcan.c
 * * AÇÃO CONTÍNUA (COMER ENLATADOS) - Módulo ND_MISSIONS
 * Impede que o jogador consuma latas de comida grandes e pequenas enquanto usar máscaras restritivas.
 */

modded class ActionEatCan: ActionEatBig
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO: Validação primária para prevenir processamento em jogadores nulos
		if (!player) 
		{
			return false;
		}
		
		// OTIMIZAÇÃO E SEGURANÇA: Previne Null Pointer Exceptions ao buscar as opções do servidor
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPlayerOptions())
		{
			if (GetND().GetRP().GetPlayerOptions().MaskPreventConsume)
			{
				EntityAI mask = player.FindAttachmentBySlotName("Mask");
				
				// LÓGICA MANTIDA: Bloqueia o consumo caso a máscara não possua abertura
				if (mask && !IsExceptionsALP(mask))
				{
					return false;
				}
			}
		}
		
		return super.ActionCondition(player, target, item);
	}
}; // Adicionado ponto e vírgula obrigatório


modded class ActionEatSmallCan: ActionEatBig
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO: Validação primária
		if (!player) 
		{
			return false;
		}
		
		// OTIMIZAÇÃO E SEGURANÇA: Verificação em cascata
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPlayerOptions())
		{
			if (GetND().GetRP().GetPlayerOptions().MaskPreventConsume)
			{
				EntityAI mask = player.FindAttachmentBySlotName("Mask");
				
				// LÓGICA MANTIDA
				if (mask && !IsExceptionsALP(mask))
				{
					return false;
				}
			}
		}
		
		return super.ActionCondition(player, target, item);
	}
};