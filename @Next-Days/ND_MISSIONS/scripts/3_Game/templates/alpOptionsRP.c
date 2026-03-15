/**
 * alpOptionsRP.c
 * * CONFIGURAÇÕES GERAIS DE ROLEPLAY - Módulo ND_MISSIONS
 * Define regras para jogadores (máscaras, morte, respawn) e física de veículos.
 */

class alpOptionsRP_Players 
{
	bool DisableClimbOverVehicle						= false;
	bool ItemsCanBeRepairedToPristine					= true;
	bool MaskPreventConsume								= true;
	ref TStringArray ExceptionsInMask					= {"Balaclava3Holes_Beige", "Balaclava3Holes_Blue", "Balaclava3Holes_Black", "Balaclava3Holes_Green"};	
	
	bool RaiseZombieAfterDeath							= false;
	bool RaiseZombieFromPlayersBodyOnly					= false;
	int	RaiseZombieTime[2]								= {30, 120};
	float RuinDroppedAttch								= 0.5;	
	int AttchLifeTime									= 3600;	
	int ZombieLifeTime									= 3600;	
	int DeadBodyLifeTime								= 180;	
	
	ref TStringArray MaleZombies = {
		"ZmbM_PatrolNormal_Autumn", "ZmbM_PatrolNormal_Flat", "ZmbM_PatrolNormal_PautRev", "ZmbM_PatrolNormal_Summer", 
		"ZmbM_SoldierNormal", "ZmbM_usSoldier_normal_Desert", "ZmbM_usSoldier_normal_Woodland", "ZmbM_CitizenASkinny_Blue", 
		"ZmbM_CitizenASkinny_Grey", "ZmbM_CitizenASkinny_Red", "ZmbM_CitizenBFat_Blue", "ZmbM_CitizenBFat_Green", 
		"ZmbM_CitizenBFat_Red", "ZmbM_ClerkFat_Grey"
	};

	ref TStringArray FemaleZombies = {
		"ZmbF_ShortSkirt_white", "ZmbF_ShortSkirt_yellow", "ZmbF_SkaterYoung_Brown", "ZmbF_SkaterYoung_Striped", 
		"ZmbF_SkaterYoung_Violet", "ZmbF_SurvivorNormal_Blue", "ZmbF_SurvivorNormal_Red", "ZmbF_SurvivorNormal_White"
	};
}; // Adicionado ponto e vírgula

class alpOptionsRP_Vehicles 
{
	bool RequiredKeyToStartEngine						= true;
	bool DisableLocpicking								= false;
	
	bool DisableLocpickingInTradeZone					= false;
	bool DisableKeyDuplicationInTradeZone				= false;
	
	bool IndestructibleLockedVehicle					= false;
	bool IndestructibleVehicles							= false;
	
	int TimeToForceOpen									= 60; // Tempo em segundos para forçar abertura
	int DamageLockpick									= 40; // Dano causado à gazua após sucesso	
	
	bool InitVehiclesProperties							= true;
}; // Adicionado ponto e vírgula

class alpVehicleBehavior 
{
	string Name;
	float DamageLight;
	float DamageHeavy;
	bool EnableCutDownTrees; 	
	float RequiredImpulseToCutDown;
	float DamageContactCoefHitTree;
	float DamageContactCoefHitAI;
	float DamageContactCoefHitAnyOther;
	float DamageToKillCrew;
	
	// CONSTRUTOR: Atribuição correta dos parâmetros de comportamento físico
	void alpVehicleBehavior(string name, float dmgLight, float dmgHeavy, bool cutTrees, float impulse, float coefTree, float coefAI, float coefOther, float killCrew)
	{
		Name = name;
		DamageLight = dmgLight;
		DamageHeavy = dmgHeavy;
		EnableCutDownTrees = cutTrees;
		RequiredImpulseToCutDown = impulse;
		DamageContactCoefHitTree = coefTree;
		DamageContactCoefHitAI = coefAI;
		DamageContactCoefHitAnyOther = coefOther;
		DamageToKillCrew = killCrew;
	}
}; // Adicionado ponto e vírgula