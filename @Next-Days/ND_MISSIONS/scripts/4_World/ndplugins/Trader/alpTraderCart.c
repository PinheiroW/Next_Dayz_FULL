/**
 * alpTraderCart.c
 * * TRANSACTION & CART MANAGER - Módulo ND_MISSIONS (Trader)
 * Gerencia o carrinho de compras, escaneamento de itens e logística de entrega.
 */

class alpTraderItem 
{
	string Group;
	string Category;
	string Subcategory;
	
	EntityAI Item;
	ref array<string> ItemsID;
	
	void alpTraderItem(EntityAI ent)
	{
		Item = ent;
		ItemsID = new array<string>;
	}
	
	void AddItem(string id) { ItemsID.Insert(id); }
	array<string> GetStock() { return ItemsID; }
	string GetType() { return Item.GetType(); }
	EntityAI GetItem() { return Item; }
}

class alpTraderCart 
{
	protected PlayerBase alp_Player;
	protected int alp_NPCID;
	protected int alp_MissionID;
	
	protected ref map<string, EntityAI> alp_ItemsMapped;
	protected ref array<ItemBase> alp_AllMoney;
	protected ref array<ref alpProductCard> alp_ReservedProducts;
	protected ref map<string, ref map<string, ref alpTraderItem>> alp_ItemsTosell;

	void alpTraderCart(PlayerBase player)
	{
		alp_Player = player;
		alp_ReservedProducts = new array<ref alpProductCard>;
		alp_AllMoney = new array<ItemBase>;
		alp_ItemsMapped = new map<string, EntityAI>;
		alp_ItemsTosell = new map<string, ref map<string, ref alpTraderItem>>;
	}

	// --- Lógica de Transação ---

	/**
	 * Finaliza a transação baseada no menu atual (Compra ou Venda).
	 */
	bool Confirm()
	{
		if (!CheckCashCondition(0))
		{
			GetND().GetNotf().GetHud().SendMessageALP(ALPMSTYPE.SMPERSONAL, "#trader_info_notpossible"); 
			return false;
		}
		
		if (GetND().GetMS().GetTrader().IsBuyMenu())
			SendItemsToBuy();
		else
			SendItemsToSell();

		ClearCart();	
		GetND().GetMS().GetTrader().SetValidTraderData(false);		
		return true;
	}

