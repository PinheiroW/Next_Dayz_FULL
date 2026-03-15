/**
 * @class   ActionGiveBloodTarget
 * @brief   Ação de transfusão de sangue com sistema de moralidade Next Days
 * Auditado em: 2024 - Foco em Prevenção de Exploits e Sucesso de Ação
 */
modded class ActionGiveBloodTarget: ActionContinuousBase
{
	// MUDANÇA: Usamos OnFinishProgressServer para evitar ganho de reputação em ações canceladas
	override void OnFinishProgressServer(ActionData action_data)
	{
		// 1. Executa a lógica vanilla primeiro (Transfere o sangue e verifica compatibilidade)
		super.OnFinishProgressServer(action_data);

		// 2. Referências seguras
		PlayerBase treater = action_data.m_Player;
		PlayerBase patient = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		// 3. Validação de segurança
		if (treater && patient && treater != patient && treater.GetRP())
		{
			float reputationBonus = 0;
			// Transfuração é uma ação demorada e vital, merece um multiplicador
			float multiplier = 1.5; 

			if (treater.GetRP().IsHero())
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO) * multiplier;
			}
			else if (treater.GetRP().IsBandit())
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT);
			}
			else // Sobrevivente Neutro
			{
				reputationBonus = 7.5; 
			}

			// 4. Aplicação da recompensa
			if (reputationBonus != 0)
			{
				treater.GetRP().ChangeReputation(reputationBonus);
			}
		}
	}
	
	// Limpeza: Removemos o OnEndServer se não houver outra lógica específica para garantir performance
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
	}
};