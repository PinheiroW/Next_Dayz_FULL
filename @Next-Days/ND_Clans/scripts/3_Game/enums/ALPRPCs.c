//RPC FOR CLANS
enum ALP_RPC_PLUGIN_CLANS
{
	// Atribuição de um Offset único e alto para evitar sobreposição (Mismatch) de rede
	// Garante compatibilidade universal com o DayZ Vanilla e qualquer outro Mod.
	SET_CLAN_ID = 84520, 
	CREATENEWCLAN,	
	SEND_CLAN_TO_CLIENT,
	UPDATE_ONLINE_MEMBERS,
	DISBAND_CLAN,
	LEAVE_CLAN,
	KICK_HIM,
	MATE_POSITION,
	SYNC_PLOTPOLE
}