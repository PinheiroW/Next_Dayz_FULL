/**
 * farminghoe.c
 * * MODDED ENTITY (ENXADA) - Módulo ND_MISSIONS
 * Adiciona funcionalidade de interação com barris radioativos.
 */

modded class FarmingHoe : ItemBase
{
	/**
	 * Injeta a ação de missão sem romper as funções de agricultura originais.
	 */
	override void SetActions()
	{
		super.SetActions();
		
		// Permite que a enxada interaja com barris radioativos (ex: cavar conteúdo)
		AddAction(alpActionDigInRadioactiveBarrel);
	}
};