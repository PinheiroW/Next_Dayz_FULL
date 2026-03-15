/**
 * alpClientData.c
 * * ESTRUTURA DE DADOS DO CLIENTE - Módulo ND_MISSIONS
 * Armazena informações temporárias de missões e sincronização de tempo.
 */

class alpClientData
{
	int date;
	ref map<int, int> RegisteredPrivateMissions; // Referência mantida conforme original
	
	void alpClientData(int actualdate)
	{
		date = actualdate;
		
		// CORREÇÃO: Inicialização obrigatória para evitar Null Pointer Exception
		RegisteredPrivateMissions = new map<int, int>();
	}
}