/**
 * alpLockpicking.c
 * * CONTINUOUS ACTION (VEHICLE LOCKPICKING) - Módulo ND_MISSIONS
 * Permite o arrombamento de veículos com restrições de zona e desgaste de ferramenta.
 */

class alpLockpickingCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = 30.0; // Valor de segurança (fallback)
		
		// Consulta o tempo configurado nas opções de veículos do mod
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetVehicleOptions())
		{
			time = GetND().GetRP().GetVehicleOptions().TimeToForceOpen;
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}
};

class alpLockpicking: ActionContinuousBase
{
	void alpLockpicking()
	{
		m_CallbackClass   = alpLockpickingCB;
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody        = true;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone;
		m_ConditionItem   = new CCINonRuined; // Gazua não pode estar quebrada
	}
		
	override string GetText()
	{
		return "#unlock";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !target || !item) return false;
		
		CarScript car;
		CarDoor carDoor; 
		Lockpick lockpick = Lockpick.Cast(item);
		
		// Validação de existência dos componentes do mod
		if (!lockpick || !GetND() || !GetND().GetRP()) return false;
		
		auto vOptions = GetND().GetRP().GetVehicleOptions();
		if (!vOptions || !vOptions.EnableLocpicking) return false;

		// O alvo deve ser uma porta de um veículo trancado
		if (Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()))
		{
			if (car.GetInventory().IsInventoryLocked())
			{
				// Verificação de Zona Segura: Impede roubos em Trade Zones se configurado
				if (vOptions.DisableLocpickingInTradeZone && player.GetRP() && player.GetRP().IsInTradeZone())
				{
					return false;
				}
				
				return true;
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		CarScript car;
		Lockpick lockpick;
		
		if (Class.CastTo(car, action_data.m_Target.GetParent()) && Class.CastTo(lockpick, action_data.m_MainItem))
		{
			// Transita o estado do veículo para DESTRANCADO
			car.LockVehicleALP(false);	
			
			// Aplica penalidade de integridade à ferramenta utilizada
			float damage = 20.0; // Dano base padrão
			if (GetND() && GetND().GetRP() && GetND().GetRP().GetVehicleOptions())
			{
				damage = GetND().GetRP().GetVehicleOptions().DamageLockpick;
			}

			lockpick.DecreaseHealth("", "", damage);	
		}
	}
	
	override void OnFinishProgressClient(ActionData action_data)
	{
		CarScript car;
		if (Class.CastTo(car, action_data.m_Target.GetParent()))
		{
			// Feedback sonoro local para o jogador que realizou o arrombamento
			SEffectManager.PlaySoundOnObject("lockpick_success_SoundSet", car);
		}
	}
};