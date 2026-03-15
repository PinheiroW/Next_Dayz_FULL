/**
 * alpActionServerConsoleDeleteData.c
 * * AÇÃO DE INTERAÇÃO (DELETAR DADOS DO CONSOLE) - Módulo ND_MISSIONS
 * Utilizada em missões de sabotagem para apagar registros de dados do terminal.
 */

class alpActionServerConsoleDeleteDataCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: 3 segundos de retenção para deletar os dados
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsoleDeleteData extends ActionInteractLoopBase
{
	void alpActionServerConsoleDeleteData()
	{
		m_CallbackClass	= alpActionServerConsoleDeleteDataCB;
		// Animação de interação complexa em tela cheia (FullBody)
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
		return "#alp_action_console_delete";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;
		
		// Verifica se o jogador está interagindo com o painel frontal (índice 1)
		if ( target.GetComponentIndex() != 1 ) return false;

		alp_ServerConsole console;
		if ( Class.CastTo(console, target.GetObject()) )
		{
			// Conjunto de regras para permitir a deleção:
			// 1. Console destrancado.
			// 2. Não destruído (Ruined) ou danificado gravemente.
			// 3. Objeto configurado como Painel de Dados.
			// 4. Deleção permitida pela missão e dados ainda não deletados.
			if ( console.IsUnlockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() )
			{
				if ( console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_PANEL) && 
					 console.IsSetSettingALP(alpMISSIONTRIGGER.CAN_BE_DATA_DELETED) && 
					 !console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED) )
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnEndServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Target ) return;

		alp_ServerConsole console;
		if ( Class.CastTo(console, action_data.m_Target.GetObject()) )
		{
			// Segurança: Revalida se os dados ainda podem ser deletados antes de executar
			if ( console.IsSetSettingALP(alpMISSIONTRIGGER.CAN_BE_DATA_DELETED) && !console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED) )
			{
				console.DeleteDataALP();
			}
		}
		
		super.OnEndServer(action_data);
	}
};