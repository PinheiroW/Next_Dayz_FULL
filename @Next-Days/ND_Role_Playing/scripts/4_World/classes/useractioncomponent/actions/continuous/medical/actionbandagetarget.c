/**
 * @class   ActionBandageTarget
 * @brief   Estende a ação de bandagem em terceiros para incluir ganhos de reputação
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Prevenção de Exploits
 */
modded class ActionBandageTarget: ActionBandageBase
{
	override void OnFinishProgressServer(ActionData action_data)
	{	
		// 1. Extração segura dos objetos
		PlayerBase treater = action_data.m_Player;
		PlayerBase patient = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		// 2. Validação de segurança e Prevenção de Exploit
		// Só ganha reputação se o paciente existir e NÃO for o próprio médico
		if (treater && patient && treater != patient && treater.GetRP())
		{
			float reputationBonus = 0;
			
			// 3. Lógica de Reputação baseada no alinhamento atual
			if (treater.GetRP().IsHero())
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO);
			}
			else if (treater.GetRP().IsBandit()) // Recomendado: Verificação específica
			{
				reputationBonus = GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT);
			}
			else // Caso para sobreviventes neutros/civis
			{
				// Opcional: bônus menor para neutros
				reputationBonus = 5.0; 
			}

			// Aplica a mudança
			if (reputationBonus != 0)
			{
				treater.GetRP().ChangeReputation(reputationBonus);
			}
		}		
		
		// 4. Executa a lógica vanilla (remover sangramento, consumir bandagem)
		super.OnFinishProgressServer(action_data);
	}
};