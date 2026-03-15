/**
 * building.c
 * * MODDED ENTITY (BASE DE CONSTRUÇÕES) - Módulo ND_MISSIONS
 * Define metadados para identificar construções pertencentes a missões.
 */

modded class BuildingBase
{
	/**
	 * Identifica se a construção foi criada por um script de missão.
	 * Estruturas de missão podem ter comportamentos de colisão ou persistência diferentes.
	 */
	bool alp_IsMissionStructure = false;
	
	/**
	 * Define o estado de trava/missão da estrutura.
	 * @param state Se verdadeiro, define a estrutura como parte integrante de uma missão ativa.
	 */
	void SetLockALP(bool state)
	{
		alp_IsMissionStructure = !state;
	}
};