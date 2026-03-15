/**
 * alpOptionsNotf.c
 * * CONFIGURAÇÕES DO SISTEMA DE NOTIFICAÇÕES - Módulo ND_MISSIONS
 * Define ícones, cores e comportamento das mensagens In-Game.
 */

class alpOptionsNotf 
{	
	bool EnableGameInfo					= true;
	bool EnableCharacterInfo			= true;	
	bool EnableNotification				= true;
	int NotificationAlign				= 0; // 0=Esquerda, 1=Centro, 2=Direita
	bool EnableDeathNotification		= false;
	int ShownMessagesAtOnce				= 3;
	float MessageDisplayedMinimalFor	= 5;
	float MessageProlong				= 0.5; // Aumento de tempo por cada 10 caracteres
}

enum ALPMSTYPE
{
	SMINFO,
	SMIMPORTANT,
	SMPERSONAL,
	SMTRADERIN,
	SMTRADEROUT,
	SMRADIATIONIN,
	SMRADIATIONOUT,
	SMLEVELUP,
	SMLEVELDOWN,
	SMGAINEDEXPUP,
	SMGAINEDEXPDOWN,	
	SMDEATH,
	SMHEADSHOT,
	SMACTIVATE,	
	SMEND, // Mensagens de fim de ciclo do servidor
	MMCOUNTDOWN,
	MMCONQUER,
	MMDEFEND,
	MMCAPTURE,
	MMPERSONAL,
	MMTRADERSTART,
	MMTRADEREND,
	MMRADIATIONSTART,
	MMRADIATIONEND,
	MMMISSIONCARSTART,
	MMMISSIONCAREND,	
	MMMISSIONSTART,	// Missão sem radiação iniciada
	MMMISSIONEND,	// Missão sem radiação finalizada
	COUNT,
}; // Adicionado ponto e vírgula obrigatório

// CORREÇÃO: ref em vez de autoptr e preenchimento total dos 28 índices para evitar crash
ref array<string> ALPMSICON = {
	"ND_MISSIONS/gui/images/smInfo.paa",         // 00 SMINFO
	"ND_MISSIONS/gui/images/smInfo.paa",         // 01 SMIMPORTANT
	"ND_MISSIONS/gui/images/smInfo.paa",         // 02 SMPERSONAL
	"ND_MISSIONS/gui/images/smTrader.paa",       // 03 SMTRADERIN
	"ND_MISSIONS/gui/images/smTrader.paa",       // 04 SMTRADEROUT
	"ND_MISSIONS/gui/images/smRadiation.paa",    // 05 SMRADIATIONIN
	"ND_MISSIONS/gui/images/smRadiation.paa",    // 06 SMRADIATIONOUT
	"ND_MISSIONS/gui/images/levelup.paa",        // 07 SMLEVELUP
	"ND_MISSIONS/gui/images/leveldown.paa",      // 08 SMLEVELDOWN
	"ND_MISSIONS/gui/images/levelup.paa",        // 09 SMGAINEDEXPUP
	"ND_MISSIONS/gui/images/leveldown.paa",      // 10 SMGAINEDEXPDOWN
	"ND_MISSIONS/gui/images/death.paa",          // 11 SMDEATH
	"ND_MISSIONS/gui/images/headshot.paa",       // 12 SMHEADSHOT
	"ND_MISSIONS/gui/images/enter.paa",          // 13 SMACTIVATE
	"ND_MISSIONS/gui/images/smInfo.paa",         // 14 SMEND
	"ND_MISSIONS/gui/images/time.paa",           // 15 MMCOUNTDOWN
	"ND_MISSIONS/gui/images/fight.paa",          // 16 MMCONQUER
	"ND_MISSIONS/gui/images/flag.paa",           // 17 MMDEFEND
	"ND_MISSIONS/gui/images/flag.paa",           // 18 MMCAPTURE
	"ND_MISSIONS/gui/images/smInfo.paa",         // 19 MMPERSONAL
	"ND_MISSIONS/gui/images/smTrader.paa",       // 20 MMTRADERSTART
	"ND_MISSIONS/gui/images/smTrader.paa",       // 21 MMTRADEREND
	"ND_MISSIONS/gui/images/smRadiation.paa",    // 22 MMRADIATIONSTART
	"ND_MISSIONS/gui/images/smRadiation.paa",    // 23 MMRADIATIONEND
	"ND_MISSIONS/gui/images/mmMissionCar.paa",   // 24 MMMISSIONCARSTART
	"ND_MISSIONS/gui/images/mmMissionCar.paa",   // 25 MMMISSIONCAREND
	"ND_MISSIONS/gui/images/mmMission.paa",      // 26 MMMISSIONSTART
	"ND_MISSIONS/gui/images/mmMission.paa"       // 27 MMMISSIONEND
};

// CORREÇÃO: ref em vez de autoptr
ref array<int> ALPMSCOLOR = {
	0xffffffff, // Branco
	0xffe74c3c, // Vermelho (Importante)
	0xff2ecc71, // Verde (Pessoal)
	0xff3498db, // Azul (Trader)
	0xff3498db, 
	0xffe67e22, // Laranja (Radiação)
	0xffe67e22, 
	0xfff1c40f, // Dourado (Level Up)
	0xff95a5a6, // Cinza (Level Down)
	0xfff1c40f, 
	0xff95a5a6, 
	0xffc0392b, // Vermelho Escuro (Morte)
	0xffc0392b, 
	0xffffffff, 
	0xffffffff, 
	0xffffffff, // Início de Missão
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff,
	0xffffffff
};