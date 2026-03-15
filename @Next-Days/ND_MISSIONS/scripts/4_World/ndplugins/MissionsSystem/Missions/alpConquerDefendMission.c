/**
 * alpConquerDefendMission.c
 * * MISSION LOGIC: CONQUER & DEFEND - Módulo ND_MISSIONS
 * Gerencia a progressão de tempo de ocupação e defesa de territórios.
 */

enum alpDEFENDAREA {
	NONE,
	STARTED,
	FINISHED
}

class alpConquerDefendMission extends alpMission
{
	protected int m_EventDefentArea;
	protected float m_TimeCounter;
	protected float m_MessageTime;
	protected int m_TimeRequired;

	// --- Inicialização ---

	override void OnInit()
	{
		// Configuração de strings de mensagens padrão
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut    = ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;
		
		m_EventDefentArea   = alpDEFENDAREA.NONE;
		m_TimeCounter       = 0;
		m_MessageTime       = 0;
		
		// Carrega o tempo necessário do template da missão
		if (GetTemplate())
			m_TimeRequired = GetTemplate().countdownDefentArea;
	}

	// --- Verificação de Conclusão ---

	override protected bool CheckSecuredCondition(float timeslice)
	{
		// A missão só é garantida se a área foi limpa de inimigos e o tempo de defesa expirou
		if ( (alp_Setting & alpMISSION_SETTING.MISSION_CLEARED) && m_EventDefentArea == alpDEFENDAREA.FINISHED ) 
		{
			return true;
		}
		return false;
	}

	// --- Lógica de Atualização (Tick) ---

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		// Se a missão foi limpa, inicia a contagem de defesa se houver jogadores na área
		if ( (alp_Setting & alpMISSION_SETTING.MISSION_CLEARED) && m_EventDefentArea != alpDEFENDAREA.FINISHED )
		{
			if ( alp_Insiders.Count() > 0 )
			{
				m_EventDefentArea = alpDEFENDAREA.STARTED;
				m_TimeCounter += timeslice;
				m_MessageTime += timeslice;

				// Envia atualização de tempo a cada 30 segundos
				if ( m_MessageTime >= 30 )
				{
					m_MessageTime = 0;
					SendDefendStatus(ALPMSTYPE.MMCONQUER_INFO);
				}

				// Verifica se o tempo de defesa foi atingido
				if ( m_TimeCounter >= m_TimeRequired )
				{
					m_EventDefentArea = alpDEFENDAREA.FINISHED;
					SendDefendStatus(ALPMSTYPE.MMCONQUER);
				}
			}
		}
	}

	// --- Auxiliares de Comunicação ---

	/**
	 * Envia o status do cronômetro para todos os jogadores dentro da zona de missão.
	 */
	protected void SendDefendStatus(int typemessage)
	{
		string m = GetTimeStamp();
		
		foreach (alpMissionInsider ins : alp_Insiders)
		{
			PlayerBase player;
			if ( ins && Class.CastTo( player, ins.GetObject() ) && player.IsAlive() ) 
			{
				// Envia a mensagem formatada (Tempo restante)
				GetND().GetNotf().SendMissionMessage(typemessage, GetID(), m, GetPosition(), player);
			}
		}
	}

	/**
	 * Converte os segundos restantes em uma string formatada (HHh MMm SSs).
	 */
	string GetTimeStamp()
	{
		int hour, min, sec;
		int remainingTime = m_TimeRequired - Math.Floor(m_TimeCounter);
		
		if (remainingTime < 0) remainingTime = 0;

		hour = remainingTime / 3600;
		min  = (remainingTime % 3600) / 60;
		sec  = remainingTime % 60;

		string messageTime = "";
		if ( hour > 0 ) messageTime += hour.ToString() + "h ";
		if ( min > 0 )  messageTime += min.ToString() + "m ";
		if ( sec >= 0 ) messageTime += sec.ToString() + "s";
		
		return messageTime;
	}
}