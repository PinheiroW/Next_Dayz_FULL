/**
 * @class   alpSync
 * @brief   Gerenciador Central de Sincronização de Stats e RPG
 * Auditado em: 2026 - Foco em Limpeza de Código e Integridade de Registro
 */
modded class alpSync
{
	override void Init()
	{
		// 1. Inicializa a base e garante que o alp_Player esteja pronto
		super.Init();

		if (!alp_Player) return;

		// --- REGISTRO DE STATS (Básicas/Bitmask) ---
		
		RegisterElement( new alpStatsStamina( alp_Player ) );
		RegisterElement( new alpStatsReputation( alp_Player ) );
		RegisterElement( new alpStatsReputationRole( alp_Player ) );		
		RegisterElement( new alpStatsHunting( alp_Player ) );
		RegisterElement( new alpStatsRadResistance( alp_Player ) );
		RegisterElement( new alpStatsToxicResistance( alp_Player ) );
		RegisterElement( new alpStatsTendencyTiredness( alp_Player ) );
		RegisterElement( new alpStatsDiseases( alp_Player ) );

		// --- REGISTRO DE STATS ENHANCED (Floats/Progresso/Barras) ---
		
		RegisterElementEnhanced( new alpStatsEnhancedStaminaProgress(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedReputationProgress(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedReputationScore(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedHuntingProgres(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedRadResitProgres(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedToxicResistanceProgres(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedFatigue(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedTemperature(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedRadiationSickStage(alp_Player) );
		
		// Nota: As versões "Saved" foram removidas pois a persistência 
		// agora é tratada internamente pelos componentes de Stat do PlayerBase.
	}
}