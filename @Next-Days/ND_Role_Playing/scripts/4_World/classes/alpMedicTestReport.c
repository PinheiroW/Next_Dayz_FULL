/**
 * @class   alpMedicTestReport
 * @brief   Gera o relatório de diagnóstico médico para o sistema Next Days
 * Auditado em: 2024 - Foco em Correção de Sintaxe e Localização
 */
class alpMedicTestReport
{
	static void DisplayReport(ActionBase action, PlayerBase player, PlayerBase target)
	{
		if (!player || !target) return;

		// 1. Tradução dos níveis de imunidade
		EStatLevels immunityLevel = target.GetImmunityLevel();
		string immunityLevelStr = "#me_immunity_unknown";
		
		switch (immunityLevel)
		{
			case EStatLevels.GREAT:    immunityLevelStr = "#me_immunity_great"; break;
			case EStatLevels.HIGH:     immunityLevelStr = "#me_immunity_high"; break;
			case EStatLevels.MEDIUM:   immunityLevelStr = "#me_immunity_medium"; break;
			case EStatLevels.LOW:      immunityLevelStr = "#me_immunity_low"; break;
			case EStatLevels.CRITICAL: immunityLevelStr = "#me_immunity_critical"; break;
		}
		
		string positive = "#me_disease_positive"; // Corrigido erro de digitação 'pozitive'
		string negative = "#me_disease_negative";
		
		string stateCholera, stateInfluenza, statePoisoning, stateWound, stateContamination, stateDrunkenness, stateSalmonela, stateRadiation;
		
		// 2. Verificação de Agentes e Modificadores
		if (target.GetModifiersManager())
		{
			// Correção da lógica de Radiação (Sintaxe corrigida)
			if (target.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L1)
				stateRadiation = positive;
			else
				stateRadiation = negative;			
			
			if (target.GetModifiersManager().IsModifierActive(eModifiers.MDF_SALMONELLA))
				stateSalmonela = positive;
			else
				stateSalmonela = negative;
			
			if (target.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHOLERA))
				stateCholera = positive;
			else
				stateCholera = negative;

			if (target.GetModifiersManager().IsModifierActive(eModifiers.MDF_INFLUENZA))
				stateInfluenza = positive;
			else
				stateInfluenza = negative;

			if (target.GetModifiersManager().IsModifierActive(eModifiers.MDF_FOODPOISON))
				statePoisoning = positive;
			else
				statePoisoning = negative;

			if (target.GetModifiersManager().IsModifierActive(eModifiers.MDF_WOUND_INFECTION))
				stateWound = positive;
			else
				stateWound = negative;
				
			if (target.GetSingleAgentCount(alpeAgents.DRUNKENNESS) > 0)
				stateDrunkenness = positive;
			else
				stateDrunkenness = negative;
		}
		
		// 3. Envio das mensagens formatadas (Sugestão: Agrupar em blocos)
		action.SendMessageToClient(player, "--------------------------------");
		action.SendMessageToClient(player, "#me_medical_record:");
		action.SendMessageToClient(player, "#me_immunity_desc: " + immunityLevelStr);
		
		// Exibe contagem exata + veredito para cada doença
		action.SendMessageToClient(player, "#me_cholera_desc: " + target.GetSingleAgentCount(eAgents.CHOLERA).ToString() + " (" + stateCholera + ")");
		action.SendMessageToClient(player, "#me_salmonella_desc: " + target.GetSingleAgentCount(eAgents.SALMONELLA).ToString() + " (" + stateSalmonela + ")");
		action.SendMessageToClient(player, "#me_influenza_desc: " + target.GetSingleAgentCount(eAgents.INFLUENZA).ToString() + " (" + stateInfluenza + ")");
		action.SendMessageToClient(player, "#me_woundinfection_desc: " + target.GetSingleAgentCount(eAgents.WOUND_AGENT).ToString() + " (" + stateWound + ")");
		action.SendMessageToClient(player, "#me_radiation_desc: " + target.GetSingleAgentCount(alpeAgents.RADIATION).ToString() + " (" + stateRadiation + ")");
		action.SendMessageToClient(player, "#me_drunkenness_desc: " + target.GetSingleAgentCount(alpeAgents.DRUNKENNESS).ToString() + " (" + stateDrunkenness + ")");
		action.SendMessageToClient(player, "--------------------------------");
	}
};