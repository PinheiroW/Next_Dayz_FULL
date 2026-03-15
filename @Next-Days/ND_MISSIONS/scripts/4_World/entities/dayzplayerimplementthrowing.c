/**
 * dayzplayerimplementthrowing.c
 * * PLAYER THROWING IMPLEMENTATION - Módulo ND_MISSIONS
 * Restringe a capacidade de arremesso em zonas de trade para evitar abusos e garantir a paz.
 */

modded class DayZPlayerImplementThrowing
{
	/**
	 * Valida se o jogador pode continuar ou iniciar a fase de arremesso de um item.
	 */
	override bool CanContinueThrowing(HumanInputController pHic)
	{
		PlayerBase player = PlayerBase.Cast(m_Player);
		
		if (player && player.GetRP())
		{
			// Verifica se o jogador está em uma zona de comércio onde o dano é proibido
			if (player.GetRP().IsInTradeZone() && !player.GetRP().IsAllowedDamage()) 
			{
				return false;
			}
		}
		
		// Se não houver restrições, segue a lógica padrão do motor de jogo
		return super.CanContinueThrowing(pHic);
	}
}