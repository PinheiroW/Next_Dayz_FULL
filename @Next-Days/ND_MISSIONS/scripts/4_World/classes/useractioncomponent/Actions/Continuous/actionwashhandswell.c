/**
 * actionwashhandswell.c
 * * AÇÃO CONTÍNUA (LAVAR MÃOS NO POÇO) - Módulo ND_MISSIONS
 * Bloqueia a ação caso o poço esteja sem água, respeitando o sistema de recursos.
 */

modded class ActionWashHandsWell: ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// SEGURANÇA: Validação primária de entidade e alvo
		if (!player || !target || !target.GetObject())
		{
			return false;
		}

		Well well;
		
		// OTIMIZAÇÃO E SEGURANÇA: Verifica se o objeto alvo é um Poço (Well)
		if (Class.CastTo(well, target.GetObject()))
		{
			// Leitura protegida em cascata das opções globais do servidor
			if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
			{
				auto options = GetND().GetResources().GetOptions();
				
				// LÓGICA MANTIDA: Se o gerenciamento está ativo, impede a lavagem em poços vazios
				if (options.EnableWellManagement && GetGame().IsServer() && !well.HasWaterALP()) 
				{		
					return false;	
				}
			}
		}
		
		// Retorna a condição base (verifica se as mãos estão realmente sujas/ensanguentadas)
		return super.ActionCondition(player, target, item);
	}
}; // Fechamento de classe com ponto e vírgula