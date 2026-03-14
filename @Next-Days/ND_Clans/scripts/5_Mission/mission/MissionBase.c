modded class MissionBase
{
	// Método responsável por interceptar a criação de menus customizados do mod
 	override UIScriptedMenu CreateScriptedMenuALP(int id)
	{
		// 1. Tenta buscar o menu nas classes base ou em outros plugins
		UIScriptedMenu menu = super.CreateScriptedMenuALP(id);	
		
		if (!menu)
		{
			// 2. Se o ID corresponder ao menu de Clãs, instancia a classe da UI
			if (id == ALP_MENU_MANAGE_PLOTPOLE)
			{	
				menu = new alpPlotPoleMenu;			
			}				
		}		
		
		return menu;
	}
}