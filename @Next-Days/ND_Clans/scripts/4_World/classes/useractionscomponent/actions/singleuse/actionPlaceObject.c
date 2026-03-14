modded class ActionPlaceObject: ActionDeployObject
{
	// CORREÇÃO 1: A variável global 'bool WasPlaced' foi deletada. 
	// Ações são Singletons e variáveis globais aqui causam Race Conditions (conflito entre jogadores).
	
    override void OnFinishProgressServer(ActionData action_data)
    {
		super.OnFinishProgressServer(action_data);
		
		// CORREÇÃO 2: Prevenção de Null Pointer Crash
		if ( !action_data.m_MainItem ) return;
		
		// CORREÇÃO 3: A exclusão foi movida para o OnFinishProgressServer.
		// Como este método só roda se a ação for um sucesso (círculo completo), 
		// isso elimina a necessidade da variável 'WasPlaced' e limpa a arquitetura.
        if ( action_data.m_MainItem.IsKindOf("alp_PlotPoleKit") )
        {
			GetGame().ObjectDelete(action_data.m_MainItem);
		}
    }	

	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer( action_data );
		
		// Blindagem de memória do jogador e item alvo no início da ação
		if ( !action_data.m_MainItem || !action_data.m_Player ) return;
		
		EntityAI entity_for_placing = action_data.m_MainItem;
		
		if ( entity_for_placing.IsKindOf("alp_PlotPoleKit") )
		{
			int playerID = action_data.m_Player.GetPlayerID();
			
			alp_PlotPoleKit ppk = alp_PlotPoleKit.Cast( entity_for_placing );
			
			// Null check no Cast
			if ( ppk )
			{
				ppk.alp_PlayerID = playerID;
			}
		}
	}
}