/**
 * actioneatfruit.c
 * * AÇÃO CONTÍNUA (COMER FRUTAS) - Módulo ND_MISSIONS
 * Impede que o jogador consuma frutas enquanto usar máscaras restritivas.
 */

modded class ActionEatFruit
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO: Validação primária de segurança para evitar processos em entidades nulas
		if (!player) 
		{
			return false;
		}
		
		// OTIMIZAÇÃO E SEGURANÇA: Previne Null Pointer Exceptions e alivia o uso de CPU
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