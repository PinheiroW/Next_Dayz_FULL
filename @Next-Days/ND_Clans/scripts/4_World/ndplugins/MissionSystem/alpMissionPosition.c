modded class alpMissionPosition 
{
	// Nota: Verifique se o nome na classe base é realmente 'IsSomeOneInRadisu' (com 'u') 
	// para garantir que o override funcione.
	override bool IsSomeOneInRadisu(vector position, int radius)
	{	
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );	
		
		if( players && players.Count() > 0 )
		{
			foreach(Man player: players)
			{
				if( player && player.IsAlive() )
				{
					// CORREÇÃO 1: Uso de função nativa vector.Distance (Alta performance)
					if ( vector.Distance(position, player.GetPosition()) < radius )
					{
						return true;
					}
				}
			}
		}

		// CORREÇÃO 2: Verificação de PlotPoles em raio de segurança.
		// Removido o Clamp(0,30) para respeitar o raio real solicitado pela missão.
		if ( radius > 0 ) 
		{
			// CORREÇÃO 3: Remoção de autoptr (Obsoleto na Enfusion moderna)
			array<Object> nearest_objects = new array<Object>;
			array<CargoBase> proxy_cargos = new array<CargoBase>;
				
			if (GetGame())
			{
				GetGame().GetObjectsAtPosition( position , radius , nearest_objects, proxy_cargos ); 						
				for (int x = 0; x < nearest_objects.Count(); x++)
				{
					Object obj = nearest_objects.Get(x);				
					if ( obj && obj.GetType() == "alp_PlotPole" ) 
					{
						return true;
					}
				}	
			}	
		}

		return false;
	}
}