/**
 * alpActionATM.c
 * * USER INTERACTION (ATM/BANK) - Módulo ND_MISSIONS
 * Gerencia o acesso a contas bancárias, validação de cartões e biometria.
 */

class alpActionATMCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// Ciclo de interação de 2 segundos para representar o tempo de login no terminal
		m_ActionData.m_ActionComponent = new CAInteractLoop(2);
	}
};

class alpActionATM extends ActionInteractLoopBase 
{
	void alpActionATM()
	{
		m_CallbackClass = alpActionATMCB;
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE; 
		m_FullBody      = true;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem   = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#action_atm";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !target.GetObject()) return false;
		
		// 1. Verifica se o servidor permite acesso direto (Biometria por GUID)
		if (GetND() && GetND().GetMS() && GetND().GetMS().GetOptoinsTrader())
		{
			if (GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard)
			{
				return true;
			}
		}
		
		// 2. Caso exija cartão, verifica se o jogador está segurando um cartão de débito
		alp_Debitcard card;			
		if (Class.CastTo(card, player.GetItemInHands()))
		{
			return true;
		}

		return false;
	}
	
	override void OnStartServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Player) return;

		auto traderMod = GetND().GetMS();
		if (!traderMod) return;

		// LÓGICA DE AUTENTICAÇÃO
		if (traderMod.GetOptoinsTrader().ATM_NotRequiresPaymentCard)
		{
			// Acesso por GUID do Jogador
			if (action_data.m_Player.GetPlayerHive())
			{
				int playerID = action_data.m_Player.GetPlayerHive().GetPlayerID();
				traderMod.GetTrader().GiveMeAccount(playerID, action_data.m_Player);	
			}
		}				
		else
		{
			// Acesso por Cartão Físico
			alp_Debitcard card;			
			if (Class.CastTo(card, action_data.m_Player.GetItemInHands()))
			{
				if (action_data.m_Player.GetPlayerHive())
				{
					// Vincula cartão novo ao jogador se necessário
					if (!card.alp_CARD_ID)
					{
						card.alp_CARD_ID = action_data.m_Player.GetPlayerHive().GetPlayerID();
					}
					
					// Solicita os dados da conta vinculada ao cartão
					traderMod.GetTrader().GiveMeAccount(card.alp_CARD_ID, action_data.m_Player);
				}
			}
		}
	}
	
	override void OnEndClient(ActionData action_data)
	{
		// Abre a interface de usuário (UI) após a conclusão do loop
		if (action_data && action_data.m_Player)
		{
			action_data.m_Player.OpenBankMenu();
		}
	}
};