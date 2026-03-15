/**
 * alpND.c
 * * CENTRAL CORE MANAGER - Módulo ND_MISSIONS (4_World)
 * O coração do mod: gerencia plugins, missões, economia e eventos globais.
 */

/**
 * Singleton: Fornece acesso global à instância do mundo Next-Days.
 */
alpND_world GetND()
{
	if ( !alp_ND_base )
	{
		alp_ND_base = new alpND_world();						
	}
	
	return alpND_world.Cast( alp_ND_base );
}

class alpND_world extends alpND_base
{
	/**
	 * Inicialização principal: Registra plugins e configura sistemas de arquivos.
	 */
	override protected void Init()
	{	
		// --- Registro de Plugins Fundamentais ---
		AddPlugin( new alpPluginNDoptions( alpPLUGIN_BASE_ID.OPTIONS, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDnotf( alpPLUGIN_BASE_ID.NOTF, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDinfo( alpPLUGIN_BASE_ID.INFO, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDrp( alpPLUGIN_BASE_ID.RP, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDresources( alpPLUGIN_BASE_ID.RESOURCES, alpPLUGIN_BASE_EVENTS.ONCONNECT ) );
	 
		// Inicialização de Quests para compatibilidade
		alp_ActiveQuests = new array<ref alpRegisteredQuest>;
		
		// --- Lógica Lado Servidor (Multiplayer) ---
		if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
		{		
			if ( !FileExist(ALP_MISSIONSYSTEM_FOLDER) ) MakeDirectory(ALP_MISSIONSYSTEM_FOLDER);

			// Configurações Básicas do Sistema de Missões
			JsonFileLoader<autoptr alpMSoptions>.JsonLoadFile(ALP_MISSIONS_DEFAULT_FILE, alp_OptionsMS );	
			if ( !alp_OptionsMS )
			{
				alp_OptionsMS = new alpMSoptions;
				JsonFileLoader<autoptr alpMSoptions>.JsonSaveFile(ALP_MISSIONS_DEFAULT_FILE, alp_OptionsMS);
			}
			else
			{
				JsonFileLoader<autoptr alpMSoptions>.JsonSaveFile(ALP_MISSIONS_DEFAULT_FILE, alp_OptionsMS);
			}

			// Gerenciamento de Quests de Comerciantes
			JsonFileLoader<array<ref alpTraderQuest>>.JsonLoadFile(ALP_MISSIONSYSTEM_QUESTS, alp_Quests );	
			if ( !alp_Quests )
			{
				alp_Quests = new array<ref alpTraderQuest>;				
				alp_Quests.Insert( new alpTraderQuest( 1 ) ); // Exemplo inicial
				JsonFileLoader<array<ref alpTraderQuest>>.JsonSaveFile(ALP_MISSIONSYSTEM_QUESTS, alp_Quests);
			}

			// Inicialização de Logs com Carimbo de Data/Hora
			int y, mm, d, h, m, s;
			GetYearMonthDayUTC(y, mm, d);
			GetHourMinuteSecondUTC(h, m, s);
			string timeStamp = y.ToString() + "-" + mm.ToString() + "-" + d.ToString() + "_" + h.ToString() + "-" + m.ToString() + "-" + s.ToString() + ".log";
			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CreateNewTraderLogFile, 1, false, timeStamp);
		}

		// --- Lógica Lado Cliente ---
		if ( GetGame().IsClient() )
		{
			alp_OptionsMS = new alpMSoptions;			
			alp_MarkedMission = new array<ref alpMissionTemplateClient>;
			alp_Quests = new array<ref alpTraderQuest>;
		}

		// Registro do Plugin de Missões (Fim da cadeia de init)
		AddPlugin( new alpPluginNDmissionsSystem( alpPLUGIN_BASE_ID.MS, alpPLUGIN_BASE_EVENTS.START | alpPLUGIN_BASE_EVENTS.UPDATE | alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN | alpPLUGIN_BASE_EVENTS.FINISH ) );
	}	

	/**
	 * Atualiza marcadores de missão no mapa baseados na rádio ou exploração.
	 */
	override void MarkMissionOnMap()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		alp_MarkedMission = new array<ref alpMissionTemplateClient>;
									
		foreach ( alpMissionBase mission : GetMS().alp_Missions )
		{			
			if ( mission.IsActive() )
			{
				alpMissionTemplateClient data = alpMissionTemplateClient.Cast( alpMissionTemplateClient.CompileDataToClient(mission) );
				 
				if ( data.showInMapWhenEnter )
				{
					// Exibe se foi tocada ou se o jogador possui rádio de base
					if ( mission.alp_Touched || mission.alp_WasTouched || player.GetRP().GetWalkieTalkieType() & alpRADIO.HAS_BASE_RADIO )
					{
						mission.alp_WasTouched = true;
						alp_MarkedMission.Insert( data );
					}
				}
				else
				{
					alp_MarkedMission.Insert( data );
				}
			}											
		}
	}

	override int HasWalkieTalkie()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		return player.GetRP().HasWalkieTalkie();		
	}
	
	override int GetRadiationLevel()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if ( player )
		{	
			return alpGeigerSound.GetSoundTypeValue( player.GetRP().GetRadiation() );
		}
		return alpGEIGERSOUNTYPE.NONE;			
	}	

	/**
	 * Propaga o evento de Spawn para plugins registrados.
	 */
	override void OnSpawn( Man player )
	{
		PlayerBase p = PlayerBase.Cast( player );
		if ( p && !p.alp_IsEventOnRunActive )
		{
			foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONSPAWN )
			{
				plugin.OnSpawn( player );
			}					
			p.alp_IsEventOnRunActive = true;
		}
	}	

	// --- Getters de Plugins (Casting Seguro) ---

	alpPluginNDnotf GetNotf() {
		return alpPluginNDnotf.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.NOTF ) );
	}	
	
	alpPluginNDinfo GetInfo() {
		return alpPluginNDinfo.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.INFO ) );
	}	
	
	alpPluginNDrp GetRP() {
		return alpPluginNDrp.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.RP ) );
	}			
	
	alpPluginNDmissionsSystem GetMS() {
		return alpPluginNDmissionsSystem.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.MS ) );
	}		
	
	alpPluginNDresources GetResources() {
		return alpPluginNDresources.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.RESOURCES ) );
	}	

	// --- Sistema de Logs do Trader ---

	void CreateNewTraderLogFile(string timeStamp)
	{		
		if ( GetMS().GetOptoinsTrader().MakeTraderLogs ) 
		{			
			string path = ALP_LOGS + "trader_" + timeStamp;
			m_FileTraderLogs = OpenFile( path, FileMode.WRITE );
		}			
	}
	
	void MakeTraderLog(string timeStamp, PlayerBase player, int stockID, int akce, string item, int count, int price) 
	{
		price = Math.AbsInt( price );
		if ( m_FileTraderLogs && player ) 
		{
			string akceTitle = ( akce == 0 ) ? "buyed" : "sold";
			item = alpUF.GetDisplayName(item);
			
			string log = string.Format("%1 | %2 %3 | %4 | %5 | x %6 | for %7 | trader(StockID) %8 | %9", 
				timeStamp, player.GetIdentity().GetPlainId(), player.GetIdentity().GetName(), 
				akceTitle, item, count.ToString(), price.ToString(), stockID.ToString(), player.GetPosition().ToString());
			
			FPrintln( m_FileTraderLogs, log );	
		}
	}
}