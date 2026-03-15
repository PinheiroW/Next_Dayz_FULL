/**
 * alpOptionsMS_templates_NPC.c
 * * DEFINIÇÃO DE ESTRUTURA PARA NPCs E TRADERS - Módulo ND_MISSIONS
 * Gerencia o estoque, interações e spawn de NPCs no mundo.
 */

class alpNPCtraderStock 
{
	int RequiredCharacterTraits;  // RequiredRole
	int EnabledInteractions = 3;  // settingNPC
		
	int CurrencyID;	
	
	int Cash = 500000;	
	int CashAddingPerRestock = 100000; // adding per spawn
	
	int CashMinimal = 1000000; // trader cash
	int CashOptimal = 5000000; // cashAffectsPrices
	float CashAffectsPrices = 0.25; 
					
	float PricelistRatioHero = 1;
	float PricelistRatioBandit = 1;	
	int CentralStock = 0;
	bool NoReputationRequirementsWhileBuying = false; // CORREÇÃO: 0 -> false
	ref map<string, int> Stock;	
	
	// CONSTRUTOR: Evita Null Pointer Exception
	void alpNPCtraderStock()
	{
		Stock = new map<string, int>;
	}
}

class alpMissionAddNPC 
{
	string className;
	float chance;
	int IsDead;
	vector position;
	float yaw;
	float pitch;
	float roll;
	int stance;	

	ref array<string> attachments;
	int lootMaxCount = 0;			
	ref array<ref alpLootCargo> cargo;	

	int AllowedQuestsAtOnce; // 0-means nothing
	int EnabledInteractions;	
	ref array<string> AvailableGoodsByTag; // works at first run	
	int CurrencyID;
	int CentralStockID;
	int StockID;

	string managedMission;	
	string triggerId;
	
	// CONSTRUTOR: Inicialização segura de Arrays
	void alpMissionAddNPC()
	{
		attachments = new array<string>;
		cargo = new array<ref alpLootCargo>;
		AvailableGoodsByTag = new array<string>;
	}
}

class alpNPC_Merchant : alpMissionAddNPC
{
	bool NoReputationRequirementsWhileBuying = false; // CORREÇÃO: 0 -> false
	ref map<string, int> Stock;
	ref map<string, int> AllowedTradingGoods;
	
	// CONSTRUTOR: Inicialização para classe herdada
	void alpNPC_Merchant()
	{
		Stock = new map<string, int>;
		AllowedTradingGoods = new map<string, int>;
	}
}