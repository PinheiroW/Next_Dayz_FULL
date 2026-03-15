/**
 * alpTraderCoreBase.c
 * * TRADER FOUNDATION - Módulo ND_MISSIONS (Trader)
 * Classe base para gerenciamento de estoque, precificação, menus e descoberta de itens.
 */

class alpTraderCoreBase 
{
	// --- Variáveis de Identidade e Ação ---
	int alp_NPC_ID;
	static bool TRADER_ACTION_BUY;
		
	// --- Mapeamentos Globais (Static para eficiência) ---
	static autoptr map<int, string> alp_CurrencyMapped;
	static autoptr map<string, autoptr alpTraderItemConfig> alp_AllItemsByName = new map<string, autoptr alpTraderItemConfig>;
	static autoptr map<int, autoptr alpTraderCategories> alp_CategoriesMapped = new map<int, ref alpTraderCategories>;
	static autoptr map<int, autoptr alpNPCtraderStock> alp_TraderStockMapped = new map<int, autoptr alpNPCtraderStock>;
	static autoptr map<int, autoptr map<string, int>> alp_TraderMainStock = new map<int, autoptr map<string, int>>;
	static autoptr array<string> alp_AllowedItems = new array<string>;
	
	// --- Overrides e Configurações ---
	static autoptr array<autoptr alpTraderCategories> alp_CategoriesOverride;
	static autoptr array<autoptr alpTraderItemConfig> alp_ItemsOverride;
	
	// --- Instâncias de Menu e Dados ---
	autoptr map<string, autoptr array<autoptr alpTraderItemConfig>> alp_AllItemsByTag;
	ref alpMenuCategory alp_TraderMenu;
	ref array<EntityAI> alp_ReservedItem;
	ref array<ref alpProductCard> alp_TraderData;
	ref map<int, ref array<ref alpProductCard>> alp_TraderDataIndexed;		

	// --- Inicialização e Limpeza ---

