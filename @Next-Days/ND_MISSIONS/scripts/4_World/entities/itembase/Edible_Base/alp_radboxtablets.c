/**
 * alp_radboxtablets.c
 * * ENTIDADE CONSUMÍVEL (TABLETES ANTIRRADIAÇÃO) - Módulo ND_MISSIONS
 * Ativa a proteção química interna contra radiação por um tempo determinado.
 */

class alp_radboxtablets : VitaminBottle
{
	/**
	 * Chamado quando o jogador finaliza a ação de consumir o item.
	 */
	override void OnConsume(float amount, PlayerBase consumer)
	{
		if (!consumer || !consumer.GetModifiersManager())
			return;

		// Verifica se o modificador de bloqueio de radiação já está ativo
		if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONBLOCK))
		{
			// Desativa para permitir o "reset" do cronômetro de duração
			consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONBLOCK);
		}
		
		// Ativa o modificador de proteção
		consumer.GetModifiersManager().ActivateModifier(rModifiers.MDF_ALPRADIATIONBLOCK);
		
		// Log opcional para debug do servidor (pode ser removido em produção)
		// Print("[ND_MISSIONS] " + consumer.GetIdentity().GetName() + " consumiu tabletes de radiação.");
	}
}