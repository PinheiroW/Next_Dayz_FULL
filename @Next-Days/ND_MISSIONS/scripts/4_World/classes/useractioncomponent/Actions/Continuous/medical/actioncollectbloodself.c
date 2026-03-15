/**
 * actioncollectbloodself.c
 * * AÇÃO MÉDICA (COLETAR SANGUE DE SI MESMO) - Módulo ND_MISSIONS
 * Garante que o sangue coletado seja arruinado se o jogador estiver contaminado por radiação.
 */

modded class ActionCollectBloodSelf
{
	override void OnEndServer(ActionData action_data)
	{
		// Executa o comportamento padrão do jogo (coletar o sangue)
		super.OnEndServer(action_data);

		// OTIMIZAÇÃO E SEGURANÇA: Previne Crash (NPE) caso a ação seja interrompida abruptamente
		if (!action_data || !action_data.m_Player || !action_data.m_MainItem)
		{
			return;
		}

		// SEGURANÇA: Confirma que a extensão de Roleplay do jogador está carregada
		if (action_data.m_Player.GetRP())
		{
			// LÓGICA MANTIDA: Se o jogador tem radiação (Estágio > 0), o sangue é arruinado (0 HP)
			if (action_data.m_Player.GetRP().GetRadiationSickStage() > 0)
			{
				ItemBase blood = action_data.m_MainItem;
				
				if (blood)
				{
					blood.SetHealth("", "", 0);	
				}
			}
		}
	}
};