/**
 * alpActionStartMission.c
 * * AÇÃO DE INTERAÇÃO (INICIAR MISSÃO COM NPC) - Módulo ND_MISSIONS
 * Gerencia o início de diálogos e triggers de missões através de NPCs.
 */

class alpActionStartMission: ActionInteractBase
{
	string alp_Title;
	
	void alpActionStartMission()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan define que o alvo deve ser um ser humano/NPC a uma distância padrão
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;

		alpNPC ntarget;
		if ( Class.CastTo(ntarget, target.GetObject()) )
		{
			// Verifica se o NPC está habilitado para missões, vivo, em pé e se o player tem permissão (ex: cooldown)
			int actionType = ntarget.GetTypeOfManagedMissionAction();
			
			if ( ntarget.IsSetSettingALP(alpMISSIONTRIGGER.ENABLED) && ntarget.IsAlive() && ntarget.IsErectedALP() )
			{
				if ( ntarget.CanSpeakWithMe(player) && actionType != 0 )
				{
					// Lado do Cliente: Define o texto do HUD dinamicamente
					if ( GetGame().IsClient() )
					{
						SetTextALP( actionType, ntarget.IsSwapedActionTitle() );
					}
					return true;
				}
			}
		}
		
		return false;
	}
	
	/**
	 * Define o texto baseado no estado da missão:
	 * action == 1: Primeiro contato ("Falar")
	 * action == 2: Contatos subsequentes ("Falar Novamente")
	 */
	void SetTextALP(int action, bool swapedTitle) 
	{
		// Lógica base
		if ( action == 1 ) 
			alp_Title = "#alp_action_npc_talk";
		else 
			alp_Title = "#alp_action_npc_talkagain";
		
		// Inverte o título se a configuração do NPC assim exigir
		if ( swapedTitle ) 
		{
			if ( alp_Title == "#alp_action_npc_talk" ) 
				alp_Title = "#alp_action_npc_talkagain";
			else 
				alp_Title = "#alp_action_npc_talk";
		}
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Target ) return;

		alpNPC ntarget;
		if ( Class.CastTo(ntarget, action_data.m_Target.GetObject()) )
		{
			// Dispara a lógica de missão no servidor (pode abrir menus, spawnar itens ou atualizar o DB)
			ntarget.ManageMissionAction();
		}
	}
};