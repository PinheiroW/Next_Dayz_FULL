/**
 * Lockpick.c
 * * MODDED ENTITY (GAZUA) - Módulo ND_MISSIONS
 * Expande as funcionalidades da Gazua para incluir o sistema de lockpicking do mod.
 */

modded class Lockpick : Inventory_Base
{
	/**
	 * Injeta a ação personalizada de missão sem remover as funções originais do item.
	 */
	override void SetActions()
	{
		// Mantém as ações nativas (trancar/destrancar portas vanilla)
		super.SetActions();
		
		// Adiciona a lógica de lockpicking específica para objetos de missão ND
		AddAction(alpLockpicking);
	}
};