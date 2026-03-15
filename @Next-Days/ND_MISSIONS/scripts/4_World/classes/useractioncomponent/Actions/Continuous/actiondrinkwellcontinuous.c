/**
 * actiondrinkwellcontinuous.c
 * * AÇÃO CONTÍNUA (BEBER EM POÇOS) - Módulo ND_MISSIONS
 * Gerencia o consumo em poços de água urbanos, com verificação de máscaras, 
 * zonas radioativas e gestão de capacidade (esvaziamento) do poço.
 */

modded class ActionDrinkWellContinuous : ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO: Impede falha imediata caso a entidade seja nula
		if (!player) return false;
		
		// OTIMIZAÇÃO: Validação segura em cascata das opções de RP e Máscara
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPlayerOptions())
		{
			if (GetND().GetRP().GetPlayerOptions().MaskPreventConsume)
			{
				EntityAI mask = player.FindAttachmentBySlotName("Mask");
				
				// LÓGICA MANTIDA: Bloqueia o consumo se houver máscara restritiva
				if (mask && !IsExceptionsALP(mask))
				{
					return false;
				}
			}
		}
		
		Well well;
		
		// OTIMIZAÇÃO: Verifica primeiro se o alvo é válido antes de buscar configurações de gestão
		if (target && Class.CastTo(well, target.GetObject()) && GetGame().IsServer()) 
		{		
			if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
			{
				// LÓGICA MANTIDA: Se a gestão de poços estiver ligada e o poço estiver seco, oculta a ação
				if (GetND().GetResources().GetOptions().EnableWellManagement && !well.HasWaterALP())
				{
					return false;
				}
			}
		}			

		return super.ActionCondition(player, target, item);
	}
	
	override bool ActionConditionContinue(ActionData action_data)
	{
		// OTIMIZAÇÃO: Proteção para evitar travamentos de frame (Crash)
		if (!action_data || !action_data.m_Target) return false;

		Well well;
		
		if (Class.CastTo(well, action_data.m_Target.GetObject()) && GetGame().IsServer()) 
		{		
			if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
			{
				// LÓGICA MANTIDA: Interrompe a animação se o poço secar no meio do processo
				if (GetND().GetResources().GetOptions().EnableWellManagement && !well.HasWaterALP())
				{
					return false;	
				}
			}
		}
		
		return super.ActionConditionContinue(action_data);
	}	
	
		
	override void OnFinishProgressServer(ActionData action_data)
	{
		// SEGURANÇA: Previne Null Pointer Exceptions no processamento de conclusão
		if (!action_data || !action_data.m_Player) return;

		Param1<float> nacdata;
		if (action_data.m_ActionComponent)
		{
			nacdata = Param1<float>.Cast(action_data.m_ActionComponent.GetACData());
		}
		
		float amount = UAQuantityConsumed.DRINK;
		Well well;

		if (action_data.m_Target && Class.CastTo(well, action_data.m_Target.GetObject()))
		{					
			if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
			{
				if (GetND().GetResources().GetOptions().EnableWellManagement)
				{
					if (nacdata)
					{
						// Esvazia fisicamente o poço
						well.DrainWaterALP(amount);
					}
				}
			}
		}
				
		if (nacdata)
		{			
			// SEGURANÇA: Verifica o módulo RP antes de consultar níveis de radiação
			if (action_data.m_Player.GetRP())
			{
				if (action_data.m_Player.GetRP().IsRadiationHigh())
				{
					action_data.m_Player.Consume(NULL, amount, alpeConsumeType.ENVIRO_WELL_CONTAMINED);
				}
				else
				{
					action_data.m_Player.Consume(NULL, amount, EConsumeType.ENVIRO_WELL);
				}			
			}
			else
			{
				// Fallback: Caso RP não exista (ex: npc, erro momentâneo), consome água normal
				action_data.m_Player.Consume(NULL, amount, EConsumeType.ENVIRO_WELL);
			}
		}
		
		// LÓGICA MANTIDA: Penaliza o jogador se beber água de mãos nuas e sangrentas (Risco de infecção/cólera)
		if (action_data.m_Player.HasBloodyHands() && !action_data.m_Player.GetInventory().FindAttachment(InventorySlots.GLOVES))
		{
			action_data.m_Player.SetBloodyHandsPenalty();
		}
	}
};