ref alpLifeTime alp_LifeTime;

alpLifeTime GetLifeTimeManager()
{
	if ( !alp_LifeTime )
	{
		alp_LifeTime = new alpLifeTime();
	}

	return alp_LifeTime;
}

class alpLifeTimeItem 
{
	vector Position;
	float Radius;
	int LifeTime; // CORREÇÃO: Ponto e vírgula adicionado
	
	void alpLifeTimeItem(vector v, float radius, int lifetime = 3888000)
	{
		Position = v;
		Radius = radius;
		LifeTime = lifetime;
	}
}

class alpLifeTime 
{
	ref array<ref alpLifeTimeItem> alp_Bases;
	
	void alpLifeTime()
	{
		alp_Bases = new array<ref alpLifeTimeItem>;
	}
	
	void AddBase( alpLifeTimeItem base)
	{
		if (base)
			alp_Bases.Insert(base);	
	}

	void UpdateLifeTime()
	{
		if (!alp_Bases) return;

		for ( int i = 0; i < alp_Bases.Count(); i++)
		{
			alpLifeTimeItem item = alp_Bases.Get(i);
			if (item)
			{
				SetLifeTime( item.Position, item.Radius, item.LifeTime );
			}
		}
	}

	void SetLifeTime( vector pos, float radius, int lifetime = 3888000 )
	{
		// CORREÇÃO: Remoção de autoptr (obsoleto na Enfusion moderna)
		array<Object> nearest_objects = new array<Object>;
		array<CargoBase> proxy_cargos = new array<CargoBase>;
		
		if (!GetGame()) return;

		GetGame().GetObjectsAtPosition( pos, radius, nearest_objects, proxy_cargos ); 	
		
		for (int i = 0; i < nearest_objects.Count(); i++)
		{
			Object obj = nearest_objects.Get(i);
			if (!obj) continue;

			ItemBase item; 
			if ( Class.CastTo( item, obj ) && item.IsBuildingALP() )
			{
				// Otimização: renova o lifetime usando o máximo do item ou o valor da base
				float lt = item.GetLifetimeMax();
				if (lifetime > 0) lt = lifetime;
				
				item.SetLifetime( lt );			 					
			}
			else
			{
				Transport vehicle;
				if ( Class.CastTo( vehicle, obj ) )
				{
					float vlt = vehicle.GetLifetimeMax();
					if (lifetime > 0) vlt = lifetime;
					
					vehicle.SetLifetime( vlt );						
				}
			}
		}		
	}			
}