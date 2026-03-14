modded class ClientData
{
	static ref array<EntityAI> PlotPoleList = new array<EntityAI>;	
	static ref array<EntityAI> EstateList 	= new array<EntityAI>;	

	override static void ResetClientData()
	{
		// SEMPRE chamar o super primeiro para não quebrar o jogo base ou outros mods
		super.ResetClientData(); 
		
		if ( PlotPoleList )
			PlotPoleList.Clear();
		
		if ( EstateList )
			EstateList.Clear();		
	}

	static void AddPlotPole( EntityAI plotpole )
	{
		// Null check preventivo
		if ( !plotpole ) return;

		// Prevenção de duplicação de referências
		if ( PlotPoleList && PlotPoleList.Find( plotpole ) == -1 )
		{
			PlotPoleList.Insert( plotpole );
		}
	}
	
	static void RemovePlotPole( EntityAI plotpole )
	{
		if ( !plotpole ) return;

		if ( PlotPoleList )
		{
			PlotPoleList.RemoveItem( plotpole );
		}
	}
	
	static void AddEstate( EntityAI estate )
	{
		if ( !estate ) return;

		if ( EstateList && EstateList.Find( estate ) == -1 )
		{
			EstateList.Insert( estate );
		}
	}
	
	static void RemoveEstate( EntityAI estate )
	{
		if ( !estate ) return;

		if ( EstateList )
		{
			EstateList.RemoveItem( estate );
		}
	}
}