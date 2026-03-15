/**
 * plugintransmissionagents.c
 * * AGENT & PROTECTION SYSTEM - Módulo ND_MISSIONS
 * Gerencia o registro de novos agentes (Radiação) e o cálculo de proteção customizado.
 */

modded class PluginTransmissionAgents extends PluginBase
{
	/**
	 * Construtor: Registra os agentes customizados do sistema Next-Days.
	 */
	void PluginTransmissionAgents()
	{
		// Registro do agente de radiação para processamento pelo motor de agentes
		RegisterAgent(new alpRadiationAgent);
	}
	
	/**
	 * Sobrescreve o cálculo de nível de proteção para integrar com o sistema de RP.
	 * @param type: Tipo do agente/contaminação.
	 * @param slot: Slot de vestuário sendo verificado.
	 * @param player: O jogador afetado.
	 * @param consider_filter: Se deve considerar apenas proteção respiratória.
	 */
	override static float GetProtectionLevelEx(int type, int slot, Man player, bool consider_filter = true, int system = 0)
	{
		float protection = 0;
		
		// Realiza o cast para PlayerBase para acessar o componente de RP
		PlayerBase p = PlayerBase.Cast(player);
		
		// Validação de segurança: Verifica se o jogador e seu componente de proteção existem
		if (p && p.GetRP() && p.GetRP().GetProtection())
		{
			if (consider_filter)
			{
				// Busca proteção específica para vias respiratórias (ex: máscaras de gás)
				protection = p.GetRP().GetProtection().GetProtectionRespiratory(type);
			}
			else
			{
				// Busca proteção geral para o slot específico do corpo
				protection = p.GetRP().GetProtection().GetProtection(type, slot);
			}
		}
		
		return protection;
	}
};