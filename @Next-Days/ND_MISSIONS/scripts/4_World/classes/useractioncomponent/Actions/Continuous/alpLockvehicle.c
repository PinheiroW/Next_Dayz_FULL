/**
 * alpLockvehicle.c
 * * CONTINUOUS ACTION (LOCK VEHICLE WITH KEY) - Módulo ND_MISSIONS
 * Gerencia o trancamento externo de veículos baseado em IDs de chaves eletrónicas.
 */

class alpLockVehicleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo ultrarrápido de 0.5 segundos para representar o acionamento do alarme/tranca
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);
	}
};

class alpLockVehicle: ActionContinuousBase
{
	void alpLockVehicle()
	{
		m_CallbackClass   = alpLockVehicleCB;
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_INTERACT; // Animação de interação simples
		m_FullBody        = true;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone;
		m_ConditionItem   = new CCINonRuined; // Exige chave íntegra
	}
		
	override string GetText()
	{
		return "#key_lock";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Validação primária da entidade e do item (Chave)
		if (!player || !item) return false;

		alp_CarKey_Base key = alp_CarKey_Base.Cast(item);
		if (!key) return false;

		// Bloqueio de uso interno: Não permite trancar enquanto estiver dentro do veículo
		if (player.GetCommand_Vehicle()) return false;

		CarScript car;
		CarDoor carDoor; 
		
		// O alvo da interação deve ser a porta do veículo
		if (Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()))
		{
			// Condição: O veículo deve estar atualmente DESTRANCADO
			if (car.GetInventory().IsInventoryUnlocked())
			{
				// Verificação de Identidade: Chave compatível ou Master Key de Admin
				if (key.GetAlpKeyID() == car.GetAlpCarID() || key.IsAdminKey())
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		if (!action_data || !action_data.m_Target) return;

		CarScript car;
		// Executa a transição de estado para TRANCADO no lado do servidor (Sincronizado)
		if (Class.CastTo(car, action_data.m_Target.GetParent()))
		{
			car.LockVehicleALP(true);
		}
	}
};