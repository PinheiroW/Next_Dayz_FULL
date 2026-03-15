/**
 * DayzGame.c
 * * GERENCIADOR DE CLASSES DE PERSONAGENS - Módulo ND_MISSIONS
 * Filtra prefixos técnicos e impede a exibição de NPCs/Bots nos menus de seleção.
 */

modded class DayZGame extends CGame
{
	// --- CRIAÇÃO DE JOGADOR PADRÃO ---
	override string CreateDefaultPlayer()
	{	
		string child_name = super.CreateDefaultPlayer();
		
		// CORREÇÃO: Necessário atribuir o resultado do Replace à variável
		if (child_name.Contains("alp_")) 
		{
			child_name = child_name.Replace("alp_", "");
		}
		
		if (child_name.Contains("Bot")) 
		{
			child_name = child_name.Replace("Bot", "Survivor");
		}
		
		return child_name;
	}
	
	// --- CRIAÇÃO DE JOGADOR ALEATÓRIO ---
	override string CreateRandomPlayer()
	{
		string child_name = super.CreateRandomPlayer();
		
		// CORREÇÃO: Atribuição correta para garantir a limpeza do nome
		if (child_name.Contains("alp_")) 
		{
			child_name = child_name.Replace("alp_", "");
		}
		
		if (child_name.Contains("Bot")) 
		{
			child_name = child_name.Replace("Bot", "Survivor");
		}
		
		return child_name;		
	}
	
	// --- LISTAGEM DE PERSONAGENS DISPONÍVEIS NO MENU ---
	override TStringArray ListAvailableCharacters()
	{
		array<string> char_class_names = super.ListAvailableCharacters();
		array<string> new_char_class_names = new array<string>;
		
		for (int i = 0; i < char_class_names.Count(); i++)
		{
			string name = char_class_names.Get(i);
			
			// Mantém na lista apenas personagens que NÃO são técnicos (sem prefixo alp_)
			if (!name.Contains("alp_")) 
			{
				new_char_class_names.Insert(name);
			}
		}
				
		return new_char_class_names;
	}
}