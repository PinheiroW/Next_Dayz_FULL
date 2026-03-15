/**
 * shovel.c
 * * MODDED ENTITY (PÁ) - Módulo ND_MISSIONS
 * Adiciona a funcionalidade de escavação em objetivos de missão radioativos.
 */

modded class Shovel extends ItemBase
{
	/**
	 * Injeta a ação de missão preservando a lógica original de ferramentas de solo.
	 */
	override void SetActions()
	{
		// Mantém as ações vanilla (enterrar itens, agricultura, construção)
		super.SetActions();
		
		// Adiciona a capacidade de interagir com barris radioativos das missões ALP
		AddAction(alpActionDigInRadioactiveBarrel);
	}
}