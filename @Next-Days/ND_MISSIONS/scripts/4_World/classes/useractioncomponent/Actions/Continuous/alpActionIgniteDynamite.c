/**
 * alpActionIgniteDynamite.c
 * * CONTINUOUS ACTION (IGNITE DYNAMITE) - Módulo ND_MISSIONS
 * Gerencia o acendimento de explosivos utilizando fontes de calor compatíveis.
 */

class alpActionIgniteDynamiteCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo fixo de 3 segundos para representar o tempo de queima inicial do pavio
		m_ActionData.m_ActionComponent = new CAContinuousTime(3); 
	}
}

class alpActionIgniteDynamite: ActionContinuousBase
{
	void alpActionIgniteDynamite()
	{
		m_CallbackClass   = alpActionIgniteDynamiteCB;
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_STARTFIRE; // Animação de acender fogueira
		m_FullBody        = true;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem   = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#ignite";
	}

	override bool CanBePerformedFromQuickbar()
	{
		return true;
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		if (!player || !target || !item) return false;

		ItemBase target_item = ItemBase.Cast(target.GetObject());
		
		// Verifica se a ferramenta na mão (item) é capaz de gerar fogo para o alvo
		if (target_item && item.CanIgniteItem(target_item))
		{
			alp_Dynamite_Base grenade;
			if (Class.CastTo(grenade, target_item))
			{
				// Condição lógica: Dinamite precisa estar em estado inicial (Pinned)
				if (grenade.IsPinned())
				{
					return true;	
				}
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		if (!action_data || !action_data.m_Target || !action_data.m_MainItem) return;

		ItemBase target_item = ItemBase.Cast(action_data.m_Target.GetObject());
		ItemBase item        = action_data.m_MainItem;

		if (target_item && item)
		{
			// Aciona a lógica de detonação e efeitos visuais no servidor
			target_item.OnIgniteItem(item);
			item.OnIgniteTarget(target_item);
			
			// Progresso de Habilidades do Sobrevivente
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
		}
	}
};