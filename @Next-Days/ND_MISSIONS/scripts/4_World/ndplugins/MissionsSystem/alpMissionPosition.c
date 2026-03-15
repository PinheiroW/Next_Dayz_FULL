/**
 * alpMissionPosition.c
 * Gerenciador de coordenadas e validação de spawn seguro.
 */
class alpMissionPosition 
{
	// Busca posição baseada em Postos de Combustível existentes
	array<float> GetPositionFS(alpMission mission)
	{	
		array<float> coordinates = new array<float>;
		if ( alpPluginNDmissionsSystem.FuelStations && alpPluginNDmissionsSystem.FuelStations.Count() > 0 )
		{
			int index = alpPluginNDmissionsSystem.FuelStations.GetRandomIndex();
			FuelStation station = alpPluginNDmissionsSystem.FuelStations.Get( index );
			
			if (!station || !station.IsAlive() )
			{
				alpPluginNDmissionsSystem.FuelStations.Remove( index );
				return coordinates;			
			}
			
			vector pos = station.GetPosition();
			coordinates.Insert(pos[0]); // x
			coordinates.Insert(pos[1]); // h
			coordinates.Insert(pos[2]); // y
			coordinates.Insert(0);      // yaw (rotação)
		}
		return coordinates;
	}
	
	// Verifica se há jogadores num raio específico para evitar spawn visual
	bool IsSomeOneInRadisu(vector position, int radius)
	{	
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );	
		foreach(Man player: players)
		{
			if( player && alpUF.VectorDistance(position, player.GetPosition()) < radius )
			{
				return true;
			}
		}
		return false;
	}
}