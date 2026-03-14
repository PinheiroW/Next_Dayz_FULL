modded class alpND_base 
{
	//compatibility issues clans
	ref alpClanBasesOptions alp_ClanBasesOptions;
	
	//METHODS
	//-------	

	//COMPATIBILITY ISSUES
	//just for Clans
	//-----------------------
	alpClanBasesOptions GetBases()
	{
		// Null Guard: Retorna erro nos logs ao invés de crashar o servidor silenciosamente
		if (!alp_ClanBasesOptions)
		{
			Error("[ND_Clans] CRITICAL ERROR: alp_ClanBasesOptions is NULL! Failed to initialize base settings.");
		}
		
		return alp_ClanBasesOptions;
	}	
}