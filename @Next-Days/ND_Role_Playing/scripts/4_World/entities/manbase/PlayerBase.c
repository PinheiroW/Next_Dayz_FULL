


// Script File

modded class PlayerBase extends ManBase
{
	ref PlayerStatAlp<int> 			alp_StatPerkStamina;
	ref PlayerStatAlp<float>		 	alp_StatPerkStaminaProgress;	
	
	ref PlayerStatAlp<float>		 	alp_StatPerksSoftDayZ;	
	ref PlayerStatAlp<float>		 	alp_StatPerksRoughDayZ;	
		
	ref PlayerStatAlp<int> 			alp_StatCountPlayers;
	ref PlayerStatAlp<int> 			alp_StatCountZombies;
	ref PlayerStatAlp<int> 			alp_StatCountAnimals;
	ref PlayerStatAlp<int> 			alp_StatCountSkinned;
	
	ref PlayerStatAlp<int> 			alp_StatPerkReputation;
	ref PlayerStatAlp<float>		 	alp_StatPerkReputationProgress;		
	
	ref PlayerStatAlp<int> 			alp_StatPerkHunting;
	ref PlayerStatAlp<float>		 	alp_StatPerkHuntingProgress;			
	
	ref PlayerStatAlp<int> 			alp_StatPerkRadResistance;
	ref PlayerStatAlp<float>		 	alp_StatPerkRadResistanceProgress;		
	
	ref PlayerStatAlp<int> 			alp_StatPerkToxicResistance;
	ref PlayerStatAlp<float>		 	alp_StatPerkToxicResistanceProgress;		
	
	ref PlayerStatAlp<float>		 	alp_StatTiredness;	
	
	ref PlayerStatAlp<float>		 	alp_StatCurrentScore;	
	
	//fatigue
	float												 	alp_HandleFatigueTick;
	EffectSound 											alp_YawnSound;
	EffectSound 											alp_RoflSound;
	
	bool													alp_IsSleeping = false;
	
	bool													alp_IsWink = false;	
	
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
				float specialty_soft = p_synch.param1;
				float specialty_hard = p_synch.param2;
				GetSoftSkillsManager().SetSpecialtyLevelSoft( specialty_soft );
				GetSoftSkillsManager().SetSpecialtyLevelHard( specialty_hard );
			break;
		}
	}	
	
	override void KilledByPlayerALP(PlayerBase player, string source)
	{
		super.KilledByPlayerALP( player, source  );

		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation )
		{		
			//chceck player reputation
			float repEXP = GetRP().GetTotalReputationExp() * GetND().GetRP().GetReputationBonusKillPlayer();
				
			if (player.GetRP().IsHero())
			{
				if (GetRP().IsHero()) 
					player.GetRP().ChangeReputation(	GetND().GetRP().GetReputationBonusKillHero( ALP_RP_HERO) - repEXP);				
				else 		
					player.GetRP().ChangeReputation(	GetND().GetRP().GetReputationBonusKillBandit( ALP_RP_HERO) - repEXP );	
			}	
			else 
			{
				if (GetRP().IsHero()) 
					player.GetRP().ChangeReputation(	GetND().GetRP().GetReputationBonusKillHero( ALP_RP_BANDIT) - repEXP);					
				else 
					player.GetRP().ChangeReputation(	GetND().GetRP().GetReputationBonusKillBandit( ALP_RP_BANDIT) + repEXP );	
			}	
			player.GetStatCountPlayers().Add(1);									
		}
	}	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);	
		
		if (damageType == DT_CUSTOM && ammo == "FallDamage" && GetHealth("", "") < 70)
		{
			// fall
			BreakLegsALP();
		}	
		/*
		else if (!damageResult && Math.RandomFloat01() < GetND().GetRP().GetDiseases().ZombieArmsFractureChance )
		{
			BreakArmsALP();
		}
		else if (damageResult)
		{
			float dmg = damageResult.GetHighestDamage("Health");

			if ((dmgZone == "LeftLeg" || dmgZone == "RightLeg" || dmgZone == "LeftFoot" || dmgZone == "RightFoot"))
			{
				if (source && source.IsMeleeWeapon() && dmg >= 30)
				{
					// melee
					BreakLegsALP();
				}
				else if (dmg >= 50)
				{
					// anything else
					BreakLegsALP();
				}
			}
			else if ((dmgZone == "LeftHand" || dmgZone == "RightHand" || dmgZone == "LeftArm" || dmgZone == "RightArm"))
			{
				if (source && source.IsMeleeWeapon() && dmg >= 30)
				{
					// melee
					BreakArmsALP();
				}
				else if (dmg >= 50)
				{
					// anything else
					BreakArmsALP();
				}
			}
		}		
		*/
		
		
	}	
	
	override void EEItemIntoHands(EntityAI item)//HOT FIX FOR KILLING ZOMBIES BY GRENADE
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
	
	
	PlayerStatAlp<int> GetStatPerkStamina()
	{
		if( !alp_StatPerkStamina && GetPlayerStatsALP())
		{
			alp_StatPerkStamina = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_STAMINA));
		}
		return alp_StatPerkStamina;
	}		
	PlayerStatAlp<float> GetStatPerkStaminaProgress()
	{
		if( !alp_StatPerkStaminaProgress  && GetPlayerStatsALP())
		{
			alp_StatPerkStaminaProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_STAMINAPROGRESS));
		}
		return alp_StatPerkStaminaProgress;
	}		
	
	
	PlayerStatAlp<float> GetStatPerkSoft()
	{
		if( !alp_StatPerksSoftDayZ  && GetPlayerStatsALP())
		{
			alp_StatPerksSoftDayZ = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_SPECIALTY_SOFT));
		}
		return alp_StatPerksSoftDayZ;
	}		
	PlayerStatAlp<float> GetStatPerkRough()
	{
		if( !alp_StatPerksRoughDayZ  && GetPlayerStatsALP())
		{
			alp_StatPerksRoughDayZ = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_SPECIALTY_HARD));
		}
		return alp_StatPerksRoughDayZ;
	}	
	
	
	PlayerStatAlp<int> GetStatCountPlayers()
	{
		if( !alp_StatCountPlayers && GetPlayerStatsALP())
		{
			alp_StatCountPlayers = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTPLAYERS));
		}
		return alp_StatCountPlayers;
	}	
	PlayerStatAlp<int> GetStatCountZombies()
	{
		if( !alp_StatCountZombies && GetPlayerStatsALP())
		{
			alp_StatCountZombies = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTZOMBIES));
		}
		return alp_StatCountZombies;
	}			
	PlayerStatAlp<int> GetStatCountAnimals()
	{
		if( !alp_StatCountAnimals && GetPlayerStatsALP())
		{
			alp_StatCountAnimals = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTANIMALS));
		}
		return alp_StatCountAnimals;
	}	
	PlayerStatAlp<int> GetStatCountSkinned()
	{
		if( !alp_StatCountSkinned && GetPlayerStatsALP())
		{
			alp_StatCountSkinned = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.COUNTANIMALS));
		}
		return alp_StatCountSkinned;
	}		
	
	PlayerStatAlp<int> GetStatPerkReputation()
	{
		if( !alp_StatPerkReputation && GetPlayerStatsALP())
		{
			alp_StatPerkReputation = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_REPUTATION));
		}
		return alp_StatPerkReputation;
	}		
	PlayerStatAlp<float> GetStatPerkReputationProgress()
	{
		if( !alp_StatPerkReputationProgress  && GetPlayerStatsALP())
		{
			alp_StatPerkReputationProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_REPUTATIONPROGRESS));
		}
		return alp_StatPerkReputationProgress;
	}		
	PlayerStatAlp<float> GetStatCurrentScore()
	{
		if( !alp_StatCurrentScore  && GetPlayerStatsALP())
		{
			alp_StatCurrentScore = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.CURRENT_SCORE));
		}
		return alp_StatCurrentScore;
	}		
	
	PlayerStatAlp<int> GetStatPerkHunting()
	{
		if( !alp_StatPerkHunting && GetPlayerStatsALP())
		{
			alp_StatPerkHunting = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_HUNTING));
		}
		return alp_StatPerkHunting;
	}		
	PlayerStatAlp<float> GetStatPerkHuntingProgress()
	{
		if( !alp_StatPerkHuntingProgress  && GetPlayerStatsALP())
		{
			alp_StatPerkHuntingProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_HUNTINGPROGRESS));
		}
		return alp_StatPerkHuntingProgress;
	}		
	

	
	PlayerStatAlp<int> GetStatPerkRadiationResistance()
	{
		if( !alp_StatPerkRadResistance && GetPlayerStatsALP())
		{
			alp_StatPerkRadResistance = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_RADIATIONIMMUNITY));
		}
		return alp_StatPerkRadResistance;
	}		
	PlayerStatAlp<float> GetStatPerkRadiationResistanceProgress()
	{
		if( !alp_StatPerkRadResistanceProgress  && GetPlayerStatsALP())
		{
			alp_StatPerkRadResistanceProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_RADIATIONPROGRESS));
		}
		return alp_StatPerkRadResistanceProgress;
	}		
	
		
	
	PlayerStatAlp<int> GetStatPerkToxicResistance()
	{
		if( !alp_StatPerkToxicResistance && GetPlayerStatsALP())
		{
			alp_StatPerkToxicResistance = PlayerStatAlp<int>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_TOXICIMMUNITY));
		}
		return alp_StatPerkToxicResistance;
	}		
	PlayerStatAlp<float> GetStatPerkToxicResistanceProgress()
	{
		if( !alp_StatPerkToxicResistanceProgress  && GetPlayerStatsALP())
		{
			alp_StatPerkToxicResistanceProgress = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.SKILL_TOXICIMMUNITYPROGRESS));
		}
		return alp_StatPerkToxicResistanceProgress;
	}		
		
	//TIREDNESS

	PlayerStatAlp<float> GetStatTiredness()
	{
		if( !alp_StatTiredness  && GetPlayerStatsALP())
		{
			alp_StatTiredness = PlayerStatAlp<float>.Cast(GetPlayerStatsALP().GetStatObject(EPlayerStats_ALP.TIREDNESS));
		}
		return alp_StatTiredness;
	}			
	
	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{		
		super.SetActionsRemoteTarget(InputActionMap);	
		AddAction(alpSpreadRumourAction);
		AddAction(alpActionExamination);
	}	


	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);	
			

		//fatigue
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
			//yawn
			if (Math.RandomFloatInclusive(0,1) >= 0.90) 
			{
				
				if ( ( !alp_YawnSound || !alp_YawnSound.IsPlaying() )&& !IsPlayerSleeping() )
				{						
					PlaySoundSet(alp_YawnSound, "yawn_SoundSet", 0, 0 );	
					
				}

			}
		}	

	}
		
	
	bool IsPlayerSleeping()
	{
		bool isSleeping = true;
		
		if (IsUnconscious())
			return isSleeping;
		
		if (!m_EmoteManager || !m_EmoteManager.m_bEmoteIsPlaying || !m_EmoteManager.m_Callback || m_EmoteManager.m_Callback.m_callbackID != DayZPlayerConstants.CMD_GESTUREFB_LYINGDOWN)
		{
			isSleeping = false;
		}


		return isSleeping;
	}	
	
	bool IsPlayerInShelter()
	{
		if (m_Environment && m_Environment.IsInShelter() )
			return true;
		
		if ( GetND().GetRP().GetFatigue().SleepingBag.Count() > 0 )
		{
			autoptr array<Object> nearest_objects = new array<Object>;
			autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
	
			GetGame().GetObjectsAtPosition(GetPosition(), 1.0, nearest_objects, proxy_cargos);
	
			for (int i = 0; i < nearest_objects.Count(); i++)
			{
				Object nearest_object = nearest_objects.Get(i);
	
				if (nearest_object != this && nearest_object.IsInherited(ItemBase) && nearest_object.GetParent() == null ) // not in player possession
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
	
	

		
	//fatigue
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)	
	{
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
		
		if ( GetND().GetRP().GetPerksOptions().EnableFatigue  )
		{

				//wink
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
						
				//blidness	
				if ( GetND().GetRP().GetFatigue().ClosedEyesWhileSleeping )
				{
					if ( IsPlayerSleeping() )
					{
						if ( !IsUnconscious() )
						{
							if (! alp_IsSleeping )
							{
								alp_IsSleeping = true;
							
								if (GetGame().IsClient())
									PPEffects.EnableClosedEyesALP();
							
								SetSynchDirty();
							}

						}					
					}
					else
					{
						if ( alp_IsSleeping )
						{	
							alp_IsSleeping = false;	
						
							if (GetGame().IsClient())			
								PPEffects.DisableClosedEyesALP();
						
							SetSynchDirty();
						
						}
																
					}
				}
						
			
		}
	}	
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		
		if (GetGame().IsClient() && this != PlayerBase.Cast( GetGame().GetPlayer() ) && IsAlive() )
		{
								
			if ( alp_IsSleeping && !alp_RoflSound && !alp_IsSleeping )
			{
				PlaySoundSet(alp_RoflSound, "alp_rofl_SoundSet", 0, 0 );			
			}
			if ( !alp_IsSleeping && alp_RoflSound)
			{
				alp_RoflSound.SoundStop();
				alp_RoflSound = null;			
			}			
			if ( alp_IsSleeping && alp_RoflSound)
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
	
	
	//FOOD BONUSES
	override void ConsumeBonusesALP(ItemBase source, float amount, EConsumeType consume_type = EConsumeType.ITEM_SINGLE_TIME)
	{
		float alcohol,doses,toxicity;
		int drunkenness,drunkennessMax;		
		
		//just edible so far
		Edible_Base edible_item = Edible_Base.Cast(source);
		if(!edible_item)
		{
			if( consume_type == alpeConsumeType.ENVIRO_POND_CONTAMINED || consume_type == alpeConsumeType.ENVIRO_WELL_CONTAMINED ) {
				alpLiquidBonuses liq = GetND().GetRP().GetFatigue().GetLiquidBonus( 268435456 );	//268435456 contaminated water
				if ( liq )
				{
					//energy
					GetStatTiredness().Add( liq.Energy * amount );			
					
					//alcohol
					drunkenness = GetSingleAgentCount( alpeAgents.DRUNKENNESS );
					drunkennessMax = PluginTransmissionAgents.GetAgentMaxCount( alpeAgents.DRUNKENNESS );					
					
					alcohol = liq.Alcohol *  amount;
				
					
					if (drunkenness + alcohol > drunkennessMax)
					{
						alcohol = drunkennessMax - drunkenness;
					}	
					InsertAgent(alpeAgents.DRUNKENNESS, alcohol);	
					
					//radiation reduce						
					doses = liq.Radiation * amount;
					
					if ( doses > 0 )
					{
						doses *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstRadiation());
						
					}				
					InsertAgent(alpeAgents.RADIATION, doses );				
					
					//toxicity reduce						
					toxicity = liq.Toxicity * amount;
					
					if ( toxicity > 0 )
					{
						toxicity *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstChemical());
						
					}				
					InsertAgent(eAgents.CHEMICAL_POISON, toxicity );								
				}				
			}
			return;
		}

		
		if ( edible_item.IsLiquidContainer() )
		{
			int lid = edible_item.GetLiquidType();
			alpLiquidBonuses liquid = GetND().GetRP().GetFatigue().GetLiquidBonus( lid );
			
			if ( liquid )
			{
				//energy
				GetStatTiredness().Add( liquid.Energy * amount );			
				
				//alcohol
				drunkenness = GetSingleAgentCount( alpeAgents.DRUNKENNESS );
				drunkennessMax = PluginTransmissionAgents.GetAgentMaxCount( alpeAgents.DRUNKENNESS );					
				
				alcohol = liquid.Alcohol *  amount;
			
				
				if (drunkenness + alcohol > drunkennessMax)
				{
					alcohol = drunkennessMax - drunkenness;
				}	
				InsertAgent(alpeAgents.DRUNKENNESS, alcohol);	
				
				//radiation reduce						
				doses = liquid.Radiation * amount;
				
				if ( doses > 0 )
				{
					doses *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstRadiation());
					
				}				
				InsertAgent(alpeAgents.RADIATION, doses );				
				
				//toxicity reduce						
				toxicity = liquid.Toxicity * amount;
				
				if ( toxicity > 0 )
				{
					toxicity *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstChemical());
					
				}				
				InsertAgent(eAgents.CHEMICAL_POISON, toxicity );								
			}
		
		}
		else
		{
			alpFoodBonuses food = GetND().GetRP().GetFatigue().GetFoodBonus( edible_item.GetType() );
			
			if ( food )
			{
				//energy
				GetStatTiredness().Add( food.Energy * amount );			
				
				//alcohol
				drunkenness = GetSingleAgentCount( alpeAgents.DRUNKENNESS );
				drunkennessMax = PluginTransmissionAgents.GetAgentMaxCount( alpeAgents.DRUNKENNESS );					
				
				alcohol = food.Alcohol *  amount;
			
				
				if (drunkenness + alcohol > drunkennessMax)
				{
					alcohol = drunkennessMax - drunkenness;
				}	
				InsertAgent(alpeAgents.DRUNKENNESS, alcohol);	
				
				//radiation reduce						
				doses = food.Radiation * amount;
				
				if ( doses > 0 )
				{
					doses *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstRadiation());
					
				}				
				InsertAgent(alpeAgents.RADIATION, doses );				
				
				//toxicity reduce						
				toxicity = food.Toxicity * amount;
				
				if ( toxicity > 0 )
				{
					toxicity *= (1 - GetRP().GetProtection().GetNaturalResistanceAgainstChemical());
					
				}				
				InsertAgent(eAgents.CHEMICAL_POISON, toxicity );				
			}
		}
	
	}	
	
	//fracture
	void BreakLegsALP()
	{
		if ( GetModifiersManager().IsModifierActive( eModifiers.MDF_BROKEN_LEGS ) )//effectively resets the modifier
		{
			GetModifiersManager().DeactivateModifier( eModifiers.MDF_BROKEN_LEGS );
		}
		GetModifiersManager().ActivateModifier( eModifiers.MDF_BROKEN_LEGS );	
		
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_BONE_REGEN))
		{
			GetModifiersManager().DeactivateModifier(eModifiers.MDF_BONE_REGEN);
		}		
	}
	
	void BreakArmsALP()
	{
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_ARMS))
		{
			GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_ARMS);
		}
		GetModifiersManager().ActivateModifier(eModifiers.MDF_BROKEN_ARMS);		
		
	}
	
	override void ApplySplint()
	{
		if (GetModifiersManager().IsModifierActive(eModifiers.MDF_BONE_REGEN)) //effectively resets the timer
		{
			GetModifiersManager().DeactivateModifier(eModifiers.MDF_BONE_REGEN);
		}
		GetModifiersManager().ActivateModifier(eModifiers.MDF_BONE_REGEN);
	}	
	
	
	
	override int GetShakeLevel()
	{
		if (m_BrokenLegState != eBrokenLegs.NO_BROKEN_LEGS)
		{
			return SHAKE_LEVEL_MAX;
		}
		else
		{
			return super.GetShakeLevel();
		}
	}	
	
	override float GetReputationMltp(int action ) {//0-buy,1-sell
		int role;
		if (GetRP().IsHero()) { //ALP_RP_HERO
			role = 	ALP_RP_HERO;
		} else {//ALP_RP_BANDIT
			role = 	ALP_RP_HERO;
		}				
		if ( action == 0 ) {
			return GetND().GetRP().GetReputationBonusBuy( role );
		} else {
			return GetND().GetRP().GetReputationBonusSell( role );			
		}		
	}	
}