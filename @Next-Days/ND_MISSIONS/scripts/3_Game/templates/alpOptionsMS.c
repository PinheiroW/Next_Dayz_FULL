/**
 * alpOptionsMS.c
 * * CONFIGURAÇÕES GERAIS DE MISSÕES E RADIAÇÃO - Módulo ND_MISSIONS
 * Define os parâmetros de comportamento do sistema, HUD, e mecânicas de NBC.
 */

class alpMSoptions 
{
	bool ShowRealPlayerName				= true;
	bool RequiresWalkieTalkie			= true; // Requisito de rádio para notificações e posição
	bool BaseRadioUncoverAllMissions	= true;
	float RequiredTunedFrequency		= 0;
	bool ShowPlayersOnMap				= false; // Marcadores no mapa
	bool SetMapPositionToPlayer			= false;
	bool ShowMissionRadius				= true;
	string LabelOfSafeZone 				= "";
	bool DamageSpawnedVehiclesInMission	= true;	
	bool DeleteDeadMissionAI			= true;
	bool DeleteAliveMissionAI			= false;
	float AllowedRatioAliveMissionAI	= 0.1;

	bool EnableSafePosition				= false;
	bool UseDefaultSafePosition			= false;
	ref array<ref array<float>> SafePositions;
	
	ref array<vector> ArtilleryPositions;

	// --- CONFIGURAÇÕES DE RADIAÇÃO ---
	int TimeToEffectRadiationProtect	= 10; // Duração em segundos
	int EffectAntiRadBlockPills			= 100; // Redução de doses (Sv/h)
	float AutoRadiationReduce			= 0.1; // Redução natural fora da zona (10 Sv/h)
	int GeigerSoundEffect_Radiation_Low	= 5;
	int GeigerSoundEffect_Radiation_Medium = 50;
	int GeigerSoundEffect_Radiation_High = 100;
	
	// float ArmorRatioNBC				= 0.95; // Default 0.9
	ref array<float> EfficiencyNBCbyState;
	
	int WaterDrainInRadiationPerSec		= 5; // Top hydration é 5000
	int RadiationCapForCalc				= 200; // x / 200 * (10/2) * ( 2 - shield / 100 );
	float ArmorRatioNBCforWaterDrain	= 0.80;
	
	bool HeadgearsDetermineBodyProtection = false; // Corrigido de 0 para false
	
	bool NotRequiredFilterForRadiation	= false;

	int RadiationLimitToContamineItems	= 50;	
	bool EnableFoodDecontamination		= false; // Corrigido de 0 para false

	// CONSTRUTOR: Garante a inicialização dos arrays para evitar crashes por Null Pointer
	void alpMSoptions()
	{
		SafePositions = new array<ref array<float>>;
		
		ArtilleryPositions = {
			"-500.00 165.00 5231.69",
			"-500.00 300.00 9934.41",
			"10406.86 192.00 15860.00",
			"4811.75 370.00 15860.00"
		};
		
		EfficiencyNBCbyState = {1.0, 0.95, 0.75, 0.5, 0};
	}
}