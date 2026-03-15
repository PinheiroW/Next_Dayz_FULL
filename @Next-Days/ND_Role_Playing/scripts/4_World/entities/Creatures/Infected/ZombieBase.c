/**
 * @class   ZombieBase
 * @brief   Gerencia recompensas, XP e bônus de dano contra infectados no Next Days
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Justiça Moral
 */
modded class ZombieBase extends DayZInfected
{
	// 1. Definição de bônus base (pode ser expandido para tipos de zumbis diferentes)
	float GetReputationBonusALP()
	{
		return 1.0;
	}

	override void EEKilled(Object killer)
	{
		if (GetGame().IsServer() && m_KillerData)
		{	
			PlayerBase player;
			// Tenta capturar o jogador diretamente do m_KillerData (mais preciso que o parâmetro killer)
			if (Class.CastTo(player, m_KillerData.m_Killer))
			{
				PlayerKillZombieALP(player);
			}
		}
		
		super.EEKilled(killer);
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		// 2. Sistema de Atribuição de Morte (Granadas e Armadilhas)
		if (GetGame().IsServer() && !IsAlive() && source)
		{
			Grenade_Base grenade = Grenade_Base.Cast(source);
			TrapBase trap = TrapBase.Cast(source);
			PlayerBase owner;

			if (grenade && grenade.alp_LastOwner)
			{
				owner = grenade.alp_LastOwner;
			}
			else if (trap && trap.alp_LastOwner)
			{
				owner = trap.alp_LastOwner;
			}

			if (owner)
			{
				PlayerKillZombieALP(owner);
			}
		}
	}

	void PlayerKillZombieALP(PlayerBase player)
	{
		if (!player || !GetND() || !GetND().GetRP()) return;

		// 3. Sistema de Reputação Multi-Alinhamento
		if (GetND().GetRP().GetPerksOptions().EnablePerkReputation)
		{
			int role = ALP_RP_NEUTRAL; // Valor padrão seguro

			if (player.GetRP().IsHero())
				role = ALP_RP_HERO;
			else if (player.GetRP().IsBandit())
				role = ALP_RP_BANDIT;

			// Aplica a mudança baseada no tipo de zumbi e alinhamento do jogador
			float repBonus = GetND().GetRP().GetReputationBonusKillZombie(role) * GetReputationBonusALP();
			player.GetRP().ChangeReputation(repBonus);
		}
	}

	// 4. Bônus de Dano (Força/Bruto) aplicado a ataques contra Zumbis
	float BonusDamageALP(float damage, PlayerBase player)
	{
		if (!player || !GetND().GetRP()) return damage;

		// Usa o Perk de SoftSkills (Rough/Hard) para aumentar o dano físico
		float skillLevel = player.GetStatPerkRough().Get();
		float bonus = GetND().GetRP().GetPerkStrengthDamageMdf(skillLevel);	
		
		if (bonus <= 0.1) bonus = 1.0; // Failsafe contra config errada
	
		return (damage * bonus);
	}
};