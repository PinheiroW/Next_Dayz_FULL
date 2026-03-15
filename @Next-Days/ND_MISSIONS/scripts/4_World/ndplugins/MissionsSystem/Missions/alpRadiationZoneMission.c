/**
 * alpRadiationZoneMission.c
 * * MISSION LOGIC: DYNAMIC RADIATION EVENT - Módulo ND_MISSIONS
 * Gerencia eventos de radiação com parâmetros aleatórios e barris interativos.
 */

class alpRadiationZoneMission extends alpMission
{
	// --- Configurações Iniciais ---

	override void OnInit()
	{
		// Configuração de strings de mensagens (Broadcast e Pager)
		alp_SendInfoStart   = ALPMSTYPE.MMRADIATIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMRADIATIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMRADIATIONIN;
		alp_AlertInfoOut    = ALPMSTYPE.SMRADIATIONOUT;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}

	// --- Lógica de Spawn e Loot ---

	override protected bool SpawnLoot(bool missionSecured = false)
	{
		if (super.SpawnLoot(missionSecured))
		{
			SetRadioactiveBarrels(); // Configura barris amarelos como focos de radiação
			return true;
		}
		return false;
	}

	/**
	 * Define os valores de raio e força da radiação baseados no template da missão.
	 */
	override protected void InitMissionValues(int radius = 0, float radiation = 0)
	{	
		if ( !radius && !radiation ) 
		{
			// Seleciona valores aleatórios dentro do range configurado no JSON
			if ( GetTemplate().radiusOfRadiation.Count() == 2 && GetTemplate().strengthOfRadiation.Count() == 2)
			{
				alp_DamageRadius     = Math.RandomIntInclusive(GetTemplate().radiusOfRadiation.Get(0), GetTemplate().radiusOfRadiation.Get(1));
				alp_RadiationStrength = Math.RandomFloat(GetTemplate().strengthOfRadiation.Get(0), GetTemplate().strengthOfRadiation.Get(1));
			}
		}
		
		super.InitMissionValues(radius, radiation);
	}

	// --- Processamento de Radiação ---

	/**
	 * Aplica a radiação continuamente aos jogadores dentro da área.
	 */
	override protected void InteractionOnInsiders(Object obj, float distance) 
	{
		if (obj && obj.IsMan()) 
		{
			SetPlayerInRadiation(PlayerBase.Cast(obj), distance);
		}
	}

	override protected void OnLeave(Object obj)
	{
		super.OnLeave(obj);
		if (obj.IsMan()) 
			CleanPlayer(PlayerBase.Cast(obj));		
	}

	override void OnLeavePlayer(PlayerBase player) 	
	{
		super.OnLeavePlayer(player);
		CleanPlayer(player);		
	}

	override void SetSettingOnEnter()
	{
		// Ativação dinâmica da radiação (Delay para "vazamento")
		if ( GetTemplate().radiationDynamic && !GetTemplate().radiationSpawnedByContaminedArea )
		{
			int timeMs = GetTemplate().radiationDynamic * 1000;		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetSetting, timeMs, false, alpMISSION_SETTING.RADIATION_ACTIVE);
		}
	}

	// --- Gerenciamento de Objetos Radioativos ---

	/**
	 * Localiza barris amarelos e define se podem ser trancados/desativados.
	 */
	private void SetRadioactiveBarrels()
	{
		foreach (alpMissionElement e : alp_LootContainer)
		{
			if ( e.Get() && e.Get().GetType() == "alp_Barrel_Yellow" )			
			{
				alp_Barrel_Yellow barrel = alp_Barrel_Yellow.Cast( e.Get() );
				if (barrel)
				{
					barrel.Open(); // Inicia a emissão visual
					barrel.SetMissionID( GetID() ); 

					// Define se o jogador pode interagir para desativar a radiação do barril
					if (GetTemplate().enableDeactivation) 
						barrel.alp_Lock(false);  
					else 
						barrel.alp_Lock(true);						
				}
			}
		}					
	}

	// --- Helpers de Sistema ---

	private void CleanPlayer(PlayerBase player)
	{
		if (player) GetND().GetRadiation().CleanPlayer(player);
	}

	private void SetPlayerInRadiation(PlayerBase player, float distance)
	{
		if (player) GetND().GetRadiation().SetPlayerInRadiation(player, distance, GetID());
	}
}