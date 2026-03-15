/**
 * actioncollectbloodtarget.c
 * * AÇÃO MÉDICA (COLETAR SANGUE DE ALVO) - Módulo ND_MISSIONS
 * Garante que o sangue coletado de outro jogador seja arruinado se ele estiver com radiação.
 */

modded class ActionCollectBloodTarget
{
	override void OnEndServer(ActionData action_data)
	{
		// Executa o comportamento padrão do jogo (coletar o sangue do alvo)
		super.OnEndServer(action_data);

		// OTIMIZAÇÃO E SEGURANÇA: Previne Crash (NPE) caso a ação/alvo sejam interrompidos
		if (!action_data || !action_data.m_Target || !action_data.m_MainItem)
		{
			return;
		}

		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());						
		ItemBase blood = action_data.m_MainItem;
		
		// LÓGICA MANTIDA E BLINDADA: Verifica se o alvo é válido, tem RP e está irradiado
		if (ntarget && ntarget.GetRP() && ntarget.GetRP().GetRadiationSickStage() > 0)
		{
			// SEGURANÇA: Confirma que o item (bolsa de sangue) existe antes de danificá-lo
			if (blood)
			{
				// Arruína o sangue coletado
				blood.SetHealth("", "", 0);	
			}
		}
	}
}; // Adicionado ponto e vírgula obrigatório