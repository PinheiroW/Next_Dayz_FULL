/**
 * alpActionBuy.c
 * * USER INTERACTION (TRADER BUY MENU) - Módulo ND_MISSIONS
 * Gerencia a abertura do menu de compra e sincronização de estoque com NPCs.
 */

class alpActionBuy: ActionInteractBase
{
	void alpActionBuy()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan define a interação direta com o objeto da entidade (NPC)
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem   = new CCINone;
	}

	override string GetText()
	{
		return "#trader_buing";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// 1. Bloqueio se o jogador estiver impossibilitado
		if (!player || player.IsRestrained()) return false;

		// 2. Validação do NPC Alvo
		alpNPC ntarget;
		if (Class.CastTo(ntarget, target.GetObject()))
		{
			// O NPC precisa estar funcional para permitir o comércio
			if (ntarget.IsAlive() && ntarget.IsErectedALP() && ntarget.alp_StockID > 0)
			{
				// Verifica flags de permissão de compra e alinhamento de Roleplay
				if (ntarget.CanBuingALP() && CanSpeakWithMe(ntarget, player))
				{
					return true;
				}
			}
		}
	
		return false;
	}

	/**
	 * Verifica a compatibilidade social entre o jogador e o NPC.
	 */
	bool CanSpeakWithMe(alpNPC npc, PlayerBase player)
	{
		if (!npc || !player) return false;
		return npc.CanSpeakWithMe(player);
	}
	
	override void OnExecuteServer(ActionData action_data)
	{
		alpNPC npc;
		if (Class.CastTo(npc, action_data.m_Target.GetObject()))
		{
			PlayerBase player = action_data.m_Player;
			
			// 1. Configura o contexto do Trader no carrinho do jogador
			if (player.GetRP() && player.GetRP().GetCart())
			{
				player.GetRP().GetCart().SetNPCid(npc.alp_StockID, npc.alp_IDmission);
			}

			// 2. Prepara a rede: Ativa estatísticas de alta precisão e sincroniza
			if (player.GetSyncData())
			{
				player.GetSyncData().RegisterToStats(true);
				player.GetSyncData().ForceSync();
			}

			// 3. Solicita a lista de itens (Stock) ao núcleo do Trader
			auto traderCore = GetND().GetMS().GetTrader();
			if (traderCore)
			{
				traderCore.GiveMeStock(npc.alp_StockID, player);
			}
		}		
	}
};