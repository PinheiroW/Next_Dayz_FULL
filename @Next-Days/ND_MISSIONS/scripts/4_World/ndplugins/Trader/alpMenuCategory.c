/**
 * alpMenuCategory.c
 * * TRADER MENU STRUCTURE - Módulo ND_MISSIONS (Trader)
 * Gerencia a hierarquia de categorias e a lógica de seleção de menus.
 */

class alpMenuCategory 
{
	protected int alp_LastSelectedMenu;
	protected int alp_CategoryID;
	protected string alp_Name;
	
	// Mapa recursivo para submenus: Chave (Nome) -> Valor (Objeto Categoria)
	protected ref map<string, ref alpMenuCategory> alp_Menu = new map<string, ref alpMenuCategory>;

	// --- Gerenciamento de Hierarquia ---

	/**
	 * Adiciona uma subcategoria ao menu atual.
	 * Se já existir, retorna a referência existente.
	 */
	alpMenuCategory AddSubMenu(string name, int id)
	{
		alpMenuCategory submenu;
		
		if (!alp_Menu.Find(name, submenu))
		{
			submenu = new alpMenuCategory();
			submenu.alp_CategoryID = id;
			submenu.alp_Name = name;
			alp_Menu.Insert(name, submenu);
		}
		return submenu;
	}
	
	// --- Lógica de Seleção ---

	/**
	 * Retorna o índice do item atualmente selecionado, garantindo que esteja dentro do range.
	 */
	int GetSelected()
	{
		int index = -1;
		if (alp_Menu.Count() > 0)
		{		
			index = Math.Min(alp_LastSelectedMenu, alp_Menu.Count() - 1);	
		}
		return index;
	}

	void SetSelected(int id)
	{
		alp_LastSelectedMenu = id;
	}	
	
	/**
	 * Retorna o mapa de submenus contido dentro da categoria selecionada.
	 */
	ref map<string, ref alpMenuCategory> GetSelectedSubMenu()
	{
		if (alp_Menu.Count() > 0)
		{
			int index = Math.Min(alp_LastSelectedMenu, alp_Menu.Count() - 1);						
			alpMenuCategory subMenu = alp_Menu.GetElement(index);
			alp_LastSelectedMenu = index; // Atualiza o cache de seleção
			return subMenu.alp_Menu;						
		}
		return null;
	}	
	
	/**
	 * Retorna o objeto alpMenuCategory do item selecionado.
	 */
	alpMenuCategory GetSelectedMenu()
	{
		if (alp_Menu.Count() > 0)
		{
			int index = Math.Min(alp_LastSelectedMenu, alp_Menu.Count() - 1);
			alpMenuCategory subMenu = alp_Menu.GetElement(index);
			alp_LastSelectedMenu = index;
			return subMenu;						
		}
		
		return null;		
	}	

	// --- Getters e Setters de Identidade ---

	int GetCategoryID()
	{
		return alp_CategoryID;
	}

	void SetCategoryID(int id)
	{
		alp_CategoryID = id;
	}

	string GetName()
	{
		return alp_Name;
	}
}