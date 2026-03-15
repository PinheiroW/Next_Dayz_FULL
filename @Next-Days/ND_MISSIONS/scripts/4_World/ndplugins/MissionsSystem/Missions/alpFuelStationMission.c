/**
 * alpFuelStationMission.c
 * * MISSION LOGIC: FUEL STATION - Módulo ND_MISSIONS
 * Gerencia o reabastecimento e a disputa por combustível em postos específicos.
 */

class alpFuelStationMission extends alpMission
{
	ref array<FuelStation> alp_FuelStations;

	void ~alpFuelStationMission()
	{
		if (alp_FuelStations)
			delete alp_FuelStations;					
	}

	// --- Configurações Iniciais ---
	
	override void OnInit()
	{
		// Configuração de mensagens padrão
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut    = ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
		
		alp_FuelStations    = new array<FuelStation>;
	}
	
	// --- Posicionamento e Spawn ---

	override protected bool SetPosition()
	{
		// Busca um posto de combustível disponível no mapa
		array<float> coordinates = GetND().GetMS().GetFreePlace().GetPositionFS( this );
		
		if ( coordinates && coordinates.Count() >= 4 )
		{
			alp_Position = Vector( coordinates.Get(0), coordinates.Get(1), coordinates.Get(2) );
			alp_Angle = Vector( coordinates.Get(3), 0, 0 ); // Define a rotação baseada no layout do posto
			return true;
		}
		return false;
	}

	override protected void SpawnMissionObjects()
	{
		super.SpawnMissionObjects();

		// Identifica e configura as bombas de combustível no raio da missão
		array<Object> objects = new array<Object>;
		GetGame().GetObjectsAtPosition( alp_Position, 20, objects, null );

		foreach (Object obj : objects)
		{
			FuelStation fs;
			if ( Class.CastTo( fs, obj ) )
			{
				// Calcula um reabastecimento aleatório para a bomba
				float maxNeeded = fs.GetFuelAmmountMax() - fs.GetFuelAmmount();
				maxNeeded = maxNeeded * Math.RandomFloat(0.4, 1.0);
				
				fs.AddFuelALP( maxNeeded );
				fs.SaveFuelStationALP();
								
				// Transfere o controle da bomba para a missão
				alpPluginNDmissionsSystem.FuelStations.RemoveItem( fs );					
				alp_FuelStations.Insert( fs );
			}
		}
	}

	override void DespawnMission()
	{		
		super.DespawnMission();	
		if (alp_FuelStations) alp_FuelStations.Clear();
		alp_Position = "0 0 0";
	}

	// --- Verificações de Estado ---

	override protected bool CheckSecuredCondition(float timeslice) 
	{	
		// Sucesso: Condição base OK + Fim do combustível disponível
		if ( super.CheckSecuredCondition( timeslice ) && !IsAvailableFuel() ) 
		{
			return true;
		}
		return false;
	}
	
	override protected bool CheckFailedCondition(float timeslice) 
	{	
		// Falha: As bombas foram destruídas
		if ( IsFuelStationRuined() ) 
		{
			return true;
		}
		return false;
	}	

	/**
	 * Verifica se ainda há combustível nas bombas da missão.
	 */
	bool IsAvailableFuel()
	{
		foreach (FuelStation fs : alp_FuelStations)
		{
			if ( fs.GetFuelAmmount() > 1.0 ) // Considera disponível se houver mais de 1 litro
				return true;
		}
		return false;
	}

	/**
	 * Verifica se alguma das bombas essenciais foi arruinada.
	 */
	bool IsFuelStationRuined()
	{
		foreach (FuelStation fs : alp_FuelStations)
		{
			if ( fs.IsRuined() )
				return true;
		}
		return false;
	}
}