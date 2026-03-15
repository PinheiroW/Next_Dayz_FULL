/**
 * @class   ActionInjectTarget
 * @brief   Ação de aplicar injeção em terceiros com integração de moralidade Next Days
 * Auditado em: 2024 - Foco em Alinhamento Neutro e Segurança de Execução
 */
modded class ActionInjectTarget: ActionSingleUseBase
{
	override void OnEndServer( ActionData action_data )
	{
		// 1. Executa a lógica vanilla primeiro (aplica o medicamento e consome o item)
		super.OnEndServer( action_data );

		// 2. Valida se a ação foi realmente concluída e se os ponteiros são seguros
		if (action_data.m_WasExecuted && action_data.m_Player && action_data.m_Player.GetRP())
		{
			PlayerBase treater = action_data.m_Player;
			
			// 3. Sistema de Moralidade Dinâmico
			float reputationBonus = 0;

			if (treater.GetRP().IsHero())
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO);
			}
			else if (treater.GetRP().IsBandit())
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT);
			}
			else // Sobrevivente Neutro / Civil
			{
				// Atribui um bônus padrão de ajuda para não penalizar neutros
				reputationBonus = 5.0; 
			}

			// 4. Aplica a alteração se houver bônus definido
			if (reputationBonus != 0)
			{
				treater.GetRP().ChangeReputation(reputationBonus);
			}
		}
	}
};