/**
 * alpOptionsMS_templates.c
 * * DEFINIÇÃO DE TEMPLATES E DADOS DE MISSÃO - Módulo ND_MISSIONS
 * Gerencia a estrutura de dados enviada ao cliente e as configurações do servidor.
 */

// --- DADOS PARA SINCRONIZAÇÃO COM O CLIENTE ---

class alpMissionData
{
	int id;
	int setting;
	bool active;
	vector position;
	int missionRadius;
	float strengthOfRadiation;
	int missionStarted;
	int startAt;
	int endAt;

	// CORREÇÃO: Removida inconsistência de nomes e alinhado com alpMissionBase
	static alpMissionData CompileDataToClient( alpMissionBase mission )
	{	
		if (!mission) return null;

		alpMissionData data 	= new alpMissionData;
		data.id 				= mission.m_Id; 
		data.setting 			= mission.alp_Setting;
		data.active 			= (mission.alp_Setting & alpMISSION_SETTING.MISSION_STATUS);

		data.position 			= mission.m_Position;
		data.missionRadius 		= 100; // Default fallback
		data.strengthOfRadiation = 0;
		
		return data;		
	}
}

class alpMissionTemplateClient extends alpMissionData
{
	string name;
	int type;
	int requiredLevel;
	int cleanRadius;
	string title;
	int	heightOfRadiationArea;
	float strengthOfRadiationOffset;
	bool enableSineFunction = false;
	float rainingMultiplyRadiation = 0;
	bool showInMap;	
	bool showInMapWhenEnter;
	float aspectRatioB; 
	vector safeRadiusPointA;
	vector safeRadiusPointB;
	int countdownBeforeDespawn;
	int timeToFullRadiation;
	
	// CORREÇÃO: Static não permite override. Removido para compilação limpa.
	static alpMissionTemplateClient CompileTemplateToClient( alpMissionBase mission )
	{
		if (!mission || !mission.GetTemplate()) return null;

		alpMissionTemplateClient data = new alpMissionTemplateClient;
		auto tmpl = mission.GetTemplate();

		data.id 				= mission.m_Id;
		data.setting 			= mission.alp_Setting;
		data.name 				= mission.m_Name;
		data.position 			= mission.m_Position;
		
		data.requiredLevel 		= tmpl.requiredLevel;	
		data.aspectRatioB 		= tmpl.aspectRatioB;
		data.showInMap 			= tmpl.showInMap;
		data.title 				= tmpl.mapTitle;
		
		data.countdownBeforeDespawn = tmpl.countdownBeforeDespawn;
		data.timeToFullRadiation 	= tmpl.timeToFullRadiation;
		
		return data;
	}	
	
	// OTIMIZAÇÃO: Lógica de multiplicador corrigida para float
	float GetRadiusMultiplier()
	{
		float mlt = 1.0;
		int missionTime = alp_ND_base.GetTimeStamp();
		
		if ( timeToFullRadiation > 0 && startAt > 0 ) 
		{
			float fullRadMs = timeToFullRadiation * 1000.0;
			if ( (missionTime - startAt) < fullRadMs ) 
			{
				mlt = ( missionTime - startAt ) / fullRadMs; // Agora funcional (float)
			}
		}

		if ( countdownBeforeDespawn > 0 && endAt > 0 ) 
		{
			float cdTimeMs = countdownBeforeDespawn * 1000.0;
			if ( missionTime > endAt ) 
			{
				float progress = ( missionTime - endAt ) / cdTimeMs;
				mlt = Math.Clamp(1.0 - progress, 0.0, 1.0);
			}
		}
		return mlt;
	}	
}

// --- CONFIGURAÇÕES DE TEMPLATE (SERVIDOR) ---

class alpMissionTemplate 
{
	bool active;
	string missionGroup;
	bool isManaged;
	bool isActive;
	int saveMissionStage;
	int nominal; 
	int lifeTime; 
	int restock;
	int safeRadius;
	int cleanRadius;

	ref array<string> eventOnStartSpawn = new array<string>;
	ref array<string> eventOnEndDespawn = new array<string>;
	
	ref array<ref array<float>> position = new array<ref array<float>>;
	
	int requiredLevel;
	string mapTitle;
	bool showInMap;
	bool sendInfo;
	string startMessage;
	string endMessage;

	// Adicionados para suporte a radiação conforme lógica do mod
	int timeToFullRadiation = 0;
	int countdownBeforeDespawn = 0;
	float aspectRatioB = 0;
}

class alpMissionAI 
{
	bool spawned = false;
	float chance;
	string className;
	string type;
	ref array<int> nominal = new array<int>;
	int spawnRadius = 0;
	vector position;
}

class alpLoot 
{
	string title;
	string type;
	float chance;
	int quantmin;
	int quantmax;
	ref array<ref array<string>> items = new array<ref array<string>>;
}

class alpProtectionItem 
{
	string type;
	float biological;
	float chemical;
	float radiation;
	bool hasdosimeter;			
	float filterefficiency;
}