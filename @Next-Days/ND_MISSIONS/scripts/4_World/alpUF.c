/**
 * alpUF.c
 * * USEFUL FUNCTIONS - Módulo ND_MISSIONS (4_World)
 * Biblioteca central de utilitários: Matemática, Colisão, Inventário e Veículos.
 */

class alpUF
{
	// --- Métodos Matemáticos ---

	/**
	 * Calcula a distância entre dois vetores. 
	 * Se uma das coordenadas Y for 0, o cálculo é feito em 2D (ignora altura).
	 */
	static float VectorDistance(vector v1, vector v2)
	{
		if (v1[1] == 0 || v2[1] == 0)
		{
			v1[1] = 0;
			v2[1] = 0;	
		}
		
		return vector.Distance(v1, v2);
	}

	// --- Detecção e Manipulação de Colisão ---

	/**
	 * Remove vegetação cortável (árvores/arbustos) em volta de um objeto para evitar clipping.
	 */
	static bool NoCollisionObjects(Object obj)
	{
		if (!obj) return false;

		vector position = obj.GetPosition();		
		vector minMax[2];
		obj.GetCollisionBox(minMax);			
		float radius = vector.Distance(minMax[0], minMax[1]);
		
		array<Object> nearest_objects = new array<Object>;
		array<CargoBase> proxy_cargos = new array<CargoBase>;
		
		GetGame().GetObjectsAtPosition(position, radius, nearest_objects, proxy_cargos); 
		
		for (int i = 0; i < nearest_objects.Count(); i++)
		{
			Object target = nearest_objects.Get(i);
			if (target && (target.IsBush() || (target.IsTree() && target.IsCuttable())))
			{
				GetGame().ObjectDelete(target);
			}
		}

		return true;
	}

	/**
	 * Verifica se o objeto está colidindo com outros elementos da geometria.
	 */
	static bool IsColliding(Object obj)
	{
		if (!obj) return false;

		vector minMax[2];
		obj.GetCollisionBox(minMax);			
		float radius = vector.Distance(minMax[0], minMax[1]);
		vector box = Vector(radius, radius, radius);
		
		array<Object> excluded_objects = new array<Object>;
		array<Object> nearby_objects = new array<Object>;
		excluded_objects.Insert(obj);
	
		return GetGame().IsBoxColliding(obj.GetPosition(), obj.GetOrientation(), box, excluded_objects, nearby_objects);
	}

	// --- Gerenciamento de Itens e Inventário ---
	
	static void RemoveAttachments(PlayerBase player)
	{
		if (!player) return;

		for (int i = 0; i < player.GetInventory().GetAttachmentSlotsCount(); ++i)
		{
			ItemBase item = ItemBase.Cast(player.GetInventory().FindAttachment(i));
			if (item) GetGame().ObjectDelete(item);
		}

		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		if (item_in_hands) GetGame().ObjectDelete(item_in_hands);
	}
	
	static void RemoveAllItems(ItemBase inventory)
	{
		if (!inventory) return;

		array<EntityAI> itemsArray = new array<EntityAI>;
		inventory.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			EntityAI item = itemsArray.Get(i);
			if (item && item != inventory) GetGame().ObjectDelete(item);
		}
	}

	static void RemoveAllItemsFromPlayer(PlayerBase player)
	{
		if (!player) return;

		array<EntityAI> itemsArray = new array<EntityAI>;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			EntityAI item = itemsArray.Get(i);
			if (item && !item.IsInherited(SurvivorBase)) 
			{
				GetGame().ObjectDelete(item);
			}
		}
	}

	// --- Funções de Comércio e Interface ---
	
	/**
	 * Obtém o nome amigável (Display Name) de uma classe consultando os diversos caminhos do Cfg.
	 */
	static string GetDisplayName(string className)
	{
		string name;
		TStringArray configs = {"CfgVehicles ", "CfgWeapons ", "CfgMagazines ", "CfgAmmo "};
		
		foreach (string path : configs)
		{
			GetGame().ConfigGetText(path + className + " displayName", name);
			if (name != "")
			{
				name.Replace("$UNT$", "");
				return name;
			}
		}
		return className;
	}

	/**
	 * Formata números com separadores de milhar (Espaço).
	 */
	static string NumberToString(float value, int k = 1000)
	{
		int v = value * k;		
		string text = v.ToString();
		string output = "";
		int len = text.Length();
		int s = 0;

		for (int i = len - 1; i >= 0; i--)
		{
			if (s > 0 && s % 3 == 0) output = text.Get(i) + " " + output;
			else output = text.Get(i) + output;
			s++;
		}
		return output;
	}

	// --- Logística de Veículos ---

	/**
	 * Abastece os fluidos vitais de um veículo (Combustível, Óleo e Radiador).
	 */
	static void FillFluidsToVehicle(Transport transport, bool fill = true, bool missionObject = false, float minFuel = 0, float maxFuel = 0)
	{
		CarScript car;
		if (Class.CastTo(car, transport))
		{
			if (fill)
			{
				float fuelCapacity = car.GetFluidCapacity(CarFluid.FUEL);
				float fuelAmount = fuelCapacity;

				if (maxFuel > 0)
				{
					fuelAmount = fuelCapacity * Math.RandomFloatInclusive(minFuel, maxFuel);
				}
				
				car.Fill(CarFluid.FUEL, fuelAmount);
				car.Fill(CarFluid.COOLANT, car.GetFluidCapacity(CarFluid.COOLANT));
				car.Fill(CarFluid.OIL, car.GetFluidCapacity(CarFluid.OIL));				
			}
			car.SetMissionObjectState(missionObject);
			return;		
		}

		HelicopterScript heli;
		if (Class.CastTo(heli, transport))
		{
			heli.SetMissionObjectState(missionObject);
		}		
	}
}