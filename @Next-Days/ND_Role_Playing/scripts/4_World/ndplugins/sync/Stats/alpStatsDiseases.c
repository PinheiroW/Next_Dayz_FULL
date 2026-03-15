/**
 * @class   alpStatsDiseases
 * @brief   Gerencia a sincronização de bitmask das doenças do jogador
 * Auditado em: 2026 - Foco em Integridade de Bits e Segurança de Memória
 */
class alpStatsDiseases extends alpStatsBase
{
	void alpStatsDiseases(PlayerBase player)
	{
		alp_Type = alpRPelements.DISEASES;
		
		// 1. EXPANSÃO DE BITS: Alterado de 17 para 32 bits.
		// O enum alpDiseases atual vai até 65536 (17 bits), mas usar 32 bits 
		// evita overflow se você adicionar novas doenças e mantém alinhamento de memória.
		NUM_OF_BITS = 32; 
	}
	
	override void Update()
	{
		// 2. SAFETY CHECK: Garante que o player e o módulo RP existem antes de ler o valor
		if (alp_Player && alp_Player.GetRP())
		{
			alp_Value = alp_Player.GetRP().GetDiseases();
		}
		else
		{
			alp_Value = 0; // Se falhar, assume nenhuma doença para evitar lixo na memória
		}
	}
}