/**
 * cooking.c
 * * SISTEMA DE COCÇÃO MODIFICADO - Módulo ND_MISSIONS
 * Preserva o envenenamento radioativo após o preparo e gerencia a cocção em panelas/espetos.
 */

modded class Cooking
{
	// -------------------------------------------------------------------------
	// COOK COM EQUIPAMENTO (Panelas e Frigideiras)
	// -------------------------------------------------------------------------
	override int CookWithEquipment(ItemBase cooking_equipment, float cooking_time_coef = 1)
	{
		bool is_empty;
		
		if (cooking_equipment == null) return 0;
		
		Param2<bool, bool> stateFlags = new Param2<bool, bool>(false, false); 
		Param2<CookingMethodType, float> cookingMethodWithTime = GetCookingMethodWithTimeOverride(cooking_equipment);
		
		CargoBase cargo = cooking_equipment.GetInventory().GetCargo();
		if (cargo)
		{
			is_empty = (cargo.GetItemCount() == 0);
			
			for (int i = 0; i < cargo.GetItemCount(); i++)
			{
				ProcessItemToCook(ItemBase.Cast(cargo.GetItem(i)), cooking_equipment, cookingMethodWithTime, stateFlags);
			}
		}
		else
		{
			ProcessItemToCook(cooking_equipment, cooking_equipment, cookingMethodWithTime, stateFlags);
		}
		
		Bottle_Base bottle_base = Bottle_Base.Cast(cooking_equipment);
		if (bottle_base)
		{
			float cooking_equipment_temp = cooking_equipment.GetTemperature();
			bool is_water_boiling;
			
			if (cooking_equipment_temp >= LIQUID_BOILING_POINT)
			{
				// LÓGICA DE MOD MANTIDA: Água fervida mata cólera, mas NÃO remove a radiação.
				cooking_equipment.RemoveAllAgentsExcept(alpeAgents.RADIATION);
				
				if (cooking_equipment.GetQuantity() > 0)
				{
					is_water_boiling = true;
					cooking_equipment.AddQuantity(-LIQUID_VAPOR_QUANTITY);
				} // CORREÇÃO: Removido o ponto e vírgula perdido aqui
			}
			
			bottle_base.RefreshAudioVisualsOnClient(cookingMethodWithTime.param1, stateFlags.param1, is_empty, stateFlags.param2);
		}

		FryingPan frying_pan = FryingPan.Cast(cooking_equipment);
		if (frying_pan && !bottle_base)
		{
			frying_pan.RefreshAudioVisualsOnClient(cookingMethodWithTime.param1, stateFlags.param1, is_empty, stateFlags.param2);
		}
		
		return 1;
	}
	
	// -------------------------------------------------------------------------
	// ATUALIZAÇÃO DE ESTADO DO ITEM
	// -------------------------------------------------------------------------
	override protected int UpdateCookingState(Edible_Base item_to_cook, CookingMethodType cooking_method, ItemBase cooking_equipment, float cooking_time_coef)
	{
		float food_temperature = item_to_cook.GetTemperature();
		FoodStageType new_stage_type = item_to_cook.GetNextFoodStageType(cooking_method);

		float food_min_temp 	= 0;
		float food_time_to_cook = 0;
		float food_max_temp		= -1;
		
		if (item_to_cook.CanChangeToNewStage(cooking_method)) 
		{
			// OTIMIZAÇÃO: Eliminado o memory leak e validado de forma mais segura
			array<float> next_stage_cooking_properties = FoodStage.GetAllCookingPropertiesForStage(new_stage_type, null, item_to_cook.GetType());
			
			if (next_stage_cooking_properties)
			{
				food_min_temp = next_stage_cooking_properties.Get(eCookingPropertyIndices.MIN_TEMP);
				food_time_to_cook = next_stage_cooking_properties.Get(eCookingPropertyIndices.COOK_TIME);
				
				if (next_stage_cooking_properties.Count() > 2)
				{
					food_max_temp = next_stage_cooking_properties.Get(eCookingPropertyIndices.MAX_TEMP);
				}
			}
		}
		
		AddTemperatureToItem(item_to_cook, cooking_equipment, food_min_temp);
		
		if (food_min_temp > 0 && food_temperature >= food_min_temp)
		{
			float new_cooking_time = item_to_cook.GetCookingTime() + COOKING_FOOD_TIME_INC_VALUE * cooking_time_coef;
			item_to_cook.SetCookingTime(new_cooking_time);
			
			if (item_to_cook.GetCookingTime() >= food_time_to_cook)
			{
				if (food_max_temp >= 0)
				{
					if (food_temperature > food_max_temp && item_to_cook.GetFoodStageType() != FoodStageType.BURNED)
					{
						new_stage_type = FoodStageType.BURNED;
					}
				}
				
				item_to_cook.ChangeFoodStage(new_stage_type);
				// Dinâmica central do mod mantida rigorosamente
				item_to_cook.RemoveAllAgentsExcept(eAgents.BRAIN | alpeAgents.RADIATION);
				
				if (cooking_equipment)
				{
					if (cooking_method == CookingMethodType.BAKING)
					{
						ItemBase lard = GetItemTypeFromCargo(COOKING_INGREDIENT_LARD, cooking_equipment);
						if (lard)
						{
							float lardQuantity = lard.GetQuantity() - COOKING_LARD_DECREASE_COEF;
							lardQuantity = Math.Clamp(lardQuantity, 0, lard.GetQuantityMax());
							lard.SetQuantity(lardQuantity);
							
							DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_LARD);
						}
						else
						{
							// BUGFIX CRÍTICO: Agora há um 'else'. A comida não perde tamanho duplo se a banha foi usada.
							DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_NONE);
						}
					}
					else
					{
						// BUGFIX: Condição tratada com as chaves corretas para assados padrão
						DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_NONE);
					}
				}
				else
				{
					DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_NONE);
				}
				
				item_to_cook.SetCookingTime(0);
				return 1;
			}
		}
		
		return 0;
	}
	
	// -------------------------------------------------------------------------
	// ATUALIZAÇÃO DE ESTADO NO ESPETO (Stick)
	// -------------------------------------------------------------------------
	override protected int UpdateCookingStateOnStick(Edible_Base item_to_cook, float cook_time_inc)
	{
		float food_temperature = item_to_cook.GetTemperature();
		FoodStageType new_stage_type = item_to_cook.GetNextFoodStageType(CookingMethodType.BAKING);
		float food_min_temp = 0;
		float food_time_to_cook = 0;
		float food_max_temp = -1;
		
		// CORREÇÃO: Variáveis não-utilizadas "is_done" e "is_burned" foram removidas.

		if (item_to_cook.CanChangeToNewStage(CookingMethodType.BAKING))
		{
			// OTIMIZAÇÃO: Memory leak da matriz limpo.
			array<float> next_stage_cooking_properties = FoodStage.GetAllCookingPropertiesForStage(new_stage_type, null, item_to_cook.GetType());
			
			if (next_stage_cooking_properties)
			{
				food_min_temp = next_stage_cooking_properties.Get(eCookingPropertyIndices.MIN_TEMP);
				food_time_to_cook = next_stage_cooking_properties.Get(eCookingPropertyIndices.COOK_TIME);
				
				if (next_stage_cooking_properties.Count() > 2)
					food_max_temp = next_stage_cooking_properties.Get(eCookingPropertyIndices.MAX_TEMP);
			}
		}
		
		if (item_to_cook.GetInventory().IsAttachment())
		{
			item_to_cook.MakeSoundsOnClient(true);
			AddTemperatureToItem(item_to_cook, null, food_min_temp);
		}
		
		if (food_min_temp > 0 && food_temperature >= food_min_temp)
		{
			float new_cooking_time = item_to_cook.GetCookingTime() + cook_time_inc;
			item_to_cook.SetCookingTime(new_cooking_time);
			
			if (item_to_cook.GetCookingTime() >= food_time_to_cook)
			{
				if (food_max_temp >= 0)
				{
					if (food_temperature > food_max_temp && item_to_cook.GetFoodStageType() != FoodStageType.BURNED)
					{
						new_stage_type = FoodStageType.BURNED;
					}
				}
				
				item_to_cook.ChangeFoodStage(new_stage_type);
				item_to_cook.RemoveAllAgentsExcept(eAgents.BRAIN | alpeAgents.RADIATION);
				item_to_cook.SetCookingTime(0);
				return 1;
			}
		}
		
		return 0;
	}
	
	// -------------------------------------------------------------------------
	// DEFUMAÇÃO (Smoke)
	// -------------------------------------------------------------------------
	override void SmokeItem(Edible_Base item_to_cook, float cook_time_inc)
	{
		if (item_to_cook)
		{
			if ((item_to_cook.GetFoodStageType() == FoodStageType.RAW) || 
				(item_to_cook.GetFoodStageType() == FoodStageType.BAKED) || 
				(item_to_cook.GetFoodStageType() == FoodStageType.BOILED))
			{
				float new_cooking_time = item_to_cook.GetCookingTime() + cook_time_inc;
				item_to_cook.SetCookingTime(new_cooking_time);

				if (item_to_cook.GetCookingTime() >= FoodStage.GetCookingPropertyFromIndex(eCookingPropertyIndices.COOK_TIME, FoodStageType.DRIED, null, item_to_cook.GetType()))
				{
					item_to_cook.ChangeFoodStage(FoodStageType.DRIED);
					item_to_cook.RemoveAllAgentsExcept(eAgents.BRAIN | alpeAgents.RADIATION);
				}
			}
			else
			{
				item_to_cook.SetCookingTime(0);
			}
		}
	}
}