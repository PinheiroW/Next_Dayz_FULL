/**
 * actioneatmeat.c
 * * AÇÃO CONTÍNUA (COMER CARNE) - Módulo ND_MISSIONS
 * Impede consumo com máscaras e induz vômito automático caso a carne consumida esteja crua.
 */

modded class ActionEatMeat
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO: Validação primária da entidade
		if (!player) 
		{
			return false;
		}
		
		// OTIMIZAÇÃO E SEGURANÇA: Leitura protegida das opções globais do servidor
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPlayerOptions())
		{
			if (GetND().GetRP().GetPlayerOptions().MaskPreventConsume)
			{
				EntityAI mask = player.FindAttachmentBySlotName("Mask");
				
				// LÓGICA MANTIDA: Bloqueia a ação se a máscara não possuir abertura
				if (mask && !IsExceptionsALP(mask))
				{
					return false;
				}
			}
		}
		
		return super.ActionCondition(player, target, item);
	}	
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);

		// SEGURANÇA: Previne Null Pointer Exceptions caso a ação ou o item sejam destruídos no milissegundo final
		if (!action_data || !action_data.m_Player || !action_data.m_MainItem)
		{
			return;
		}

		Edible_Base food_item = Edible_Base.Cast(action_data.m_MainItem);
		
		// LÓGICA MANTIDA E OTIMIZADA: Verifica se o item é válido, é carne, e está crua
		if (food_item && food_item.IsMeat() && food_item.IsFoodRaw())
		{
			// SEGURANÇA: Garante que o gerenciador de sintomas está ativo antes de forçar o vômito
			if (action_data.m_Player.GetSymptomManager())
			{
				action_data.m_Player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
			}
		}
	}
}; // Adicionado ponto e vírgula obrigatório