/**
 * alpRP.c
 * * REMOTE PLAYER COMPONENT - Módulo ND_MISSIONS (RP)
 * Hub central de estados, radiação, recompensas e comunicações do jogador.
 */

class alpRP 
{
	// --- Referências de Sistema ---
	PlayerBase          alp_Player;
	Transport           alp_Car; // Sincronização para alcance do Trader
	ref alpProtection   alp_Protection;
	ref alpTraderCart   alp_Cart;
	alp_geiger_counter  alp_GeigerCounter;

	// --- Estados de Radiação ---
	ref map<int, float> alp_Radiation; // ID da Missão -> Dose
	int                 alp_RadiationSickStage;
	protected bool      alp_HasContaminedItems;
	protected bool      alp_IsHighRadiation;

	// --- Estados de Jogo ---
	protected bool      alp_IsAllowedDamage = true;
	protected bool      alp_IsInTradeZone;
	protected bool      alp_IsRained = false;
	
	// --- Sistema de Procurado (Wanted/Debt) ---
	protected bool      alp_IsDebtor;
	protected bool      alp_EchoCooldown;
	int                 alp_RewardForKill[2]; // [ID Moeda, Quantidade]
	const int           alp_EchoPostpone = 5000;
	const int           alp_EchoCDTime   = 30000;

	// --- Inicialização ---

	void alpRP(PlayerBase player)
	{
		alp_Player     = player;
		alp_Protection = new alpProtection(alp_Player);
		alp_Cart       = new alpTraderCart(alp_Player);
		alp_Radiation  = new map<int, float>;
		
		Init();
	}

	void Init() {}

	// --- Sistema de Bounty (Procurado) ---

	/**
	 * Gera um alerta de posição se o jogador for um alvo e disparar sem supressor.
	 */
	void MakeEchoWatnedPerson(ItemBase suppressor, int from)
	{
		if (!suppressor || suppressor.GetHealth01("", "Health") < Math.RandomFloat01())
		{
			SetEchoCooldown(true);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SendEchoWantedPersonMessage, alp_EchoPostpone, false, from);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetEchoCooldown, alp_EchoCDTime, false, false);		
		}
	}

	void SetDebt(int currency, int debt)
	{
		int reward[2] = GetND().GetMS().GetOptoinsTrader().BankRewardForWantedPerson;
		float rate    = alpBANK.GetCurrencyRate(currency);
		int base      = reward[0] * rate;
		
		if (reward[1]) // Bônus percentual sobre a dívida
		{
			base += (reward[1] / 100.0) * debt;
		}
		
		alp_RewardForKill = {currency, base};
	}

	// --- Comunicação e Sensores ---

	/**
	 * Verifica equipamentos de navegação e rádio ativos.
	 */
	int HasWalkieTalkie()
	{	
		int radioType = 0;
		MapNavigationBehaviour nav = alp_Player.GetMapNavigationBehaviour();
		
		if (nav.GetNavigationType() & EMapNavigationType.GPS)     radioType |= alpRADIO.HAS_GPS;
		if (nav.GetNavigationType() & EMapNavigationType.COMPASS) radioType |= alpRADIO.HAS_COMPASS;		
		
		if (!GetND().GetMS().GetOptions().RequiresWalkieTalkie)
		{
			radioType |= alpRADIO.ALLOWED_BY_CONFIG_PERSONAL;
			if (!GetND().GetMS().GetOptions().BaseRadioUncoverAllMissions) return radioType;
		}
			
		array<EntityAI> itemsArray = new array<EntityAI>;
		float frequency = GetND().GetMS().GetOptions().RequiredTunedFrequency;
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		foreach (EntityAI item : itemsArray)
		{	
			TransmitterBase radio = TransmitterBase.Cast(item);
			if (radio && radio.IsWorking())
			{
				bool freqOk = (!frequency || frequency == radio.GetTunedFrequency());
				if (freqOk)
				{
					if (radio.IsBaseRadio()) { radioType |= alpRADIO.HAS_BASE_RADIO; break; }
					radioType |= alpRADIO.HAS_WALKIE_TALKIE;
				}
			}		
		}	
		return radioType;		
	}

	// --- Núcleo de Radiação ---

	/**
	 * Calcula a radiação atual baseada no ambiente e nos itens contaminados.
	 */
	float GetRadiation()
	{
		alp_IsHighRadiation = false;
		alp_HasContaminedItems = false;
		float radiation = 0;
		
		// Prioridade 1: Radiação emitida por itens no inventário
		if (GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems && alp_Player.HasContaminedItems())
		{
			float limit = GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems;
			radiation = limit + Math.RandomFloat(-0.05, -0.01) * limit;
			alp_HasContaminedItems = true;
		}
		
		// Prioridade 2: Radiação ambiental (pega o valor mais alto das missões próximas)
		if (alp_Radiation.Count() > 0)
		{
			array<float> values = alp_Radiation.GetValueArray();
			values.Sort(true); 
			
			if (values.Get(0) > radiation)
			{
				if (alp_HasContaminedItems) alp_IsHighRadiation = true;
				radiation = values.Get(0);
			}
		}
		return radiation;	
	}

	/**
	 * Varre missões ativas para aplicar radiação ambiental local.
	 */
	void SetLocalRadiation()
	{
		alp_Radiation.Clear();
		map<int, ref alpMission> missions = GetND().GetMS().GetMissions();
		
		for (int i = 0; i < missions.Count(); i++)
		{
			alpMission mission = missions.GetElement(i);		
			if (mission.IsActive() && mission.alp_Touched && (mission.alp_Type == ALP_MISSIONTYPEID.radiation || mission.alp_Type == ALP_MISSIONTYPEID.radiationMission))
			{
				float dist = alpUF.VectorDistance(mission.GetPosition(), alp_Player.GetPosition());	
				if (dist <= mission.alp_DamageRadius)
				{
					mission.SetPlayerInRadiation(alp_Player, dist);	
				}			
			}
		}
	}

	// --- Auxiliares de Estado ---

	void SetAllowedDamage(bool state)
	{
		if (GetGame().IsServer()) alp_Player.SetAllowDamage(state);
		alp_IsAllowedDamage = state;
	}

	void Decontamination(bool all = false)
	{
		array<EntityAI> itemsArray = new array<EntityAI>;
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);	
		foreach (EntityAI item : itemsArray)
		{
			if (item && item != alp_Player && (item.GetAgents() & alpeAgents.RADIATION))
			{
				bool canCleanFood = GetND().GetMS().GetOptionsRadiation().EnableFoodDecontamination;
				if (canCleanFood || (!canCleanFood && !item.IsFood()))
				{
					alp_Player.RemoveContaminedItem(item.GetID());
					item.RemoveAgent(alpeAgents.RADIATION);
					item.SetSynchDirty();
				}
			}			
		}				
	}
}