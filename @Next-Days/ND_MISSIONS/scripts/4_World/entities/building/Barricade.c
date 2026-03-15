/**
 * Barricade.c
 * * ENTIDADE DE MUNDO (BARRICADA DESTRUTÍVEL) - Módulo ND_MISSIONS
 * Define a resistência e as condições de destruição de barreiras táticas.
 */

class alp_Barricade : House
{
	void alp_Barricade()
	{
		// Inicialização da entidade
	}

	/**
	 * Evento disparado quando o objeto recebe qualquer tipo de dano.
	 */
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		// Executa a lógica nativa de recebimento de dano
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if ( !GetGame().IsServer() ) return;

		float health = GetHealth("", "Health");
		float damage = damageResult.GetDamage("", "Health");
		
		/**
		 * Lógica de Arrombamento (Breaching):
		 * Se o dano for por explosão pesada (Dinamite ou Explosivo Plástico),
		 * a barricada é removida instantaneamente.
		 */
		if ( damageType == DT_EXPLOSION && damage > 200 )
		{
			if ( ammo == "alp_DynamiteExplosion" || ammo == "Plastic_Explosive_Ammo" )
			{
				GetGame().ObjectDelete( this );
				return;
			}
		}	
		
		/**
		 * Resistência Estrutural:
		 * Se a vida total cair abaixo de um limiar crítico (50), a estrutura colapsa.
		 */
		if ( health < 50 ) 
		{
			GetGame().ObjectDelete( this );
		}
	}
}