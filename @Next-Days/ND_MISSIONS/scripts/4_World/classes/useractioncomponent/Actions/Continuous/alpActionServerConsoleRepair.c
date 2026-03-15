/**
 * alpActionServerConsoleRepair.c
 * * AÇÃO CONTÍNUA CUSTOMIZADA (REPARAR CONSOLE DE SERVIDOR)
 * Permite o conserto de consoles usando ferramentas específicas.
 */

class alpActionServerConsoleRepairCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: Usa o tempo padrão de reparo de construções rápidas
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.BASEBUILDING_REPAIR_FAST );
	}
};

class alpActionServerConsoleRepair: ActionContinuousBase
{
	void alpActionServerConsoleRepair()
	{
		m_CallbackClass = alpActionServerConsoleRepairCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = true;
		m_LockTargetOnUse = false;
		m_Text = "#repair";
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined();
		m_ConditionTarget = new CCTObject(UAMaxDistances.REPAIR);
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// SEGURANÇA: Validação primária
		if (!player || !target) return false;

		// LÓGICA MANTIDA: Action not allowed if player has broken legs
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		alp_ServerConsole console;
		if ( Class.CastTo(console, target.GetObject()) )
		{
			// Verifica se o console precisa de reparo e ainda pode ser reparado
			if ( console.IsDamagedALP() && !console.IsRuinedALP() ) 
			{
				return true;
			}
		}

		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		if (!action_data || !action_data.m_Target) return;

		alp_ServerConsole console;
		if ( Class.CastTo(console, action_data.m_Target.GetObject()) )
		{
			// Executa o reparo no objeto
			console.RepairALP();
			
			// Aplica dano à ferramenta utilizada (Lógica de desgaste)
			if (action_data.m_MainItem)
			{
				action_data.m_MainItem.DecreaseHealth("", "", 5.0); // Dano moderado à ferramenta
			}

			// Evolui a perícia do jogador
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
		}
	}
};