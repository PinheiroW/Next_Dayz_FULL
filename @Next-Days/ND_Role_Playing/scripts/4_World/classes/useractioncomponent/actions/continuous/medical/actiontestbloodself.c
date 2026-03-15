/**
 * @class   ActionTestBloodSelf
 * @brief   Ação de autoteste sanguíneo com integração de Relatório Médico Next Days
 * Auditado em: 2024 - Foco em Estabilidade de Configuração e Feedback ao Jogador
 */
modded class ActionTestBloodSelf
{
	override void OnFinishProgressServer(ActionData action_data)
	{	
		// 1. Executa a lógica vanilla (determina o tipo sanguíneo e consome o item)
		super.OnFinishProgressServer(action_data);

		PlayerBase player = action_data.m_Player;
		if (!player) return;

		// 2. Verificação de segurança na árvore de configuração
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetDiseases())
		{
			if (GetND().GetRP().GetDiseases().MedicalTestReport)
			{		
				/**
				 * @note Chama a exibição do relatório. 
				 * Passamos o player como médico e paciente simultaneamente.
				 */
				alpMedicTestReport.DisplayReport(this, player, player);
			}
		}
	}
};