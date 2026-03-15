/**
 * alpActionServerConsoleDownloadData.c
 * * USER INTERACTION (DATA DOWNLOAD) - Módulo ND_MISSIONS
 * Permite a extração de inteligência e ficheiros de terminais em missões específicas.
 */

class alpActionServerConsoleDownloadDataCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo de 3 segundos para representar o tempo de transferência de ficheiros
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsoleDownloadData : ActionInteractLoopBase
{
	void alpActionServerConsoleDownloadData()
	{
		m_CallbackClass	= alpActionServerConsoleDownloadDataCB;
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET; // Animação de digitação
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
		return "#alp_action_console_download";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;
		
		// Validação de foco: O monitor/painel (Index 1) deve estar na mira
		if (target.GetComponentIndex() != 1) return false;

		alp_ServerConsole console;
		if (Class.CastTo(console, target.GetObject()))
		{
			// Condições para iniciar o download:
			// 1. Hardware operacional e desbloqueado.
			// 2. Configurado como um terminal que contém dados de missão.
			// 3. Os dados ainda devem estar presentes no disco (não deletados).
			if (console.IsUnlockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP())
			{
				if (console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_PANEL) && 
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
			// Validação final de integridade de dados antes de concluir a extração
			if (!console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED))
			{
				// Executa a lógica de recompensa/progresso de missão no servidor
				console.DownloadDataALP();
			}
		}
		
		super.OnEndServer(action_data);
	}
};