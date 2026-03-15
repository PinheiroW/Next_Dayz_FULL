/**
 * @class   ActionGiveSalineTarget
 * @brief   Ação de aplicação de soro fisiológico com integração de moralidade Next Days
 * Auditado em: 2024 - Foco em Diferenciação de Alinhamento e Integridade de Ação
 */
modded class ActionGiveSalineTarget: ActionContinuousBase
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		// 1. Executa a lógica vanilla primeiro (Consumo do soro e hidratação do sangue)
		super.OnFinishProgressServer(action_data);

		// 2. Referências seguras
		PlayerBase treater = action_data.m_Player;
		PlayerBase patient = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		// 3. Validação de segurança e Prevenção de Exploit (Não curar a si mesmo por esta ação)
		if (treater && patient && treater != patient && treater.GetRP())
		{
			float reputationBonus = 0;
			
			// Definimos bônus específicos para cada alinhamento
			if (treater.GetRP().IsHero())
			{
				// Soro dá menos reputação que sangue/desfibrilador por ser mais comum
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO);
			}
			else if (treater.GetRP().IsBandit())
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT);
			}
			else // Caso para Sobreviventes Neutros / Civis
			{
				reputationBonus = 5.0; // Valor base para quem não tem alinhamento definido
			}

			// Aplica a mudança de reputação se houver bônus válido
			if (reputationBonus != 0)
			{
				treater.GetRP().ChangeReputation(reputationBonus);
			}
		}
	}
};