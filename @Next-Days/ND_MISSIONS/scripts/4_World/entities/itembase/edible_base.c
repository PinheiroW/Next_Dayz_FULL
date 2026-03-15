/**
 * edible_base.c
 * * MODDED ENTITY (CONSUMÍVEIS) - Módulo ND_MISSIONS
 * Integração de bônus de consumo e compatibilidade com Namalsk Survival.
 */

modded class Edible_Base extends ItemBase
{
#ifdef NAMALSK_SURVIVAL	
	/**
	 * Sobrescreve a lógica de consumo para injetar bônus personalizados do Next-Days.
	 */
	override bool Consume(float amount, PlayerBase consumer)
	{
		// Executa a lógica original de consumo (nutrição, hidratação)
		if (super.Consume(amount, consumer)) 
		{
			// Se o consumo for válido e houver um jogador associado
			if (consumer) 
			{
				// Aplica bônus específicos (ex: calor, resistência, buffs de RP)
				consumer.ConsumeBonusesALP(this, amount);
			}			
			return true;
		}
		
		return false;
	}			
#endif			
}