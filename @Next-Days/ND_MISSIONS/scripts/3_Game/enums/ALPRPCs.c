/**
 * ALPRPCs.c
 * * Definições de constantes e enums para o sistema de RPC (Remote Procedure Call)
 * Responsável pela sincronização entre Cliente e Servidor.
 */

// GLOBAL RPC ID - Identificadores de canal principal
const int ALP_RPC_GAME                        = 2120579;
const int ALP_RPC_PLAYER                      = 2120580;
const int ALP_RPC_PLAYER_SYNC_BIT             = 2120581;
const int ALP_RPC_PLAYER_SYNC_VALUE           = 2120582;
const int ALP_RPC_DAYZ_SKILLS_SPECIALTY_SYNC  = 2120583;

// TYPE OF PLAYER RPC - Tipos de sincronização de dados do jogador (Hive)
enum ALP_RPC_PLAYER_TYPE
{
	HIVE_SYNC_ALL,
	HIVE_SYNC_SMALL,
	SYNC_REGISTER_ENHANCEDSTATS,
};

// TYPE OF GAME RPC - Inicialização e sincronização global do jogo
enum ALP_RPC_GAME_TYPE
{
	INIT,
	SYNC,
};

// RPC FOR NOTF - Sistema de notificações e mensagens
enum ALP_RPC_PLUGIN_NOTF
{
	SM,
	MISSION,
	MOSTWANTED,
	PERSONAL,
	MESSAGE,
	MESSAGE_POSITION,
	MESSAGE_RAID_ALERT,
	QUEST_START,
	QUEST_END,
};

// RPC FOR MS - Sistema de Missões e estados de área
enum ALP_RPC_PLUGIN_MS
{
	SERVER_TIME,
	VERIFY_CLIENT,
	MISSIONS_TO_CLIENT,
	UPDATE,
	UPDATE_ALL,
	REGISTER_MISSION,	
	UPDATE_SETTING,
	INOUT,
	TRADER,
	NPC_QUESTS,
};

// RPC FOR MS_TRADER - Economia, Banco, Propriedades e Exames Médicos
enum ALP_RPC_PLUGIN_MS_TRADER
{
	GIVE_ME_ALL_STOCK,
	UPDATE_THESE_ITEMS,
	BUY_ITEMS,
	SELL_ITEMS,
	GIVE_ME_ACCOUNT,
	CARD_CHANGE_PASSWORD,
	CARD_BLOCK,
	ATM_CASH,
	ATM_TAKELOAN,
	ATM_REPAYLOAN,
	ATM_EXCHANGE,
	SPREAD_RUMOURS,
	ME_CURE_DISEASE,
	ME_DNA_SAVE,
	ME_DNA_LOAD,
	PP_TAXES,
	ESTATE_BUY,
	ESTATE_SELL,	
	ESTATE_BUY_KEY,
	ESTATE_UPDATE_SETTINGS,
	PP_PERMISSION,
};

// RPC FOR RP - Sistema de Roleplay (Registros e Experiência)
enum ALP_RPC_PLUGIN_RP
{
	RECORDS,
	GAINED_EXP,
};