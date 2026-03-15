/**
 * @class   alpSpreadRumourAction
 * @brief   Ação de interação com NPC para acessar rumores e fofocas (Sistema de Informação)
 * Auditado em: 2024 - Foco em Performance de Rede e Integridade de Dados
 */
class alpSpreadRumourAction: ActionInteractBase
{
	void alpSpreadRumourAction()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(4);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "#npc_gossipmenu";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// 1. Previne abertura dupla no cliente
		if ( GetGame().IsClient() )
		{
			if ( GetGame().GetUIManager() && GetGame().GetUIManager().FindMenu(ALP_MENU_SPREADRUMOUR) )
				return false;		
		}
		
		// 2. Validação do NPC
		alpNPC ntarget = alpNPC.Cast( target.GetObject() );
		if ( ntarget && ntarget.IsAlive() )
		{
			// Verifica se o NPC tem um ID de estoque válido e se permite rumores
			if ( ntarget.alp_StockID > 0 && ntarget.CanSpreadRumoursMenu() )
			{
				// Verifica afinidade ou permissão de fala (Sistema de Facção/Reputação)
				return ntarget.CanSpeakWithMe(player);
			}
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );
		PlayerBase player = action_data.m_Player;

		if ( npc && player && player.GetRP() )
		{
			// 3. Vincula o NPC atual ao contexto de transação do jogador
			player.GetRP().GetCart().SetNPCid( npc.alp_StockID, npc.alp_IDmission );
			
			// 4. Sincronização seletiva (Otimizado)
			// Apenas registre se houver necessidade de estatísticas na UI de rumores
			player.GetSyncData().RegisterToStats( true );
			player.GetSyncData().ForceSync();

			// 5. Abre a interface de Rumores/Estoque
			// O parâmetro 'true' no final deve indicar que é um menu de rumores/diálogo
			GetND().GetMS().GetTrader().GiveMeStock( npc.alp_StockID, player, true );
		}		
	}
};