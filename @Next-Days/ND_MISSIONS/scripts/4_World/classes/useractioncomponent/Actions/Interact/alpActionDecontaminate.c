/**
 * alpActionDecontaminate.c
 * * USER INTERACTION (RADIOLOGICAL DECONTAMINATION) - Módulo ND_MISSIONS
 * Permite ao jogador remover radiação acumulada utilizando infraestrutura médica.
 */

class alpActionDecontaminateCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// Mantém o ciclo de tempo baseado na ação de lavar as mãos (imersivo)
		m_ActionData.m_ActionComponent = new CAInteractLoop(UATimeSpent.WASH_HANDS);
	}
};

class alpActionDecontaminate extends ActionInteractLoopBase 
{
	void alpActionDecontaminate()
	{
		m_CallbackClass = alpActionDecontaminateCB;
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONFB_WASHHANDSWELL; 
		m_FullBody      = true;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem   = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#action_decontamination";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Verifica se o alvo é um chuveiro médico funcional
		Land_Medical_Tent_Shower shower;
		if (Class.CastTo(shower, target.GetObject()))
		{
			return true;
		}
		
		return false;
	}
	
	override void OnStartServer(ActionData action_data)
	{
		Land_Medical_Tent_Shower shower;
		if (Class.CastTo(shower, action_data.m_Target.GetObject()))
		{
			// Ativa os efeitos de partículas e áudio no servidor (replicado para os clientes)
			shower.StartShower();
		}
	}
	
	override void OnEndServer(ActionData action_data)
	{
		Land_Medical_Tent_Shower shower;
		if (Class.CastTo(shower, action_data.m_Target.GetObject()))
		{
			// Desliga os efeitos do objeto ao encerrar a interação
			shower.StopShower();
			
			// Aplica a redução da radiação no organismo do jogador
			if (action_data.m_Player && action_data.m_Player.GetRP())
			{
				// Redução direta: Valor base ND de 20 unidades por ciclo
				action_data.m_Player.GetRP().AddRadiation(-20.0);
			}
		}
		
		super.OnEndServer(action_data);
	}
};