class alpActionDisassemblePlotPoleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(10); // default value can be set in recipes
	}
};

class alpActionDisassemblePlotPole : ActionContinuousBase
{	
	void alpActionDisassemblePlotPole()	
	{
		m_CallbackClass = alpActionDisassemblePlotPoleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
	}

	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}	
	
	override string GetText()
	{
		return "#pp_context_menu_pack";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// CORREÇÃO 1: Prevenção contra Null Pointer Exception
		if (!target || !target.GetObject()) return false;
		
		alp_PlotPole plotpole = alp_PlotPole.Cast(target.GetObject());
		
		if ( plotpole )
		{
			// CORREÇÃO 2: Verificação de Permissão Front-end (Client-Side)
			// Impede que invasores vejam a opção de desmontar o Plot Pole inimigo
			if ( !player.IsAuthorized( plotpole ) )
			{
				return false;
			}
			
			// Melhoria recomendada: Você pode querer adicionar uma verificação aqui
			// para garantir que o Plot Pole esteja vazio antes de desmontar.
			// Ex: if (plotpole.GetInventory().GetCargo().GetItemCount() > 0) return false;
			
			return true;
		}
		
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		// CORREÇÃO 3: Blindagem de memória no Servidor
		if (!action_data.m_Target || !action_data.m_Target.GetObject()) return;

		alp_PlotPole plotpole = alp_PlotPole.Cast(action_data.m_Target.GetObject());
		
		if ( plotpole )
		{
			// CORREÇÃO 4: Exploit Resolvido. Validação rigorosa no Backend (Server-Side).
			// Garante que se um cheater injetar o RPC, o servidor vai rejeitar o desmanche.
			if ( action_data.m_Player && action_data.m_Player.IsAuthorized( plotpole ) )
			{
				plotpole.Disassemble();
			}
		}
	}
};