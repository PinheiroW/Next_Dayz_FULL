/**
 * alpOptionsMS_templates_traderQuests.c
 * * DEFINIÇÃO DE ESTRUTURA PARA QUESTS DE TRADER - Módulo ND_MISSIONS
 * Gerencia o registro de missões ativas e as propriedades das quests (itens pedidos e recompensas).
 */

class alpRegisteredQuest
{
	int NPC;
	int Quest;
	int CurrencyID;
	float PosX;
	float PosY;

	void alpRegisteredQuest(int npc, int quest, vector pos, int currencyID)
	{
		NPC = npc;
		Quest = quest;
		PosX = pos[0];
		PosY = pos[2]; // Armazena apenas coordenadas X e Z para economia de dados
		CurrencyID = currencyID;
	}
	
	vector GetPosition()
	{
		return vector.ArrayToVector({PosX, 0, PosY}); // CORREÇÃO: Uso de helper nativo para consistência
	}
}

class alpTraderQuest
{
	ref array<int> AssociatedTraders = new array<int>;
	string AssociatedMission;
	// bool DespawnAssocitedMission = true;
	
	string StartMessage;
	string EndMessage;
	int RepeatStartMessageEvery;
	string MapTitle; // Mantido para compatibilidade de carregamento (Obs: Bring Me)
	
	float Chance;
	int Nominal;
	int LifeTime;
	int LastRun;
	int CoolDown;		
	bool HideWantedItems = true; // CORREÇÃO: Removido semicolon duplo

	string WantedItem;
	string WantedItemAllowedType;
	int WantedRequiredCount = 1;
	
	string RewardItem;
	int RewardGivenCount = 1;
	float RewardPrice = 1;
	float RewardReputation = 0;
	
	int RequiredLevel = 0;
	int StoreAt = 0;
}