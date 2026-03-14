modded class ActionBuildPart: ActionContinuousBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		// 1. OBRIGATÓRIO: A checagem vanilla do jogo precisa ser válida primeiro (Ex: ter ferramenta, objeto alvo existir)
		if ( !super.ActionCondition( player, target, item ) )
		{
			return false;
		}
			
		// 2. CORREÇÃO DE SEGURANÇA: Ambos (Client e Server) DEVEM verificar a permissão.
		// Isso impede exploits de forçagem de RPC por parte de clientes hackeados.
		if ( !player.IsAuthorized(item) )
		{
			return false;
		}
		
		return true;
	}
}