	protected void SendItemsToBuy()
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetMS().GetID());
		rpc.Write(ALP_RPC_PLUGIN_MS.TRADER);	
		rpc.Write(ALP_RPC_PLUGIN_MS_TRADER.BUY_ITEMS);	
		
		array<ref Param3<string, int, int>> items = new array<ref Param3<string, int, int>>;	
		foreach(alpProductCard product : alp_ReservedProducts)
		{
			items.Insert(new Param3<string, int, int>(product.GetType(), product.GetPrice(), product.GetCountReserved()));
		}
		
		rpc.Write(items);	
		GetND().SendGameRPC(rpc, alp_Player);	
	}

	protected void SendItemsToSell()
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetMS().GetID());
		rpc.Write(ALP_RPC_PLUGIN_MS.TRADER);	
		rpc.Write(ALP_RPC_PLUGIN_MS_TRADER.SELL_ITEMS);	
		
		array<ref Param2<string, int>> items = new array<ref Param2<string, int>>;	
		foreach(alpProductCard product : alp_ReservedProducts)
		{
			int price = product.GetPrice();
			int count = product.GetCountReserved();
			array<string> itemsID = product.GetIndexedItemToSell();
			for(int i = 0; i < count; i++)
			{
				items.Insert(new Param2<string, int>(itemsID.Get(i), price));	
			}
		}
		
		rpc.Write(items);		
		GetND().SendGameRPC(rpc, alp_Player);	
	}

	// --- Gestão de Dinheiro ---

	/**
	 * Converte um valor de saldo em notas físicas no inventário do jogador.
	 */
	void GiveMeMoney(int cash, int currencyID)
	{
		for (int i = 0; i < alp_AllMoney.Count();)
		{
			if (alpBANK.VerifyBankNote(currencyID, alp_AllMoney.Get(i).GetType()))
				GetGame().ObjectDelete(alp_AllMoney.Get(i));
			alp_AllMoney.Remove(i);
		}	

		if (cash > 0) GiveMeJustMoney(cash, currencyID);
	}

	void GiveMeJustMoney(int cash, int currencyID)
	{
		map<int, ref alpBankNote> banknotes = alpBANK.GetBankNotes(currencyID);	
		array<int> nominals = banknotes.GetKeyArray();		
		nominals.Sort(true);
		
		for (int i = 0; i < nominals.Count(); i++)
		{
			int nominal = nominals.Get(i);
			alpBankNote bn = banknotes.Get(nominal);
			int count = Math.Floor(cash / nominal); 

			if (count >= 1)
			{
				cash -= (count * nominal);	
				int stack = bn.Quantity;	
				
				while (count > 0)
				{
					int currentStack = (count > stack) ? stack : count;
					count -= currentStack;
					
					alp_Cash money = alp_Cash.Cast(alp_Player.CreateInInventory(bn.Name));
					if (!money) money = alp_Cash.Cast(GetGame().CreateObject(bn.Name, alp_Player.GetPosition(), false, false, true));
					
					if (money) money.SetQuantity(currentStack);
				}
			}
			if (cash == 0) break;
		}
	}

	// --- Escaneamento de Inventário ---

	/**
	 * Atualiza a lista de itens disponíveis para venda (Jogador + Veículos próximos).
	 */
	void Refresh()
	{
		alp_ItemsMapped.Clear();
		alp_ItemsTosell.Clear();
		alp_AllMoney.Clear();
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		ProcessItemsForSell(itemsArray, alp_Player.GetIdentity().GetName());

		// Escaneamento de Veículos Próximos
		Transport tr = alp_Player.GetRP().GetCar();		
		if (tr)
		{
			itemsArray.Clear();
			tr.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			ProcessItemsForSell(itemsArray, tr.GetDisplayName());
		}
	}

	protected void ProcessItemsForSell(array<EntityAI> items, string parentGroupName)
	{
		foreach (EntityAI ent : items)
		{
			ItemBase item = ItemBase.Cast(ent);
			if (item)
			{
				if (item.IsInherited(alp_Cash) && item.GetType() != "alp_CoinRare1")
					alp_AllMoney.Insert(item);
				else
					RegisterTraderItem(item, parentGroupName);
			}
		}
	}

	protected void RegisterTraderItem(ItemBase item, string groupName)
	{
		string name = item.GetNameALP(); 
		string subcat = GetParent(item, alp_Player.GetType());
		string category = groupName + groupName + subcat;
		
		map<string, ref alpTraderItem> traderItems;
		if (!alp_ItemsTosell.Find(category, traderItems))
		{
			traderItems = new map<string, ref alpTraderItem>;
			alp_ItemsTosell.Set(category, traderItems);
		}

		alpTraderItem tItem;
		if (!traderItems.Find(name, tItem))
		{
			tItem = new alpTraderItem(item);
			tItem.Group = groupName;
			tItem.Category = groupName;
			tItem.Subcategory = subcat;
			traderItems.Set(name, tItem);
		}
		string index = item.GetServerWorldID();
		tItem.AddItem(index);
		alp_ItemsMapped.Set(index, item);
	}

	// --- Logística de Veículos ---

	/**
	 * Realiza o spawn do veículo comprado no local designado pela missão.
	 */
	EntityAI BuyVehicle(string type)
	{
		EntityAI ent;
		alpMission mission = GetND().GetMS().GetMission(alp_MissionID);
		if (!mission) return null;

		foreach (alpMissionAddSpawn spawn : mission.GetTemplate().spawnPlaceForVehicles)
		{
			vector pos = mission.GetWorldPosition(spawn.position);
			ent = EntityAI.Cast(GetGame().CreateObject(type, pos));
			
			if (ent && !alpUF.IsColliding(ent))
			{
				ent.SetYawPitchRoll(mission.GetWorldOrientation(spawn.yaw, spawn.pitch, spawn.roll));	
				
				CarScript car;
				HelicopterScript heli;
				array<string> atts = GetND().GetMS().GetTrader().GetCarAttachments(type);

				if (Class.CastTo(car, ent))
				{
					if (!atts) { GetGame().ObjectDelete(ent); return null; }
					foreach (string att : atts) car.GetInventory().CreateInInventory(att);
					
					alpUF.FillFluidsToVehicle(car);
					if (!GetND().GetMS().GetOptoinsTrader().NoKeyForBoughtVehicle)
					{
						GiveMeVehicleKey(car.GetAlpCarID());
						car.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
						car.alp_Lock = true;							
					}
				}
				else if (Class.CastTo(heli, ent))
				{
					if (!atts) { GetGame().ObjectDelete(ent); return null; }
					foreach (string attH : atts) heli.GetInventory().CreateInInventory(attH);
				}

				ent.SetLifetimeMax(ALP_LIFETIMEMAX);
				ent.SetLifetime(ALP_LIFETIMEMAX);		
				ent.PlaceOnSurface();		
				return ent;
			}
			else if (ent) GetGame().ObjectDelete(ent);
		}
		return null;		
	}

	// --- Auxiliares ---

	bool CheckCashCondition(int price)
	{
		int cost = GetTotalAmount();
		int balance = (GetND().GetMS().GetTrader().IsBuyMenu()) ? GetTotalBalance() : GetCredit();
		return (balance - cost - price >= 0);
	}

	EntityAI InsertIntoCart(string type)
	{
		EntityAI ent = alp_Player.GetInventory().CreateInInventory(type);
		if (!ent)
		{
			Transport car = alp_Player.GetRP().GetCar();
			if (car)
			{
				car.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);		
				ent = car.GetInventory().CreateInInventory(type);
				car.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
			}		
		}
		if (GetGame().IsClient() && !ent) GetND().GetNotf().GetHud().SendMessageALP(ALPMSTYPE.SMPERSONAL, "#trader_info_noroom"); 
		return ent;
	}

	void GiveMeVehicleKey(int carID)
	{
		array<string> keys = {"alp_CarKey", "alp_CarKeyBlue", "alp_CarKeyGreen", "alp_CarKeyYellow", "alp_CarKeyWhite", "alp_CarKeyPurple", "alp_CarKeyBrown"};
		string keyType = keys.GetRandomElement();
		alp_CarKey key = alp_CarKey.Cast(alp_Player.CreateInInventory(keyType));
		if (!key) key = alp_CarKey.Cast(GetGame().CreateObject(keyType, alp_Player.GetPosition(), false, false, true));
		
		if (key) { key.SetAlpKeyID(carID); key.SetSynchDirty(); }		
	}

	int GetMoney(int currency = 0)
	{
		int total = 0;
		foreach (ItemBase moneyItem : alp_AllMoney)
		{
			alp_Cash cash = alp_Cash.Cast(moneyItem);
			if (cash && alpBANK.VerifyBankNote(currency, cash.GetType())) total += (int)cash.GetMonyeSum();
		}
		return total;		
	}

	int GetTotalBalance() { return (HasBankAccount() == alpPAY_METHODS.BANK_ONLY) ? GetCredit() : (GetCredit() + GetCash()); }
	int GetCash() { return GetMoney(GetCurrencyID()); }
	int GetCredit() { float b; alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.PLAYER_BALANCE).GetValue(b); return (int)b; }
	int GetCurrencyID() { alpNPCtraderStock s = alpTraderCoreBase.alp_TraderStockMapped.Get(alp_NPCID); return (s) ? s.CurrencyID : 0; }
	int HasBankAccount() { alpNPCtraderStock t = alpTraderCoreBase.alp_TraderStockMapped.Get(alp_NPCID); return (t) ? t.EnabledInteractions : 0; }
	int GetTotalAmount() { int t = 0; foreach(alpProductCard p : alp_ReservedProducts) t += p.GetCountReserved() * p.GetPrice(); return t; }
	string GetParent(EntityAI item, string root) { string n = item.GetDisplayName(); EntityAI p = EntityAI.Cast(item.GetHierarchyParent()); while(p && p.GetType() != root) { n = p.GetDisplayName(); p = EntityAI.Cast(p.GetHierarchyParent()); } return n; }
	void ClearCart() { foreach(alpProductCard p : alp_ReservedProducts) p.RemoveReservation(true); alp_ReservedProducts.Clear(); }
	void SetNPCid(int id, int mID = 0) { alp_NPCID = id; alp_MissionID = mID; }
}