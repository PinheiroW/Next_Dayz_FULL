/**
 * @class   InfluenzaAgent
 * @brief   Gerencia a infecção por gripe com suporte ao sistema de imunidade Next Days
 * Auditado em: 2024 - Foco em Consistência de Imunidade Adquirida
 */
modded class InfluenzaAgent extends AgentBase
{
	/**
	 * @brief Verifica se o jogador pode contrair a doença automaticamente (ex: frio)
	 */
	override bool CanAutoinfectPlayer(PlayerBase player)
	{
		if (!player) return false;

		float heat_comfort = player.GetStatHeatComfort().Get();
		
		// 1. Verifica se o jogador está com frio
		bool isFreezing = (heat_comfort < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING);
		
		// 2. Verifica se o jogador possui o modificador de imunidade ativa (vacina/anticorpos)
		bool isImmune = false;
		if (player.GetModifiersManager())
		{
			isImmune = player.GetModifiersManager().IsModifierActive(rModifiers.MDF_IMMUNITY_INFLUENZA);
		}

		// Só infecta se estiver com frio E NÃO for imune
		return (isFreezing && !isImmune);
	}

	/**
	 * @brief Extensão para garantir que a imunidade também bloqueie contágio via ar/contato
	 */
	override void Transfer(PlayerBase src, PlayerBase target)
	{
		// Se o alvo for imune pelo sistema Next Days, cancelamos a transferência
		if (target && target.GetModifiersManager() && target.GetModifiersManager().IsModifierActive(rModifiers.MDF_IMMUNITY_INFLUENZA))
		{
			return;
		}

		super.Transfer(src, target);
	}
}