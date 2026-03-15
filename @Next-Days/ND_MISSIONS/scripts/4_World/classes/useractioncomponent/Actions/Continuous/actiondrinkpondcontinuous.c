/**
 * actiondrinkpondcontinuous.c
 * * AÇÃO CONTÍNUA (BEBER EM LAGOAS/POÇAS) - Módulo ND_MISSIONS
 * Gerencia o consumo de água na natureza, aplicando contaminação se a zona for radioativa.
 */

modded class ActionDrinkPondContinuous
{
	/*
	// BLOCO DE COMPATIBILIDADE NAMALSK MANTIDO COMO REGISTRO HISTÓRICO
	override void OnFinishProgressServer( ActionData action_data )
	{
		Param1<float> nacdata = Param1<float>.Cast( action_data.m_ActionComponent.GetACData() );
		float amount = nacdata.param1 * UAQuantityConsumed.DRINK;

		EConsumeType m_WaterSourceType = EConsumeType.ENVIRO_POND;
		vector pos_cursor = action_data.m_Target.GetCursorHitPos();
		string surfType;
		int liquidType;
		g_Game.SurfaceUnderObject(action_data.m_Player, surfType, liquidType);

		if ( liquidType == LIQUID_WATER )
		{
			if ( action_data.m_Player.GetRP().IsRadiationHigh() )
			{
				m_WaterSourceType = alpeConsumeType.ENVIRO_POND_CONTAMINED_FREEZING;
			}
			else
			{
				m_WaterSourceType = EConsumeTypeNamalsk.ENVIRO_FREEZING;
			}
		}
		else if ( ( surfType == "nam_snow" ) || ( surfType == "nam_seaice" ) || ( surfType == "nam_lakeice_ext" ) )
		{
			
			if ( action_data.m_Player.GetRP().IsRadiationHigh() )
			{
				m_WaterSourceType = alpeConsumeType.ENVIRO_SNOW_CONTAMINED_FROZEN;
			}
			else
			{
				m_WaterSourceType = EConsumeTypeNamalsk.ENVIRO_FROZEN;
			}			
		}

		action_data.m_Player.Consume( NULL, amount, m_WaterSourceType );
	}
	*/
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		// OTIMIZAÇÃO E SEGURANÇA: Validação em cascata contra Null Pointers
		if (!action_data || !action_data.m_Player)
			return;

		// Busca a quantidade consumida pelo tempo da animação de forma segura
		Param1<float> nacdata;
		if (action_data.m_ActionComponent)
		{
			nacdata = Param1<float>.Cast(action_data.m_ActionComponent.GetACData());
		}
		
		// Quantidade estática original do seu mod
		float amount = UAQuantityConsumed.DRINK;
		
		// SEGURANÇA: Verifica se o módulo RP do jogador existe antes de avaliar a radiação
		if (action_data.m_Player.GetRP())
		{
			// LÓGICA MANTIDA: Aplica água contaminada se a radiação ambiente for alta
			if (action_data.m_Player.GetRP().IsRadiationHigh())
			{
				action_data.m_Player.Consume(NULL, amount, alpeConsumeType.ENVIRO_POND_CONTAMINED);
			}
			else
			{
				action_data.m_Player.Consume(NULL, amount, EConsumeType.ENVIRO_POND);
			}
		}
		else
		{
			// Fallback de segurança: Caso o RP não esteja carregado, bebe água normal da lagoa
			action_data.m_Player.Consume(NULL, amount, EConsumeType.ENVIRO_POND);
		}
	}
}; // Adicionado ponto e vírgula obrigatório