/**
 * ModifiersManager.c
 * * GERENCIADOR DE MODIFICADORES - Módulo ND_MISSIONS
 * Registra todos os modificadores customizados (doenças, radiação e curas) na engine.
 */

modded class ModifiersManager
{
	override void Init()
	{
		// Inicializa os modificadores vanilla do DayZ primeiro
		super.Init();
		
		// --- Modificadores de Ambiente e Cura ---
		AddModifier(new alpRadiationMdfr);
		AddModifier(new alpRadiationBlockMdfr);	
		
		// --- Modificadores de Estágios da Doença de Radiação ---
		AddModifier(new alpRadiationSick1Mdfr);
		AddModifier(new alpRadiationSick2Mdfr);
		AddModifier(new alpRadiationSick3Mdfr);
		AddModifier(new alpRadiationSick4Mdfr);
		AddModifier(new alpRadiationSick5Mdfr);
	}
}; // Adicionado ponto e vírgula obrigatório