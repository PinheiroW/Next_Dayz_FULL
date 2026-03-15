/**
 * alpActionBuy.c
 * * AÇÃO DE INTERAÇÃO (ABRIR TRADER) - Módulo ND_MISSIONS
 * Gerencia a abertura do menu de compra e sincronização de estoque com NPCs.
 */

class alpActionBuy: ActionInteractBase
{
	void alpActionBuy()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan(4) define o raio de interação com o NPC
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#trader_buing";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// 1. Validação primária de estado do jogador
		if ( !player || player.IsRestrained() ) return false;

		// 2. Validação do NPC (Alvo)
		alpNPC ntarget;
		if ( Class.CastTo(ntarget, target.GetObject()) )
		{
			// Verifica se o NPC está vivo, em posição de interação e possui um estoque válido
			if ( ntarget.IsAlive() && ntarget.IsErectedALP() && ntarget.alp_StockID > 0 )
			{
				// Verifica condições customizadas de fala e permissão de compra
				if ( ntarget.CanBuingALP() && CanSpeakWithMe(ntarget, player) )
				{
					return true;
				}
			}
		}
	
		return false;
	}

	// Lógica de expansão para sistemas de reputação ou facções
	bool CanSpeakWithMe(alpNPC npc, PlayerBase player)
	{
		if ( !npc || !player ) return false;
		return npc.CanSpeakWithMe(player);
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC npc;
		if ( Class.CastTo(npc, action_data.m_Target.GetObject()) )
		{
			PlayerBase player = action_data.m_Player;
			
			// 1. Vincula o NPC atual ao carrinho de compras do jogador
			if ( player.GetRP() && player.GetRP().GetCart() )
			{
				player.GetRP().GetCart().SetNPCid( npc.alp_StockID, npc.alp_IDmission );
			}

			// 2. Sincroniza dados e solicita o estoque ao módulo Trader
			if ( player.GetSyncData() )
			{
				player.GetSyncData().RegisterToStats( true );
				player.GetSyncData().ForceSync();
			}

			if ( GetND() && GetND().GetMS() && GetND().GetMS().GetTrader() )
			{
				GetND().GetMS().GetTrader().GiveMeStock( npc.alp_StockID, player );
			}
		}		
	}
};