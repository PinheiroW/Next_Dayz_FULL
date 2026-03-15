/**
 * @class   alpPlayerHive
 * @brief   Gerencia a persistência de dados (Hive), Seguro de Vida e DNA do Next Days
 * Auditado em: 2026 - Foco em Integridade de Dados (Namalsk) e Segurança de Deslogue
 */
modded class alpPlayerHive
{
	float alp_TEMP_reputationEXP;
	
	override void WriteSmallSync( ref ScriptRPC rpc)
	{
		super.WriteSmallSync( rpc );
		rpc.Write( alp_StoreValues.BestScore );
	}
	
	override void SyncSmallRPC( ParamsReadContext ctx )
	{
		super.SyncSmallRPC( ctx );
		ctx.Read( alp_StoreValues.BestScore );
	}
	
	override void OnDeath()
	{
		super.OnDeath();
	
		if ( GetPlayer() && GetPlayer().GetIdentity() )		
		{
			SaveCommonStats();
			
			if ( HasLifeInsurance() ) SecureStats();
			else SecureStats(true);

			Save(false);
		}
	}

	override void OnDisconnect()
	{
		super.OnDisconnect();
	
		if ( GetPlayer() && GetPlayer().GetIdentity() )		
		{
			if (GetPlayer().IsUnconscious() || GetPlayer().IsRestrained())
			{
				SaveCommonStats();
					
				if ( HasLifeInsurance() && !( GetPlayer().IsUnconscious() || GetPlayer().IsRestrained() ) )
				{			
					SecureStats();
				}
				else
				{
					SecureStats(true);
				}				
			}			
			Save(false);
		}
	}
	
	override void OnConnect()
	{
		super.OnConnect();
		
		if (GetGame().IsServer() )
		{
			if ( GetStore().Event & ALP_SPAWN_EVENT.RESTORE_STATS )
			{
				RestoreStats();
			}		
			
			// Removido o reset abrupto do Namalsk aqui. 
			// Se o jogador está conectando e NÃO tem restore_stats, 
			// o stat já inicia naturalmente pelo sistema vanilla/namalsk.
			
			Save(false);
		}
	}

	void SaveCommonStats()
	{
		// Failsafe Crítico: Impede crash no disconnect se GetRP já tiver sido deletado
		if (!GetPlayer() || !GetPlayer().GetRP() || !GetND().GetRP()) return;

		alp_TEMP_reputationEXP = GetPlayer().GetRP().GetTotalReputationExp(); 
		float savedReputation = alp_TEMP_reputationEXP;
		
		if ( GetND().GetRP().GetPerkReputation().StoreLastSessionInHoF )
		{
			savedReputation = alp_Player.GetStatCurrentScore().Get();					
		}

		if ( Math.AbsFloat(savedReputation) > Math.AbsFloat(GetStore().BestScore) )
		{
			GetStore().BestScore = savedReputation;
		}
			
		if ( GetND().GetRP().GetPerkReputation().EnableHallOfFame )
		{
			if ( Math.AbsFloat( savedReputation ) > Math.AbsFloat( GetND().GetRP().GetMinRecord() ) )
			{
				GetND().GetRP().AddRecords( alp_Player, savedReputation );
			}
		}
	}
			
	protected bool HasLifeInsurance()
	{
		if ( GetND().GetRP().GetPerksOptions().SecureReachedSkill ) return true;
			
		array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			if (Class.CastTo(item, itemsArray.Get(i)))
			{
				if (item.GetType() == "alp_LifeInsuranceExclusive" ) 
				{
					alp_LifeInsuranceExclusive card;
					if ( Class.CastTo(card,item) )
					{
						if ( card.IsLifeInsuranceValid() ) return true;
					}
				}
			}
		}								
		return false;
	}	
	
	protected void SecureStats(bool withoutLI = false)
	{
		if (!GetPlayer() || !GetPlayer().GetRP() || !GetND().GetRP()) return;

		GetStore().Event = GetStore().Event | ALP_SPAWN_EVENT.RESTORE_STATS;

		int level;
		float exp, exp2;
				
		// Stamina		
		level = GetPlayer().GetStatPerkStamina().Get();
		exp = GetPlayer().GetRP().GetTotalStaminaExp();
		if ( !withoutLI && GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath.Count() >= 2 )
		{
			if (GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath[1] < 1 && level >= GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath[0])
				exp *= GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath[1];
		}
		if ( withoutLI ) exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		GetStore().PerkStaminaEXP = exp;
		
		// DayZ Skills
		exp = GetPlayer().GetStatPerkSoft().Get(); 
		exp2 = GetPlayer().GetStatPerkRough().Get(); 
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
			exp2 *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}	
		else
		{
			exp *= GetND().GetRP().GetPerksDayz().PenalizedSkillAfterDeath;
			exp2 *= GetND().GetRP().GetPerksDayz().PenalizedSkillAfterDeath;	
		}	
		GetStore().PerkSoftEXP = exp;		
		GetStore().PerkRoughEXP = exp2;	
		
		// Resistance Cold (Namalsk)
