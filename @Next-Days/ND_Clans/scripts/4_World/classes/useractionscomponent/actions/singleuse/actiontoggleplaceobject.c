modded class ActionTogglePlaceObject: ActionSingleUseBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		// 1. OBRIGATÓRIO: A checagem vanilla do jogo precisa ser válida primeiro
		if ( !super.ActionCondition( player, target, item ) )
		{
			return false;
		}
			
		// 2. CORREÇÃO DE SEGURANÇA: Ambos (Client e Server) DEVEM verificar a permissão.
		// Isso garante que cheaters não consigam forçar o modo de construção em base inimiga.
		if ( !player.IsAuthorized(item) )
		{
			return false;
		}
		
		return true;
	}
};