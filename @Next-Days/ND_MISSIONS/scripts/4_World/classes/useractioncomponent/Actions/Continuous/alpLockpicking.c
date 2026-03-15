/**
 * alpLockpicking.c
 * * AÇÃO CONTÍNUA (ARROMBAR VEÍCULO) - Módulo ND_MISSIONS
 * Permite o uso de lockpicks para abrir carros, com restrições de zona e dano à ferramenta.
 */

class alpLockpickingCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = 30.0; // Fallback de segurança (30s)
		
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
		m_CallbackClass = alpLockpickingCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#unlock";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !player || !target || !item ) return false;
		
		CarScript car;
		CarDoor carDoor; 
		Lockpick lockpick = Lockpick.Cast(item);
		
		// SEGURANÇA: Verifica se o lockpick e os módulos ND estão ativos
		if ( !lockpick || !GetND() || !GetND().GetRP() ) return false;
		
		auto vOptions = GetND().GetRP().GetVehicleOptions();
		if ( !vOptions || !vOptions.EnableLocpicking ) return false;

		// LÓGICA MANTIDA: Verifica se o alvo é uma porta de um carro e se o carro está trancado
		if ( Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()) )
		{
			if ( car.GetInventory().IsInventoryLocked() )
			{
				// Checagem de Trade Zone
				if ( vOptions.DisableLocpickingInTradeZone && player.GetRP() && player.GetRP().IsInTradeZone() )
				{
					return false;
				}
				
				return true;
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		CarScript car;
		Lockpick lockpick;
		
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) && Class.CastTo(lockpick, action_data.m_MainItem) )
		{
			// LÓGICA MANTIDA: Destranca o veículo e aplica dano ao lockpick
			car.LockVehicleALP( false );	
			
			float damage = 20.0; // Padrão
			if (GetND() && GetND().GetRP() && GetND().GetRP().GetVehicleOptions())
				damage = GetND().GetRP().GetVehicleOptions().DamageLockpick;

			lockpick.DecreaseHealth("", "", damage);	
		}
	}
	
	override void OnFinishProgressClient( ActionData action_data )
	{
		CarScript car;
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) )
		{
			// Executa efeito sonoro de sucesso no cliente
			SEffectManager.PlaySoundOnObject("lockpick_success_SoundSet", car);
		}
	}
};