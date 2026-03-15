/**
 * alp_accescard.c
 * * ENTIDADE DE ITEM (CARTÕES DE ACESSO) - Módulo ND_MISSIONS
 * Gerencia a leitura de chaves eletrônicas baseadas em IDs configurados no Config.cpp.
 */

class alp_AccessCard_Base extends ItemBase
{
	/**
	 * Obtém o ID numérico do cartão definido no arquivo de configuração do item.
	 * @return int ID da chave para validação em consoles/portas.
	 */
	int GetKeyID()
	{
		int value = 0;
		string subclass_path = "CfgVehicles " + GetType() + " keyid";
		
		// Verifica se o parâmetro existe no config antes de tentar ler
		if (GetGame().ConfigIsExisting(subclass_path))
		{
			value = GetGame().ConfigGetInt(subclass_path);
		}
		
		return value;
	}
}

// Definições de classes para os diferentes níveis de acesso
class alp_AccessCardRed    extends alp_AccessCard_Base {}
class alp_AccessCardBlue   extends alp_AccessCard_Base {}
class alp_AccessCardGreen  extends alp_AccessCard_Base {}
class alp_AccessCardYellow extends alp_AccessCard_Base {}