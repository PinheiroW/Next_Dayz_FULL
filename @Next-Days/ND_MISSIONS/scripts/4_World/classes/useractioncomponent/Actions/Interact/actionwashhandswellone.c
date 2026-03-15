/**
 * actionwashhandswellone.c
 * * AÇÃO DE INTERAÇÃO (LAVAR MÃOS NO POÇO) - Módulo ND_MISSIONS
 * Bloqueia a ação se o poço estiver sem água (Sistema de Gestão de Recursos).
 */

modded class ActionWashHandsWellOne extends ActionInteractLoopBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// 1. Validação primária do alvo
		Well well;
		if ( !Class.CastTo( well, target.GetObject() ) )
			return false;

		// 2. LÓGICA MANTIDA: Verifica se o gerenciamento de poços está ativo e se há água disponível
		// Removido o IsServer() para sincronizar o menu de contexto no Cliente
		if ( GetND() && GetND().GetResources() )
		{
			auto options = GetND().GetResources().GetOptions();
			if ( options && options.EnableWellManagement )
			{
				if ( !well.HasWaterALP() )
				{
					return false; // Bloqueia a ação se o poço estiver seco
				}
			}
		}

		// 3. Retorna a condição base do jogo (verifica se as mãos estão sujas/com sangue)
		return super.ActionCondition( player, target, item );
	}
};