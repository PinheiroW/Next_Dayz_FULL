/**
 * alpActionQuestBringMe.c
 * * USER INTERACTION (QUEST DELIVERY) - Módulo ND_MISSIONS
 * Gerencia a entrega física de itens e veículos para conclusão de objetivos de RP.
 */

class alpActionQuestBringMe: ActionInteractBase
{
	protected string alp_WantedItemName;

	void alpActionQuestBringMe()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan: Interação com NPC humano a curta distância
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem   = new CCINone;
	}

	override string GetText()
	{
		return "#trader_give_items - " + alp_WantedItemName;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player) return false;

		alpNPC ntarget = alpNPC.Cast(target.GetObject());
		if (ntarget && ntarget.IsAlive() && ntarget.IsErectedALP())
		{
			// Verifica se o NPC é um Quest Giver válido e se o diálogo está disponível
			if (ntarget.alp_StockID > 0 && ntarget.CanSpeakWithMe(player))
			{
				array<ref alpTraderQuest> quests = GetND().GetQuestByNPC_ID(ntarget.alp_StockID);
				if (quests)
				{
					// Itera sobre as quests vinculadas ao NPC para encontrar um requisito atendido
					foreach (alpTraderQuest quest : quests)
					{
						if (HasSomethingUse(player, quest))
						{
							alp_WantedItemName = quest.Name; // Popula o HUD com o nome da Quest
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	/**
	 * Verifica se o jogador possui o objeto solicitado (no inventário ou próximo a ele).
	 */
	bool HasSomethingUse(PlayerBase player, alpTraderQuest quest)
	{
		if (!quest || !player) return false;

		// Caso Veículo: Busca no mundo em um raio de 10m
		if (quest.IsVehicle)
		{
			array<Object> objects = new array<Object>;
			GetGame().GetObjectsAtPosition(player.GetPosition(), 10.0, objects, null);
			foreach (Object obj : objects)
			{
				if (obj.GetType() == quest.Type || GetGame().IsKindOf(obj.GetType(), quest.Parent))
					return true;
			}
		}
		else // Caso Item: Busca no inventário via API de RP
		{
			return (player.GetRP().GetInventoryCount(quest.Type, quest.Parent) >= quest.Count);
		}
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		alpNPC ntarget = alpNPC.Cast(action_data.m_Target.GetObject());
		if (!ntarget) return;

		array<ref alpTraderQuest> quests = GetND().GetQuestByNPC_ID(ntarget.alp_StockID);
		if (!quests) return;

		foreach (alpTraderQuest quest : quests)
		{
			if (HasSomethingUse(action_data.m_Player, quest))
			{
				// 1. Remove fisicamente o item/veículo e calcula o valor da entrega
				float rewardValue = TakeQuestItems(action_data.m_Player, quest);
				
				// 2. Finaliza a missão e aplica recompensas (XP/Dinheiro/Reputação)
				action_data.m_Player.GetRP().FinishQuest(quest, rewardValue);
				break; 
			}
		}
	}

	/**
	 * Executa a remoção do bem entregue e atualiza o estoque global do Trader.
	 */
	float TakeQuestItems(PlayerBase player, alpTraderQuest quest)
	{
		float price = 0;
		string type = quest.Type;
		string parent = quest.Parent;
		int count = quest.Count;

		if (quest.IsVehicle)
		{
			array<Object> objects = new array<Object>;
			GetGame().GetObjectsAtPosition(player.GetPosition(), 10.0, objects, null);
			foreach (Object obj : objects)
			{
				CarScript car = CarScript.Cast(obj);
				HelicopterScript heli = HelicopterScript.Cast(obj);

				if ((car || heli) && (obj.GetType() == type || GetGame().IsKindOf(obj.GetType(), parent)))
				{
					// Captura o valor de mercado para recompensas proporcionais
					if (car) price = car.GetDefaultPrice();
					else if (heli) price = heli.GetDefaultPrice();

					// Integração com o Estoque do Trader (NPC armazena o que o player entrega)
					if (quest.StoreAt)
						alpTraderCoreBase.AddCount(quest.StoreAt, type, 1);

					GetGame().ObjectDelete(obj);
					return price;
				}
			}
		}
		else
		{
			// Processa a remoção de múltiplos itens do inventário
			price = player.GetRP().RemoveInventoryItems(type, parent, count);
			if (quest.StoreAt)
				alpTraderCoreBase.AddCount(quest.StoreAt, type, count);
		}
		return price;
	}
};