/**
 * BaseBuildingBase.c
 * * MODDED ENTITY (ESTRUTURAS DE BASE) - Módulo ND_MISSIONS
 * Garante que construções de jogadores não sejam tratadas como objetos de missão.
 */

modded class BaseBuildingBase extends ItemBase
{
	/**
	 * Impede que o sistema de limpeza de missões (Cleanup) delete construções de jogadores.
	 * @return bool false para proteger o objeto da lógica de remoção de missões.
	 */
	override bool CanBeMissionObject()
	{
		return false;
	}	
}