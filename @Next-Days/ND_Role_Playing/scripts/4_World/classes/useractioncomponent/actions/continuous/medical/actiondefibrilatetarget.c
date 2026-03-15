/**
 * @class   ActionDefibrilateTarget
 * @brief   Ação de desfibrilação com validação de estado de saúde e reputação
 * Auditado em: 2026 - Foco em Integridade de Roleplay e Antifrape
 */
modded class ActionDefibrilateTarget: ActionDefibrilateBase
{	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		// 1. Referências seguras
		PlayerBase treater = action_data.m_Player;
		PlayerBase patient = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		// 2. Executa a lógica vanilla primeiro (Consumo de carga, choque, chance de acordar)
		super.OnFinishProgressServer(action_data);

		// 3. Validação de segurança e Moralidade
		if (treater && patient && treater != patient && treater.GetRP())
		{
			// VERIFICAÇÃO CRÍTICA: O bônus de reputação só deve ser dado se o alvo estiver INCONSCIENTE.
			// Choques em pessoas acordadas são considerados agressão ou teste, não salvamento.
			if (patient.IsUnconscious())
			{
				float reputationBonus = 0;
				float multiplier = 2.0; // Desfibrilar é uma ação de alto valor médico

				if (treater.GetRP().IsHero())
				{
					reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO) * multiplier;
				}
				else if (treater.GetRP().IsBandit())
				{
					reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT);
				}
				else // Sobrevivente Neutro / Civil
				{
					reputationBonus = 10.0; // Valor fixo razoável para quem está começando
				}

				if (reputationBonus != 0)
				{
					treater.GetRP().ChangeReputation(reputationBonus);
				}
			}
		}
	}
};