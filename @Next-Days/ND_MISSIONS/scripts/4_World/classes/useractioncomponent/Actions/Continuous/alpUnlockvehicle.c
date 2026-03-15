/**
 * alpUnlockvehicle.c
 * * CONTINUOUS ACTION (UNLOCK VEHICLE WITH KEY) - Módulo ND_MISSIONS
 * Gerencia o destrancamento externo de veículos baseado em IDs de chaves eletrónicas.
 */

class alpUnlockVehicleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo ultrarrápido de 0.5 segundos para representar o destrancamento remoto/físico
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);
	}
};

class alpUnlockVehicle: ActionContinuousBase
{
	void alpUnlockVehicle()
	{
		m_CallbackClass   = alpUnlockVehicleCB;
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody        = true;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone;
		m_ConditionItem   = new CCINonRuined; // Chave deve estar funcional
	}
		
	override string GetText()
	{
		return "#key_unlock";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !item || !target) return false;

		alp_CarKey_Base key = alp_CarKey_Base.Cast(item);
		if (!key) return false;

		// Restrição de contexto: O jogador deve estar fora do veículo para usar a chave
		if (player.GetCommand_Vehicle()) return false;

		CarScript car;
		CarDoor carDoor; 
		
		// O alvo deve ser uma porta vinculada a um veículo funcional
		if (Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()))
		{
			// Condição Lógica: Só permite destrancar se o veículo estiver TRANCADO
			if (!car.GetInventory().IsInventoryUnlocked())
			{
				// Verificação de Segurança: Chave correta para este veículo ou Chave de Administrador
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
		// Executa a transição para estado DESTRANCADO no servidor (Sincronizado via RPC)
		if (Class.CastTo(car, action_data.m_Target.GetParent()))
		{
			car.LockVehicleALP(false);
		}
	}
};