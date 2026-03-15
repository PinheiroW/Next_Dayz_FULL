/**
 * alpCreateduplicate.c
 * * AÇÃO CONTÍNUA (DUPLICAR/VINCULAR CHAVE AO VEÍCULO)
 * Permite transformar uma chave virgem na chave oficial do veículo alvo.
 */

class alpCreateDuplicateCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: 45 segundos para concluir a duplicação
		m_ActionData.m_ActionComponent = new CAContinuousTime(45);
	}
};

class alpCreateDuplicate: ActionContinuousBase
{
	void alpCreateDuplicate()
	{
		m_CallbackClass = alpCreateDuplicateCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNone; // Alvo será validado manualmente no ActionCondition
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#key_createduplicate";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !player || !target || !item ) return false;
		
		alp_CarKey key = alp_CarKey.Cast(item);
		CarScript car;
		
		// 1. Verifica se a chave em mãos é "virgem" (ID < 1)
		if ( key && key.GetAlpKeyID() < 1 && Class.CastTo(car, target.GetObject()) )
		{
			// 2. Verifica se o inventário do carro está destrancado e se o carro tem um ID válido
			if ( car.GetInventory().IsInventoryUnlocked() && car.GetAlpCarID() != 0 )
			{
				// 3. Checagem de Trade Zone (Segurança ND_MISSIONS)
				if ( GetND() && GetND().GetRP() && GetND().GetRP().GetVehicleOptions() )
				{
					if ( GetND().GetRP().GetVehicleOptions().DisableKeyDuplicationInTradeZone )
					{
						if ( player.GetRP() && player.GetRP().IsInTradeZone() )
							return false;
					}
				}

				// 4. Verificação de proximidade das portas (Lógica de modelo 3D)
				int componentIndex = target.GetComponentIndex();
				array<string> selections = new array<string>();
				car.GetActionComponentNameList( componentIndex, selections );
				
				for ( int i = 0; i < selections.Count(); i++ )
				{
					if ( car.CanReachSeatFromDoors(selections[i], player.GetPosition(), 1.0) )
					{
						return true;
					}						
				}
			}
		}
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Player || !action_data.m_Target ) return;

		CarScript car;
		alp_CarKey key;
		
		// LÓGICA MANTIDA: Vincula o ID do carro à chave e salva no banco de dados
		if ( Class.CastTo(car, action_data.m_Target.GetObject()) && Class.CastTo(key, action_data.m_MainItem) )
		{
			key.SetAlpKeyID( car.GetAlpCarID() );
			
			// Notifica o jogador (Opcional, mas recomendado para feedback)
			// NotificationSystem.SendNotificationToPlayerIdentity(action_data.m_Player.GetIdentity(), "Key", "Key successfully duplicated.", "set:dayz_gui image:backpack");
		}
	}
};