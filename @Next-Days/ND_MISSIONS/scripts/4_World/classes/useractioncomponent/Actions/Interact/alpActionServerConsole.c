/**
 * alpActionServerConsole.c
 * * AÇÃO DE INTERAÇÃO (TERMINAL DE MISSÃO) - Módulo ND_MISSIONS
 * Gerencia a ativação/desativação de triggers de missão via console físico.
 */

class alpActionServerConsoleCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: 3 segundos de interação para operar o terminal
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsole extends ActionInteractLoopBase
{
	string alp_Title;
	
	void alpActionServerConsole()
	{
		m_CallbackClass	= alpActionServerConsoleCB;
		// Utiliza a animação de manipulação de reféns/algemas (RESTRAINTARGET) para simular operação de teclado
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH; 
		m_HUDCursorIcon = CursorIcons.CloseHood;
		m_FullBody = true;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;
		
		// Verifica se o jogador está mirando no componente correto do modelo 3D (Botão/Painel)
		if ( target.GetComponentIndex() != 1 ) return false;

		alp_ServerConsole console;
		if ( Class.CastTo(console, target.GetObject()) )
		{
			int actionType = console.GetTypeOfManagedMissionAction();
			
			// Condições para interagir: Habilitado via script, Destrancado, Não arruinado e Não danificado
			if ( console.IsSetSettingALP(alpMISSIONTRIGGER.ENABLED) && console.IsUnlockedALP() )
			{
				if ( !console.IsRuinedALP() && !console.IsDamagedALP() && actionType != 0 )
				{
					// Lado do Cliente: Atualiza o texto dinâmico do HUD
					if ( GetGame().IsClient() )
					{
						SetTextALP( actionType, console.IsSwapedActionTitle() );
					}
					return true;
				}
			}
		}
		
		return false;
	}
	
	// Define se o texto exibido será "Ativar" ou "Desativar" baseado no estado da missão
	void SetTextALP(int action, bool swapedTitle) 
	{
		if ( action == alpMMACTION.ACTIVE || action == alpMMACTION.SET_TIME_TO_ACTIVE || action == alpMMACTION.CANCEL_DEACTIVE_TIME ) 
		{
			alp_Title = "#alp_action_console_deactivate";
		} 
		else 
		{
			alp_Title = "#alp_action_console_activate";			
		}
		
		// Inverte o título se o console estiver configurado com lógica reversa
		if ( !swapedTitle ) 
		{
			if ( alp_Title == "#alp_action_console_activate" ) 
				alp_Title = "#alp_action_console_deactivate";
			else 
				alp_Title = "#alp_action_console_activate";
		} 	
	}

	override void OnEndServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Target ) return;

		alp_ServerConsole console;
		if ( Class.CastTo(console, action_data.m_Target.GetObject()) )
		{
			// Executa a transição de estado da missão no servidor
			console.ManageMissionAction();
		}
		
		super.OnEndServer(action_data);
	}
};