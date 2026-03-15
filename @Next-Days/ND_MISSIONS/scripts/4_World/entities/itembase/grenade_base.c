/**
 * grenade_base.c
 * * MODDED ENTITY (BASE DE GRANADAS) - Módulo ND_MISSIONS
 * Adiciona suporte para identificação de propriedade/autoria em explosivos.
 */

modded class Grenade_Base extends InventoryItemSuper
{
	/**
	 * Armazena a referência do último jogador que manuseou ou ativou a granada.
	 * Útil para logs de dano e validação de objetivos de missão.
	 */
	PlayerBase alp_LastOwner;
}