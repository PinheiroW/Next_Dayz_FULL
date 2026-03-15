/**
 * @class   alpFatigueOptions
 * @brief   Gerencia os parâmetros de fadiga e bônus de consumíveis
 * Auditado em: 2024 - Otimização de busca e segurança de strings
 */

class alpFoodBonuses
{
	string Item;
	float  Energy;
	float  Water;
	float  Health;
	float  Blood;
	float  Shock;
	
	void alpFoodBonuses(string name, float e, float w, float h, float b, float s)
	{
		Item = name;
		Energy = e;
		Water = w;
		Health = h;
		Blood = b;
		Shock = s;
	}
}

class alpLiquidBonuses
{
	int   LiquidID;
	float Energy;
	float Water;
	float Health;
	float Blood;
	float Shock;
	
	void alpLiquidBonuses(int name, float e, float w, float h, float b, float s)
	{
		LiquidID = name;
		Energy = e;
		Water = w;
		Health = h;
		Blood = b;
		Shock = s;
	}
}

class alpFatigueOptions 
{
	int ConfigVersion = 1;

	float RegenerationBlood			= 6; 
	float RegenerationHealth		= 1.5; 
	float FatigueBasal				= 0.0025; 
	float FatigueWalk				= 0.005; 
	float FatigueJog				= 0.008; 
	float FatigueSprint				= 0.016; 
	float FatigueRadiationMultiplier		= 1.2;  
	float FatigueRadiationSickMultiplier	= 2;  
	float FatigueSickMultiplier		= 1.5;  
	float FatigueHeatMultiplier		= 2;  
	float Resting					= 2; 
	float RestingPenaltyHeat		= 0.5; 
	float RestingPenaltyShelter		= 0.5; 
	bool ClosedEyesWhileSleeping	= true;
	float EpinephrineEnergyBoost	= 10; 
	
	ref array<ref alpFoodBonuses> FoodBonuses;
	ref array<ref alpLiquidBonuses> LiquidBonuses;

	void alpFatigueOptions()
	{
		FoodBonuses = new array<ref alpFoodBonuses>;
		
		// Sugestão: Mantenha nomes de classes sempre em minúsculo na config para consistência
		FoodBonuses.Insert( new alpFoodBonuses( "apple", -0.01, 0.1, -0.1, 0, 0 ) );
		FoodBonuses.Insert( new alpFoodBonuses( "banana", -0.01, 0.1, -0.1, 0, 0 ) );
		FoodBonuses.Insert( new alpFoodBonuses( "orange", -0.01, 0.1, -0.1, 0, 0 ) );
		FoodBonuses.Insert( new alpFoodBonuses( "plum", -0.01, 0.1, -0.1, 0, 0 ) );
		FoodBonuses.Insert( new alpFoodBonuses( "sodacan_kvass", -0.01, 0.1, -0.1, 0, 0 ) );	
		
		LiquidBonuses = new array<ref alpLiquidBonuses>;
		
		LiquidBonuses.Insert( new alpLiquidBonuses( 2048, -0.05, 0.6, -0.6, -0.2, 0 ) ); // vodka
		LiquidBonuses.Insert( new alpLiquidBonuses( 4096, -0.01, 0.1, -0.1, 0, 0 ) );    // beer
	}	
	
	alpFoodBonuses GetFoodBonus(string name)
	{
		if (!FoodBonuses) return null;
		
		// Otimização: Cache do tamanho da array e normalização da string
		int count = FoodBonuses.Count();
		string searchName = name;
		searchName.ToLower();

		for (int i = 0; i < count; i++)
		{
			string itemInList = FoodBonuses.Get(i).Item;
			itemInList.ToLower();

			if (searchName == itemInList)
			{
				return FoodBonuses.Get(i);
			}
		}
		return null;
	}
	
	alpLiquidBonuses GetLiquidBonus(int liquidId)
	{
		if (!LiquidBonuses) return null;
		
		int count = LiquidBonuses.Count();
		for (int i = 0; i < count; i++)
		{
			if (liquidId == LiquidBonuses.Get(i).LiquidID)
			{
				return LiquidBonuses.Get(i);
			}
		}
		return null;
	}	
}