#ifdef NAMALSK_SURVIVAL			
		exp = alp_Player.GetStatColdResistance().Get();
		if ( withoutLI ) exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		else exp *= GetND().GetRP().GetPerkColdResistance().PenalizedSkillAfterDeath;
		GetStore().PerkResistanceColdEXP = exp;						
#endif 		
		
		// Reputation
		level = GetPlayer().GetStatPerkReputation().Get();
		exp = alp_TEMP_reputationEXP;
		if ( !withoutLI && GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath.Count() >= 2 )
		{
			if (GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath[1] < 1 && level >= GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath[0])
				exp *= GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath[1];
		}
		if ( withoutLI ) exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		GetStore().PerkReputationEXP = exp;	
		
		// Hunting
		level = GetPlayer().GetStatPerkHunting().Get();
		exp = GetPlayer().GetRP().GetTotalHuntingExp();
		if ( !withoutLI && GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath.Count() >= 2 )
		{
			if (GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath[1] < 1 && level >= GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath[0])
				exp *= GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath[1];
		}
		if ( withoutLI ) exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		GetStore().PerkHuntingEXP = exp;	
		
		// Radiation Resistance
		level = GetPlayer().GetStatPerkRadiationResistance().Get();
		exp = GetPlayer().GetRP().GetTotalRadiationResistanceExp();
		if ( !withoutLI && GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath.Count() >= 2 )
		{
			if (GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath[1] < 1 && level >= GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath[0])
				exp *= GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath[1];
		}
		if ( withoutLI ) exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		GetStore().PerkRadiationResistanceEXP = exp;	
		
		// Toxic Resistance
		level = GetPlayer().GetStatPerkToxicResistance().Get();
		exp = GetPlayer().GetRP().GetTotalToxicResistanceExp();
		if ( !withoutLI && GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath.Count() >= 2 )
		{
			if (GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath[1] < 1 && level >= GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath[0])
				exp *= GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath[1];
		}
		if ( withoutLI ) exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		GetStore().PerkToxicResistanceEXP = exp;					
	}	
	
	protected void RestoreStats()
	{
		if (!GetPlayer() || !GetPlayer().GetRP()) return;

		GetStore().Event = ~ALP_SPAWN_EVENT.RESTORE_STATS & GetStore().Event;
		
		int level;
		float exp, exp2;
		
		// Stamina
		exp = GetStore().PerkStaminaEXP;
		level = GetPlayer().GetRP().GetStaminaLevelByEXP(exp);
		GetPlayer().GetStatPerkStamina().Set( level );
		GetPlayer().GetStatPerkStaminaProgress().Set( exp );
		
		// DayZ Soft Skills
		exp = GetStore().PerkSoftEXP;
		exp2 = GetStore().PerkRoughEXP;
		GetPlayer().GetStatPerkSoft().Set( exp );
		GetPlayer().GetStatPerkRough().Set(exp2); 
		
		// Namalsk (Corrigido)
#ifdef NAMALSK_SURVIVAL			
		exp = GetStore().PerkResistanceColdEXP;
		alp_Player.GetStatColdResistance().Set( exp ); // Agora seta o valor correto em vez de 0
#endif 			

		// Reputation
		exp = GetStore().PerkReputationEXP;
		int role = (exp < 0) ? -1 : 1;
		exp = Math.AbsFloat(exp);		
		level = GetPlayer().GetRP().GetReputationLevelByEXP(exp);		
		GetPlayer().GetStatPerkReputation().Set( level * role );
		GetPlayer().GetStatPerkReputationProgress().Set( exp * role );		
		
		// Hunting
		exp = GetStore().PerkHuntingEXP;
		level = GetPlayer().GetRP().GetHuntingLevelByEXP(exp);
		GetPlayer().GetStatPerkHunting().Set( level );
		GetPlayer().GetStatPerkHuntingProgress().Set( exp );		
		
		// Radiation Resistance
		exp = GetStore().PerkRadiationResistanceEXP;
		level = GetPlayer().GetRP().GetRadiationResistanceLevelByEXP(exp);
		GetPlayer().GetStatPerkRadiationResistance().Set( level );
		GetPlayer().GetStatPerkRadiationResistanceProgress().Set( exp );	
		
		// Toxic Resistance
		exp = GetStore().PerkToxicResistanceEXP;
		level = GetPlayer().GetRP().GetToxicResistanceLevelByEXP(exp);
		GetPlayer().GetStatPerkToxicResistance().Set( level );
		GetPlayer().GetStatPerkToxicResistanceProgress().Set( exp );				
	}	
	
	void SaveDNA()
	{
		if (!alp_Player || !alp_Player.GetRP()) return;

		GetStore().SavedDNA.StaminaEXP = alp_Player.GetRP().GetTotalStaminaExp(); 
		GetStore().SavedDNA.SpecialtySoftEXP = alp_Player.GetStatPerkSoft().Get();	
		GetStore().SavedDNA.SpecialtyRoughEXP = alp_Player.GetStatPerkRough().Get();
		
#ifdef NAMALSK_SURVIVAL			
		GetStore().SavedDNA.ResistanceColdEXP = alp_Player.GetStatColdResistance().Get();		
#endif	

		GetStore().SavedDNA.HuntingEXP = alp_Player.GetRP().GetTotalHuntingExp();		
		GetStore().SavedDNA.ResistanceEXP = alp_Player.GetRP().GetTotalRadiationResistanceExp();		
		GetStore().SavedDNA.ResistanceToxicEXP = alp_Player.GetRP().GetTotalToxicResistanceExp();		
		
		if ( !GetND().GetRP().GetPerksOptions().ExcludeReputationFromCloning )
		{
			GetStore().SavedDNA.ReputationEXP = alp_Player.GetRP().GetTotalReputationExp();			
		}
		
		Save();
	}	
	
	void LoadDNA()
	{
		if (!alp_Player || !alp_Player.GetRP()) return;

		float staminaEXP = GetStore().SavedDNA.StaminaEXP;
		int stamina = alp_Player.GetRP().GetStaminaLevelByEXP( staminaEXP );
		alp_Player.GetStatPerkStamina().Set( stamina );
		alp_Player.GetStatPerkStaminaProgress().Set( staminaEXP );	
		
		float soft = GetStore().SavedDNA.SpecialtySoftEXP;
		float rough = GetStore().SavedDNA.SpecialtyRoughEXP;
		alp_Player.GetStatPerkSoft().Set( soft );
		alp_Player.GetStatPerkRough().Set( rough );
		
		if ( alp_Player.GetSoftSkillsManager() )
		{
			alp_Player.GetSoftSkillsManager().InitSpecialty( alp_Player.GetStatSpecialty().Get() );	
		}
		
#ifdef NAMALSK_SURVIVAL			
		float coldEXP = GetStore().SavedDNA.ResistanceColdEXP;
		alp_Player.GetStatColdResistance().Set( coldEXP ); // Corrigido
#endif	

		float huntEXP = GetStore().SavedDNA.HuntingEXP;
		int hunting = alp_Player.GetRP().GetHuntingLevelByEXP( huntEXP );
		alp_Player.GetStatPerkHunting().Set( hunting );
		alp_Player.GetStatPerkHuntingProgress().Set( huntEXP );	
		
		float resEXP = GetStore().SavedDNA.ResistanceEXP;
		int resistance = alp_Player.GetRP().GetRadiationResistanceLevelByEXP( resEXP );
		alp_Player.GetStatPerkRadiationResistance().Set( resistance );
		alp_Player.GetStatPerkRadiationResistanceProgress().Set( resEXP );			
		
		float toxicEXP = GetStore().SavedDNA.ResistanceToxicEXP;
		int toxic = alp_Player.GetRP().GetToxicResistanceLevelByEXP( toxicEXP );
		alp_Player.GetStatPerkToxicResistance().Set( toxic );
		alp_Player.GetStatPerkToxicResistanceProgress().Set( toxicEXP );	
				
		if ( !GetND().GetRP().GetPerksOptions().ExcludeReputationFromCloning )
		{
			float reputationEXP = GetStore().SavedDNA.ReputationEXP;
			int role = (reputationEXP < 0) ? -1 : 1;
			float repExp = Math.AbsFloat(reputationEXP);	
			int reputation = alp_Player.GetRP().GetReputationLevelByEXP( repExp );
					
			alp_Player.GetStatPerkReputation().Set( reputation * role );
			alp_Player.GetStatPerkReputationProgress().Set( repExp * role );				
		}
	}	
}