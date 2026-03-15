/**
 * fieldshovel.c
 * * MODDED ENTITY (PÁ DE CAMPO) - Módulo ND_MISSIONS
 * Permite o uso da pá em interações de escavação em barris radioativos.
 */

modded class FieldShovel extends ItemBase
{
	/**
	 * Injeta a ação de missão sem interferir nas capacidades nativas da pá.
	 */
	override void SetActions()
	{
		super.SetActions();
		
		// Adiciona a capacidade de interagir com barris de missão radioativos
		AddAction(alpActionDigInRadioactiveBarrel);
	}
}