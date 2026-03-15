/**
 * alp_money.c
 * * ENTIDADE DE ECONOMIA (DINHEIRO E MOEDAS) - Módulo ND_MISSIONS
 * Gerencia valores nominais, formatação visual e propriedades físicas do dinheiro.
 */

class alp_Cash extends Inventory_Base
{
	/**
	 * Obtém o valor individual da nota/moeda definido no Config.cpp.
	 */
	int GetMoneyValue()
	{
		int value = 1;
		string subclass_path = "CfgVehicles " + GetType() + " nominalValue";
		
		if (GetGame().ConfigIsExisting(subclass_path))
			value = GetGame().ConfigGetInt(subclass_path);
		
		return value;
	}			

	/**
	 * Calcula o valor total do stack (quantidade * valor nominal).
	 */
	int GetMonyeSum()
	{	
		if (GetQuantity() > 0)
			return GetMoneyValue() * GetQuantity();
		
		return GetMoneyValue();
	}
	
	override string GetDisplayName()
	{
		return FormatNumber(GetMonyeSum()) + " " + super.GetDisplayName();
	}
	
	/**
	 * Formata números grandes para facilitar a leitura (ex: 10000 -> 10 000).
	 */
	string FormatNumber(float value)
	{		
		int v = value;		
		string text = v.ToString();
		string output = "";
		int len = text.Length();
		int count = 0;

		for (int i = len - 1; i >= 0; i--)
		{
			if (count > 0 && count % 3 == 0)
				output = text.Get(i) + " " + output;
			else 
				output = text.Get(i) + output;
			count++;
		}
		return output;
	}

	// --- Lógica de Combustível/Fogo ---

	override bool IsKindling() { return true; }
	override bool IsFuel() { return false; }
	override bool CanIgniteItem(EntityAI ignite_target = NULL) { return false; }
	override bool IsTargetFlammable(ItemBase target) { return false; }
	
	override bool CanBeIgnitedBy(EntityAI igniter = NULL)
	{
		// Só pode queimar se estiver fora de containers
		if (GetHierarchyParent()) return false;
		return true;
	}
	
	override void OnIgnitedThis(EntityAI fire_source)
	{
		Fireplace.IgniteEntityAsFireplace(this, fire_source);
	}

	override bool IsThisIgnitionSuccessful(EntityAI item_source = NULL)
	{
		return Fireplace.CanIgniteEntityAsFireplace(this);
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCreateIndoorFireplace);
		AddAction(ActionCreateIndoorOven);
		AddAction(ActionAttach);
		AddAction(ActionDetach);
	}	
}

// --- Definições de Classes Específicas ---

class alp_Money : alp_Cash {} // Base para notas de papel
class alp_Coin  : alp_Cash {} // Base para moedas metálicas

// Moedas
class alp_CoinRare1 extends alp_Coin {}
class alp_Coin1     extends alp_Coin {}
class alp_Coin2     extends alp_Coin {}
class alp_Coin5     extends alp_Coin {}

// Notas
class alp_Money10   extends alp_Money {}
class alp_Money20   extends alp_Money {}
class alp_Money50   extends alp_Money {}
class alp_Money100  extends alp_Money {}
class alp_Money200  extends alp_Money {}
class alp_Money500  extends alp_Money {}
class alp_Money1000 extends alp_Money {}