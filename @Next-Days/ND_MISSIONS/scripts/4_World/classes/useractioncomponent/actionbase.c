/**
 * actionbase.c
 * * MODDED BASE CLASS (AÇÕES GERAIS) - Módulo ND_MISSIONS
 * Define utilitários globais para todas as ações do jogo.
 */

modded class ActionBase : ActionBase_Basic
{	
	/**
	 * Verifica se uma entidade (máscara) está na lista de exceções do servidor.
	 * Itens na lista de exceção NÃO impedem o consumo de alimentos/líquidos.
	 */
	bool IsExceptionsALP(EntityAI mask)
	{
		if (!mask) return true; // Se não há máscara, não há obstrução

		// Obtém o nome da classe do item (ex: "SurgicalMask", "TacticalGlass")
		string type = mask.GetType();
		
		// Acessa as configurações globais do mod Next-Days
		auto playerOptions = GetND().GetRP().GetPlayerOptions();
		
		if ( playerOptions && playerOptions.ExceptionsInMask )
		{
			// Realiza a busca na lista configurada no servidor
			int find = playerOptions.ExceptionsInMask.Find( type );
			
			// Se encontrou o index (>= 0), o item é uma exceção permitida
			if ( find >= 0 )
			{
				return true;
			}
		}
		
		// Por padrão, se não estiver na lista, a máscara é considerada obstrutiva
		return false;
	}
};