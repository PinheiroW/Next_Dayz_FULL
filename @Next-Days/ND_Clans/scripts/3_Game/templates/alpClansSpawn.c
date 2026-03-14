class alpClansSpawn 
{
	bool EnableEnhancedSpawnSettings;
	bool EnableSpawnInBase;
	int SpawnInBaseCoolDown;

	// Construtor: Garante a inicialização segura na memória antes da leitura do JSON
	void alpClansSpawn()
	{
		EnableEnhancedSpawnSettings = false;
		EnableSpawnInBase = true;
		SpawnInBaseCoolDown = 900;
	}
}