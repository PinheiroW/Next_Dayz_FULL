/**
 * alpMission.c
 * CORE MISSION CLASS - Módulo ND_MISSIONS
 * Governa a inteligência, persistência e spawn de todos os eventos.
 */

class alpMission extends alpMissionBase
{
	// --- Variáveis de Controle e Quest ---
	int alp_Count_ALL_AI;
	int alp_FirstEnterTime;
	bool alp_AllowedFirstEnterEcho;
	string alp_WantedItem;	
	int alp_NPC_id;
	int alp_QuestID;

	// --- Inicialização e Configuração de Flags ---
	
	void SetQuestMissions(int npc_id, int quest_id, string wantedItem)
	{
		alp_WantedItem = wantedItem;
		alp_NPC_id = npc_id;
		alp_QuestID = quest_id;
	}

	protected void InitVariables(int setting = 0)
	{
		alp_StartAt = 0;
		alp_EndAt = 0;
		
		// Configuração de Persistência (Hive)
		if ( GetTemplate().saveMissionStage ) {
			alp_Setting = (setting) ? setting : (alp_Setting | alpMISSION_SETTING.SAVE_STAGE);
		} else {
			alp_Setting = 0;				
		}

		if ( alp_Setting == alpMISSION_SETTING.SAVE_STAGE || alp_Setting == 0 ) {
			SetSetting( alpMISSION_SETTING.MISSION_IDLE );	
		}

		// Configurações de Visibilidade e Status
		if ( GetTemplate().showMissionStatus ) SetSetting( alpMISSION_SETTING.MISSION_STATUS );	
		if ( GetTemplate().isActive ) RemoveSetting( alpMISSION_SETTING.MISSION_IDLE );			
		
		if ( GetTemplate().showNameWhoStartedMission ) {
			alp_IsFirstEnter = true;
			alp_AllowedFirstEnterEcho = true;
			alp_FirstEnterTime = 180;
		}
		
		if ( GetTemplate().isPrivateMission ) alp_MissionStarted = GetND().GetTimeStamp();
		
		// Inicialização de Arrays de Objetos
		alp_LootContainer = new array< ref alpMissionElement>;
		alp_Structures = new array< ref alpMissionElement>;
		alp_ToxicZones = new array< ref alpMissionElement>;
		alp_NPC = new array< ref alpMissionElement>;
		alp_Vehicles = new array< ref alpMissionElement>;
		
		alp_StaticAI = new array< EntityAI>;
		alp_DynamicAI = new array< EntityAI>;
		alp_Insiders = new array<ref alpMissionInsider>;	
		
		alp_OccupiedManagement.ClearFlags();
	}

	// --- Ciclo de Vida: Spawning e Loading ---

	override alpMissionBase SpawnMission(vector pos = "0 0 0", vector angle = "0 0 0", int parentID = -1 )
	{
		Print("ALPMS: spawning mission: " + alp_Name);
		InitVariables();

		if ( GetTemplate().isManaged && GetTemplate().isPositionRelativeToMasterMission ) {
			alp_Position = pos; alp_Angle = angle;
		}		
		
		m_Hive = alpMHIVE.RegisterMission(this);
		m_Hive.UpdateSetting(alp_Setting);

		if ( IsMissionCreated() ) {
			alp_Active = true;
			alp_ParendId = parentID;
			InitMissionValues();
			
			int maxRadius = Math.Max(alp_SafeRadius, alp_DamageRadius);
			alp_CleanRadius = Math.Max( alp_CleanRadius, maxRadius);
			EstimateSides(); 
		
			if (!IsCleared()) SpawnAIstatic();

			alp_Restock -= 1;
			alp_StartAt = GetND().GetTimeStamp();
			GetND().GetMS().SendRPC_Update( this );
									
			if ( GetTemplate().sendInfo && GetTemplate().startMessage != "" ) {				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( GetND().GetNotf().SendMissionMessage, 1000, false, alp_SendInfoStart, GetID(), GetTemplate().startMessage, GetPosition(), null, true );
			}
			
			GetND().GetMS().ChangeGroupLimit( GetTemplate().missionGroup, 1);
			m_Hive.InitMission(this);
			return this;
		}
		
		RespawnMission( GetMissionRespawnTime() );			
		return null;
	}

	void LoadMission( alpMissionStore s )
	{
		m_Hive = s;
		InitVariables(s.m_Setting);	
		alp_EventOnEnter = true;

		LoadStructures();
		LoadControlPanels();
		LoadLoots();
		LoadCars();
		LoadToxicZones();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.LoadNPCs, 2000);
			
		alp_Active = true;
		alp_Position = s.m_Position; alp_Angle = s.m_Angle; alp_ParendId = s.m_ParendId;	
		
		InitMissionValues(s.m_DamageRadius, s.m_Radiation);
		alp_CleanRadius = s.m_CleanRadius;
		EstimateSides();

		if (!IsCleared()) SpawnAIstatic();
		GetND().GetMS().SendRPC_Update( this );
		GetND().GetMS().ChangeGroupLimit( GetTemplate().missionGroup, 1);		
	}

	// --- Lógica de Update e Monitoramento ---

	override void ManageMission(float timeslice)
	{
		if ( !IsActive() ) return;
		
		alp_MissionTime = GetND().GetTimeStamp();
		UpdateInsiders();
		
		if ( !IsMissionEnded() ) CheckMissionStage(timeslice);
		
		if ( IsMissionEnded() ) {
			if ( !alp_EndAt ) alp_EndAt = GetND().GetTimeStamp();
			if ( !alp_EventOnSecured ) {
				EventOnMissionSecured();
				alp_EventOnSecured = true;
			}
			if ( IsCountdownExpired(timeslice) && (GetTemplate().forceCheckDespawnCondition || IsAreaClear()) ) {
				DespawnMission();
				return;											
			}
		}

		// Lógica de Manutenção de Área
		if ( IsAreaClear() ) {
			if ( !IsCleared() && !alp_SpawnedStaticAI && alp_AvailableStaticInRestockAI ) SpawnAIstatic();
			
			alp_RespawnLootLifeTime -= timeslice;
			if ( IsLootRespawnEnabled() && alp_RespawnLootLifeTime <= 0 ) {
				alp_RespawnLootLifeTime = GetTemplate().timeRespawn; 	
				RespawnLoot();
			}
		}

		// Sincronização RPC com Clientes
		if ( alp_LastSetting != alp_Setting ) {
			if ( IsMissionEnded() && alp_CountdownDespawn ) {
				GetND().GetMS().SendRPC_Update( this, null);
			} else {
				GetND().GetMS().SendRPC_Update( this, null, false, true );
			}
			alp_LastSetting = alp_Setting;									
		}
	}

	// --- Limpeza e Despawn ---

	override void DespawnMission()
	{		
		alp_Active = false;
		DespawnMissionObjects();
		CleanUp();
	
		if ( GetTemplate().sendInfo && GetTemplate().endMessage != "" ) {
			GetND().GetNotf().SendMissionMessage( alp_SendInfoEnd, GetID(), GetTemplate().endMessage, GetPosition(), null, true);
		}					
		
		GetND().GetMS().SendRPC_Update( this );
		RespawnMission( GetMissionRespawnTime() );	
		GetND().GetMS().ChangeGroupLimit( GetTemplate().missionGroup, -1);			
		alpMHIVE.UnRegisterMission( GetID() );
	}
}