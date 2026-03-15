modded class MissionBase extends MissionBaseWorld
{
    /**
     * @fn		CreateScriptedMenuALP
     * @brief	Fábrica de menus para o sistema Next-Days.
     * Responsável por instanciar os menus de Rumores e Exames Médicos.
     */
    override UIScriptedMenu CreateScriptedMenuALP(int id)
    {
        // Tenta buscar o menu nas classes base primeiro
        UIScriptedMenu menu = super.CreateScriptedMenuALP(id);	
        
        // Se o menu ainda não foi criado pelas classes superiores, verificamos os IDs do Next-Days
        if (!menu)
        {
            switch (id)
            {
                case ALP_MENU_SPREADRUMOUR:
                {
                    menu = new alpSpreadRumoursMenu();
                    break;
                }

                case ALP_MENU_EXAMINATION:
                {
                    menu = new alpMedicExaminationMenu();
                    break;
                }
            }
        }
        
        // Retorna a instância do menu (ou null se o ID não pertencer a este sistema)
        return menu;
    }
}