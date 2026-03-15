/**
 * @class   ActionTestBloodTarget
 * @brief   Ação de testar sangue de terceiros com Relatório Médico e Reputação
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Consistência de RPG
 */
modded class ActionTestBloodTarget
{
	override void OnFinishProgressServer(ActionData action_data)
	{	
		// 1. Executa a lógica vanilla primeiro (Consome o item e identifica o sangue)
		super.OnFinishProgressServer(action_data);

		// 2. Referências seguras
		PlayerBase treater = action_data.m_Player;
		PlayerBase patient = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (!treater || !patient) return;

		// 3. Integração com o Relatório Médico Next Days
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetDiseases())
		{
			if (GetND().GetRP().GetDiseases().MedicalTestReport)
			{
				alpMedicTestReport.DisplayReport(this, treater, patient);
			}
		}

		// 4. Bônus de Reputação (Consistência com o sistema médico do mod)
		if (treater.GetRP() && treater != patient)
		{
			float reputationBonus = 0;

			if (treater.GetRP().IsHero())
			{
				// Teste de sangue dá um bônus menor que o tratamento real
				reputationBonus = 2.0; 
			}
			else if (treater.GetRP().IsBandit())
			{
				reputationBonus = 1.0;
			}
			else
			{
				reputationBonus = 1.5; // Neutros
			}

			if (reputationBonus != 0)
			{
				treater.GetRP().ChangeReputation(reputationBonus);
			}
		}
	}
};