/**
 * @class   PluginTransmissionAgents
 * @brief   Registro de agentes patogênicos e substâncias no motor de transmissão
 * Auditado em: 2026 - Foco em Consistência de Agentes Customizados
 */
modded class PluginTransmissionAgents
{
	void PluginTransmissionAgents()
	{
		// 1. Registro do agente de Álcool (Drunkenness)
		RegisterAgent(new alpAlcoholAgent);

		// 2. Registro do agente de Radiação
		// Essencial para que o sistema de itens contaminados (HasAnyContaminedItems) funcione.
		RegisterAgent(new alpRadiationAgent);

		// 3. Registro do agente Químico
		// Necessário para as doenças de envenenamento químico (POISONING_CHEMICAL)
		RegisterAgent(new alpChemicalAgent);
	}
}