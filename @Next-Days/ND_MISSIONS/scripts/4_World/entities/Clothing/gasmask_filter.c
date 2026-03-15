/**
 * gasmask_filter.c
 * * MODDED ENTITY (FILTROS DE MÁSCARA) - Módulo ND_MISSIONS
 * Ajusta a taxa de degradação dos filtros com base nas configurações de radiação.
 */

modded class GasMask_Filter : ItemBase
{
	/**
	 * Retorna a proporção de dano que o filtro recebe por quantidade de ar consumida.
	 * Calculado como: Dano à Vida / Consumo de Quantidade.
	 */
	override float GetFilterDamageRatio() 
	{
		float ratio = super.GetFilterDamageRatio();
		
		// Tenta obter o ajuste dinâmico do sistema Next-Days
		float adjusted = GetND().GetMS().GetOptionsRadiation().FilterDamageRatio;
		
		if ( adjusted > 0 ) 
		{
			return adjusted;		
		} 
		
		return ratio;
	}
}

modded class GasMask_Filter_Improvised : GasMask_Filter
{
	/**
	 * Filtros improvisados geralmente possuem uma durabilidade muito menor.
	 */
	override float GetFilterDamageRatio() 
	{
		float ratio = super.GetFilterDamageRatio();
		
		// Tenta obter o ajuste para filtros improvisados
		float adjusted = GetND().GetMS().GetOptionsRadiation().ImprovisedFilterDamageRatio;
		
		if ( adjusted > 0 ) 
		{
			return adjusted;		
		} 
		
		return ratio;	
	}
}