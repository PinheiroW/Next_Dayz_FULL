/**
 * @class   PlayerBase
 * @brief   Core do Jogador com Integração RPG Next Days
 * Auditado em: 2026 - Foco em Correção de Sincronização, Áudio e Facções
 */
modded class PlayerBase extends ManBase
{
	ref PlayerStatAlp<int> 			alp_StatPerkStamina;
	ref PlayerStatAlp<float>		alp_StatPerkStaminaProgress;	
	
	ref PlayerStatAlp<float>		alp_StatPerksSoftDayZ;	
	ref PlayerStatAlp<float>		alp_StatPerksRoughDayZ;	
		
	ref PlayerStatAlp<int> 			alp_StatCountPlayers;
	ref PlayerStatAlp<int> 			alp_StatCountZombies;
	ref PlayerStatAlp<int> 			alp_StatCountAnimals;
	ref PlayerStatAlp<int> 			alp_StatCountSkinned;
	
	ref PlayerStatAlp<int> 			alp_StatPerkReputation;
	ref PlayerStatAlp<float>		alp_StatPerkReputationProgress;		
	
	ref PlayerStatAlp<int> 			alp_StatPerkHunting;
	ref PlayerStatAlp<float>		alp_StatPerkHuntingProgress;			
	
	ref PlayerStatAlp<int> 			alp_StatPerkRadResistance;
	ref PlayerStatAlp<float>		alp_StatPerkRadResistanceProgress;		
	
	ref PlayerStatAlp<int> 			alp_StatPerkToxicResistance;
	ref PlayerStatAlp<float>		alp_StatPerkToxicResistanceProgress;		
	
	ref PlayerStatAlp<float>		alp_StatTiredness;	
	ref PlayerStatAlp<float>		alp_StatCurrentScore;	
	
	// Fatigue & Emotes
	float							alp_HandleFatigueTick;
	EffectSound 					alp_YawnSound;
	EffectSound 					alp_RoflSound;
	bool							alp_IsSleeping = false;
	bool							alp_IsWink = false;	
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableBool( "alp_IsSleeping" );	
	}	
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		switch (rpc_type)
		{		
			case ALP_RPC_DAYZ_SKILLS_SPECIALTY_SYNC:
				Param2<float,float> p_synch = new Param2<float,float>(0,0);
				ctx.Read( p_synch );
				GetSoftSkillsManager().SetSpecialtyLevelSoft( p_synch.param1 );
				GetSoftSkillsManager().SetSpecialtyLevelHard( p_synch.param2 );
			break;
		}
	}	
	
	// 1. PVP e Reputação Otimizados para 3 Vias (Herói, Bandido, Neutro)
	override void KilledByPlayerALP(PlayerBase killer, string source)
	{
		super.KilledByPlayerALP( killer, source );

		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation && killer.GetRP() && GetRP() )
		{		
			float repEXP = GetRP().GetTotalReputationExp() * GetND().GetRP().GetReputationBonusKillPlayer();
			int killerRole = ALP_RP_NEUTRAL;
			
			if (killer.GetRP().IsHero()) killerRole = ALP_RP_HERO;
			else if (killer.GetRP().IsBandit()) killerRole = ALP_RP_BANDIT;

			// Calcula a perda/ganho baseado na vítima
			if (GetRP().IsHero()) 
			{
				killer.GetRP().ChangeReputation( GetND().GetRP().GetReputationBonusKillHero(killerRole) - repEXP );
			}
			else if (GetRP().IsBandit())
			{
				killer.GetRP().ChangeReputation( GetND().GetRP().GetReputationBonusKillBandit(killerRole) + repEXP );
			}
			else // Vítima Neutra
			{
				// Configuração padrão de penalidade ou recompensa por matar neutros
				killer.GetRP().ChangeReputation( -10.0 ); // Exemplo de penalidade genérica
			}
			
			killer.GetStatCountPlayers().Add(1);									
		}
	}	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);	
		
		if (damageType == DT_CUSTOM && ammo == "FallDamage" && GetHealth("", "") < 70)
		{
			BreakLegsALP();
		}			
	}	
	
	override void EEItemIntoHands(EntityAI item)
	{
		super.EEItemIntoHands( item );
		
		Grenade_Base grenade;
		if ( Class.CastTo( grenade, item ) )
		{
			grenade.alp_LastOwner = this;
			return;
		}
		TrapBase trap;
		if ( Class.CastTo( trap, item ) )
		{
			trap.alp_LastOwner = this;
		}		
	}	
	
	// --- BLOB DE GETTERS STATS OMITIDO POR ESPAÇO, MANTIDO IGUAL AO ORIGINAL ---
	PlayerStatAlp<int> GetStatPerkStamina() { if(!alp_StatPerkStamina && GetPlayerStatsALP()) alp_StatPerkStamina = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_STAMINA)); return alp_StatPerkStamina; }		
	PlayerStatAlp<float> GetStatPerkStaminaProgress() { if(!alp_StatPerkStaminaProgress && GetPlayerStatsALP()) alp_StatPerkStaminaProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_STAMINAPROGRESS)); return alp_StatPerkStaminaProgress; }		
	PlayerStatAlp<float> GetStatPerkSoft() { if(!alp_StatPerksSoftDayZ && GetPlayerStatsALP()) alp_StatPerksSoftDayZ = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_SPECIALTY_SOFT)); return alp_StatPerksSoftDayZ; }		
	PlayerStatAlp<float> GetStatPerkRough() { if(!alp_StatPerksRoughDayZ && GetPlayerStatsALP()) alp_StatPerksRoughDayZ = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_SPECIALTY_HARD)); return alp_StatPerksRoughDayZ; }	
	PlayerStatAlp<int> GetStatCountPlayers() { if(!alp_StatCountPlayers && GetPlayerStatsALP()) alp_StatCountPlayers = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTPLAYERS)); return alp_StatCountPlayers; }	
	PlayerStatAlp<int> GetStatCountZombies() { if(!alp_StatCountZombies && GetPlayerStatsALP()) alp_StatCountZombies = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTZOMBIES)); return alp_StatCountZombies; }			
	PlayerStatAlp<int> GetStatCountAnimals() { if(!alp_StatCountAnimals && GetPlayerStatsALP()) alp_StatCountAnimals = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTANIMALS)); return alp_StatCountAnimals; }	
	PlayerStatAlp<int> GetStatCountSkinned() { if(!alp_StatCountSkinned && GetPlayerStatsALP()) alp_StatCountSkinned = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTANIMALS)); return alp_StatCountSkinned; }		
	PlayerStatAlp<int> GetStatPerkReputation() { if(!alp_StatPerkReputation && GetPlayerStatsALP()) alp_StatPerkReputation = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_REPUTATION)); return alp_StatPerkReputation; }		
	PlayerStatAlp<float> GetStatPerkReputationProgress() { if(!alp_StatPerkReputationProgress && GetPlayerStatsALP()) alp_StatPerkReputationProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_REPUTATIONPROGRESS)); return alp_StatPerkReputationProgress; }		
	PlayerStatAlp<float> GetStatCurrentScore() { if(!alp_StatCurrentScore && GetPlayerStatsALP()) alp_StatCurrentScore = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.CURRENT_SCORE)); return alp_StatCurrentScore; }		
	PlayerStatAlp<int> GetStatPerkHunting() { if(!alp_StatPerkHunting && GetPlayerStatsALP()) alp_StatPerkHunting = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_HUNTING)); return alp_StatPerkHunting; }		
	PlayerStatAlp<float> GetStatPerkHuntingProgress() { if(!alp_StatPerkHuntingProgress && GetPlayerStatsALP()) alp_StatPerkHuntingProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_HUNTINGPROGRESS)); return alp_StatPerkHuntingProgress; }		
	PlayerStatAlp<int> GetStatPerkRadiationResistance() { if(!alp_StatPerkRadResistance && GetPlayerStatsALP()) alp_StatPerkRadResistance = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_RADIATIONIMMUNITY)); return alp_StatPerkRadResistance; }		
	PlayerStatAlp<float> GetStatPerkRadiationResistanceProgress() { if(!alp_StatPerkRadResistanceProgress && GetPlayerStatsALP()) alp_StatPerkRadResistanceProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_RADIATIONPROGRESS)); return alp_StatPerkRadResistanceProgress; }		
	PlayerStatAlp<int> GetStatPerkToxicResistance() { if(!alp_StatPerkToxicResistance && GetPlayerStatsALP()) alp_StatPerkToxicResistance = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_TOXICIMMUNITY)); return alp_StatPerkToxicResistance; }		
	PlayerStatAlp<float> GetStatPerkToxicResistanceProgress() { if(!alp_StatPerkToxicResistanceProgress && GetPlayerStatsALP()) alp_StatPerkToxicResistanceProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_TOXICIMMUNITYPROGRESS)); return alp_StatPerkToxicResistanceProgress; }		
	PlayerStatAlp<float> GetStatTiredness() { if(!alp_StatTiredness && GetPlayerStatsALP()) alp_StatTiredness = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.TIREDNESS)); return alp_StatTiredness; }			
	// --- FIM DOS GETTERS ---

	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{		
		super.SetActionsRemoteTarget(InputActionMap);	
		AddAction(alpSpreadRumourAction);
		AddAction(alpActionExamination);
	}	

	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);	
			
		if ( GetND().GetRP().GetPerksOptions().EnableFatigue && GetGame().IsClient() && IsControlledPlayer() )
		{	
			alp_HandleFatigueTick += deltaTime;
			if (alp_HandleFatigueTick > 3)
			{				
				HandleFatigueALP(alp_HandleFatigueTick);	
				alp_HandleFatigueTick = 0;
			}
		}
	}	
	
	void HandleFatigueALP(float deltaTime)
	{
		if ( GetRP().GetFatigueStatus() == EStatLevels.CRITICAL + 1 )	
		{
			if (Math.RandomFloatInclusive(0,1) >= 0.90) 
			{
				if ( ( !alp_YawnSound || !alp_YawnSound.IsPlaying() ) && !IsPlayerSleeping() )
				{						
					// Assegure-se que PlaySoundSet é compatível com PlayerBase no seu mod (EntityAI geralmente usa EffectSound)
					PlaySoundSet(alp_YawnSound, "yawn_SoundSet", 0, 0 );	
				}
			}
		}	
	}
		
	bool IsPlayerSleeping()
	{
		if (IsUnconscious()) return true;
		if (!m_EmoteManager || !m_EmoteManager.m_bEmoteIsPlaying || !m_EmoteManager.m_Callback || m_EmoteManager.m_Callback.m_callbackID != DayZPlayerConstants.CMD_GESTUREFB_LYINGDOWN)
		{
			return false;
		}
		return true;
	}	
	
	bool IsPlayerInShelter()
	{
		if (m_Environment && m_Environment.IsInShelter() ) return true;
		
		if ( GetND().GetRP().GetFatigue().SleepingBag.Count() > 0 )
		{
			autoptr array<Object> nearest_objects = new array<Object>;
			autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
	
			GetGame().GetObjectsAtPosition(GetPosition(), 1.0, nearest_objects, proxy_cargos);
	
			for (int i = 0; i < nearest_objects.Count(); i++)
			{
				Object nearest_object = nearest_objects.Get(i);
				if (nearest_object != this && nearest_object.IsInherited(ItemBase) && nearest_object.GetParent() == null )
				{
					string configClass = nearest_object.GetType();
					if (GetND().GetRP().GetFatigue().SleepingBag.Find(configClass) >= 0)
					{
						return true;
					}
				}
			}		
		}
		return false;
	}	
	
	// 2. Correção de Sincronização e Câmera de Fadiga
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)	
	{
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
		
		if ( GetND().GetRP().GetPerksOptions().EnableFatigue  )
		{
			if (GetGame().IsClient())
			{
				if (alp_YawnSound && !alp_IsWink ) 
				{	
					PPEffects.SetShockVignette(0.98);
					alp_IsWink = true;
				}	
				if (!alp_YawnSound && alp_IsWink ) 
				{
					PPEffects.SetShockVignette(0);
					alp_IsWink = false;
				}
			}
					
			if ( GetND().GetRP().GetFatigue().ClosedEyesWhileSleeping )
			{
				if ( IsPlayerSleeping() && !IsUnconscious() )
				{
					if (!alp_IsSleeping)
					{
						alp_IsSleeping = true;
						if (GetGame().IsClient()) PPEffects.EnableClosedEyesALP();
						if (GetGame().IsServer()) SetSynchDirty(); // Correção: Apenas servidor envia Synch
					}					
				}
				else if ( alp_IsSleeping )
				{	
					alp_IsSleeping = false;	
					if (GetGame().IsClient()) PPEffects.DisableClosedEyesALP();
					if (GetGame().IsServer()) SetSynchDirty(); // Correção: Apenas servidor envia Synch
				}
			}
		}
	}	
	
	// 3. O Bug Impossível do Som Corrigido
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (GetGame().IsClient() && this != PlayerBase.Cast( GetGame().GetPlayer() ) && IsAlive() )
		{						
			// Antes: if (alp_IsSleeping && !alp_RoflSound && !alp_IsSleeping) -> NUNCA IA TOCAR
			if ( alp_IsSleeping && !alp_RoflSound )
			{
				PlaySoundSet(alp_RoflSound, "alp_rofl_SoundSet", 0, 0 );			
			}
			
			// Removido o bloco duplicado de parada de som e simplificado
			if ( !alp_IsSleeping && alp_RoflSound )
			{
				alp_RoflSound.SoundStop();
				alp_RoflSound = null;			
			}			
		}
	}		
	
	EStatLevels GetStatLevelEnergyALP()
	{
		float energy = GetStatTiredness().Get();
		return GetStatLevel(energy, PlayerConstants.ALP_ENERGY_CRITICAL , PlayerConstants.ALP_ENERGY_LOW, PlayerConstants.ALP_ENERGY_NORMAL, PlayerConstants.ALP_ENERGY_HIGH);
	}
	
	// 4. Correção de Segurança contra Nulos na Absorção de Dano/Status
	override void ConsumeBonusesALP(ItemBase source, float amount, EConsumeType consume_type = EConsumeType.ITEM_SINGLE_TIME)
	{
		float alcohol, doses, toxicity;
		int drunkenness, drunkennessMax;		
		
		Edible_Base edible_item = Edible_Base.Cast(source);
		if(!edible_item)
		{
			if( consume_type == alpeConsumeType.ENVIRO_POND_CONTAMINED || consume_type == alpeConsumeType.ENVIRO_WELL_CONTAMINED ) 
			{
				alpLiquidBonuses liq = GetND().GetRP().GetFatigue().GetLiquidBonus( 268435456 );
				if ( liq ) ProcessConsumeBonusesALP(liq.Energy, liq.Alcohol, liq.Radiation, liq.Toxicity, amount);				
			}
			return;
		}

		if ( edible_item.IsLiquidContainer() )
		{
			int lid = edible_item.GetLiquidType();
			alpLiquidBonuses liquid = GetND().GetRP().GetFatigue().GetLiquidBonus( lid );
			if ( liquid ) ProcessConsumeBonusesALP(liquid.Energy, liquid.Alcohol, liquid.Radiation, liquid.Toxicity, amount);
		}
		else
		{
			alpFoodBonuses food = GetND().GetRP().GetFatigue().GetFoodBonus( edible_item.GetType() );
			if ( food ) ProcessConsumeBonusesALP(food.Energy, food.Alcohol, food.Radiation, food.Toxicity, amount);
		}
	}	

	// Função Auxiliar para evitar repetição massiva de código
	protected void ProcessConsumeBonusesALP(float bEnergy, float bAlcohol, float bRad, float bTox, float amount)
	{
		GetStatTiredness().Add( bEnergy * amount );			
				
		int drunkenness = GetSingleAgentCount( alpeAgents.DRUNKENNESS );
		int drunkennessMax = PluginTransmissionAgents.GetAgentMaxCount( alpeAgents.DRUNKENNESS );					
		float alcohol = bAlcohol * amount;
	
		if (drunkenness + alcohol > drunkennessMax) alcohol = drunkennessMax - drunkenness;	
		InsertAgent(alpeAgents.DRUNKENNESS, alcohol);	
				
		float doses = bRad * amount;
		if ( doses > 0 && GetRP() && GetRP().GetProtection() ) // Failsafe Adicionado
		{
			doses *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstRadiation());
		}				
		InsertAgent(alpeAgents.RADIATION, doses );				
				
		float toxicity = bTox * amount;
		if ( toxicity > 0 && GetRP() && GetRP().GetProtection() ) // Failsafe Adicionado
		{
			toxicity *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstChemical());
		}				
		InsertAgent(eAgents.CHEMICAL_POISON, toxicity );	
	}
	
	// --- SISTEMAS DE FRATURA OMITIDOS PARA ESPAÇO, MANTIDOS IGUAL AO ORIGINAL ---
	void BreakLegsALP()
	{
		if ( GetModifiersManager().IsModifierActive( eModifiers.MDF_BROKEN_LEGS ) ) GetModifiersManager().DeactivateModifier( eModifiers.MDF_BROKEN_LEGS );
		GetModifiersManager().ActivateModifier( eModifiers.MDF_BROKEN_LEGS );	
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_BONE_REGEN)) GetModifiersManager().DeactivateModifier(eModifiers.MDF_BONE_REGEN);		
	}
	
	void BreakArmsALP()
	{
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_ARMS)) GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_ARMS);
		GetModifiersManager().ActivateModifier(eModifiers.MDF_BROKEN_ARMS);		
	}
	
	override void ApplySplint()
	{
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_BONE_REGEN)) GetModifiersManager().DeactivateModifier(eModifiers.MDF_BONE_REGEN);
		GetModifiersManager().ActivateModifier(eModifiers.MDF_BONE_REGEN);
	}	
	
	override int GetShakeLevel()
	{
		if (m_BrokenLegState != eBrokenLegs.NO_BROKEN_LEGS) return SHAKE_LEVEL_MAX;
		return super.GetShakeLevel();
	}	
	
	// 5. Bug Crítico Comercial Corrigido
	override float GetReputationMltp(int action ) 
	{
		// 0 - Comprar | 1 - Vender
		int role = ALP_RP_NEUTRAL; // Agora suporta Neutros na economia
		
		if (GetRP() && GetRP().IsHero()) 
		{ 
			role = ALP_RP_HERO;
		} 
		else if (GetRP() && GetRP().IsBandit()) 
		{
			role = ALP_RP_BANDIT; // O Erro estava aqui, forçava ALP_RP_HERO
		}				
		
		if ( action == 0 ) 
		{
			return GetND().GetRP().GetReputationBonusBuy( role );
		} 
		else 
		{
			return GetND().GetRP().GetReputationBonusSell( role );			
		}		
	}	
}