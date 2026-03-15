/**
 * alpActionSell.c
 * * AÇÃO DE INTERAÇÃO (VENDER PARA TRADER) - Módulo ND_MISSIONS
 * Gerencia a abertura do menu de venda e sincronização de estoque com NPCs.
 */

class alpActionSell: ActionInteractBase
{
	void alpActionSell()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan(4) define o raio de interação com o NPC (4 metros)
		m_ConditionTarget = new CCTMan(4);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#trader_selling";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// 1. Validação primária de estado do jogador
		if ( !player || player.IsRestrained() ) return false;

		// 2. Validação do NPC (Alvo)
		alpNPC ntarget;
		if ( Class.CastTo(ntarget, target.GetObject()) )
		{
			// Verifica se o NPC está vivo, erguido e configurado com um estoque
			if ( ntarget.IsAlive() && ntarget.IsErectedALP() && ntarget.alp_StockID > 0 )
			{
				// Verifica se este NPC específico permite vendas e se o jogador tem permissão de diálogo
				if ( ntarget.CanSellingALP() && ntarget.CanSpeakWithMe(player) )
				{
					return true;
				}
			}
		}
	
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC npc;
		if ( Class.CastTo(npc, action_data.m_Target.GetObject()) )
		{
			PlayerBase player = action_data.m_Player;
			
			// 1. Vincula o NPC ao carrinho de vendas do jogador
			if ( player.GetRP() && player.GetRP().GetCart() )
			{
				player.GetRP().GetCart().SetNPCid( npc.alp_StockID );
			}

			// 2. Sincroniza estatísticas e força atualização de dados de comércio
			if ( player.GetSyncData() )
			{
				player.GetSyncData().RegisterToStats( true );
				player.GetSyncData().ForceSync();
			}

			// 3. Solicita o estoque de venda ao módulo central do Trader
			if ( GetND() && GetND().GetMS() && GetND().GetMS().GetTrader() )
			{
				GetND().GetMS().GetTrader().GiveMeStock( npc.alp_StockID, player );
			}
		}	
	}

	override void OnEndClient( ActionData action_data )
	{
		// LÓGICA MANTIDA: Abre a interface de comércio no cliente após a execução
		if ( action_data.m_Player )
		{
			action_data.m_Player.OpenTraderMenu();
		}
	}
};