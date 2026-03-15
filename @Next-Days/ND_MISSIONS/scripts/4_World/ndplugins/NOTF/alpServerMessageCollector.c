/**
 * alpServerMessageCollector.c
 * * MESSAGE SCHEDULER & COLLECTOR - Módulo ND_MISSIONS (NOTF)
 * Gerencia o agendamento, repetição e disparo de mensagens automáticas.
 */

class alpServerMessageCollector
{
	protected int alp_Index;
	protected ref map<int, ref alpServerMessageTemplate> alp_Messages;
	protected ref map<int, ref alpServerMessageTemplate> alp_MessagesRegular;
	protected ref map<int, ref alpServerMessageTemplate> alp_MessagesOnSpawn;
	protected ref map<int, ref alpServerMessageTemplate> alp_MessagesOnConnect;

	// --- Inicialização e Limpeza ---

	void alpServerMessageCollector()
	{
		alp_Messages          = new map<int, ref alpServerMessageTemplate>;
		alp_MessagesRegular   = new map<int, ref alpServerMessageTemplate>;
		alp_MessagesOnSpawn   = new map<int, ref alpServerMessageTemplate>;
		alp_MessagesOnConnect = new map<int, ref alpServerMessageTemplate>;
		
		alp_Index = 0;
	}
	
	void ~alpServerMessageCollector()
	{
		delete alp_Messages;
		delete alp_MessagesRegular;
		delete alp_MessagesOnSpawn;					
		delete alp_MessagesOnConnect;		
	}	

	// --- Gerenciamento de Mensagens ---

	alpServerMessageTemplate GetServerMessage(int id)
	{
		return alp_Messages.Get(id);			
	}
	
	/**
	 * Adiciona e categoriza a mensagem nos mapas correspondentes baseada no tempo de disparo.
	 */
	void AddMessage(alpServerMessageTemplate message)
	{
		alp_Messages.Set(alp_Index, message);
		
		int timeFlag = message.Time.Get(0);

		if (timeFlag == -2) // On Spawn
		{
			alp_MessagesOnSpawn.Set(alp_Index, message);
		}
		else if (timeFlag == -3) // On Connect
		{
			alp_MessagesOnConnect.Set(alp_Index, message);
		}
		else // Regular (Intervalo ou Horário Fixo)
		{
			alp_MessagesRegular.Set(alp_Index, message);	
		}
		
		alp_Index++;	
	} 

	// --- Lógica de Disparo (Server Side) ---

	/**
	 * Envia a mensagem via RPC e agenda a próxima repetição se necessário.
	 */
	void ShowServerMessage(int id, Man player = null)
	{
		if (!GetGame().IsServer()) return;

		// Envia para o cliente via RPC SM
		SendServerMessageToClient(id, player);
		
		alpServerMessageTemplate message = alp_Messages.Get(id);
		if (!message) return;

		int time;
		bool shouldLoop = (message.Loop > 0 || message.Loop < 0);

		if (shouldLoop)
		{
			if (message.Loop > 0) message.Loop--;
			
			time = message.LoopTime * 1000;
			// Re-agenda a exibição baseada no LoopTime
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ShowServerMessage, time, false, id, player);	
		}
		else if (message.Time.Get(0) >= 0)
		{
			// Cálculo para mensagens de horário fixo (reset de ciclo 24h)
			time = (24 * 60 * 60) - (message.LoopTime * message.LoopTime); // Lógica original mantida
		}
	}

	/**
	 * Comunicação RPC para o Plugin NOTF no cliente.
	 */
	void SendServerMessageToClient(int id, Man player = null)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetND().GetNotf().GetID());					
		rpc.Write(ALP_RPC_PLUGIN_NOTF.SM);
		rpc.Write(id);
		
		if (player)
			GetND().SendGameRPC(rpc, player);	
		else
			GetND().SendGameRPC(rpc, player, true, true, true);	
	}

	// --- Inicialização de Ciclos ---

	/**
	 * Inicia o monitoramento de mensagens regulares (horário fixo ou loop infinito).
	 */
	void StartRegularMessages()
	{
		int hourS, minuteS, secondS, timemessage, timecurrent;
		GetHourMinuteSecondUTC(hourS, minuteS, secondS);	
		
		timecurrent = hourS * 3600 + minuteS * 60 + secondS;
		
		for (int i = 0; i < alp_MessagesRegular.Count(); i++)
		{
			int key = alp_MessagesRegular.GetKey(i);
			alpServerMessageTemplate message = alp_MessagesRegular.GetElement(i);
			
			if (message.Time.Get(0) >= 0) // Horário específico HH:MM:SS
			{
				timemessage = message.Time.Get(0) * 3600 + message.Time.Get(1) * 60 + message.Time.Get(2);
				timemessage = timemessage - timecurrent;
				
				if (timemessage < 0) timemessage = 86400 + timemessage; // Agenda para o dia seguinte
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ShowServerMessage, timemessage * 1000, false, key);
			}
			else // Intervalo de repetição (Time -1)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ShowServerMessage, message.LoopTime * 1000, false, key);
			}																				
		}
	}

	void StartOnConnectMessages(Man player)
	{
		StartPlayersMessages(player, alp_MessagesOnConnect);
	}	

	void StartOnSpawnMessages(Man player)
	{
		StartPlayersMessages(player, alp_MessagesOnSpawn);
	}	

	/**
	 * Helper para iniciar sequências de mensagens individuais para um jogador.
	 */
	protected void StartPlayersMessages(Man player, map<int, ref alpServerMessageTemplate> messages)
	{
		for (int i = 0; i < messages.Count(); i++)
		{
			int key = messages.GetKey(i);
			alpServerMessageTemplate message = messages.GetElement(i);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ShowServerMessage, message.LoopTime * 1000, false, key, player);			
		}	
	}	
}