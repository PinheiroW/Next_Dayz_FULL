/**
 * trap_base.c
 * * MODDED ENTITY (BASE DE ARMADILHAS) - Módulo ND_MISSIONS
 * Adiciona suporte para identificação do jogador responsável pela armadilha.
 */

modded class TrapBase extends ItemBase
{
	/**
	 * Armazena a referência do último jogador que manuseou ou armou a armadilha.
	 * Utilizado para logs de dano e validação de autoria em missões.
	 */
	PlayerBase alp_LastOwner;
}