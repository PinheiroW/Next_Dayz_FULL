/**
 * radiationagent.c
 * * AGENTE DE RADIAÇÃO (DOENÇA BIOLÓGICA) - Módulo ND_MISSIONS
 * Define a agressividade da radiação e a taxa em que o corpo do jogador consegue se curar naturalmente.
 */

class alpRadiationAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= alpeAgents.RADIATION;
		m_Invasibility 			= 0;
		m_TransferabilityIn		= 0.0;
		m_TransferabilityOut	= 0.0;
		m_Digestibility	 		= 1.0;
		m_TransferabilityAirOut	= 0;
		m_AntibioticsResistance = 1; // Medicamentos normais do DayZ são inúteis contra a radiação
		m_MaxCount 				= 100000;
		m_Potency 				= EStatLevels.CRITICAL;
		m_DieOffSpeed 			= 0; // Configurado dinamicamente no método abaixo
	}
	
	override float GetDieOffSpeedEx(PlayerBase player)
	{
		// OTIMIZAÇÃO: Proteção primária para evitar crash ao acessar a entidade
		if (!player)
		{
			return 0;
		}

		// LÓGICA MANTIDA: O corpo só se cura sozinho se a contaminação for menor que o Nível 2 (L2)
		if (player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L2) 
		{
			float doses = 0;
			
			// OTIMIZAÇÃO: Null checks rigorosos antes de varrer configurações globais do servidor
			if (GetND() && GetND().GetMS() && GetND().GetMS().GetOptionsRadiation())
			{
				// CORREÇÃO MATEMÁTICA: Uso de 3600.0 evita arredondamento prematuro para 0 em divisões inteiras
				doses = (GetND().GetMS().GetOptionsRadiation().AutoRadiationReduce / 3600.0) * 1000.0;
			}
			
			// OTIMIZAÇÃO: Proteção da árvore de RPG antes de aplicar o bônus de resistência natural
			if (player.GetRP() && player.GetRP().GetProtection())
			{
				doses = doses * (1.0 + player.GetRP().GetProtection().GetNaturalResistanceAgainstRadiation());
			}
			
			return doses;
		}
		
		// Retorno para Estágios L2+ (Radiação se acumulou e o corpo não limpa mais sozinho)
		return 0;
	}
}