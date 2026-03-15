/**
 * @class   alpProductCard
 * @brief   Gerencia a lógica de preços e permissões de compra no Trader baseada em RPG
 * Auditado em: 2026 - Foco em Performance de UI e Segurança de Ponteiro
 */
modded class alpProductCard 
{
	// 1. OTIMIZAÇÃO: Cache de Player para evitar múltiplas chamadas GetPlayer()
	override float GetPlayerCoef(alpNPCtraderStock trader)
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !trader) return 1.0; // Failsafe: preço padrão

		float hero = trader.PricelistRatioHero;
		float bandit = trader.PricelistRatioBandit;
		
		auto traderManager = GetND().GetMS().GetTrader();
		if (!traderManager) return 1.0;

		auto stock = traderManager.GetCurrentTrader();
		bool isHero = player.GetRP().IsHero();

		// 2. LÓGICA DE PREÇOS SIMPLIFICADA
		if (stock && !stock.RequiredCharacterTraits) 
		{
			if (traderManager.IsBuyMenu())
			{
				return isHero ? hero : bandit;
			}
			else // Menu de Venda
			{
				// No menu de venda, o jogador sempre quer o melhor coeficiente (menor perda)
				return Math.Min(hero, bandit);
			}
		}
		
		// Fallback para quando há Traits obrigatórios ou falha no stock
		return isHero ? hero : bandit;
	}

	// 3. REVISÃO DE REPUTAÇÃO: Foco em legibilidade e performance
	override bool HasReputation()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.GetSyncData()) return false;

		auto syncData = player.GetSyncData().GetElement(alpRPelements.REPUTATION);
		if (!syncData) return false;

		int currentRepLevel = syncData.GetValue();
		int requiredRep = GetRequiredReputation();
		
		auto traderManager = GetND().GetMS().GetTrader();
		if (!traderManager) return false;

		auto stock = traderManager.GetCurrentTrader();
		if (!stock) return false;

		// Lógica: Pode operar se tiver o nível OU se for menu de venda e o trader não exigir reputação para comprar de você
		bool hasLevel = (currentRepLevel >= requiredRep);
		bool isSellMenu = traderManager.IsSellMenu();
		bool ignoreRepOnSell = stock.NoReputation;

		if (hasLevel || (isSellMenu && ignoreRepOnSell))
		{
			return true;
		}

		return false;
	}
}