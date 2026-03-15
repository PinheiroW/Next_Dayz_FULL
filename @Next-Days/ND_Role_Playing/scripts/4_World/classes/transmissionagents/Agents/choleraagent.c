/**
 * @class   CholeraAgent
 * @brief   Modifica o agente da Cólera para o ecossistema Next Days
 * Auditado em: 2024 - Foco em Progressão de Doença e Equilíbrio de Imunidade
 */
modded class CholeraAgent
{
	override void Init()
	{
		m_Type 					= eAgents.CHOLERA;
		
		// Invasibilidade: 0.175 (Equilíbrio entre o vanilla 0.15 e o seu 0.185)
		m_Invasibility 			= 0.175;
		
		m_TransferabilityIn		= 1;
		m_TransferabilityOut	= 0;
		
		// Antibióticos funcionam 100% contra cólera
		m_AntibioticsResistance = 0;
		
		// Limite máximo de agentes no sangue
		m_MaxCount 				= 1000;
		
		/** * @note m_Potency alterado para HIGH (um nível abaixo de GREAT)
		 * Isso permite que jogadores saudáveis mas não "perfeitos" consigam 
		 * combater a doença naturalmente com repouso.
		 */
		m_Potency 				= EStatLevels.HIGH;
		
		// Velocidade de morte do agente (Reduzido para 0.65 para a cura ser gradual)
		m_DieOffSpeed 			= 0.65;
	}
}