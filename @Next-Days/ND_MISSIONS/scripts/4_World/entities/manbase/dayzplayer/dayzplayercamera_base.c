/**
 * dayzplayercamera_base.c
 * * MODDED CAMERA SYSTEM - Módulo ND_MISSIONS
 * Gerencia efeitos visuais de radiação integrados à Visão Noturna e Óticas.
 */

modded class DayZPlayerCameraBase extends DayZPlayerCamera
{
	int last_Radiation;
	
	// IDs internos para categorização de periféricos visuais
	int ALP_GOOGLES = 1;
	int ALP_OPTICS = 2;
	int ALP_OPTICS_DAY = 3;

	/**
	 * Obtém o nível atual de radiação do jogador para converter em efeito visual.
	 */
	int GetRaditaionLevel()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player && player.GetRP())
		{	
			// Converte o valor bruto de radiação em um enum de som/visão (NONE a VERYHIGH)
			int radiation = alpGeigerSound.GetSoundTypeValue(player.GetRP().GetRadiation());
			return radiation;
		}
		return alpGEIGERSOUNTYPE.NONE;	
	}

	/**
	 * Sobrescreve a ativação da visão noturna para injetar filtros de radiação.
	 */
	override bool IsNVvision(int type)
	{
		int nv;
		if (type == NVTypes.NV_GOGGLES)
		{
			nv = GetNV_ID(ALP_GOOGLES);
			PPERequesterBank.GetRequester(PPERequesterBank.REQ_CAMERANV).Start(new Param1<int>(nv));
			GetGame().GetMission().GetEffectWidgets().AddActiveEffects({EffectWidgetsTypes.NVG_OCCLUDER});
			
			// Inicia loop de atualização do efeito visual
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateCameraNVALP, 1000, false, PlayerBase.Cast(GetGame().GetPlayer()));
			return true;
		}
		
		if (type == NVTypes.NV_OPTICS)
		{
			nv = GetNV_ID(ALP_OPTICS);
			PPERequesterBank.GetRequester(PPERequesterBank.REQ_CAMERANV).Start(new Param1<int>(nv));
			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateCameraNVALP, 1000, false, PlayerBase.Cast(GetGame().GetPlayer()));
			return true;
		}
		
		return super.IsNVvision(type);
	}

	/**
	 * Loop de atualização que verifica se o nível de radiação mudou e ajusta o PPE.
	 */
	void UpdateCameraNVALP(PlayerBase player)
	{
		if (!player) return;
		
		int radiation = GetRaditaionLevel();
		
		// Se a radiação mudou, reinicia o efeito visual com o novo filtro
		if (radiation != last_Radiation)
		{
			last_Radiation = radiation;
			
			// Força a atualização do NV vision chamando o método original de ID
			// Isso fará com que o PPE mude dinamicamente baseado no last_Radiation
			if (player.IsNVGWorking())
			{
				IsNVvision(NVTypes.NV_GOGGLES);
			}
		}
		
		// Continua o loop enquanto o jogador estiver em visão especial
		if (player.IsNVGWorking())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateCameraNVALP, 1000, false, player);
		}
	}

	/**
	 * Mapeamento de IDs de Post-Processing (PPE) baseados na radiação.
	 */
	int GetNV_ID(int type)
	{
		if (type == ALP_GOOGLES)
		{
			switch (last_Radiation)
			{
				case alpGEIGERSOUNTYPE.NONE:     return PPERequester_CameraNV.NV_DEFAULT_GLASSES;
				case alpGEIGERSOUNTYPE.LOW:      return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_LOW;
				case alpGEIGERSOUNTYPE.MEDIUM:   return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_MEDIUM;
				case alpGEIGERSOUNTYPE.HIGH:     return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_HIGH;
				case alpGEIGERSOUNTYPE.VERYHIGH: return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_VERYHIGH;
			}
		}
		else // Optics ou DayVision
		{
			switch (last_Radiation)
			{
				case alpGEIGERSOUNTYPE.NONE:     return PPERequester_CameraNV.NV_DAYTIME_OPTICS;
				case alpGEIGERSOUNTYPE.LOW:      return PPERequester_CameraNV.NV_DAYTIME_RAD_LOW;
				case alpGEIGERSOUNTYPE.MEDIUM:   return PPERequester_CameraNV.NV_DAYTIME_RAD_MEDIUM;
				case alpGEIGERSOUNTYPE.HIGH:     return PPERequester_CameraNV.NV_DAYTIME_RAD_HIGH;
				case alpGEIGERSOUNTYPE.VERYHIGH: return PPERequester_CameraNV.NV_DAYTIME_RAD_VERYHIGH;
			}
		}
		return PPERequester_CameraNV.NV_DEFAULT_GLASSES;
	}
}