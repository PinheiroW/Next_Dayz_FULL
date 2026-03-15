/**
 * alpOptionsMS_templates_trader.c
 * * CONFIGURAÇÃO DE TEMPLATES DO TRADER E ECONOMIA - Módulo ND_MISSIONS
 * Gerencia categorias, preços de itens, multiplicadores de alimentos e regras bancárias.
 */

class alpTraderCategories 
{
	int			CategoryID;
	string 		Tag;
	string 		Groups;
	string 		Category;
	string 		SubCategory;	
	int 		Restock	= 0;
	int 		RestockCap = 0;
	int			StockCap = 0;	
	float 		SellingRatioMin = 0.25;
	float		SellingRatioMax = 0.8;
	float 		BuingRatioMin = 1;	
	
	static alpTraderCategories GetCategory(string path)
	{
		alpTraderCategories cat = new alpTraderCategories();
		
		string subclass_path = path + " CategoryID";	
		cat.CategoryID = GetGame().ConfigGetInt(subclass_path);
		
		subclass_path = path + " Tag";	
		GetGame().ConfigGetText(subclass_path, cat.Tag);		
		
		subclass_path = path + " Groups";	
		GetGame().ConfigGetText(subclass_path, cat.Groups);	

		subclass_path = path + " Category";	
		GetGame().ConfigGetText(subclass_path, cat.Category);	
		
		subclass_path = path + " SubCategory";	
		GetGame().ConfigGetText(subclass_path, cat.SubCategory);							
		
		subclass_path = path + " Restock";	
		cat.Restock = GetGame().ConfigGetInt(subclass_path);	
						
		subclass_path = path + " RestockCap";	
		cat.RestockCap = GetGame().ConfigGetInt(subclass_path);	

		subclass_path = path + " StockCap";	
		cat.StockCap = GetGame().ConfigGetInt(subclass_path);			
		
		subclass_path = path + " SellingRatioMin";	
		cat.SellingRatioMin = GetGame().ConfigGetFloat(subclass_path);			
			
		subclass_path = path + " SellingRatioMax";	
		cat.SellingRatioMax = GetGame().ConfigGetFloat(subclass_path);	

		subclass_path = path + " BuingRatioMin";	
		cat.BuingRatioMin = GetGame().ConfigGetFloat(subclass_path);						
		
		return cat;	
	}
}

class alpTraderItemConfig 
{
	string Name;
	int CategoryID;
	int Price;	
	bool CanBuy;
	bool CanSell;
	int RequiredReputation;
	float ReputationRatioSelling;
	float ReputationRatioBuying;
	
	void alpTraderItemConfig(string name, int category, int price, bool canbuy, bool cansell, int reqRep, float ratioSelling, float ratioBuing)
	{
		Name = name;
		CategoryID = category;
		Price = price;
		CanBuy = canbuy;
		CanSell = cansell;
		RequiredReputation = reqRep;
		ReputationRatioSelling = ratioSelling;
		ReputationRatioBuying = ratioBuing;
	}
}

// Opções globais do sistema de Trader e Banco
class alpOptionsMStrader 
{	
	int QuestNominal									= 2;	
	
	int GiftToNewPlayer[3]								= {0, 0, 0};	

	float NPC_Menu_blur									= 0.0;	
	float ATM_Menu_blur									= 0.0;	
	bool ATM_NotRequiresPaymentCard						= false; // CORREÇÃO: 0 -> false
	int TraderRestockingPerTime							= 7200; // Segundos para repor estoque	
	float BankProfit									= 0.02;
	float BankLoanLimitPerAssets						= 0.02;
	float BankLoanInterestPerDay						= 0.05;
	int BankRewardForWantedPerson[2]					= {5000, 2};
	int PlayerDepositLimit								= 100000000;
	int PlayerLoanLimit									= 500000;
	bool DisableExchange								= false; // CORREÇÃO: 0 -> false

	bool MakeTraderLogs									= false;
	bool DeleteDroppedItem								= true;
	bool NoKeyForBoughtVehicle							= false;	
	bool KillZombiesWhileAttackAtTrader					= true;
	
	bool ShowAvailableItemInStock						= true;	
	bool ShowItemsWithNoStock							= false;	
	bool ShowItemsNotTradeable							= false;	
	
	// Multiplicadores de valor de alimentos baseados no estado
	float FoodRaw										= 1;
	float FoodBaked										= 1.5;
	float FoodBoiled									= 1.5;
	float FoodDried										= 3;
	float FoodBurned									= 0;
	float FoodRotten									= 0;	
	
	ref map<int, float> LiquidPricelist;
	
	void alpOptionsMStrader()
	{
		LiquidPricelist = new map<int, float>;
		
		// Preços de líquidos por tipo (ID vanilla)
		LiquidPricelist.Set(512, 0.25);   // Water
		LiquidPricelist.Set(2048, 5);     // Vodka
		LiquidPricelist.Set(4096, 2);     // Beer
		LiquidPricelist.Set(8192, 5);     // Gasoline
		LiquidPricelist.Set(16384, 1);    // Diesel
	}
}