/**
 * alpActionStartMission.c
 * * USER INTERACTION (NPC MISSION START) - Módulo ND_MISSIONS
 * Gerencia a ativação de diálogos e gatilhos de missão via interação direta com NPCs.
 */

class alpActionStartMission: ActionInteractBase
{
	protected string alp_Title;
	
	void alpActionStartMission()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan: O alvo obrigatório deve ser um Humano/NPC dentro da distância padrão
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem   = new CCINone;
	}

	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;

		alpNPC ntarget;
		if (Class.CastTo(ntarget, target.GetObject()))
		{
			// Verifica se o sistema de missões do NPC está habilitado e operacional
			int actionType = ntarget.GetTypeOfManagedMissionAction();
			
			if (ntarget.IsSetSettingALP(alpMISSIONTRIGGER.ENABLED) && ntarget.IsAlive() && ntarget.IsErectedALP())
			{
				// Valida permissões sociais (reputação/facção/cooldown) e se há uma ação válida (actionType > 0)
				if (ntarget.CanSpeakWithMe(player) && actionType != 0)
				{
					// Lado do Cliente: Processa o rótulo dinâmico para o HUD
					if (GetGame().IsClient())
					{
						SetTextALP(actionType, ntarget.IsSwapedActionTitle());
					}
					return true;
				}
			}
		}
		
		return false;
	}
	
	/**
	 * Define o texto do HUD baseado no contexto da missão.
	 * @param action: 1 para Novo Diálogo, outros valores para Diálogo Recorrente.
	 */
	void SetTextALP(int action, bool swapedTitle) 
	{
		if (action == 1) 
			alp_Title = "#alp_action_npc_talk";
		else 
			alp_Title = "#alp_action_npc_talkagain";
		
		// Aplica inversão de título se configurado no script do NPC
		if (swapedTitle) 
		{
			if (alp_Title == "#alp_action_npc_talk") 
				alp_Title = "#alp_action_npc_talkagain";
			else 
				alp_Title = "#alp_action_npc_talk";
		}
	}

	override void OnExecuteServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return;

		alpNPC ntarget;
		if (Class.CastTo(ntarget, action_data.m_Target.GetObject()))
		{
			// Executa a transição lógica da missão no servidor
			ntarget.ManageMissionAction();
		}
	}
};