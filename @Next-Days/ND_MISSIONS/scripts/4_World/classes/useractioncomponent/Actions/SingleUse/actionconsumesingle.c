/**
 * actionconsumesingle.c
 * * MODDED ACTION (CONSUMO ÚNICO) - Módulo ND_MISSIONS
 * Impede o consumo de itens (comida/remédio) se o jogador estiver usando máscaras obstrutivas.
 */

modded class ActionConsumeSingle
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		if (!player) return false;

		// Verifica se a restrição de máscara está habilitada nas opções do servidor
		if ( GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			// Tenta localizar o item no slot de máscara
			EntityAI mask = player.FindAttachmentBySlotName("Mask");
			
			// Se houver máscara e ela NÃO for uma exceção (ex: óculos, bandanas abertas)
			if ( mask && !IsExceptionsALP(mask) )
			{
				// Bloqueia a ação e não prossegue para a lógica nativa
				return false;
			}								
		}
		
		// Se passar pela trava da máscara, segue para as validações padrão do DayZ
		return super.ActionCondition(player, target, item);
	}

	/**
	 * Define quais itens no slot de máscara NÃO impedem o consumo.
	 * Geralmente inclui óculos, máscaras táticas que não cobrem a boca, etc.
	 */
	bool IsExceptionsALP(EntityAI mask)
	{
		// Esta lógica geralmente consulta uma lista de classes no config do mod
		// ou verifica tipos específicos de máscaras.
		if (mask.IsInherited(EyeMask_Base)) return true; // Exemplo: Óculos de sol/proteção
		
		return false; 
	}
}