/**
 * alpSaveSurvivorMission.c
 * * MISSION LOGIC: SAVE SURVIVOR - Módulo ND_MISSIONS
 * Gerencia o resgate de civis/sobreviventes e as recompensas pós-combate.
 */

class alpSaveSurvivorMission extends alpMission
{
	protected bool m_WasStartedSecondPhase;

	// --- Inicialização ---

	override void OnInit()
	{
		// Configuração de mensagens padrão (Broadcast e Pessoal)
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut    = ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}

	// --- Verificações de Estado ---

	/**
	 * A missão falha se o sobrevivente for morto.
	 */
	override protected bool CheckFailedCondition(float timeslice) 
	{	
		if ( !IsNPCAlive() ) 
		{
			return true;
		}
		return false;
	}

	// --- Gerenciamento de NPCs ---

	override void SetUpNPC(Man npc, alpMissionAddNPC template)
	{
		super.SetUpNPC(npc, template);
		
		alpNPC survivor;
		if ( Class.CastTo( survivor, npc ) )
		{		
			survivor.alp_StockID = template.StockID;
			survivor.alp_IDmission = GetID();		
		}
	}

	/**
	 * Define a vulnerabilidade do sobrevivente após o resgate.
	 */
	void SetUpMortality(alpNPC survivor)
	{
		bool state = !GetTemplate().godmodTrader;
		survivor.GetRP().SetAllowedDamage( state );		
	}

	// --- Lógica de Conclusão de Fase ---

	/**
	 * Transiciona a missão para o estado de "Resgatado" quando os inimigos são eliminados.
	 */
	override protected void ActionClearedArea(float timeslice)
	{
		if ( !m_WasStartedSecondPhase ) 
		{
			// Configura a mortalidade/invulnerabilidade para todos os sobreviventes na zona
			if ( alp_NPC && alp_NPC.Count() > 0 ) 
			{
				for ( int i = 0; i < alp_NPC.Count(); i++ )
				{
					alpNPC npc = alpNPC.Cast( alp_NPC.Get(i).Get() );
					if ( npc )
					{
						SetUpMortality( npc );
					}
				}
			}

			m_WasStartedSecondPhase = true;
			
			// Nota: O SpawnLoot aqui geralmente representa a recompensa física deixada pelo sobrevivente
			SpawnLoot(true); 
		}
	}
}