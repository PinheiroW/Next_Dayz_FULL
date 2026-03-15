/**
 * alpUnlockvehicle.c
 * * AÇÃO CONTÍNUA (DESTRANCAR VEÍCULO COM CHAVE) - Módulo ND_MISSIONS
 * Permite destrancar o carro externamente se o ID da chave coincidir com o do veículo.
 */

class alpUnlockVehicleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: Ação rápida de 0.5 segundos para fluidez do gameplay
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);
	}
};

class alpUnlockVehicle: ActionContinuousBase
{
	void alpUnlockVehicle()
	{
		m_CallbackClass = alpUnlockVehicleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#key_unlock";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// SEGURANÇA: Validações básicas de existência
		if ( !player || !item || !target ) return false;

		alp_CarKey_Base key = alp_CarKey_Base.Cast(item);
		if ( !key ) return false;

		// OTIMIZAÇÃO: Jogador não pode estar operando o veículo (sentado/dirigindo)
		if ( player.GetCommand_Vehicle() ) return false;

		CarScript car;
		CarDoor carDoor; 
		
		// Verifica se o alvo é uma porta e se pertence a um CarScript
		if ( Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()) )
		{
			// Só permite a ação se o veículo estiver atualmente TRANCADO
			if ( !car.GetInventory().IsInventoryUnlocked() )
			{
				// LÓGICA MANTIDA: Verifica ID da chave ou se é Admin
				if ( key.GetAlpKeyID() == car.GetAlpCarID() || key.IsAdminKey() )
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		if ( !action_data || !action_data.m_Target ) return;

		CarScript car;
		// LÓGICA MANTIDA: Executa o destrancamento no servidor
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) )
		{
			car.LockVehicleALP( false );
		}
	}
};