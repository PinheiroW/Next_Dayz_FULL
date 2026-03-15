/**
 * alpActionSell.c
 * * USER INTERACTION (TRADER SELL MENU) - Módulo ND_MISSIONS
 * Gerencia a abertura do menu de venda e sincronização de dados financeiros.
 */

class alpActionSell: ActionInteractBase
{
	void alpActionSell()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		// CCTMan define a distância máxima de interação com o NPC Trader
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem   = new CCINone;
	}

	override string GetText()
	{
		return "#trader_selling";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// 1. Bloqueio se o jogador estiver impedido (ex: algemado)
		if (!player || player.IsRestrained()) return false;

		// 2. Validação do NPC Alvo
		alpNPC ntarget;
		if (Class.CastTo(ntarget, target.GetObject()))
		{
			// O NPC deve estar funcional e possuir estoque vinculado
			if (ntarget.IsAlive() && ntarget.IsErectedALP() && ntarget.alp_StockID > 0)
			{
				// Verifica flags de permissão de venda e compatibilidade de diálogo
				if (ntarget.CanSellingALP() && ntarget.CanSpeakWithMe(player))
				{
					return true;
				}
			}
		}
	
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		alpNPC npc;
		if (Class.CastTo(npc, action_data.m_Target.GetObject()))
		{
			PlayerBase player = action_data.m_Player;
			
			// 1. Define o NPC alvo no carrinho para cálculo de preços de venda
			if (player.GetRP() && player.GetRP().GetCart())
			{
				player.GetRP().GetCart().SetNPCid(npc.alp_StockID);
			}

			// 2. Atualiza a rede para garantir dados de reputação/saldo íntegros
			if (player.GetSyncData())
			{
				player.GetSyncData().RegisterToStats(true);
				player.GetSyncData().ForceSync();
			}

			// 3. Solicita a sincronização de estoque para validar itens aceitos
			auto traderCore = GetND().GetMS().GetTrader();
			if (traderCore)
			{
				traderCore.GiveMeStock(npc.alp_StockID, player);
			}
		}	
	}

	override void OnEndClient(ActionData action_data)
	{
		// Aciona a interface visual de venda no lado do cliente
		if (action_data.m_Player)
		{
			action_data.m_Player.OpenTraderMenu();
		}
	}
};