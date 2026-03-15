/**
 * alpTraderCore.c
 * * TRADER CORE SYSTEM - Módulo ND_MISSIONS (Trader)
 * Processamento de RPCs, transações de estoque, banco e logística de comércio.
 */

enum alpNPCINTERACTION
{
	UNLOCKKEYBORD,
	ME_FEES,
	ME_CURE_ALL,
	ME_CURE_DISEASE,
	ME_DNA_SAVE,
	ME_DNA_LOAD,	
	SPREADRUMOURS
}

enum alpTRADER_ACTION
{
	SYNC,
	DATA_SYNC_COMPLETED,
	DATA,
	DATA_NOPRICELIST,
	DATA_NOSTOCKLIST,
	DATA_ONLYCATEGORY,
	STOCK,
	BUYING,
	SELLING,
	BANK,
	PLOTPOLE,
	ESTATE,
	NPCPLUS,	
	NPCPLUS_RUMOURS,
	COUNT
}

class alpTraderCore extends alpTraderCoreBase
{
	// Controle de Sincronização no Cliente
	protected bool alp_AreTraderDataVaild = false;	
	protected bool m_CanMakeLogs;

	// --- Inicialização ---

	override void InitCore()
	{
		if (GetGame().IsServer())
		{
			m_CanMakeLogs = GetND().GetMS().GetOptoinsTrader().MakeTraderLogs;
			
			// Agendamento de Reposição de Estoque (Restocking)
			int restockingTime = GetND().GetMS().GetOptoinsTrader().TraderRestockingPerTime;
			if (restockingTime)
			{
				restockingTime *= 1000;
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Restocking, restockingTime, true);
			}
		}
	}

	// --- Gerenciador de RPC (Dispatcher) ---

	void OnRPC(PlayerBase player, ParamsReadContext ctx)
	{
		int rpc;
		if (!ctx.Read(rpc)) return;
		
		switch (rpc)
		{
			case ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ALL_STOCK:
			{
				array<int> items;
				ctx.Read(items);
				int stockID = player.GetRP().GetCart().GetNPCid();
				if (items && items.Count() > 0) UpdateStock(stockID, items);	
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.GetReadyClientData, 1200, false, player);
				break;
			}	
			case ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ACCOUNT:
			{
				alpBankAccount account;
				ctx.Read(account);
				ctx.Read(alpBANK.alp_BankBalance);
				ctx.Read(alpBANK.alp_PlayerBankBalance);
				ctx.Read(alpBANK.alp_TraderBankBalance);
				alpBANK.SetClientAccount(account);
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.GetReadyClientData, 1200, false, player);
				break;
			}
			case ALP_RPC_PLUGIN_MS_TRADER.ATM_CASH:
			{
				Param3<int, int, int> cash_transaction; 
				ctx.Read(cash_transaction);			
				
				player.GetRP().GetCart().Refresh();		
				int currentcash = player.GetRP().GetCart().GetMoney(cash_transaction.param2);		
				int cashBack = alpBANK.AddBalanceToAccount(cash_transaction.param1, cash_transaction.param2, cash_transaction.param3, player);	
				
				if (cash_transaction.param3 > 0) // Depósito
					currentcash -= cash_transaction.param3;
				else // Saque
					currentcash -= (cashBack) ? (cash_transaction.param3 + cashBack) : cash_transaction.param3;

				player.GetRP().GetCart().GiveMeMoney(currentcash, cash_transaction.param2);
				GiveMeAccount(cash_transaction.param1, player);
				break;
			}					
			case ALP_RPC_PLUGIN_MS_TRADER.BUY_ITEMS:
			{
				array<ref Param3<string, int, int>> itemsToBuy;
				ctx.Read(itemsToBuy);
				BuyItems(player, itemsToBuy);
				break;
			}	
			case ALP_RPC_PLUGIN_MS_TRADER.SELL_ITEMS:
			{
				array<ref Param2<string, int>> itemsToSell;
				ctx.Read(itemsToSell);
				SellItems(player, itemsToSell);				
				break;
			}		
			case ALP_RPC_PLUGIN_MS_TRADER.ATM_TAKELOAN:
			{
				Param6<int, int, int, int, float, int> takeLoan;
				ctx.Read(takeLoan);
				alpBANK.TakeLoan(player, takeLoan);
				GiveMeAccount(takeLoan.param1, player);				
				break;
			}	
			default:
				PluginsOnRPC(rpc, player, ctx);
				break;
		}	
	}

	// --- Lógica de Transação (Server-Side) ---

	/**
	 * Processa a venda de itens do jogador para o Trader.
	 */
	void SellItems(PlayerBase player, array<ref Param2<string, int>> itemstosell)
	{
		player.GetRP().GetCart().Refresh();
		int guid = player.GetPlayerHive().GetPlayerID();
		int stockID = player.GetRP().GetCart().GetNPCid();				
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();
		
		int backCash, cashTraderBalance;
		float reputationAcc;

		string timeStamp = alpUF.GetTimestamp(); // Helper original ou UF
		
		foreach(Param2<string, int> item : itemstosell)
		{
			EntityAI ent = player.GetRP().GetCart().GetItemByID(item.param1);
			if (ent)
			{
				string type = ent.GetType();
				// Gerenciamento de Estoque (Munição vs Itens)
				if (ent.IsMagazine())
				{
					Magazine_Base mag = Magazine_Base.Cast(ent);
					if (mag && mag.GetAmmoCount() / mag.GetAmmoMax() > 0.5) AddCount(stockID, type, 1);
				}
				else AddCount(stockID, type, 1);

				// Cálculo de Reputação
				reputationAcc += (ent.IsTransport()) ? (CarScript.Cast(ent).GetTraderItemConfig().ReputationRatioSelling * item.param2) : (ItemBase.Cast(ent).GetTraderItemConfig().ReputationRatioSelling * item.param2);
				
				GetGame().ObjectDelete(ent);			
				if (isEbank) alpBANK.AddBalanceToAccount(guid, currency, item.param2, player);
				else backCash += item.param2;				
				
				cashTraderBalance -= item.param2;
				if (m_CanMakeLogs) GetND().MakeTraderLog(timeStamp, player, stockID, 1, type, 1, cashTraderBalance);
			}
		}

		if (reputationAcc) player.GetRP().ChangeReputation(reputationAcc * player.GetReputationMltp(1));
		if (backCash) player.GetRP().GetCart().GiveMeMoney(player.GetRP().GetCart().GetCash() + backCash, currency);
		
		alpBANK.TakeBusinessProfit(currency, Math.AbsInt(cashTraderBalance));
		AddBalanceTrader(stockID, cashTraderBalance);
		
		player.GetSyncData().ForceSync();
		GiveMeStock(stockID, player);		
	}	

	/**
	 * Processa a compra de itens do Trader para o jogador.
	 */
	void BuyItems(PlayerBase player, array<ref Param3<string, int, int>> itemstobuy)
	{
		player.GetRP().GetCart().Refresh();
		int guid = player.GetPlayerHive().GetPlayerID();
		int stockID = player.GetRP().GetCart().GetNPCid();
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		
		int toPay, cashTraderBalance;
		float reputationAcc;
		string timeStamp = alpUF.GetTimestamp();

		foreach(Param3<string, int, int> item : itemstobuy)
		{
			int count = AddCount(stockID, item.param1, -item.param3);
			for(int i = 0; i < count; i++)
			{	
				EntityAI ent = player.GetRP().GetCart().InsertIntoCart(item.param1);		
				if (!ent && (GetGame().IsKindOf(item.param1, "CarScript") || GetGame().IsKindOf(item.param1, "HelicopterScript")))
					ent = player.GetRP().GetCart().BuyVehicle(item.param1);

				if (toPay + item.param2 > totalbalance || !ent)
				{
					if (ent) GetGame().ObjectDelete(ent);
					AddCount(stockID, item.param1, 1);
					break;
				}
				
				toPay += item.param2;
				cashTraderBalance += item.param2;
				
				// Reputação e Lógica de Cartão de Débito
				if (ent)
				{
					reputationAcc -= (ent.IsTransport()) ? (ItemBase.Cast(ent).GetTraderItemConfig().ReputationRatioBuying * item.param2) : (ItemBase.Cast(ent).GetTraderItemConfig().ReputationRatioBuying * item.param2);
					if (ent.GetType() == "alp_Debitcard")
					{
						alp_Debitcard card = alp_Debitcard.Cast(ent);
						card.SetBankID(guid);					
						alpBANK.RegisterCard(guid, card.GetCardID());
					}
				}
			}		
		}

		if (reputationAcc) player.GetRP().ChangeReputation(reputationAcc * player.GetReputationMltp(0));
		if (isEbank) toPay = alpBANK.AddBalanceToAccount(guid, currency, -toPay, player);

		if (toPay) player.GetRP().GetCart().GiveMeMoney(player.GetRP().GetCart().GetCash() - toPay, currency);			
		
		alpBANK.TakeBusinessProfit(currency, cashTraderBalance);
		AddBalanceTrader(stockID, cashTraderBalance);
		
		player.GetSyncData().ForceSync();
		GiveMeStock(stockID, player);		
	}

	// --- Interfaces de Comunicação (Client/Server) ---

	void GiveMeStock(int id, PlayerBase player, bool empty = false)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetMS().GetID());
		rpc.Write(ALP_RPC_PLUGIN_MS.TRADER);	
		rpc.Write(ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ALL_STOCK);	
		
		array<int> items = (empty) ? new array<int> : GetStockItems(id);
		rpc.Write(items);	
		GetND().SendGameRPC(rpc, player);	
	}	
	
	void GiveMeAccount(int id, PlayerBase player)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetMS().GetID());
		rpc.Write(ALP_RPC_PLUGIN_MS.TRADER);	
		rpc.Write(ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ACCOUNT);	
		
		rpc.Write(alpBANK.GetBankAccount(id));	
		rpc.Write(alpBANK.alp_BankBalance);	
		rpc.Write(alpBANK.alp_PlayerBankBalance);	
		rpc.Write(alpBANK.alp_TraderBankBalance);	
		GetND().SendGameRPC(rpc, player);	
	}		

	void CashTranscation(int accountid, int currency, int cash, PlayerBase player)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetMS().GetID());
		rpc.Write(ALP_RPC_PLUGIN_MS.TRADER);	
		rpc.Write(ALP_RPC_PLUGIN_MS_TRADER.ATM_CASH);	
		rpc.Write(new Param3<int, int, int>(accountid, currency, cash));		
		GetND().SendGameRPC(rpc, player);	
		SetValidTraderData(false);	
	}	

	void GetReadyClientData(PlayerBase player)
	{
		player.GetRP().GetCart().Refresh();
		SetValidTraderData(true);	
	}

	void SetValidTraderData(bool state) { alp_AreTraderDataVaild = state; }
	bool IsTraderSet() { return alp_AreTraderDataVaild; }
	bool PluginsOnRPC(int rpc, PlayerBase player, ParamsReadContext ctx) { return false; }	
}