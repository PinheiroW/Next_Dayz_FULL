class alpClans_BasisOptions 
{
	bool EnableClans									= true;
	bool ShowIconsInTradeZone							= true;
	
	// CORREÇÃO: O array foi apenas declarado no escopo. A atribuição foi movida para o construtor.
	int  ClanMemberIconColor[4]; // color of icon over the mate
	
	float ShowNickDistance								= 25; // distance to see mate's icon
	float ShowIconDistance								= 100;
	
	//float ShowIconDistanceInOptics					= 650; // distance to see mate's icon in optic		
	
	bool EnableCamera									= true;
	bool Enable3rdPersonCameraInVehicle					= true;
	bool Enable3rdPersonCameraAtHome					= true;
	bool Enable3rdPersonCameraAtSafeZone				= true;

	bool SplitQuestReward								= true;
	
	// CORREÇÃO: Construtor adicionado para inicializar corretamente o array na Enfusion
	void alpClans_BasisOptions()
	{
		ClanMemberIconColor[0] = 255;
		ClanMemberIconColor[1] = 255;
		ClanMemberIconColor[2] = 0;
		ClanMemberIconColor[3] = 0;
	}
}

class alpClans_Locking 
{	
	bool EnableLocking									= true;
	bool ForcerUnlockAllDoors							= false; // Sugestão: corrigir de 'Forcer' para 'Force' se possível nas referências
	
	float ChanceToLockDoorAfterRestart 					= 0;
	float RatioLockedDoors								= 0.5;
	
	bool IncludingVehiclesWrecks						= false;
}

class alpCLANoptionsClient 
{
	bool ShowPlayersIcontem								= true; // Possível erro de digitação no original (Icontem -> IconItem), mantido por compatibilidade
}