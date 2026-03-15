/**
 * alp_WoodenCrate.c
 * * ENTIDADES DE MISSÃO (CAIXOTES DE MADEIRA) - Módulo ND_MISSIONS
 * Define containers destrutíveis que não podem ser movidos manualmente.
 */

// Versão que estende o caixote vanilla
class alp_WoodenCrate: WoodenCrate
{
	override bool CanPutInCargo(EntityAI parent) { return false; }
	override bool CanPutIntoHands(EntityAI parent) { return false; }
};

// Classe Base para os caixotes customizados do Next-Days
class alp_WoodenCrate_Base: Container_Base
{
	/**
	 * Gerencia o dano recebido.
	 * Permite a destruição via explosivos específicos de missão.
	 */
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		float health = GetHealth("", "Health");
		float damage = damageResult.GetDamage("", "Health");
		
		// Lógica de explosão: Dinamite ou C4
		if (damageType == DT_EXPLOSION && damage > 200)
		{
			if (ammo == "alp_DynamiteExplosion" || ammo == "Plastic_Explosive_Ammo")
			{
				GetGame().ObjectDelete(this);
				return;
			}
		}	
		
		// Destruição por dano acumulado (HP Crítico)
		if (health < 50) 
		{
			GetGame().ObjectDelete(this);
		}
	}
		
	override bool CanPutInCargo(EntityAI parent) { return false; }
	override bool CanPutIntoHands(EntityAI parent) { return false; }
};

// --- Variantes de Tamanho ---

class alp_WoodenCrateBig : alp_WoodenCrate_Base {}
class alp_WoodenCrateSmall : alp_WoodenCrate_Base {}