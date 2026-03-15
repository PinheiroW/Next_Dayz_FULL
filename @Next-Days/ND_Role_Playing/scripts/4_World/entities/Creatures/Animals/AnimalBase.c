/**
 * @class   AnimalBase
 * @brief   Gerencia recompensas de caça, XP e bônus de dano para o sistema Next Days
 * Auditado em: 2024 - Foco em Alinhamento Moral e Progressão de Perk
 */
modded class AnimalBase extends DayZAnimal
{
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);

		if (GetGame().IsServer() && killer)
		{
			PlayerBase player;
			// 1. Identifica o jogador (seja por tiro direto ou hierarquia de arma)
			if (Class.CastTo(player, EntityAI.Cast(killer).GetHierarchyRootPlayer()))
			{
				PlayerKillAnimalALP(player);	
			}
		}
	}	
	
	void PlayerKillAnimalALP(PlayerBase player)
	{
		if (!player || !GetND() || !GetND().GetRP()) return;

		// 2. Concessão de Reputação (Lógica Humanizada)
		if (GetND().GetRP().GetPerksOptions().EnablePerkReputation)
		{		
			int role = ALP_RP_NEUTRAL; // Valor padrão para neutros
			
			if (player.GetRP().IsHero())
				role = ALP_RP_HERO;
			else if (player.GetRP().IsBandit())
				role = ALP_RP_BANDIT;

			IncreaseReputationALP(player, role);
		}

		// 3. Concessão de XP de Caça (Adicionado: Faltava aplicar o XP no abate)
		if (GetND().GetRP().GetPerksOptions().EnablePerkHunting)
		{
			float xp = GetEXPtoHunting();
			if (xp > 0)
			{
				// Assume-se que existe um método ChangeHuntingXP ou similar nos Stats
				player.GetStatPerkHunting().Add(xp); 
			}
		}
	}	
	
	// Bônus de Dano baseado no nível de caçador
	float BonusDamageALP(float damage, PlayerBase player)
	{
		if (!player || !GetND().GetRP()) return damage;

		float bonus = GetND().GetRP().GetPerkHuntingDamageMdf(player.GetStatPerkHunting().Get());	
		
		// Failsafe: impede dano zero ou negativo
		if (bonus <= 0.1) bonus = 1.0;
	
		return (damage * bonus);
	}
		
	void IncreaseReputationALP(PlayerBase player, int role)
	{					
		player.GetRP().ChangeReputation(GetND().GetRP().GetReputationBonusKillAnimal(role));			
	}
	
	// Retorna XP base (pode ser sobrescrito por animais específicos)
	float GetEXPtoHunting()
	{
		return 1.0; // Valor base para animais comuns (galinhas, etc)
	}
}

// Lobo: Recompensas específicas
modded class Animal_CanisLupus extends AnimalBase
{
	override void IncreaseReputationALP(PlayerBase player, int role)
	{
		player.GetRP().ChangeReputation(GetND().GetRP().GetReputationBonusKillWolf(role));			
	}
	
	override float GetEXPtoHunting()
	{
		return GetND().GetRP().GetPerkHunting().KillWolf;
	}	
}

// Urso: Recompensas específicas
modded class Animal_UrsusArctos extends AnimalBase
{
	override void IncreaseReputationALP(PlayerBase player, int role)
	{	
		player.GetRP().ChangeReputation(GetND().GetRP().GetReputationBonusKillBear(role));			
	}

	override float GetEXPtoHunting()
	{
		return GetND().GetRP().GetPerkHunting().KillBear;
	}
}