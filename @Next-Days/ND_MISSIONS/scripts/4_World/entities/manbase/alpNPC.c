/**
 * alpNPC.c
 * * NPC ENTITY BASE (TRADERS/MISSIONARIES) - Módulo ND_MISSIONS
 * Define a lógica de interação, menus, suporte a missões e identidades para NPCs.
 */

/**
 * Métodos de Pagamento suportados pelo sistema económico.
 */
enum alpPAY_METHODS
{
	CASH,
	BANK,
	BANK_ONLY,
}

/**
 * Identificadores de menus e serviços disponíveis no NPC.
 */
enum alpNPC_AVAILABLE_MENU
{
	ALL             = 0,
	BUY             = 1,
	SELL            = 2,
	BANK            = 4,
	MEDICAL         = 8,
	SPREADRUMOURS   = 16,
	BANK_ONLY       = 32,
	START_MISSION   = 64 
}

class alpNPC : PlayerBase
{
	// --- Lógica de Transição e Diálogos de Missão ---
	protected string m_MissionWhileCountdowningON;
	protected string m_MissionWhileCountdowningOFf;	 	
	
	protected int alp_ParentMission;
	protected ref alpMissionAddNPC alp_MissionManage;
	protected int alp_MissionTriggerSetting;
	protected int alp_MissionManaged;
	protected int alp_MissionSwitchCooldown;

	protected int alp_MissionActionGameplayCountdownedON;
	protected int alp_MissionActionGameplayCountdownedOFF;
	
	protected string alp_CountdownMessageON;	
	protected string alp_CountdownMessageOFF;	
	
	protected string alp_MissionActionMessageON;	
	protected string alp_MissionActionMessageOFF;
	protected string alp_GiveItemWhenActivate;
	protected bool   alp_RewardWasGiven;
	
	// --- Lógica de Comércio e Configuração de Interface ---
	int alp_StockID = 0; // ID vinculado à tabela de preços/estoque no JSON
	protected ref array<int> alp_Menus;
	protected bool m_ActionsInitialize = false;

	void alpNPC()
	{
		// Registra o NPC como objeto estático de missão (Prevenção de Cleanup)
		SetMissionObject(true);
		alp_Menus = new array<int>;
	}

	/**
	 * Atribui um novo menu de serviço ao NPC.
	 */
	void SetMenuALP(int menu)
	{
		if (alp_Menus)
			alp_Menus.Insert(menu);
	}

	/**
	 * Recupera a lista de IDs de menus para renderização da UI.
	 */
	array<int> GetMenusALP()
	{
		return alp_Menus;
	}

	/**
	 * Inicializa o registro de ações de interação específicas de NPC.
	 */
	override void GetActions(typename action_input_type, out array<ActionBase_Basic> actions)
	{
		super.GetActions(action_input_type, actions);

		// Flag de segurança para garantir que a injeção de ações ocorra apenas uma vez
		if (!m_ActionsInitialize)
		{
			m_ActionsInitialize = true;
			// Aqui o motor de jogo vincula as interações Buy/Sell/Talk baseadas no contexto
			InitializeActions();
		}
	}
	
	// --- Getters e Setters de Identidade Comercial ---
	int GetStockID() { return alp_StockID; }
	void SetStockID(int id) { alp_StockID = id; }
}

/**
 * REGISTRO DE VARIANTES VISUAIS (CLASSES PARA SPAWN)
 * NPCs baseados nos modelos nativos de sobreviventes.
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