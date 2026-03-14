modded class alpMAPMARKERS 
{
	override static void ShowALLRestictedAreasALP(MapWidget m)
	{
		// 1. Prevenção de Null Pointer
		if (!m) return; 

		// 2. Cacheamento da referência para evitar chamadas contínuas do Getter
		alpClanBasesOptions basesOptions = alp_ND_base.GetBases();
		
		// 3. Validação de segurança
		if (!basesOptions) return; 

		if (basesOptions.ShowRestrictedAreaOnMap && basesOptions.EnableRestrictedArea && basesOptions.RestrictedAreas)
		{	
			// Cacheamento do Count() fora do loop (Otimização pesada para UI)
			int restrictedAreasCount = basesOptions.RestrictedAreas.Count();
			
			for(int a = 0; a < restrictedAreasCount; a++)
			{
				vector pos3 = basesOptions.RestrictedAreas.Get(a);
				
				// pos3[0] = X, pos3[1] = Z, pos3[2] = Radius (Raio)
				vector tempV = Vector(pos3[0], 0, pos3[1]);					
				
				ShowResctrictedArea(m, tempV, pos3[2], COLOR_YELLOW);						
				
				// Atribuição direta do vetor otimizada para a Enfusion Engine
				vector textPos = Vector(pos3[0] - (pos3[2] * 0.75), 0, pos3[1] + (pos3[2] * 0.5));
				m.AddUserMark(textPos, basesOptions.LabelOfRestrictedArea, COLOR_YELLOW, "");	
			}														
		}	
	}
}