/**
 * alpActionServerConsoleRepair.c
 * * CONTINUOUS ACTION (CONSOLE REPAIR) - Módulo ND_MISSIONS
 * Permite a restauração de terminais de missão danificados utilizando ferramentas.
 */

class alpActionServerConsoleRepairCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo de tempo baseado no reparo rápido de construções (Equilíbrio ND)
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.BASEBUILDING_REPAIR_FAST);
	}
};

class alpActionServerConsoleRepair: ActionContinuousBase
{
	void alpActionServerConsoleRepair()
	{
		m_CallbackClass   = alpActionServerConsoleRepairCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody        = true;
		m_LockTargetOnUse = false;
		m_Text            = "#repair";
	}

	override void CreateConditionComponents()  
	{
		// A ferramenta em mãos não pode estar arruinada para o reparo
		m_ConditionItem   = new CCINonRuined();
		m_ConditionTarget = new CCTObject(UAMaxDistances.REPAIR);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !target) return false;

		// Requisito de saúde física: Não é possível reparar com pernas partidas
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		alp_ServerConsole console;
		if (Class.CastTo(console, target.GetObject()))
		{
			// O console deve estar danificado, mas não totalmente destruído (Ruined)
			if (console.IsDamagedALP() && !console.IsRuinedALP()) 
			{
				return true;
			}
		}

		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return;

		alp_ServerConsole console;
		if (Class.CastTo(console, action_data.m_Target.GetObject()))
		{
			// Executa a lógica de reparação do hardware no servidor
			console.RepairALP();
			
			// Aplica desgaste à ferramenta de trabalho (Dano de 5.0 unidades)
			if (action_data.m_MainItem)
			{
				action_data.m_MainItem.DecreaseHealth("", "", 5.0);
			}

			// Progresso nas habilidades técnicas do jogador
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
		}
	}
};