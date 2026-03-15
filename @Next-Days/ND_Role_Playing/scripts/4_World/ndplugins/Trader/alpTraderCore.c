/**
 * @class   alpTraderCore
 * @brief   Núcleo de transações do Trader (Cura, DNA e Reputação)
 * Auditado em: 2026 - Foco em Segurança de Economia e Estabilidade do Servidor
 */
modded class alpTraderCore extends alpTraderCoreBase
{
	static ref alpMedicalFees alp_Fees;
	
	alpMedicalFees GetFees()
	{
		if (!alp_Fees) alp_Fees = new alpMedicalFees();
		return alp_Fees;
	}

	override bool PluginsOnRPC(int rpc, PlayerBase player, ParamsReadContext ctx )
	{
		if (!super.PluginsOnRPC(rpc, player, ctx))
		{
			if (!player) return false;

			switch (rpc)
			{
				case ALP_RPC_PLUGIN_MS_TRADER.SPREAD_RUMOURS:
					SpreadRumours(player, ctx);
					return true;
				
				case ALP_RPC_PLUGIN_MS_TRADER.ME_CURE_DISEASE:
					CureDisease(player, ctx);
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.ME_DNA_SAVE:
					SaveDNA(player, ctx);
					return true;

				case ALP_RPC_PLUGIN_MS_TRADER.ME_DNA_LOAD:
					LoadDNA(player, ctx);
					return true;
			}
			return false;
		}
		return true;
	}

	// --- LÓGICA DE CURA (SERVER SIDE - PROTEGIDA) ---
	void CureDisease(PlayerBase player, ParamsReadContext ctx)
	{	
		int diseaseID;
		int clientAllegedPay; // Valor enviado pelo cliente (será ignorado na transação real)
		
		if (!ctx.Read(diseaseID) || !ctx.Read(clientAllegedPay)) return;

		// 1. SEGURANÇA: O Servidor recalcula o preço real
		int serverPrice = player.GetRP().GetMedicalFee(player.GetRP().GetCart().GetNPCid(), diseaseID); 
		
		// 2. PROTEÇÃO CONTRA NULL: Verifica se a doença é válida
		auto diseaseObj = player.GetRP().alp_MedicList.Get(diseaseID);
		if (!diseaseObj) return;

		if (CanAfford(player, serverPrice) && diseaseObj.IsInfected())
		{
			ProcessPayment(player, serverPrice);
			diseaseObj.CureDisease();
			
			// Notificações e Sync
			player.GetSyncData().ForceSync();
		}
	}

	// --- LÓGICA DE DNA (SERVER SIDE - PROTEGIDA) ---
	void SaveDNA(PlayerBase player, ParamsReadContext ctx)
	{	
		int clientPay;
		if (!ctx.Read(clientPay)) return;

		// 3. SEGURANÇA: Preço fixo ou calculado pelo servidor
		int dnaCost = 5000; // Exemplo de valor fixo de servidor
		
		if (CanAfford(player, dnaCost))
		{
			ProcessPayment(player, dnaCost);
			player.GetPlayerHive().SaveDNA();
			player.GetSyncData().ForceSync();
		}
	}

	// --- MÉTODOS AUXILIARES DE ECONOMIA ---
	protected bool CanAfford(PlayerBase player, int cost)
	{
		player.GetRP().GetCart().Refresh();
		int total = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		bool hasEbank = player.GetRP().GetCart().HasBankAccount();

		return (cash >= cost || (hasEbank && total >= cost));
	}

	protected void ProcessPayment(PlayerBase player, int cost)
	{
		int guid = player.GetPlayerHive().GetPlayerID();
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int stockID = player.GetRP().GetCart().GetNPCid();
		
		// Lógica simplificada de débito (Prioriza Banco, depois Dinheiro)
		if (player.GetRP().GetCart().HasBankAccount())
		{
			cost += alpBANK.AddBalanceToAccount(guid, currency, -cost, player);
			alpBANK.SaveAccount(guid);
		}
		
		if (cost > 0)
		{
			player.GetRP().GetCart().GiveMeMoney(player.GetRP().GetCart().GetCash() - cost, currency);
		}

		// Lucro do NPC/Banco
		alpBANK.TakeBusinessProfit(currency, cost);
		AddBalanceTrader(stockID, cost);
	}

	// --- RPCs ENVIADAS PELO CLIENTE ---
	void CureDiseaseRPC(int disease, int pay, PlayerBase player)
	{
		SendTraderRPC(ALP_RPC_PLUGIN_MS_TRADER.ME_CURE_DISEASE, disease, pay, player);
	}

	protected void SendTraderRPC(int type, int val1, int val2, PlayerBase player)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetMS().GetID());
		rpc.Write(ALP_RPC_PLUGIN_MS.TRADER);
		rpc.Write(type);
		rpc.Write(val1);
		rpc.Write(val2);
		GetND().SendGameRPC(rpc, player);
		SetValidTraderData(false);
	}
}