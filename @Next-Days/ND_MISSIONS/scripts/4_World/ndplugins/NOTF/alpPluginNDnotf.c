/**
 * alpPluginNDnotf.c
 * * NOTIFICATION SYSTEM PLUGIN - Módulo ND_MISSIONS (NOTF)
 * Gerencia o fluxo de mensagens globais, pessoais, alertas de missões e recompensas.
 */

class alpPluginNDnotf extends alpPlugin
{
	ref alpOptionsNotf                       alp_OptionsNotf;
	ref array<ref alpServerMessageTemplate>  alp_ServerMessages;
	ref alpServerMessageCollector            alp_ServerMessagesCollector;
	ref alpMessagesLocationLabel             alp_LocationLabels;
	ref map<int, string>                     alp_CurrencyMapped;
	
	void ~alpPluginNDnotf()
	{
		delete alp_OptionsNotf;
		delete alp_ServerMessages;
		delete alp_ServerMessagesCollector;
		delete alp_LocationLabels;					
		delete alp_CurrencyMapped;	
	}	
	
	override void Init() 
	{
		// Inicializa labels de localização (Chernarus conforme auditoria anterior)
		alp_LocationLabels = new alpMessagesLocationLabel;
		
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{	
			// Gerenciamento de Configurações (JSON)
			if (!FileExist(ALP_ROOTFOLDER + ALP_NOTF))
			{ 
				alp_OptionsNotf = new alpOptionsNotf;
				JsonFileLoader<alpOptionsNotf>.JsonSaveFile(ALP_ROOTFOLDER + ALP_NOTF, alp_OptionsNotf);
			}
			else 
			{
				JsonFileLoader<alpOptionsNotf>.JsonLoadFile(ALP_ROOTFOLDER + ALP_NOTF, alp_OptionsNotf);
			}
				
			// Garante integridade do diretório de notificações
			if (!FileExist(ALP_NOTF_FOLDER)) MakeDirectory(ALP_NOTF_FOLDER);	
			
			// Carregamento de Mensagens Automáticas do Servidor
			JsonFileLoader<array<ref alpServerMessageTemplate>>.JsonLoadFile(ALP_NOTF_SERVERMESSAGES, alp_ServerMessages);	
			
			if (!alp_ServerMessages)
			{
				alp_ServerMessages = new array<ref alpServerMessageTemplate>;
				FillTemplateServerMessages(alp_ServerMessages);
				JsonFileLoader<array<ref alpServerMessageTemplate>>.JsonSaveFile(ALP_NOTF_SERVERMESSAGES, alp_ServerMessages);	
			}
			
			InitMessages(alp_ServerMessages);		
			
			// Inicia o ciclo de mensagens regulares
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(alp_ServerMessagesCollector.StartRegularMessages, 0);
		}	
		else
		{
			// Lógica Lado Cliente: Mapeamento de Moedas para Exibição
			alp_OptionsNotf = new alpOptionsNotf;	
			alp_CurrencyMapped = new map<int, string>;
			map<int, ref alpCurrency> currencies = alpBANK.GetCurencies().GetCurrencies();	
			
			if (currencies)
			{
				for (int c = 0; c < currencies.Count(); c++)
				{
					alpCurrency currency = currencies.GetElement(c);
					alp_CurrencyMapped.Set(c, currency.Name);
				}			
			}				
		}
	}

	// --- Processamento de RPC (Sincronização Server-Client) ---

	override void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{
		int rpc, type, npcid, questID, mID;
		string text;
		vector pos;
		
		if (!ctx.Read(rpc) || !ctx.Read(type)) return;
		
		switch (rpc)
		{
			case ALP_RPC_PLUGIN_NOTF.MESSAGE:
			{				
				if (GetHud() && ctx.Read(text)) GetHud().SendMessageALP(type, text, "0 0 0");
				break;
			}		
			case ALP_RPC_PLUGIN_NOTF.MESSAGE_POSITION:
			{
				if (GetHud() && ctx.Read(text) && ctx.Read(pos)) GetHud().SendMessageALP(type, text, pos);
				break;
			}			
			case ALP_RPC_PLUGIN_NOTF.MESSAGE_RAID_ALERT:
			{				
				if (GetHud() && ctx.Read(pos)) GetHud().SendMessageALP(type, "#pp_someone_is_trying_to_get_into_your_base", pos);
				break;
			}					
			case ALP_RPC_PLUGIN_NOTF.MOSTWANTED:
			{
				if (GetHud())												
				{
					int playerID, fromID, curID, reward;
					ctx.Read(text); ctx.Read(pos); ctx.Read(playerID); ctx.Read(fromID); ctx.Read(curID); ctx.Read(reward);
		
					string messageWanted = (reward) ? "#alp_wanted #pos (" + text + " - #alp_atm_reward: " + alpUF.NumberToString(reward, 1) + " " + alp_CurrencyMapped.GetElement(curID) + ")" : "#alp_wanted #pos (" + text + ")";
					
					AddToMostWanted(fromID, curID, reward, playerID, text, messageWanted, pos);				
					GetHud().SendMessageALP(type, messageWanted, pos);	
				}				
				break;
			}			
			case ALP_RPC_PLUGIN_NOTF.MISSION:
			{				
				if (GetHud())
				{	
					ctx.Read(mID); ctx.Read(text); ctx.Read(pos); 
					alpMission mission = (mID >= 0) ? GetND().GetMS().GetMission(mID) : null;	
						
					if (mID < 0 || (mission && GetND().IsMissionKnown(mID, mission.alp_MissionStarted, mission.GetTemplate().requiredLevel)))
					{
						GetHud().SendMessageALP(type, text, pos);
					}	
				}				
				break;
			}					
		}
	}

	// --- Métodos de Envio (Server Side) ---

	void SendMissionMessage(int type, int mID, string text, vector pos, PlayerBase player, bool toAll = false)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetID());
		rpc.Write(ALP_RPC_PLUGIN_NOTF.MISSION);
		rpc.Write(type); rpc.Write(mID); rpc.Write(text); rpc.Write(pos);	
		
		if (toAll) GetND().SendGameRPC(rpc, player, true, true, true);
		else GetND().SendGameRPC(rpc, player);
	}

	void SendRaidAlert(PlayerBase player, int type, vector pos)
	{
		ScriptRPC rpc = GetND().GetSyncRPC(GetID());
		rpc.Write(ALP_RPC_PLUGIN_NOTF.MESSAGE_RAID_ALERT);
		rpc.Write(type); rpc.Write(pos);
		GetND().SendGameRPC(rpc, player);
	}
}