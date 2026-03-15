/**
 * actiondecontamineself.c
 * * AÇÃO CONTÍNUA (AUTO-DESCONTAMINAÇÃO) - Módulo ND_MISSIONS
 * Permite ao jogador aplicar agentes descontaminantes em si mesmo para remover radiação ou toxinas.
 */

class ActionDecontamineSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: 5 segundos de aplicação contínua
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class ActionDecontamineBase: ActionContinuousBase
{
	// Aplica a redução da quantidade do item (Spray/Desinfetante)
	void Apply( ActionData action_data )
	{
		if ( action_data.m_MainItem )
		{
			ItemBase item = action_data.m_MainItem;
			float quantity = item.GetDisinfectQuantity(); 
			
			// Se o item não tem um valor definido, usa um padrão de 10 unidades
			if (quantity <= 0) quantity = 10.0;
			
			item.AddQuantity(-quantity);
		}
	}
}

class ActionDecontamineSelf: ActionDecontamineBase
{
	void ActionDecontamineSelf()
	{
		m_CallbackClass = ActionDecontamineSelfCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		// Animação de borrifar/pulverizar em corpo inteiro
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_SPRAYPLANT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "#action_decontaminate_self";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// Condição: O item deve ter quantidade líquida disponível
		if ( item && item.GetQuantity() <= 0 )
			return false;

		// Realismo: Só permite a ação se o jogador estiver de fato contaminado
		// (Verifica se o sistema do mod Next-Days detecta agentes nocivos no sangue)
		if ( player.GetSingleAgentCount(alp_Agents.RADIATION) > 0 || player.GetSingleAgentCount(alp_Agents.CHEMICAL) > 0 )
		{
			return super.ActionCondition(player, target, item);
		}

		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		if ( player )
		{
			// Chama a função Apply definida na classe base
			Apply(action_data);
			
			// Lógica de cura: Remove ou reduz drasticamente a contaminação
			// Nota: Os valores de remoção são tratados pelo gerenciador de modificadores do player
			player.RemoveAgent(alp_Agents.RADIATION);
			player.RemoveAgent(alp_Agents.CHEMICAL);
		}
	}
};