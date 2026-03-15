/**
 * alpActionDecontaminate.c
 * * AÇÃO DE INTERAÇÃO (DESCONTAMINAÇÃO RADIOLÓGICA) - Módulo ND_MISSIONS
 * Permite ao jogador remover radiação acumulada utilizando chuveiros médicos.
 */

class alpActionDecontaminateCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: Utiliza o tempo padrão de lavar as mãos para o ciclo de banho
		m_ActionData.m_ActionComponent = new CAInteractLoop(UATimeSpent.WASH_HANDS);
	}
};

class alpActionDecontaminate extends ActionInteractLoopBase 
{
	void alpActionDecontaminate()
	{
		m_CallbackClass	= alpActionDecontaminateCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_WASHHANDSWELL; 
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#action_decontamination";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// OTIMIZAÇÃO: Verifica se o objeto alvo é o chuveiro médico via Cast (mais rápido que GetType)
		Land_Medical_Tent_Shower shower;
		if ( Class.CastTo(shower, target.GetObject()) )
		{
			return true;
		}
		
		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		Land_Medical_Tent_Shower shower;
		if ( Class.CastTo(shower, action_data.m_Target.GetObject()) )
		{
			// LÓGICA MANTIDA: Ativa os efeitos de partículas e som do chuveiro
			shower.StartShower();
		}
	}
	
	override void OnEndServer( ActionData action_data )
	{
		Land_Medical_Tent_Shower shower;
		if ( Class.CastTo(shower, action_data.m_Target.GetObject()) )
		{
			// SEGURANÇA: Garante que o chuveiro pare de gastar recursos ao encerrar a ação
			shower.StopShower();
			
			// LÓGICA MANTIDA: Aplica a cura de radiação ao finalizar o banho
			if ( action_data.m_Player && action_data.m_Player.GetRP() )
			{
				// Reduz a radiação em 20 unidades (ajustável via sistema de RP)
				action_data.m_Player.GetRP().AddRadiation(-20.0);
			}
		}
		
		super.OnEndServer(action_data);
	}
};