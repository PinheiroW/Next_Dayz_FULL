class alpSpawnSettings 
{
	ref map<int, ref alpSpawnSetPlayerBothRole> alp_SpawnSetMaped;
	ref alpSpawnSettings_Base alp_SpawnSettings;
	
	void alpSpawnSettings()
	{
		alp_SpawnSettings = alpSpawnSettings_Base.Load();
		alp_SpawnSetMaped = new map<int, ref alpSpawnSetPlayerBothRole>;
		
		// Inicialização segura via fila de execução
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Init, 0);
	}
	
	void Init()
	{
		// CORREÇÃO 1: Failsafe para evitar Crash no Boot se o sistema de RP não estiver pronto
		if (!GetND() || !GetND().GetRP())
		{
			// Tenta novamente em 1 segundo se o sistema falhar
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Init, 1000);
			return;
		}

		int maxLevel = GetND().GetRP().GetPerkReputationLevelCup();
		
		if ( alp_SpawnSettings && alp_SpawnSettings.PlayerSpawn )
		{
			for(int i = 0; i <= maxLevel; i++)
			{
				alpSpawnSetPlayerBothRole settings = FindPlayerSet(i);
				if (settings)
				{
					alp_SpawnSetMaped.Set( i, settings );
				}
			}
		}		
	}
	
	alpSpawnSetPlayerBothRole FindPlayerSet(int level)
	{
		alpSpawnSetPlayerBothRole sets = new alpSpawnSetPlayerBothRole;

		// CORREÇÃO 2: Performance otimizada. 
		// Percorremos a lista uma ÚNICA VEZ para encontrar ambos os papéis (Hero e Bandit)
		int lastLevelHero = -1;
		int lastLevelBandit = -1;

		if (!alp_SpawnSettings || !alp_SpawnSettings.PlayerSpawn) return sets;

		foreach( alpSpawnSetPlayer spawnset : alp_SpawnSettings.PlayerSpawn )
		{
			if (!spawnset) continue;

			// Lógica unificada para Heróis
			if ( spawnset.RequiredcharacterRole != 2 && spawnset.RequiredReputationLevel <= level )
			{
				if ( spawnset.RequiredReputationLevel > lastLevelHero || ( spawnset.RequiredReputationLevel == lastLevelHero && spawnset.RequiredcharacterRole == 1 ) )
				{
					lastLevelHero = spawnset.RequiredReputationLevel;
					sets.Hero = spawnset;
				}
			}

			// Lógica unificada para Bandidos
			if ( spawnset.RequiredcharacterRole != 1 && spawnset.RequiredReputationLevel <= level )
			{
				if ( spawnset.RequiredReputationLevel > lastLevelBandit || ( spawnset.RequiredReputationLevel == lastLevelBandit && spawnset.RequiredcharacterRole == 2 ) )
				{
					lastLevelBandit = spawnset.RequiredReputationLevel;
					sets.Bandit = spawnset;
				}
			}
		}			
		
		return sets;	
	}
	
	alpSpawnSetPlayer GetSpawnSet(int level)
	{
		int id = Math.AbsInt( level );
		alpSpawnSetPlayerBothRole settings;
		
		// CORREÇÃO 3: Verificação de existência no mapa para evitar erro de referência nula
		if ( alp_SpawnSetMaped && alp_SpawnSetMaped.Find( id, settings ) && settings )
		{
			if ( level < 0 )
			{
				return settings.Bandit; // Retorno direto para Bandido
			}
			return settings.Hero; // Retorno direto para Herói
		}	
		
		// Retorno de emergência para recém-nascidos caso o set de nível falhe
		return GetNewbornSet(); 
	}
	
	alpSpawnSetNewborn GetNewbornSet()
	{
		if (alp_SpawnSettings)
		{
			return alp_SpawnSettings.NewbornSpawn;
		}
		return null;
	}
}