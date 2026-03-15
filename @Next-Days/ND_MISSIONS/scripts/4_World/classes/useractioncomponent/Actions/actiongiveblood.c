/**
 * actiongiveblood.c
 * * MODDED ACTIONS (TRANSFUSÃO DE SANGUE) - Módulo ND_MISSIONS
 * Adiciona a funcionalidade de descontaminação radioativa via transfusão sanguínea.
 */

modded class ActionGiveBloodSelf: ActionContinuousBase
{
	override void OnEndServer(ActionData action_data)
	{
		ActionGiveBloodData action_data_b = ActionGiveBloodData.Cast( action_data );		
		
		if ( action_data_b && action_data_b.m_Player )
		{
			PlayerBase player = action_data_b.m_Player;
			int radiationLevel = player.GetRP().GetRecievedRadiation();
			
			// Cura a doença de radiação se o estágio for inferior a 5 (L5)
			if ( radiationLevel < ALP_RADPOISON.L5 )
			{
				ModifiersManager mngr = player.GetModifiersManager();
				
				// Desativa os modificadores de doença progressiva do Next-Days
				if (mngr.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
					mngr.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
		
				if (mngr.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
					mngr.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
		
				if (mngr.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
					mngr.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
					
				if (mngr.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK4))
					mngr.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK4);
			}
		}

		super.OnEndServer(action_data);
	}
};

modded class ActionGiveBloodTarget: ActionContinuousBase
{
	override void OnEndServer(ActionData action_data)
	{
		ActionGiveBloodData action_data_b = ActionGiveBloodData.Cast( action_data );
		
		if ( action_data_b && action_data_b.m_Target )
		{
			PlayerBase player_target = PlayerBase.Cast(action_data_b.m_Target.GetObject());
			
			if ( player_target && player_target.IsAlive() )
			{
				int radiationLevelTarget = player_target.GetRP().GetRecievedRadiation();
				
				// Cura o alvo se a radiação dele for recuperável (< L5)
				if ( radiationLevelTarget < ALP_RADPOISON.L5 )
				{
					ModifiersManager mngrTarget = player_target.GetModifiersManager();
					
					if (mngrTarget.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
						mngrTarget.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
			
					if (mngrTarget.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
						mngrTarget.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
						
					if (mngrTarget.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
						mngrTarget.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);

					if (mngrTarget.IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK4))
						mngrTarget.DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK4);
				}
			}
		}

		super.OnEndServer(action_data);
	}
};