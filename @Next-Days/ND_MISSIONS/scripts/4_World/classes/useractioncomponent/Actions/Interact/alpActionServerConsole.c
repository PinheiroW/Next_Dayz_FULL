/**
 * alpActionServerConsole.c
 * * USER INTERACTION (MISSION CONTROL CONSOLE) - Módulo ND_MISSIONS
 * Gerencia a ativação física de triggers e eventos de missão global.
 */

class alpActionServerConsoleCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo de 3 segundos para representar o processamento de dados no terminal
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsole extends ActionInteractLoopBase
{
	protected string alp_Title;
	
	void alpActionServerConsole()
	{
		m_CallbackClass	= alpActionServerConsoleCB;
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET; // Animação de mãos no painel
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_CROUCH; 
		m_HUDCursorIcon = CursorIcons.CloseHood;
		m_FullBody      = true;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem   = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;
		
		// Validação de colisão: Exige interagir com o painel frontal (Index 1)
		if (target.GetComponentIndex() != 1) return false;

		alp_ServerConsole console;
		if (Class.CastTo(console, target.GetObject()))
		{
			int actionType = console.GetTypeOfManagedMissionAction();
			
			// Requisitos: Sistema ativo, destrancado e em condições operacionais (integridade física)
			if (console.IsSetSettingALP(alpMISSIONTRIGGER.ENABLED) && console.IsUnlockedALP())
			{
				if (!console.IsRuinedALP() && !console.IsDamagedALP() && actionType != 0)
				{
					// UI: Atualiza o label do HUD conforme o estado da missão
					if (GetGame().IsClient())
					{
						SetTextALP(actionType, console.IsSwapedActionTitle());
					}
					return true;
				}
			}
		}
		
		return false;
	}
	
	/**
	 * Define o rótulo visual da ação baseado no estado lógico do console.
	 */
	void SetTextALP(int action, bool swapedTitle) 
	{
		// Lógica base de ativação/desativação
		if (action == alpMMACTION.ACTIVE || action == alpMMACTION.SET_TIME_TO_ACTIVE || action == alpMMACTION.CANCEL_DEACTIVE_TIME) 
		{
			alp_Title = "#alp_action_console_deactivate";
		} 
		else 
		{
			alp_Title = "#alp_action_console_activate";			
		}
		
		// Aplica inversão de título se a missão exigir lógica reversa (Ex: Botão de Pânico)
		if (!swapedTitle) 
		{
			if (alp_Title == "#alp_action_console_activate") 
				alp_Title = "#alp_action_console_deactivate";
			else 
				alp_Title = "#alp_action_console_activate";
		} 	
	}

	override void OnEndServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return;

		alp_ServerConsole console;
		if (Class.CastTo(console, action_data.m_Target.GetObject()))
		{
			// Dispara a transição de estado da missão no motor de eventos do servidor
			console.ManageMissionAction();
		}
		
		super.OnEndServer(action_data);
	}
};