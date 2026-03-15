/**
 * alpSPAWN_EVENT.c
 * * SPAWN EVENT ENUMERATIONS - Módulo ND_MISSIONS
 * Define os gatilhos para o sistema de gerenciamento de vida e morte.
 */

enum ALP_SPAWN_EVENT
{
	NONE             = 0,
	RESTORE_STATS    = 1,
	DEATH            = 2,
	DEATH_SPAWN_MENU = 4	
}