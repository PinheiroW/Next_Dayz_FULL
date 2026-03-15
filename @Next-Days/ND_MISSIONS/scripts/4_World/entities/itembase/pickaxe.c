/**
 * pickaxe.c
 * * MODDED ENTITY (PICARETA) - Módulo ND_MISSIONS
 * Adiciona a picareta ao conjunto de ferramentas de interação com barris de missão.
 */

modded class Pickaxe extends ItemBase
{
	/**
	 * Injeta a ação de missão preservando as capacidades nativas de mineração e solo.
	 */
	override void SetActions()
	{
		super.SetActions();
		
		// Permite o uso da picareta em barris radioativos (ex: extração de amostras/itens)
		AddAction(alpActionDigInRadioactiveBarrel);
	}
}