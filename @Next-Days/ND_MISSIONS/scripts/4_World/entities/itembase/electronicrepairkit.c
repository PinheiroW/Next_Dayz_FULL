/**
 * electronicrepairkit.c
 * * MODDED ENTITY (KIT DE REPARO ELETRÔNICO) - Módulo ND_MISSIONS
 * Adiciona funcionalidades de reparo para componentes de missão (Servidores/Consoles).
 */

modded class ElectronicRepairKit 
{
	/**
	 * Injeta ações personalizadas sem remover as nativas do jogo.
	 */
	override void SetActions()
	{
		super.SetActions();

		// Permite o uso do kit para consertar consoles de servidor em missões
		AddAction(alpActionServerConsoleRepair);
	}	
};