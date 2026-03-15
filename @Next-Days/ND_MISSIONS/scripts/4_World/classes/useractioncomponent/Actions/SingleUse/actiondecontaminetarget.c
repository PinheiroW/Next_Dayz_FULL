/**
 * actiondecontaminetarget.c
 * * AÇÃO CONTÍNUA (DESCONTAMINAR OUTRO JOGADOR) - Módulo ND_MISSIONS
 * Permite que um jogador cure a contaminação de um aliado utilizando sprays descontaminantes.
 */

class ActionDecontamineTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: 5 segundos de aplicação no alvo
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class ActionDecontamineTarget: ActionDecontamineBase
{	
	void ActionDecontamineTarget()
	{
		m_CallbackClass = ActionDecontamineTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		// Animação de borrifar (FullBody) - O jogador fica vulnerável durante o processo
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_SPRAYPLANT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
		
	override string GetText()
	{
		return "#action_decontamination_target";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;

		PlayerBase target_player = PlayerBase.Cast(target.GetObject());
		
		// Condição: O item deve ter quantidade e o alvo deve ser um jogador vivo
		if ( target_player && target_player.IsAlive() && item && item.GetQuantity() > 0 )
		{
			// Realismo: Só permite descontaminar se o alvo tiver agentes nocivos detectados
			if ( target_player.GetSingleAgentCount(alp_Agents.RADIATION) > 0 || target_player.GetSingleAgentCount(alp_Agents.CHEMICAL) > 0 )
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		if ( !action_data.m_Target || !action_data.m_Target.GetObject() ) return;

		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		if ( target_player )
		{
			// Consome a durabilidade/quantidade do spray
			Apply(action_data);
			
			// Executa a descontaminação no alvo
			target_player.RemoveAgent(alp_Agents.RADIATION);
			target_player.RemoveAgent(alp_Agents.CHEMICAL);
			
			// Opcional: Notifica o executor e o alvo (via sistema de mensagens do mod)
			// GetND().GetLog().SendActionLog(action_data.m_Player, "Descontaminou " + target_player.GetIdentity().GetName());
		}
	}
};