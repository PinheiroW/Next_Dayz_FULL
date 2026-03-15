/**
 * alpCreateduplicate.c
 * * CONTINUOUS ACTION (KEY DUPLICATION / PAIRING) - Módulo ND_MISSIONS
 * Gerencia a gravação de IDs de veículos em chaves virgens.
 */

class alpCreateDuplicateCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo de 45 segundos para representar o processo de codificação eletrónica
		m_ActionData.m_ActionComponent = new CAContinuousTime(45);
	}
};

class alpCreateDuplicate: ActionContinuousBase
{
	void alpCreateDuplicate()
	{
		m_CallbackClass   = alpCreateDuplicateCB;
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody        = true;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone; // Validação manual via ActionCondition
		m_ConditionItem   = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#key_createduplicate";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !target || !item) return false;
		
		alp_CarKey key = alp_CarKey.Cast(item);
		CarScript car;
		
		// 1. Requisito: Item deve ser uma chave virgem (ID < 1) e o alvo um veículo
		if (key && key.GetAlpKeyID() < 1 && Class.CastTo(car, target.GetObject()))
		{
			// 2. Requisito: O veículo deve estar DESTRANCADO e possuir um ID válido
			if (car.GetInventory().IsInventoryUnlocked() && car.GetAlpCarID() != 0)
			{
				// 3. Segurança ND: Verifica restrição de Trade Zone
				auto vOptions = GetND().GetRP().GetVehicleOptions();
				if (vOptions && vOptions.DisableKeyDuplicationInTradeZone)
				{
					if (player.GetRP() && player.GetRP().IsInTradeZone())
						return false;
				}

				// 4. Validação de Proximidade: Jogador deve estar junto às portas
				int componentIndex = target.GetComponentIndex();
				array<string> selections = new array<string>();
				car.GetActionComponentNameList(componentIndex, selections);
				
				for (int i = 0; i < selections.Count(); i++)
				{
					// Verifica se o jogador consegue alcançar o assento a partir desta porta específica
					if (car.CanReachSeatFromDoors(selections[i], player.GetPosition(), 1.0))
					{
						return true;
					}						
				}
			}
		}
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Player || !action_data.m_Target) return;

		CarScript car;
		alp_CarKey key;
		
		// Executa a gravação do ID do veículo na memória da chave no servidor
		if (Class.CastTo(car, action_data.m_Target.GetObject()) && Class.CastTo(key, action_data.m_MainItem))
		{
			key.SetAlpKeyID(car.GetAlpCarID());
			// O estado da chave será persistido automaticamente pelo sistema de Hive do mod
		}
	}
};