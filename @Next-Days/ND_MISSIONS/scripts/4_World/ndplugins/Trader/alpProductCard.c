/**
 * alpProductCard.c
 * * TRADER PRODUCT COMPONENT - Módulo ND_MISSIONS (Trader)
 * Gerencia a lógica de precificação, estoque e validação de troca para itens individuais.
 */

class alpProductCard
{
	protected string                alp_ClassName;
	protected string                alp_DisplayName;	
	protected EntityAI              alp_EntityAI;        // Preview Entity
	protected EntityAI              alp_PlayersEntityAI; // Player's actual item for sale
	protected ref alpTraderItemConfig alp_Config;
	
	protected ref array<EntityAI>   alp_ReservedItems;
	protected ref array<string>     alp_InInventory;
	protected int                   alp_Reserved;

	// --- Inicialização e Limpeza ---

	void alpProductCard(string className, alpTraderItemConfig config, array<string> ininventory = null, EntityAI ent = null)
	{
		alp_ReservedItems   = new array<EntityAI>;
		alp_PlayersEntityAI = ent;
		alp_ClassName       = className;
		alp_DisplayName     = alpUF.GetDisplayName(alp_ClassName);
		alp_Config          = config;
		alp_InInventory     = ininventory;		
	}
	
	void ~alpProductCard()
	{
		if (alp_EntityAI)
		{
			GetGame().ObjectDelete(alp_EntityAI);
		}
		ClearReservedItems(true);
	}

	// --- Lógica de Preço e Valor ---

	/**
	 * Retorna o valor base do item multiplicado pela taxa de câmbio.
	 */
	int GetValue()
	{
		int value;
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		EntityAI ent = GetEntity();		

		if (ent.IsTransport())
		{
			CarScript car = CarScript.Cast(ent);
			if (car) value = car.GetDefaultPrice();
		}
		else
		{
			ItemBase itm = ItemBase.Cast(ent);
			if (itm)
			{				
				if (itm.IsWeapon())
				{
					array<string> allowedAtt = trader.Stock.GetKeyArray();
					value = itm.GetDefaultPrice(true, allowedAtt);	
				}
				else
				{
					value = itm.GetDefaultPrice();
				}
			}		
		}
		
		float coef = GetPlayerCoef(trader) * alpBANK.GetCurrencyRate(trader.CurrencyID);		
		return (int)(value * coef);
	}	

	/**
	 * Calcula o preço final de compra ou venda considerando estoque, reputação e economia do Trader.
	 */
	int GetPrice()
	{
		alpTraderCategories category = alpTraderCoreBase.alp_CategoriesMapped.Get(alp_Config.CategoryID);
		
		int stockCap           = category.StockCap;
		float sellingRatioMin  = category.SellingRatioMin;
		float sellingRatioMax  = category.SellingRatioMax;
		float buingRatioMin    = category.BuingRatioMin;		
		
		float buy, sell, minB, minS, maxS, delta;
		int value = GetValue();

		if (!stockCap) 
		{
			if (sellingRatioMin != 1)
			{
				buy = value * (1 - GetSales());								
				if (sellingRatioMin != 0) sell = value * (sellingRatioMin + GetSales());
				if (sell >= buy) sell = buy * 0.95;
			}
			else 
			{
				buy = value;	
				sell = value * sellingRatioMin;		
			}
		}	
		else 
		{	
			minB = value * buingRatioMin;
			delta = (value - minB) / stockCap;
			
			buy = (value - Math.Min(GetCount(), stockCap) * delta);
			
			minS = buy * sellingRatioMin;		
			maxS = buy * sellingRatioMax;		
			delta = (maxS - minS) / stockCap;
			
			sell = (maxS - Math.Min(GetCount(), stockCap) * delta);
			
			if (sellingRatioMin != 1)
			{
				if (sellingRatioMin != 0) sell += buy * GetSales();
				buy = buy * (1 - GetSales());			
				if (sell > buy) sell = buy * 0.95;								
			}
		}			

		// Efeito colateral da liquidez do Trader (CashAffectsPrices)
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		float saleEffect = trader.CashAffectsPrices;

		if (saleEffect)
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			float traderCash;
			player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.TRADER_BALANCE).GetValue(traderCash);
			
