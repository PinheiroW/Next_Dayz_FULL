/**
 * alpActionATM.c
 * * AÇÃO DE INTERAÇÃO (CAIXA ELETRÔNICO / ATM) - Módulo ND_MISSIONS
 * Gerencia o acesso a contas bancárias, validação de cartões e biometria.
 */

class alpActionATMCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		// LÓGICA MANTIDA: Loop de interação de 2 segundos para acessar o terminal
		m_ActionData.m_ActionComponent = new CAInteractLoop(2);
	}
};

class alpActionATM extends ActionInteractLoopBase 
{
	void alpActionATM()
	{
		m_CallbackClass	= alpActionATMCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE; 
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override string GetText()
	{
		return "#action_atm";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !player || !target.GetObject() ) return false;
		
		// 1. Verifica se o servidor permite acesso sem cartão (Biometria/GUID)
		if ( GetND() && GetND().GetMS() && GetND().GetMS().GetOptoinsTrader() )
		{
			if ( GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard )
			{
				return true;
			}
		}
		
		// 2. Verifica se o jogador está segurando um cartão de débito válido
		alp_Debitcard card;			
		if ( Class.CastTo( card, player.GetItemInHands() ) )
		{
			return true;
		}

		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Player ) return;

		auto traderMod = GetND().GetMS();
		if ( !traderMod ) return;

		// CASO A: Acesso por Biometria (Sem Cartão)
		if ( traderMod.GetOptoinsTrader().ATM_NotRequiresPaymentCard )
		{
			if ( action_data.m_Player.GetPlayerHive() )
			{
				int guid2 = action_data.m_Player.GetPlayerHive().GetPlayerID();
				traderMod.GetTrader().GiveMeAccount( guid2 , action_data.m_Player );	
			}
			return;
		}				
		
		// CASO B: Acesso via Cartão Físico
		alp_Debitcard card;			
		if ( Class.CastTo( card, action_data.m_Player.GetItemInHands() ) )
		{
			if ( action_data.m_Player.GetPlayerHive() )
			{
				// Se o cartão é novo (ID 0), vincula ao jogador atual
				if ( !card.alp_CARD_ID )
				{
					int guid = action_data.m_Player.GetPlayerHive().GetPlayerID();
					card.alp_CARD_ID = guid;
				}
				
				// Solicita os dados da conta ao banco de dados
				traderMod.GetTrader().GiveMeAccount( card.alp_CARD_ID, action_data.m_Player );
			}
		}
	}
	
	override void OnEndClient( ActionData action_data )
	{
		// Abre a interface visual (UI) para o jogador no lado do cliente
		if ( action_data && action_data.m_Player )
		{
			action_data.m_Player.OpenBankMenu();
		}
	}
};