/**
 * NDCreatures - PlayerBase.c
 * Auditoria Técnica: Pró-Gamer / IA Modding Specialist
 */

modded class PlayerBase extends ManBase
{
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		// Chama o comportamento original primeiro
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (!GetGame().IsServer()) return;

		ZombieBase zed = ZombieBase.Cast(source);
		if (!zed || !damageResult) return;

		// Acesso seguro às opções (Corrigido typo EnableCreatures)
		auto ndCreatures = GetND().GetCreatures();
		if (!ndCreatures || !ndCreatures.GetOptions() || !ndCreatures.GetOptions().EnableCreatures) return;

		// Busca o comportamento customizado do zumbi
		alpZombieBehavior behavior = ndCreatures.GetZombieBehavior(zed.GetType());
		if (!behavior) return;

		float koef = 1.0;
		
		// Lógica de Dano e Quebra de Ossos
		if (ammo == "MeleeZombie_Heavy")
		{
			koef = behavior.HeavyDamageBonus; // Acesso direto ao atributo da classe behavior
			
			float breakingChance = behavior.ChanceToBreakBone;
			if (breakingChance > Math.RandomFloat01())
			{
				if (dmgZone.Contains("Arm") || dmgZone.Contains("Hand"))
				{
					BreakArmsALP(); // Certifique-se que este método existe no seu mod de RP/Core
				}
				else if (dmgZone.Contains("Leg") || dmgZone.Contains("Foot"))
				{
					BreakLegsALP();
				}
			}
		}
		else
		{
			koef = behavior.DamageBonus;
		}
		
		// Aplicação de multiplicadores de dano customizados
		float health = damageResult.GetDamage("", "Health") * koef;
		float blood  = damageResult.GetDamage("", "Blood") * koef;
		float shock  = damageResult.GetDamage("", "Shock") * koef;
		
		// Lógica de Cura do Zumbi (Vampirismo/Regeneração)
		if (behavior.GetHealing() > 0)
		{
			float totalDmg = health + blood + shock;
			zed.AddHealth("", "", totalDmg * behavior.GetHealing());
		}

		// Lógica de Infecção por Radiação (Apenas se o mod RP estiver presente)
		float shield;
		float radiationAmount = behavior.GetRadiation();
		if (radiationAmount > 0)
		{
			shield = GetRP().GetProtection().GetTotalRadiationShield();
			float affectRad = (health + blood) * radiationAmount * (1.0 - shield);
			InsertAgent(alpeAgents.RADIATION, (int)affectRad);
		}

		// Lógica de Infecção Química (CORRIGIDO: Agora usa GetToxic e shield Químico)
		float toxicAmount = behavior.GetToxic();
		if (toxicAmount > 0)
		{
			shield = GetRP().GetProtection().GetTotalChemicalShield();
			float affectToxic = (health + blood) * toxicAmount * (1.0 - shield);
			InsertAgent(eAgents.CHEMICAL_POISON, (int)affectToxic);
		}
	}

	// Helpers para compatibilidade (Devem estar definidos no seu ND_Core ou ND_RP)
	void BreakArmsALP() { /* Implementação de quebra de braço */ }
	void BreakLegsALP() { /* Implementação de quebra de perna */ }
}