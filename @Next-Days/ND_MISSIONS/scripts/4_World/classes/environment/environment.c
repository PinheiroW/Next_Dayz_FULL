/**
 * environment.c
 * * EXTENSÃO DE AMBIENTE - Módulo ND_MISSIONS
 * Adiciona verificações customizadas de clima e exposição do jogador.
 */

modded class Environment
{
	// Constante mantida comentada como referência original do autor
	// const float ALP_RAIN_LIMIT_LOW = 0.05;

	bool IsRainingALP()
	{
		// OTIMIZAÇÃO: Null check explícito garantindo segurança absoluta contra crashes
		if (!m_Player) 
		{
			return false;
		}

		// Verifica se está chovendo acima do limite, fora de veículos e fora de edifícios
		return (m_Rain > RAIN_LIMIT_LOW) && !m_Player.IsInVehicle() && !m_Player.IsSoundInsideBuilding();
	}
};