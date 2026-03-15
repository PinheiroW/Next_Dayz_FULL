/**
 * actionopencardoors.c
 * * AÇÃO DE INTERAÇÃO (ABRIR PORTAS DO CARRO) - Módulo ND_MISSIONS
 * Vincula a abertura física das portas ao estado da tranca do inventário (Chaves).
 */

modded class ActionOpenCarDoorsOutside: ActionCarDoorsOutside
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		// SEGURANÇA: Valida a condição base do DayZ (se a porta está fechada, integridade, etc)
		if ( !super.ActionCondition(player, target, item) )
			return false;

		CarScript car;	
		// LÓGICA MANTIDA: Se o alvo é parte de um veículo
		if ( Class.CastTo(car, target.GetParent()) )
		{
			// Regra ND_MISSIONS:
			// 1. Se o inventário está destrancado, permite abrir.
			// 2. Se o jogador está DENTRO do veículo (GetCommand_Vehicle), permite abrir por segurança.
			if ( car.GetInventory().IsInventoryUnlocked() || player.GetCommand_Vehicle() ) 
			{
				return true;
			}
			
			return false; // Veículo trancado por fora
		}
		
		return true; // Se não for um CarScript (fallback), segue fluxo padrão
	}

	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer(action_data);
		
		// LÓGICA DE SEGURANÇA: Destranca o carro automaticamente se o jogador abrir a porta por dentro
		if( action_data.m_Player && action_data.m_Player.GetCommand_Vehicle() )
		{
			CarScript car = CarScript.Cast(action_data.m_Player.GetCommand_Vehicle().GetTransport());
			if (car)
			{
				// Garante que o jogador consiga sair do veículo mesmo que ele tenha sido trancado externamente
				car.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
			}
		}
	}	
};