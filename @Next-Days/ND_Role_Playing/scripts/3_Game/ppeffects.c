/**
 * @class   PPEffects
 * @brief   Gerencia efeitos visuais de tela para o ND_Role_Playing
 * Auditado em: 2024 - Foco em Estabilidade de Visualização e Logs Limpos
 */
modded class PPEffects
{
	/**
	 * @brief Ativa o efeito visual de olhos fechados (Preto Total)
	 * Chamado geralmente pelo modificador de sono (4_World)
	 */
	static void EnableClosedEyesALP()
	{
		// Segurança: Post-Processing só existe no Cliente
		if (GetGame().IsDedicatedServer()) return;

		// Aplica o overlay de escuridão total (RGBA: 0,0,0,1 com força 1.0)
		SetColorValue(m_BurlapBlindness, 0, 0, 0, 1, 1.0);
		UpdateColor();

		// Reduz o valor de exposição (EV) para garantir escuridão absoluta
		if (GetGame())
			GetGame().SetEVValue(-5);
	}

	/**
	 * @brief Desativa o efeito visual de olhos fechados
	 */
	static void DisableClosedEyesALP()
	{		
		if (GetGame().IsDedicatedServer()) return;

		// Reseta o overlay (Alpha em 0)
		SetColorValue(m_BurlapBlindness, 0, 0, 0, 0, 0.0);
		UpdateColor();

		// Retorna o EV ao valor padrão (Neutro)
		if (GetGame())
			GetGame().SetEVValue(0);
	}
};