/**
 * @class   alpAlcoholAgent
 * @brief   Define o comportamento do agente de álcool no organismo
 * Auditado em: 2024 - Foco em Metabolismo Contínuo
 */
class alpAlcoholAgent: AgentBase
{
	override void Init()
	{
		// Tipo customizado definido no seu enum de agentes
		m_Type 					= alpeAgents.DRUNKENNESS;
		
		// O álcool não se multiplica sozinho (não é um vírus/bactéria)
		m_Invasibility 			= 0;
		
		// Não é contagioso entre jogadores (não passa pelo ar ou contato)
		m_TransferabilityIn		= 0;
		m_TransferabilityOut	= 0;
		
		// Antibióticos não afetam o álcool
		m_AntibioticsResistance = 1;
		
		// Capacidade máxima de álcool no sangue
		m_MaxCount 				= 1000;
		
		/** * @note Alterado de CRITICAL para GREAT.
		 * Isso garante que o corpo tente expelir o álcool mesmo se o jogador 
		 * estiver com a saúde debilitada.
		 */
		m_Potency 				= EStatLevels.GREAT;
		
		// Velocidade de sobriedade (0.83 = ~20 min para 1000 unidades)
		m_DieOffSpeed 			= 0.83;
	}
}