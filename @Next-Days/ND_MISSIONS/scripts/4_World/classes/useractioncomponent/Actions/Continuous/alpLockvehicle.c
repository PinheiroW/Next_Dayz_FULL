/**
 * alpLockvehicle.c
 * * AÇÃO CONTÍNUA (TRANCAR VEÍCULO COM CHAVE) - Módulo ND_MISSIONS
 * Permite trancar o carro externamente se o ID da chave coincidir com o do veículo.
 */

class alpLockVehicleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: Ação rápida de 0.5 segundos
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);
	}
};

class alpLockVehicle: ActionContinuousBase
{
	void alpLockVehicle()
	{
		m_CallbackClass = alpLockVehicleCB;
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
		return "#key_lock";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// SEGURANÇA: Validações primárias
		if ( !player || !item ) return false;

		alp_CarKey_Base key = alp_CarKey_Base.Cast(item);
		if ( !key ) return false;

		// LÓGICA MANTIDA: Jogador não pode estar dentro de um comando de veículo (dirigindo/passageiro)
		if ( player.GetCommand_Vehicle() ) return false;

		CarScript car;
		CarDoor carDoor; 
		
		// Verifica se o alvo é uma porta e se pertence a um veículo válido
		if ( Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()) )
		{
			// Só permite trancar se o veículo já estiver DESTRANCADO
			if ( car.GetInventory().IsInventoryUnlocked() )
			{
				// Verifica correspondência de ID ou permissão de Admin
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
		// LÓGICA MANTIDA: Executa o trancamento do veículo no lado do servidor
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) )
		{
			car.LockVehicleALP( true );
		}
	}
};