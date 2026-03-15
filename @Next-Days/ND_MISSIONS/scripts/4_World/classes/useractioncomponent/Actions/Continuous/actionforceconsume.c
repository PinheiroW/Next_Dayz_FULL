/**
 * actionforceconsume.c
 * * AÇÃO CONTÍNUA (FORÇAR CONSUMO EM ALVO) - Módulo ND_MISSIONS
 * Impede que jogadores alimentem ou deem água a outros jogadores que estejam usando máscaras restritivas.
 */

modded class ActionForceConsume
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// OTIMIZAÇÃO: Validações primárias de segurança para entidades nulas
		if (!player || !target) 
		{
			return false;
		}

		PlayerBase ntarget = PlayerBase.Cast(target.GetObject());

		// SEGURANÇA: Confirma se o alvo da ação é realmente um jogador válido
		if (ntarget)
		{
			// OTIMIZAÇÃO E SEGURANÇA: Leitura protegida em cascata das opções globais do servidor
			if (GetND() && GetND().GetRP() && GetND().GetRP().GetPlayerOptions())
			{
				// Verifica se a opção de bloqueio de máscara está ativada no JSON
				if (GetND().GetRP().GetPlayerOptions().MaskPreventConsume)
				{
					// LÓGICA MANTIDA: Busca a máscara no ALVO (ntarget) e não em quem executa (player)
					EntityAI mask = ntarget.FindAttachmentBySlotName("Mask");
					
					// Se o alvo tem máscara e ela NÃO é uma exceção (ex: bandana), bloqueia a ação
					if (mask && !IsExceptionsALP(mask))
					{
						return false;
					}
				}	
			}
		}
		
		return super.ActionCondition(player, target, item);
	}
}; // Adicionado ponto e vírgula obrigatório