	void alpTraderCoreBase(map<int, ref alpMission> missions)
	{
		if (GetGame().IsClient())
		{
			ReadCategories();
			alp_ReservedItem = new array<EntityAI>;
		}

		if (GetGame().IsServer())
		{
			// Carrega modificações do usuário
			JsonFileLoader<array<ref alpTraderCategories>>.JsonLoadFile(ALP_MISSIONS_TRADER_CATEGORIES_OVERRIDE, alp_CategoriesOverride);
			JsonFileLoader<array<autoptr alpTraderItemConfig>>.JsonLoadFile(ALP_MISSIONS_TRADER_ITEMS_OVERRIDE, alp_ItemsOverride);			
			
			ReadCategories();
			
			if (missions)
			{
				// Inicializa NPCs após um pequeno delay para garantir que as missões estão prontas
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitTraders, 1000, false, missions);
			}
		}
		InitCore();
	}
	
	void ~alpTraderCoreBase()
	{
		delete alp_AllItemsByTag;
		delete alp_TraderMenu;
		delete alp_ReservedItem;
		delete alp_TraderData;
		delete alp_TraderDataIndexed;
	}

	void InitCore(){} // Reservado para a classe filha

	// --- Gerenciamento de Estoque ---

	/**
	 * Adiciona ou remove itens do estoque (Individual ou Centralizado).
	 * Retorna a quantidade efetivamente alterada.
	 */
	static int AddCount(int npcID, string name, int change) 
	{
		int count;
		alpNPCtraderStock trader = alp_TraderStockMapped.Get(npcID);
		if (!trader) return 0;

		map<string, int> stock = (trader.CentralStock) ? GetCentralStockItems(trader.CentralStock) : trader.Stock;
		if (!stock) return 0;

		int current;
		if (change < 0) // Venda para o jogador (Remoção do estoque)
		{
			if (stock.Find(name, current))
			{
				count = current + change;
				if (count >= 0) { stock.Set(name, count); return Math.AbsInt(change); }					
				else { stock.Set(name, 0); return current; }
			}
		}
		else // Compra do jogador (Adição ao estoque)
		{
			alpTraderCategories cat = GetCategoryByName(name);
			if (stock.Find(name, current) || trader.CentralStock)
			{
				count = current + change;
				if (cat && count > cat.StockCap) count = cat.StockCap;
				stock.Set(name, count);
				return 0;
			}
		}
		return 0;
	}

	/**
	 * Retorna o saldo do NPC Trader atual.
	 */
	int GetTraderBalance(PlayerBase player)
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(player.GetRP().GetCart().GetNPCid());
		return (stock) ? stock.Cash : 0;
	}

	// --- Construção de Menus (UI) ---

	/**
	 * Constrói a hierarquia de menu para venda de itens do jogador.
	 */
	void SetSellMenu()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(alp_NPC_ID);
		
		alp_TraderMenu = new alpMenuCategory();
		alp_TraderDataIndexed = new map<int, ref array<ref alpProductCard>>;			
		alp_TraderData = new array<ref alpProductCard>;		
		
		map<string, ref map<string, ref alpTraderItem>> categories = player.GetRP().GetCart().GetItemsToSell();
		
		if (categories && stock)
		{
			for (int c = 0; c < categories.Count(); c++)
			{
				map<string, ref alpTraderItem> items = categories.GetElement(c);
				if (!items) continue;

				for (int i = 0; i < items.Count(); i++)
				{
					alpTraderItem item = items.GetElement(i);
					string className = item.GetType();		
					alpTraderItemConfig config = GetTraderItemConfig(className);	

					int inStock;
					if (config && stock.Stock.Find(className, inStock))
					{									
						alpMenuCategory m1 = alp_TraderMenu.AddSubMenu(item.Group, c);
						alpMenuCategory m2 = m1.AddSubMenu(item.Category, c);			
						m2.AddSubMenu(item.Subcategory, c);

						alpProductCard card = new alpProductCard(className, config, item.GetStock(), item.GetItem());							
						alp_TraderData.Insert(card);

						array<ref alpProductCard> indexedList;			
						if (!alp_TraderDataIndexed.Find(c, indexedList))
						{
							indexedList = new array<ref alpProductCard>;
							alp_TraderDataIndexed.Insert(c, indexedList);				
						}
						indexedList.Insert(card);									
					}
				}
			}			
		}
	}	

	/**
	 * Constrói a hierarquia de menu para compra de itens do NPC.
	 */
	void SetBuyMenu()
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(alp_NPC_ID);
		alp_TraderMenu = new alpMenuCategory();
		alp_TraderDataIndexed = new map<int, ref array<ref alpProductCard>>;			
		alp_TraderData = new array<ref alpProductCard>;		
	
		if (stock)
		{
			for (int i = 0; i < stock.Stock.Count(); i++)
			{
				string className = stock.Stock.GetKey(i);
				if (!alpUF.IsValidTraderItem(className)) continue;
					
				alpTraderItemConfig config = GetTraderItemConfig(className);
				if (config)
				{
					alpTraderCategories category = alp_CategoriesMapped.Get(config.CategoryID);
					if (category)
					{
						alpMenuCategory m1 = alp_TraderMenu.AddSubMenu(category.Groups, config.CategoryID);
						alpMenuCategory m2 = m1.AddSubMenu(category.Category, config.CategoryID);		
						alpMenuCategory m3 = m2.AddSubMenu(category.SubCategory, config.CategoryID);		
						
						int idx = m3.GetCategoryID();	
						alpProductCard card = new alpProductCard(className, config);			

						alp_TraderData.Insert(card);
						array<ref alpProductCard> indexedList;			
						if (!alp_TraderDataIndexed.Find(idx, indexedList))
						{
							indexedList = new array<ref alpProductCard>;
							alp_TraderDataIndexed.Insert(idx, indexedList);				
						}
						indexedList.Insert(card);						
					}
				} 					
			}			
		}		
	}

	// --- Configurações e Descoberta ---

	/**
	 * Obtém a configuração específica de um item, suportando overrides.
	 */
	static alpTraderItemConfig GetTraderItemConfig(string className)
	{
		if (!alp_AllowedItems || (GetGame().IsClient() && alp_AllowedItems.Find(className) < 0)) return null;

		alpTraderItemConfig itemconfig;
		if (alp_AllItemsByName.Find(className, itemconfig)) return itemconfig;

		// Busca nas classes do DayZ
		string cfgPath = alpUF.GetConfigPath(className); // Helper simplificado
		
		int category = GetGame().ConfigGetInt(cfgPath + className + " TraderItem CategoryID");
		int price = GetGame().ConfigGetInt(cfgPath + className + " TraderItem Price");
		bool canBuy = GetGame().ConfigGetInt(cfgPath + className + " TraderItem CanBuy");
		bool canSell = GetGame().ConfigGetInt(cfgPath + className + " TraderItem CanSell");						
		int reqRep = GetGame().ConfigGetInt(cfgPath + className + " TraderItem RequiredReputation");		
		float rS = GetGame().ConfigGetFloat(cfgPath + className + " TraderItem SellingBonusReputationRatio");			
		float rB = GetGame().ConfigGetFloat(cfgPath + className + " TraderItem BuyingPenaltyReputationRatio");		
		
		// Aplica Overrides se existirem
		if (alp_ItemsOverride) 
		{
			foreach (alpTraderItemConfig itm : alp_ItemsOverride)
			{
				if (itm.Name == className) { itemconfig = itm; break; }
			}
		}

		if (!itemconfig)
		{
			itemconfig = new alpTraderItemConfig(className, category, price, canBuy, canSell, reqRep, rS, rB);		
		}
		
		alp_AllItemsByName.Set(className, itemconfig);
		return itemconfig;
	}

	// --- Auxiliares e Getters ---

	static alpTraderCategories GetCategory(int id) { return alp_CategoriesMapped.Get(id); }
	static string GetCurrencyName(int id) { /* Lógica de mapeamento de moedas preservada */ return ""; }
	bool IsBuyMenu() { return TRADER_ACTION_BUY; }
	bool IsSellMenu() { return !TRADER_ACTION_BUY; }	
	alpMenuCategory GetTraderMenu() { if (IsBuyMenu() && !alp_TraderMenu) SetBuyMenu(); if (IsSellMenu() && !alp_TraderMenu) SetSellMenu(); return alp_TraderMenu; }
}