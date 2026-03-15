/**
 * @class   ActionSplintTarget
 * @brief   Ação de aplicar tala em terceiros com integração de moralidade Next Days
 * Auditado em: 2024 - Foco em Integridade de Moralidade e Prevenção de Spam
 */
modded class ActionSplintTarget: ActionContinuousBase
{
	override void OnFinishProgressServer(ActionData action_data)
	{	
		// 1. Referências seguras
		PlayerBase treater = action_data.m_Player;
		PlayerBase patient = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		// 2. Executa a lógica vanilla primeiro (Consome a tala e fixa o osso)
		super.OnFinishProgressServer(action_data);

		// 3. Validação de segurança e Moralidade
		if (treater && patient && treater != patient && treater.GetRP())
		{
			// Opcional: Só dá reputação se o paciente REALMENTE tiver uma fratura
			// if (patient.GetModifiersManager().IsModifierActive(eModifiers.MDF_FRACTURE)) 
			
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
				reputationBonus = 5.0; // Valor base para ações de ajuda
			}

			if (reputationBonus != 0)
			{
				treater.GetRP().ChangeReputation(reputationBonus);
			}
		}
	}
};