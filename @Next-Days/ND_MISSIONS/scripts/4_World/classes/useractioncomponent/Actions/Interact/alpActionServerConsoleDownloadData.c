/**
 * alpActionServerConsoleDownloadData.c
 * * AÇÃO DE INTERAÇÃO (BAIXAR DADOS DO CONSOLE) - Módulo ND_MISSIONS
 * Utilizada para extração de informações e inteligência em missões de espionagem.
 */

class alpActionServerConsoleDownloadDataCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: 3 segundos para completar a transferência de dados
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsoleDownloadData extends ActionInteractLoopBase
{
	void alpActionServerConsoleDownloadData()
	{
		m_CallbackClass	= alpActionServerConsoleDownloadDataCB;
		// Mantém a animação de interação de corpo inteiro (agachado)
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
		return "#alp_action_console_download";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;
		
		// O jogador deve estar olhando para o painel de interface (Componente 1)
		if ( target.GetComponentIndex() != 1 ) return false;

		alp_ServerConsole console;
		if ( Class.CastTo(console, target.GetObject()) )
		{
			// Regras para permitir o download:
			// 1. Console destrancado e funcional (não arruinado).
			// 2. Objeto configurado como Painel de Dados.
			// 3. Os dados NÃO podem ter sido deletados previamente por outro jogador.
			if ( console.IsUnlockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() )
			{
				if ( console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_PANEL) && 
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
			// Verifica novamente se os dados não foram deletados durante o progresso da ação
			if ( !console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED) )
			{
				// Executa a lógica de entrega de dados/recompensa
				console.DownloadDataALP();
			}
		}
		
		super.OnEndServer(action_data);
	}
};