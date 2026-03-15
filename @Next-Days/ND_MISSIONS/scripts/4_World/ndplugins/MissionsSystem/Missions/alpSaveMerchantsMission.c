/**
 * alpSaveMerchantsMission.c
 * * MISSION LOGIC: SAVE MERCHANTS - Módulo ND_MISSIONS
 * Gerencia o resgate de NPCs, transição para modo Trader e proteção de alvos.
 */

class alpSaveMerchantsMission extends alpMission
{
	protected bool m_WasStartedSecondPhase;

	// --- Inicialização ---

	override void OnInit()
	{
		// Configuração de mensagens para resgate e trading
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMTRADERIN;
		alp_AlertInfoOut    = ALPMSTYPE.SMTRADEROUT;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;
		
		m_WasStartedSecondPhase = false;
	}

	// --- Gatilhos de Entrada ---

	override protected void OnEnter(Object obj)
	{
		// Remove o estado de espera para garantir processamento
		RemoveSetting(alpMISSION_SETTING.MISSION_IDLE);	
		
		// Se a área não estiver limpa, não processa mensagens de trader ainda
		if (!IsCleared()) return;
					
		if (obj.IsMan() && GetTemplate().alertInfo && GetTemplate().alertMessageIn != "")
		{
			GetND().GetNotf().SendMissionMessage(alp_AlertInfoIn, GetID(), GetTemplate().alertMessageIn, GetPosition(), PlayerBase.Cast(obj));	
		}
		
		// Registra o jogador no sistema de sincronização da missão
		PlayerBase player = PlayerBase.Cast(obj);
		if (player)
		{
			player.GetRP().SetMissionID(GetID());
		}
	}

	// --- Verificações de Estado ---

	override protected bool CheckFailedCondition(float timeslice) 
	{	
		// Falha: Se os NPCs que deveriam ser salvos morrerem
		if (!IsNPCAlive()) 
		{
			return true;
		}
		return false;
	}

	// --- Gerenciamento de NPCs e Mortalidade ---

	override void SetUpNPC(Man npc, alpMissionAddNPC template)
	{
		super.SetUpNPC(npc, template);
		
		alpNPC trader;
		if (Class.CastTo(trader, npc))
		{		
			trader.alp_StockID = template.StockID;
			trader.alp_IDmission = GetID();		
			
			// Se a missão já foi limpa (ex: re-spawn/re-load), aplica mortalidade imediatamente
			if (IsCleared())
			{
				SetUpMortality(trader);
			}
		}
	}

	protected void SetUpMortality(alpNPC trader)
	{
		// Define se o Trader pode ser morto após o resgate
		bool state = !GetTemplate().godmodTrader;
		trader.GetRP().SetAllowedDamage(state);		
		trader.SetSynchDirty();
	}

	// --- Lógica de Transição de Fase ---

	override protected void ActionClearedArea(float timeslice)
	{
		// Aciona apenas uma vez quando a área é limpa de inimigos
		if (!m_WasStartedSecondPhase) 
		{
			if (alp_NPC && alp_NPC.Count() > 0) 
			{
				for (int i = 0; i < alp_NPC.Count(); i++)
				{
					alpNPC npc = alpNPC.Cast(alp_NPC.Get(i).Get());
					if (npc)
					{
						SetUpMortality(npc);
						// Simula uma entrada forçada para atualizar a UI dos jogadores próximos
						OnEnter(npc); 
					}
				}
			}

			// Atualiza todos os jogadores presentes na zona para a nova fase
			foreach (alpMissionInsider ins : alp_Insiders)
			{
				if (ins.GetObject())
					OnEnter(ins.GetObject());
			}

			m_WasStartedSecondPhase = true;
		}
	}
}