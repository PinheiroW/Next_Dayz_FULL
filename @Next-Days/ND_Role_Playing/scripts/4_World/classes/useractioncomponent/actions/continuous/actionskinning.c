/**
 * @class   ActionSkinning
 * @brief   Gerencia a esfolação de entidades com base no Perk de Caça e Moralidade
 * Auditado em: 2024 - Foco em Precisão Matemática e Segurança de Divisão
 */
modded class ActionSkinning: ActionContinuousBase
{	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if ( !super.ActionCondition( player, target, item ) )
			return false;

		if (!GetND().GetRP().GetPerksOptions().EnablePerkHunting)
			return true;
		
		int currentLevel = player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue();
		int requiredLevel = GetND().GetRP().GetPerkHunting().RequiredLevelToSkin;

		// Verifica se o jogador tem o nível mínimo para tentar esfolar
		return (currentLevel >= requiredLevel);
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		if (!GetND().GetRP().GetPerksOptions().EnablePerkHunting)
		{		
			super.OnFinishProgressServer(action_data);
			return;
		}

		PlayerBase player = action_data.m_Player;
		int level = player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue(); 
		float levelCup = (float)GetND().GetRP().GetPerkHuntingLevelCup();
		
		float peltDamageMdf = 1.0;
		
		// 1. Correção da Divisão por Zero e Cast de Float
		if ( GetND().GetRP().GetPerkHunting().AffectPeltQualityByLevel && levelCup > 0 )
		{
			// Agora a divisão resulta em um decimal (ex: 0.2, 0.4...)
			peltDamageMdf = (float)level / levelCup;			
		}
		
		float huntingModifier = GetND().GetRP().GetPerkHuntingMdf( level );
		if (huntingModifier <= 0) huntingModifier = 1.0; // Failsafe contra divisão por zero

		// 2. Aplica dano à ferramenta (Mais habilidade = menos dano ao item)
		float toolDamage = UADamageApplied.SKINNING / huntingModifier;
		MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, toolDamage);
		
		// 3. Efeitos visuais (Mãos sujas de sangue)
		PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
		if (module_lifespan)
			module_lifespan.UpdateBloodyHandsVisibility( player, true );
		
		player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );

		// 4. Executa a criação dos itens (couro, carne)
		PlayerSkinnedEntityALP( action_data );
	}	

	protected void PlayerSkinnedEntityALP( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		Object targetObject = action_data.m_Target.GetObject();
		PlayerBase targetPlayer;

		// Se o alvo for um HUMANO (Jogador ou NPC humano)
		if (Class.CastTo(targetPlayer, targetObject))
		{
			float repChange = 0;
			
			// Esfolar humanos sempre deve ser um ato maligno/degradante no RPG
			if (player.GetRP().IsHero())
			{
				// Heróis perdem muita reputação (Punição por ato cruel)
				repChange = -50.0; 
			}
			else
			{
				// Bandidos podem ganhar um bônus por "crueldade" ou simplesmente um valor neutro
				repChange = GetND().GetRP().GetReputationBonusSkinPlayer(ALP_RP_BANDIT);
			}
			
			player.GetRP().ChangeReputation(repChange);
		}
		else 
		{
			// Lógica para esfolar ANIMAIS (Ganha reputação de caçador)
			string role = ALP_RP_BANDIT;
			if (player.GetRP().IsHero()) role = ALP_RP_HERO;
			
			float animalBonus = GetND().GetRP().GetReputationBonusKillAnimal(role);
			player.GetRP().ChangeReputation(animalBonus);
		}
	}
};