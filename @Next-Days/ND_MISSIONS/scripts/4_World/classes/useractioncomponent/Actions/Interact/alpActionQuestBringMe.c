/**
 * alpActionQuestBringMe.c
 * * AÇÃO DE INTERAÇÃO (ENTREGA DE QUEST) - Módulo ND_MISSIONS
 * Gerencia a entrega de itens, veículos e aeronaves para conclusão de missões.
 */

class alpActionQuestBringMe: ActionInteractBase
{
	string alp_WantedItemName;

	void alpActionQuestBringMe()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(4); // Alcance de 4 metros para o NPC
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#trader_give_items - " + alp_WantedItemName;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !player ) return false;

		alpNPC ntarget = alpNPC.Cast( target.GetObject() );
		if ( ntarget && ntarget.IsAlive() && ntarget.IsErectedALP() )
		{
			// Só processa a lógica de quest se o NPC tiver um ID de estoque/missão válido
			if ( ntarget.alp_StockID > 0 && ntarget.CanSpeakWithMe(player) )
			{
				array<ref alpTraderQuest> quests = GetND().GetQuestByNPC_ID( ntarget.alp_StockID );
				if ( quests )
				{
					// Procura por uma quest que o jogador possa entregar no momento
					foreach ( alpTraderQuest quest : quests )
					{
						if ( HasSomethingUse(player, quest) )
						{
							alp_WantedItemName = quest.Name; // Atualiza o nome para o HUD
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	// LÓGICA MANTIDA: Verifica se o jogador possui os requisitos da quest (Inventário ou Proximidade)
	bool HasSomethingUse(PlayerBase player, alpTraderQuest quest)
	{
		if ( !quest || !player ) return false;

		// Se for veículo/heli, verifica no raio de 10 metros
		if ( quest.IsVehicle )
		{
			array<Object> objects = new array<Object>;
			GetGame().GetObjectsAtPosition(player.GetPosition(), 10.0, objects, null);
			foreach ( Object obj : objects )
			{
				if ( obj.GetType() == quest.Type || GetGame().IsKindOf(obj.GetType(), quest.Parent) )
					return true;
			}
		}
		else // Verifica itens no inventário
		{
			return ( player.GetRP().GetInventoryCount(quest.Type, quest.Parent) >= quest.Count );
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC ntarget = alpNPC.Cast( action_data.m_Target.GetObject() );
		if ( !ntarget ) return;

		array<ref alpTraderQuest> quests = GetND().GetQuestByNPC_ID( ntarget.alp_StockID );
		if ( !quests ) return;

		foreach ( alpTraderQuest quest : quests )
		{
			if ( HasSomethingUse(action_data.m_Player, quest) )
			{
				// 1. Processa a remoção do item/veículo e obtém o valor de recompensa
				float rewardValue = TakeQuestItems(action_data.m_Player, quest);
				
				// 2. Finaliza a quest no sistema de RP do jogador
				action_data.m_Player.GetRP().FinishQuest(quest, rewardValue);
				break; 
			}
		}
	}

	float TakeQuestItems(PlayerBase player, alpTraderQuest quest)
	{
		float price = 0;
		string type = quest.Type;
		string parent = quest.Parent;
		int count = quest.Count;

		if ( quest.IsVehicle )
		{
			array<Object> objects = new array<Object>;
			GetGame().GetObjectsAtPosition(player.GetPosition(), 10.0, objects, null);
			foreach ( Object obj : objects )
			{
				CarScript car = CarScript.Cast(obj);
				HelicopterScript heli = HelicopterScript.Cast(obj);

				if ( (car || heli) && (obj.GetType() == type || GetGame().IsKindOf(obj.GetType(), parent)) )
				{
					// Obtém preço base definido no config do veículo para bônus de reputação/money
					if (car) price = car.GetDefaultPrice();
					else if (heli) price = heli.GetDefaultPrice();

					// Armazena no estoque global do Trader se configurado
					if ( quest.StoreAt )
						alpTraderCoreBase.AddCount(quest.StoreAt, type, 1);

					GetGame().ObjectDelete(obj);
					return price;
				}
			}
		}
		else
		{
			// LÓGICA MANTIDA: Remoção precisa de itens do inventário
			price = player.GetRP().RemoveInventoryItems(type, parent, count);
			if ( quest.StoreAt )
				alpTraderCoreBase.AddCount(quest.StoreAt, type, count);
		}
		return price;
	}
};