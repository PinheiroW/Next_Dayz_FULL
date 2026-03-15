/**
 * @class   Inventory
 * @brief   Gerencia a exibição de elementos do inventário (GUI)
 * Auditado em: 2026 - Foco em Estabilidade de Inicialização
 */
modded class Inventory: LayoutHolder
{
	override void UpdateSpecialtyMeter()
	{
		// 1. BLINDAGEM: Verifica se o sistema de RPG e as opções estão prontos
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPerksOptions())
		{
			// 2. Se as habilidades customizadas estiverem ativas, ocultamos o painel vanilla
			if (GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills)
			{
				if (m_SpecializationPanel)
				{
					m_SpecializationPanel.Show(false);
					return; // Interrompe para não executar o super
				}
			}
		}
		
		// 3. FALLBACK: Se o sistema customizado estiver desligado ou não carregado, 
		// permite que o DayZ use a lógica original.
		super.UpdateSpecialtyMeter();
	}
}