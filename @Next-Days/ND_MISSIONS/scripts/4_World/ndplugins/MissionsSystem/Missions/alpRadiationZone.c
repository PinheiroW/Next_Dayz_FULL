/**
 * alpRadiationZone.c
 * * MISSION LOGIC: RADIATION ZONE - Módulo ND_MISSIONS
 * Gerencia zonas contaminadas, dano por proximidade e barris radioativos.
 */

class alpRadiationZone extends alpMission
{
	// --- Configurações Iniciais ---

	override void OnInit()
	{
		// Configuração de mensagens específicas de Radiação
		alp_SendInfoStart   = ALPMSTYPE.MMRADIATIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMRADIATIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMRADIATIONIN;
		alp_AlertInfoOut    = ALPMSTYPE.SMRADIATIONOUT;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}

	// --- Lógica de Entrada e Saída ---

	override protected void OnEnter(Object obj)
	{
		super.OnEnter(obj);
		// A ativação da radiação para o player ocorre no OnUpdate via distância
	}	
	
	override protected void OnLeave(Object obj)
	{
		super.OnLeave(obj);
		if (obj.IsMan()) 
			CleanPlayer(PlayerBase.Cast(obj)); // Remove efeitos visuais/sonoros		
	}

	override void OnLeavePlayer(PlayerBase player) 	
	{
		super.OnLeavePlayer(player);
		CleanPlayer(player);		
	}

	// --- Lógica de Atualização (Tick) ---

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		// Se a radiação estiver ativa na missão, aplica o dano aos jogadores próximos
		if ( (alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE) )
		{
			foreach (alpMissionInsider ins : alp_Insiders)
			{
				if ( ins.alp_DamageZone )
				{
					// Calcula intensidade baseada na distância do centro
					float distance = vector.Distance(ins.GetObject().GetPosition(), GetPosition());
					SetPlayerInRadiation(PlayerBase.Cast(ins.GetObject()), distance);
				}
			}
		}
	}

	// --- Gerenciamento de Loot e Configurações ---

	override protected bool SpawnLoot(bool missionSecured = false)
	{
		if (super.SpawnLoot(missionSecured))
		{
			SetRadioactiveBarrels(); // Configura barris especiais após o spawn do loot
			return true;
		}
		return false;
	}
	
	override void SetSettingOnEnter()
	{
		// Lógica para ativação de radiação dinâmica baseada em tempo
		if ( GetTemplate().radiationDynamic && !GetTemplate().radiationSpawnedByContaminedArea )
		{
			int timeMs = GetTemplate().radiationDynamic * 1000;		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetSetting, timeMs, false, alpMISSION_SETTING.RADIATION_ACTIVE);
		}
	}

	// --- Métodos Auxiliares ---

	/**
	 * Configura barris amarelos como objetos pertencentes a esta missão radioativa.
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
					barrel.SetMissionID( GetID() );
				}
			}
		}
	}

	/**
	 * Limpa os estados de radiação do jogador (chamado via Plugin de Radiação).
	 */
	private void CleanPlayer(PlayerBase player)
	{
		if (player)
			GetND().GetRadiation().CleanPlayer(player);
	}

	/**
	 * Define o nível de exposição do jogador baseado na distância.
	 */
	private void SetPlayerInRadiation(PlayerBase player, float distance)
	{
		if (player)
			GetND().GetRadiation().SetPlayerInRadiation(player, distance, GetID());
	}
}