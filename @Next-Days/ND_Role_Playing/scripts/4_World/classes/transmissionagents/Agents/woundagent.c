/**
 * @class   WoundAgent
 * @brief   Gerencia o agente de infecção de ferimentos com integração ao Next Days
 * Auditado em: 2024 - Foco em Estabilidade de Configuração e Progressão Médica
 */
modded class WoundAgent
{
	override void Init()
	{
		m_Type 					= eAgents.WOUND_AGENT;
		
		// Invasibilidade ajustada para 0.22 (Levemente acima do vanilla, mas menos punitivo que 0.28)
		m_Invasibility 			= 0.22;
		
		m_TransferabilityIn		= 1;
		m_TransferabilityOut	= 0;
		m_AntibioticsResistance = 0;
		m_MaxCount 				= 1000;
		
		/** * @note m_Potency alterado para HIGH.
		 * Permite que um jogador que se alimente bem e se mantenha aquecido tenha uma 
		 * chance mínima de estabilizar a infecção, embora antibióticos continuem recomendados.
		 */
		m_Potency 				= EStatLevels.HIGH;
		
		// Velocidade de morte do agente quando combatido
		m_DieOffSpeed 			= 1;
	}

	/**
	 * @brief Retorna a chance de infecção baseada no arquivo de configuração do mod
	 */
	override float GetTransferabilityIn()
	{
		// Adicionado Failsafe de segurança para evitar crash se a config estiver ausente
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetDiseases())
		{
			return GetND().GetRP().GetDiseases().WoundInfectionChance;
		}
		
		// Valor de fallback caso a configuração falhe (ex: 5% de chance)
		return 0.05;
	}
}