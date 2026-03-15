/**
 * alpNPC.c
 * * ENTIDADE DE NPC (TRADERS/MISSIONÁRIOS) - Módulo ND_MISSIONS
 * Define a lógica de interação, menus disponíveis e suporte a missões para NPCs.
 */

enum alpPAY_METHODS
{
	CASH,
	BANK,
	BANK_ONLY,
}

enum alpNPC_AVAILABLE_MENU
{
	ALL             = 0,
	BUY             = 1,
	SELL            = 2,
	BANK            = 4,
	MEDICAL         = 8,
	SPREADRUMOURS   = 16,
	BANK_ONLY       = 32,
	START_MISSION   = 64 // Funcionalidade de expansão
}

class alpNPC : PlayerBase
{
	// Propriedades de Missão e Diálogos
	string m_MissionWhileCountdowningON;
	string m_MissionWhileCountdowningOFf;	 	
	
	int alp_ParentMission;
	ref alpMissionAddNPC alp_MissionManage;
	int alp_MissionTriggerSetting;
	int alp_MissionManaged;
	int alp_MissionSwitchCooldown;

	int alp_MissionActionGameplayCountdownedON;
	int alp_MissionActionGameplayCountdownedOFF;
	
	string alp_CountdownMessageON;	
	string alp_CountdownMessageOFF;	
	
	string alp_MissionActionMessageON;	
	string alp_MissionActionMessageOFF;
	string alp_GiveItemWhenActivate;
	bool   alp_RewardWasGiven;
	
	// Propriedades de Comércio e Menus
	int alp_StockID = 0;
	ref array<int> alp_Menus;
	bool m_ActionsInitialize = false;

	void alpNPC()
	{
		// Define o NPC como objeto de missão para evitar deleção/limpeza automática
		SetMissionObject(true);
		alp_Menus = new array<int>;
	}

	/**
	 * Configura quais menus estarão disponíveis na interação com este NPC.
	 */
	void SetMenuALP(int menu)
	{
		alp_Menus.Insert(menu);
	}

	/**
	 * Retorna a lista de menus configurados para o NPC.
	 */
	array<int> GetMenusALP()
	{
		return alp_Menus;
	}

	/**
	 * Gerencia a injeção de ações de interação (Falar, Trocar, etc).
	 */
	override void GetActions(typename action_input_type, out array<ActionBase_Basic> actions)
	{
		// Mantém as ações base de humano (se houver)
		super.GetActions(action_input_type, actions);

		if (!m_ActionsInitialize)
		{
			m_ActionsInitialize = true;
			InitializeActions();
		}
	}
	
	// Métodos auxiliares de Identificação
	int GetStockID() { return alp_StockID; }
	void SetStockID(int id) { alp_StockID = id; }
}

/**
 * DEFINIÇÕES DE CLASSES VISUAIS (SUB-CLASSES)
 * Permite instanciar NPCs com diferentes faces e modelos.
 */
class alp_SurvivorM_Denis   : alpNPC {}
class alp_SurvivorM_Mirek   : alpNPC {}
class alp_SurvivorM_Boris   : alpNPC {}
class alp_SurvivorM_Cyril   : alpNPC {}
class alp_SurvivorM_Elias   : alpNPC {}
class alp_SurvivorM_Francis : alpNPC {}
class alp_SurvivorM_Guo     : alpNPC {}
class alp_SurvivorM_Hassan  : alpNPC {}
class alp_SurvivorM_Indar   : alpNPC {}
class alp_SurvivorM_Jose    : alpNPC {}