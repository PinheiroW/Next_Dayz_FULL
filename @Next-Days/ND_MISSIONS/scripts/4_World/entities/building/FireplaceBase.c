/**
 * FireplaceBase.c
 * * MODDED ENTITY (LAREIRAS E FOGUEIRAS) - Módulo ND_MISSIONS
 * Introduz suporte para fogueiras perpétuas em zonas de missão ou acampamentos.
 */

modded class FireplaceBase extends ItemBase
{
	/**
	 * Se verdadeiro, a fogueira não consome combustível (lenha/gravetos).
	 * Útil para ambientação de missões e acampamentos permanentes.
	 */
	bool alp_PermaFire = false;
	
	/**
	 * Gerencia o gasto de combustível da fogueira.
	 */
	override protected void SpendFireConsumable(float amount)
	{
		if (alp_PermaFire)
		{
			// Em modo perpétuo, apenas recalculamos o estado visual
			// sem subtrair a quantidade do combustível.
			CalcAndSetQuantity();
		}
		else 
		{
			// Segue o comportamento padrão do DayZ (consumo normal)
			super.SpendFireConsumable(amount);
		}
	}
}