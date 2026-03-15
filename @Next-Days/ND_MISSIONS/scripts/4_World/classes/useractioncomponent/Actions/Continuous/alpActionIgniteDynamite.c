/**
 * alpActionIgniteDynamite.c
 * * AÇÃO CONTÍNUA CUSTOMIZADA (ACENDER DINAMITE)
 * Permite usar fontes de fogo para iniciar a detonação de dinamites.
 */

class alpActionIgniteDynamiteCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: Tempo fixo de 3 segundos para ignição
		m_ActionData.m_ActionComponent = new CAContinuousTime( 3 ); 
	}
}

class alpActionIgniteDynamite: ActionContinuousBase
{
	void alpActionIgniteDynamite()
	{
		m_CallbackClass = alpActionIgniteDynamiteCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_STARTFIRE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#ignite";
	}

	override bool CanBePerformedFromQuickbar()
	{
		return true;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		// SEGURANÇA: Validação primária de existência
		if ( !player || !target || !item ) return false;

		ItemBase target_item = ItemBase.Cast( target.GetObject() );
		
		// LÓGICA MANTIDA: Verifica se o item na mão pode acender o alvo
		if ( target_item && item.CanIgniteItem( target_item ) )
		{
			alp_Dynamite_Base grenade;
			if ( Class.CastTo(grenade, target_item) )
			{
				// Só permite acender se a dinamite estiver "travada" (Pinned)
				if ( grenade.IsPinned() )
				{
					return true;	
				}
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		if ( !action_data || !action_data.m_Target || !action_data.m_MainItem ) return;

		ItemBase target_item = ItemBase.Cast( action_data.m_Target.GetObject() );
		ItemBase item = action_data.m_MainItem;

		if ( target_item && item )
		{
			// Dispara os eventos de ignição em ambos os itens
			target_item.OnIgniteItem( item );
			item.OnIgniteTarget( target_item );
			
			// Aplica bônus de SoftSkills ao jogador
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
}; // Ponto e vírgula obrigatório para fechar a classe