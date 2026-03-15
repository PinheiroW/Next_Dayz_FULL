/**
 * @class   ModifiersManager
 * @brief   Gerencia o registro de modificadores no motor Enfusion
 * Auditado em: 2024 - Foco em Limpeza de Redundâncias e Registro Seguro
 */
modded class ModifiersManager
{
	override void Init()
	{
		// Chama o Init original do DayZ para carregar todos os modificadores vanilla
		super.Init();
		
		// --- REGISTRO DE MODIFICADORES CUSTOMIZADOS (NEXT DAYS) ---
		
		// Gerenciamento de Metabolismo e Estados
		AddModifier(new alpAnabolicMdfr);
		AddModifier(new alpTirednessMdfr);
		AddModifier(new alpSleepingMdfr);		
		AddModifier(new alpDrunkennessMdfr);	
		
		// Imunidade e Doenças Customizadas
		AddModifier(new alpImmunityInfluenzaMdfr);
		
		// Registro de Estágios de Radiação (Classes customizadas detectadas em auditorias anteriores)
		AddModifier(new alpRadiationSick1Mdfr);
		AddModifier(new alpRadiationSick2Mdfr);
		AddModifier(new alpRadiationSick3Mdfr);
		AddModifier(new alpRadiationSick4Mdfr);

		// NOTA: BoneRegenMdfr e BrokenArmsMdfr NÃO devem ser adicionados aqui 
		// se forem apenas "modded class", pois o super.Init() já os registra.
	}
}