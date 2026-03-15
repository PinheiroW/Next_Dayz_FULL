/**
 * @class   CommonColdMdfr
 * @brief   Sincroniza o resfriado comum vanilla com o sistema RPG e ajusta limites
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Customização de Ativação
 */
modded class CommonColdMdfr
{
	// Limites personalizados de agentes para o sistema Next Days
	const int AGENT_THRESHOLD_ACTIVATE = 50;
	const int AGENT_THRESHOLD_DEACTIVATE = 21;
	
	// Sobrescrita necessária para que os limites acima sejam aplicados
	override bool ActivateCondition(PlayerBase player)
	{
		if (player.GetSingleAgentCount(eAgents.CHOLERA) >= AGENT_THRESHOLD_ACTIVATE) 
		{
			return true;
		}
		return false;
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		if (player.GetSingleAgentCount(eAgents.CHOLERA) <= AGENT_THRESHOLD_DEACTIVATE) 
		{
			return true;
		}
		return false;
	}

	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Verifica a validade do player e do componente RPG antes de acessar
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.COMMONCOLD);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante integridade durante a limpeza do modificador
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.COMMONCOLD);
		}
	}	
}