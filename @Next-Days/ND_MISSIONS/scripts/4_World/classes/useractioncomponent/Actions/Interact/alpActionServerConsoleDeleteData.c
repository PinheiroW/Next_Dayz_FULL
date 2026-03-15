/**
 * alpActionServerConsoleDeleteData.c
 * * USER INTERACTION (DATA SABOTAGE / DELETE) - Módulo ND_MISSIONS
 * Permite a eliminação de ficheiros e inteligência de terminais para fins de sabotagem.
 */

class alpActionServerConsoleDeleteDataCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo de 3 segundos: tempo necessário para a formatação/limpeza do disco virtual
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsoleDeleteData : ActionInteractLoopBase
{
	void alpActionServerConsoleDeleteData()
	{
		m_CallbackClass	= alpActionServerConsoleDeleteDataCB;
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET; // Animação de mãos no terminal
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
		return "#alp_action_console_delete";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;
		
		// Validação de foco: Focar no painel frontal do terminal (Index 1)
		if (target.GetComponentIndex() != 1) return false;

		alp_ServerConsole console;
		if (Class.CastTo(console, target.GetObject()))
		{
			// Requisitos para permitir a sabotagem:
			// 1. Hardware operacional e desbloqueado via cartão.
			// 2. O objeto deve estar configurado para conter dados.
			// 3. A missão deve permitir a deleção (sabotagem).
			// 4. Os dados ainda devem existir no sistema.
			if (console.IsUnlockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP())
			{
				if (console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_PANEL) && 
					 console.IsSetSettingALP(alpMISSIONTRIGGER.CAN_BE_DATA_DELETED) && 
					 !console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED))
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnEndServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return;

		alp_ServerConsole console;
		if (Class.CastTo(console, action_data.m_Target.GetObject()))
		{
			// Verificação final de segurança no servidor para evitar conflitos de rede
			if (console.IsSetSettingALP(alpMISSIONTRIGGER.CAN_BE_DATA_DELETED) && !console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED))
			{
				// Executa a deleção lógica e as consequências da missão
				console.DeleteDataALP();
			}
		}
		
		super.OnEndServer(action_data);
	}
};