			if (traderCash > trader.CashMinimal && traderCash < trader.CashOptimal)
			{
				saleEffect = 0;
			}
			else if (traderCash <= trader.CashMinimal)
			{
				saleEffect *= -1;	
			}		
		}

		if (GetND().GetMS().GetTrader().IsBuyMenu())
		{
			buy *= (1 + saleEffect);
			return (int)buy;
		}
		else
		{
			sell *= (1 + saleEffect);
			return (int)sell;
		}
	}

	// --- Validações de Troca ---

	/**
	 * Verifica se o item pode ser negociado (Reputação, Dinheiro, Inventário Vazio).
	 */
	bool CanBeTrade()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		bool basicConditions = HasReputation() && IsTradAble() && IsEmpty();
		bool financialCondition = player.GetRP().GetCart().CheckCashCondition(GetPrice());
		
		return (basicConditions && financialCondition);
	}

	/**
	 * Impede a venda de itens/veículos que contenham outros objetos dentro.
	 */
	bool IsEmpty()
	{
		if (GetND().GetMS().GetTrader().IsBuyMenu() || GetEntity().IsInherited(Magnum_Base))
			return true;
		
		if (alp_PlayersEntityAI)
		{
			if (alp_PlayersEntityAI.IsTransport())
			{
				CarScript car = CarScript.Cast(alp_PlayersEntityAI);
				return (car && !car.GetCargoCountALP());
			}
			else
			{
				ItemBase item = ItemBase.Cast(alp_PlayersEntityAI);
				if (item)
				{
					if (Weapon_Base.Cast(item.GetHierarchyParent())) return false;
					if (item.IsWeapon()) return true;
					
					return (!item.GetAttachmentCountALP() && !item.GetCargoCountALP());
				}
			}
		}
		return false;
	}

	// --- Reservas e Carrinho ---

	bool AddReservation()
	{
		if (alp_Reserved < GetAvailableItem())
		{
			if (GetND().GetMS().GetTrader().IsBuyMenu() && !GetEntity().IsTransport())
			{
				PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
				EntityAI ent = player.GetRP().GetCart().InsertIntoCart(GetType());
				if (!ent) return false;
				
				alp_ReservedItems.InsertAt(ent, 0);
			}
			alp_Reserved++;
			return true;
		}
		return false;
	}

	void ClearReservedItems(bool all = false)
	{
		if (alp_ReservedItems)
		{
			for (int i = 0; i < alp_ReservedItems.Count();)
			{
				EntityAI ent = alp_ReservedItems.Get(i);
				if (ent)
				{
					GetGame().ObjectDelete(ent);
					alp_ReservedItems.Remove(i);
				}
				if (!all) break;
			}
		}			
	}

	// --- Getters ---

	EntityAI GetEntity()
	{
		if (alp_PlayersEntityAI) return alp_PlayersEntityAI;
		if (!alp_EntityAI) alp_EntityAI = EntityAI.Cast(GetGame().CreateObject(alp_ClassName, "0 0 0", true, false, false));
		return alp_EntityAI;
	}

	string GetType() { return alp_ClassName; }
	string GetDisplayName() { return alp_DisplayName; }
	int GetCount() { return GetND().GetMS().GetTrader().GetCount(GetType(), GetND().GetMS().GetTrader().alp_NPC_ID); }
	int GetAvailableItem() { return (GetND().GetMS().GetTrader().IsBuyMenu()) ? GetCount() : alp_InInventory.Count(); }
	bool IsTradAble() { return (GetND().GetMS().GetTrader().IsBuyMenu()) ? alp_Config.CanBuy : alp_Config.CanSell; }
	bool HasReputation() { return true; } // Implementar lógica de Skill/Level se necessário
	float GetSales() { return 0; }
	float GetPlayerCoef(alpNPCtraderStock trader) { return trader.PricelistRatioHero; }
}