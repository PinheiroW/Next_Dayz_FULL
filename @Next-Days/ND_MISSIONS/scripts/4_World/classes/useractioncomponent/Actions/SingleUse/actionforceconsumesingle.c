/**
 * actionforceconsumesingle.c
 * * MODDED ACTION (FORÇAR CONSUMO ÚNICO) - Módulo ND_MISSIONS
 * Impede que um jogador alimente outro se o alvo estiver usando máscaras obstrutivas.
 */

modded class ActionForceConsumeSingle
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Identifica o jogador que receberá o item
		PlayerBase ntarget = PlayerBase.Cast(target.GetObject());
		
		// Se o alvo for um jogador válido e a restrição de máscara estiver ativa no servidor
		if ( ntarget && GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			// Verifica o slot de máscara do ALVO (não do executor)
			EntityAI mask = ntarget.FindAttachmentBySlotName("Mask");
			
			// Se o alvo estiver de máscara e ela não for uma exceção permitida
			if ( mask && !IsExceptionsALP(mask) )
			{
				// Bloqueia a tentativa de alimentar o outro jogador
				return false;
			}								
		}
		
		// Caso não haja máscara ou o alvo não seja um player, segue a lógica padrão do DayZ
		return super.ActionCondition(player, target, item);
	}
}