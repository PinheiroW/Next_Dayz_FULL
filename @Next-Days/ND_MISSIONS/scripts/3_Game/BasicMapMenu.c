/**
 * BasicMapMenu.c
 * * INTEGRAÇÃO COM MOD BASIC MAP - Módulo ND_MISSIONS
 * Injeta a lógica de visualização de missões e clãs no sistema de mapa.
 */

#ifdef BASICMAP

modded class BasicMapMenu extends UIScriptedMenu
{	
	override void UpdateMarkers()
	{
		// Executa a lógica vanilla/base do Basic Map primeiro
		super.UpdateMarkers();
		
		// Verifica se o objeto do mapa está instanciado para evitar Null Pointer Exception
		if (m_Map)
		{
			// CORREÇÃO: Alinhamento de case com a classe definida em alpMAPMARKERS.c
			alpMapMarkers.ShowALLMissionsALP(m_Map);	
			alpMapMarkers.ShowALLRestictedAreasALP(m_Map);
			
			/** * NOTA: Mantido o erro ortográfico original 'Memebers' para preservar 
			 * a dinâmica de chamada com o módulo ND_Clans sem quebrar referências.
			 */
			alpMapMarkers.ShowClanMemebersOnMapALP(m_Map);			
		}
	}
}

#endif // BASICMAP