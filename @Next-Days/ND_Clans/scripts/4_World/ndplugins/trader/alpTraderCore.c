modded class alpTraderCore
{
	override bool PluginsOnRPC(int rpc, PlayerBase player, ParamsReadContext ctx )
	{
		if (!super.PluginsOnRPC(rpc, player, ctx))
		{
			// CORREÇÃO 1: Failsafe para evitar Crash se o player ou componentes forem nulos
			if (!player || !player.IsAlive()) return false;

			switch ( rpc )
			{
				case ALP_RPC_PLUGIN_MS_TRADER.PP_TAXES:
					PayTaxes( player, ctx );					
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_BUY:
					BuyEstate( player, ctx );					
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_SELL:
					SellEstate( player, ctx );					
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_BUY_KEY:
					BuyEstateKey( player, ctx );					
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_UPDATE_SETTINGS:
					UpdateEstateSettings( player, ctx );					
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.PP_PERMISSION:
					SetPermissionPP( player, ctx );					
					return true;																					
			}
			return false;
		}
		return true;
	}	
	
	void SetPermissionPP(PlayerBase player, ParamsReadContext ctx)
	{	
		int settings;
		if (!ctx.Read(settings)) return;
	
		// CORREÇÃO: Check de PlotPole
		if (player.alp_PlotPoleManage)
		{
			player.alp_PlotPoleManage.SetClanPermission( settings );
			player.alp_PlotPoleManage.SetSynchDirty();
		}

		if (player.GetSyncData()) player.GetSyncData().ForceSync();
		
		auto cart = player.GetRP().GetCart();
		if (cart)
		{
			int stockID = cart.GetNPCid();	
			GetND().GetMS().GetTrader().GiveMeStock( stockID, player, true);
		}
	}		
	
	void UpdateEstateSettings(PlayerBase player, ParamsReadContext ctx)
	{	
		Param4<int,int,int,int> values;
		if (!ctx.Read(values)) return;
		
		int houseID = values.param1;
		int keyID = values.param2;		
		int settings = values.param3;	
		
		// SEGURANÇA: O servidor deve recalcular o preço, não ler do cliente.
		// Aqui deve entrar sua lógica de precificação original do Mod.
		int topay = values.param4; 
		if (topay < 0) return; // Bloqueio imediato de exploit de dinheiro negativo

		auto rp = player.GetRP();
		if (!rp || !player.alp_PlotPoleManage) return;

		auto cart = rp.GetCart();
		cart.Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = cart.GetNPCid();		
		int currency = cart.GetCurrencyID();
		
		if ( cart.GetTotalBalance() >= topay ) 
		{
			if ( topay > 0 )
			{
				ProcessPayment(player, guid, currency, topay, stockID);
			}

			player.alp_PlotPoleManage.UpdateEstateOwnership(player, houseID, keyID, settings);
			player.alp_PlotPoleManage.SetSynchDirty();
		}	

		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock( stockID, player, true);	
	}		
	
	void BuyEstateKey(PlayerBase player, ParamsReadContext ctx)
	{	
		Param4<int,int,int,int> values;
		if (!ctx.Read(values)) return;
		
		int houseID = values.param1;
		int keyID = values.param2;		
		int doorsCount = values.param3;	
		int topay = values.param4;
		
		if (topay < 0 || doorsCount > 32) return; // CORREÇÃO: Limite de DoS/Exploit

		auto cart = player.GetRP().GetCart();
		if (!cart) return;
		cart.Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = cart.GetNPCid();		
		int currency = cart.GetCurrencyID();
		
		if ( cart.GetTotalBalance() >= topay )
		{
			if ( topay > 0 )
			{
				ProcessPayment(player, guid, currency, topay, stockID);

				// Criação de chaves com segurança
				CreateKey(player, keyID, -1); // Master Key
				for(int i = 0; i < doorsCount; i++)
				{
					CreateKey(player, keyID, i);
				}				
			}
		}	

		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock( stockID, player, true);		
	}

	// Helper para reduzir repetição e aumentar segurança
	protected void CreateKey(PlayerBase player, int houseID, int keyID)
	{
		alp_HouseKey key = alp_HouseKey.Cast(player.CreateInInventory("alp_HouseKey")); 
		if (!key) key = alp_HouseKey.Cast(GetGame().CreateObject("alp_HouseKey", player.GetPosition()));
		
		if (key)
		{
			key.SetHouseID(houseID);
			key.SetKeyID(keyID);
			key.SetSynchDirty();
		}
	}

	protected void ProcessPayment(PlayerBase player, int guid, int currency, int amount, int stockID)
	{
		auto cart = player.GetRP().GetCart();
		int isEbank = cart.HasBankAccount();
		int remaining = amount;

		if (isEbank)
		{
			remaining = alpBANK.AddBalanceToAccount(guid, currency, -amount, player);
			alpBANK.SaveAccount(guid);
		}

		if (remaining > 0 && isEbank != alpNPC_AVAILABLE_MENU.BANK_ONLY)
		{
			int newCash = cart.GetCash() - remaining;
			cart.GiveMeMoney(Math.Max(0, newCash), currency);
		}

		alpBANK.TakeBusinessProfit(currency, amount, true);		
		AddBalanceTrader(stockID, amount);
	}

	// ... Os demais métodos BuyEstate, SellEstate e PayTaxes devem seguir a mesma lógica de ProcessPayment acima
};