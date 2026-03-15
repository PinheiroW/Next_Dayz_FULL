/**
 * alpTraderMission.c
 * * MISSION LOGIC: DYNAMIC TRADER - Módulo ND_MISSIONS
 * Gerencia zonas de comércio temporárias, proteção de jogadores (Safe Zone) e estoque de NPCs.
 */

class alpTraderMission extends alpMission
{
	// --- Configurações Iniciais ---

	override void OnInit()
	{
		// Mensagens específicas para início, fim e entrada em zonas de comércio
		alp_SendInfoStart   = ALPMSTYPE.MMTRADERSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMTRADEREND;
		alp_AlertInfoIn     = ALPMSTYPE.SMTRADERIN;
		alp_AlertInfoOut    = ALPMSTYPE.SMTRADEROUT;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}

	// --- Gerenciamento de Safe Zone ---

	/**
	 * Ativa as proteções de Safe Zone e Trading quando o jogador entra na área.
	 */
	override protected void OnEnter(Object obj)
	{
		super.OnEnter(obj);
		
		PlayerBase player;
		if (Class.CastTo(player, obj)) 
		{
			// Aplica GodMode aos jogadores se configurado no template
			bool state = !GetTemplate().godmodPlayers;
			player.GetRP().SetAllowedDamage(state);
			
			// Define que o jogador está em zona de troca (bloqueio de armas/ações agressivas)
			player.GetRP().SetInTradeZone(true);					
		}								
	};

	/**
	 * Remove as proteções ao sair da área (Gatilho Físico).
	 */
	override protected void OnLeave(Object obj)
	{
		super.OnLeave(obj);
		
		PlayerBase player;
		if (Class.CastTo(player, obj)) 
		{
			player.GetRP().SetAllowedDamage(true);
			player.GetRP().SetInTradeZone(false);						
		}		
	};

	/**
	 * Remove as proteções ao sair da área (Gatilho Lógico de Player).
	 */
	override void OnLeavePlayer(PlayerBase player) 	
	{
		super.OnLeavePlayer(player);
		
		if (player)
		{
			player.GetRP().SetAllowedDamage(true);
			player.GetRP().SetInTradeZone(false);	
		}			
	}

	// --- Verificações de Estado ---

	/**
	 * A missão falha se o NPC Trader for eliminado.
	 */
	override protected bool CheckFailedCondition(float timeslice) 
	{	
		if (!IsNPCAlive()) 
		{
			return true;
		}
		return false;
	}

	// --- Configuração do NPC ---

	override void SetUpNPC(Man npc, alpMissionAddNPC template)
	{
		super.SetUpNPC(npc, template);
		
		alpNPC trader;
		if (Class.CastTo(trader, npc))
		{		
			// Vincula o estoque e o ID da missão ao NPC para o menu de compra/venda
			trader.alp_StockID = template.StockID;
			trader.alp_IDmission = GetID();		
			
			SetUpMortality(trader);
		}
	}

	/**
	 * Define se o Trader é invulnerável baseado nas configurações do servidor.
	 */
	void SetUpMortality(alpNPC trader)
	{
		bool state = !GetTemplate().godmodTrader;
		trader.GetRP().SetAllowedDamage(state);		
		trader.SetSynchDirty();
	}
}