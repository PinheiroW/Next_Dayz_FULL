/**
 * alpMissionBase.c
 * * CLASSE BASE DAS MISSÕES - Módulo ND_MISSIONS
 * Define o comportamento, estados e persistência de todas as missões do sistema.
 */

enum alpMISSION_SETTING
{
	NONE = 0,
	MISSION_STATUS = 1,
	RADIATION_ACTIVE = 2,
	SAVE_STAGE = 4,
	MISSION_IDLE = 8, // Antes de alguém iniciar a missão
	MISSION_UNSECURED = 16,
	MISSION_CLEARED = 32,
	MISSION_OCCUPIED = 64,
	MISSION_HOSTILE_OCCUPIED = 128,
	MISSION_SECURED = 256,
	MISSION_EXPIRED = 512,
	MISSION_FAILED = 1024
}; // Corrigido: Adicionada vírgulas e fechamento correto

enum alpMISSIONTRIGGER
{
	ENABLED = 1,
	ISPERSISTENT = 2,
	ACTIVATION_DESPAWN_MISSION = 4,
	ENABLED_DEACTIVATION = 8,
	ISACTIVATED = 16,
	ISCOUNTDOWNED = 32,
	NOTALIVE_DEACTIVATE = 64,
	CANBELOCKED = 128,
	ISLOCKED = 256,
	CANBEDAMAGED = 512,
	ISDAMAGED = 1024,
	ISRUINED = 2048,
	ECHO_GET_PLAYERS_NEARBY = 4096,
	SWAP_DEFAULT_TITLE = 8192,
	CAN_BE_USED_ONCE = 16384,
	IS_DATA_DOWNLOADED = 32768,
	IS_DATA_DELETED = 65536
}; // Corrigido: Adicionada vírgulas e fechamento correto

class alpMissionBase
{
	int m_Id;
	int m_Seed;
	int m_ParentID = -1;
	string m_Name;
	string m_Description;
	vector m_Position;
	vector m_Angle;

	bool alp_SpawnInNightOnly = false;
	int alp_Setting = alpMISSION_SETTING.NONE;
	
	ref alpOptionsMS_templates m_Template; // CORREÇÃO: ref em vez de autoptr
	ref alpMissionStore m_Store;

	void alpMissionBase(int id, string name)
	{
		m_Id = id;
		m_Name = name;
		m_Seed = Math.RandomInt(0, int.MAX);
	}

	void ~alpMissionBase() {}

	int GetID() { return m_Id; }
	string GetName() { return m_Name; }
	vector GetPosition() { return m_Position; }
	
	void SetPosition(vector pos) { m_Position = pos; }
	void SetAngle(vector angle) { m_Angle = angle; }

	// OTIMIZAÇÃO: Lógica de contagem de jogadores mais limpa
	int GetPlayersCount()
	{
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		return players.Count();
	}

	float GetMissionRespawnTime()
	{
		float respawnTime = GetTemplate().missionRespawn;
		bool isNight = GetGame().GetWorld().IsNight();
		
		if (alp_SpawnInNightOnly && !isNight)
		{
			respawnTime = 30; // Tempo reduzido para skip de dia
		}
		
		if (GetTemplate().spawnWhenActiveMissions.Count() || GetTemplate().spawnWhenDeactiveMissions.Count()) 
		{
			respawnTime = Math.Clamp(respawnTime, 3, 86400);
		}
				
		return respawnTime;
	}

	alpOptionsMS_templates GetTemplate()
	{
		if (!m_Template)
		{
			m_Template = alpPluginNDmissionsSystem.Cast(alpPluginManager.GetPlugin(alpPluginNDmissionsSystem)).GetTemplate(m_Name);
		}
		return m_Template;
	}

	// Lógica de Persistência preservada e atualizada para Enfusion moderna
	protected void SaveMissionStage()
	{
		if (!GetGame().IsServer()) return;

		int flags = alp_Setting;
		if (IsMissionEnded()) 
		{
			flags = 0;
			flags = flags | alpMISSION_SETTING.SAVE_STAGE;
		}

		if (m_Store)
		{
			m_Store.m_Setting = flags;
			m_Store.m_Position = m_Position;
			alpMHIVE.Save();
		}
	}

	bool IsMissionEnded()
	{
		return (alp_Setting & alpMISSION_SETTING.MISSION_SECURED || alp_Setting & alpMISSION_SETTING.MISSION_EXPIRED || alp_Setting & alpMISSION_SETTING.MISSION_FAILED);
	}

	// Funções de Interface de Missão (Stubs para serem sobrescritos)
	alpMissionBase SpawnMission(vector pos = "0 0 0", vector angle = "0 0 0", int parentID = -1) { return null; }
	void ManageMission(float timeslice) {}
	void DespawnMission() {}

	void OnMissionStart() { SaveMissionStage(); }
	void OnMissionFinish() { SaveMissionStage(); }
}