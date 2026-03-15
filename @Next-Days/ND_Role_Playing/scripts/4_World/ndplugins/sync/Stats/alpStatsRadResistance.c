/**
 * @class   alpStatsRadResistance
 * @brief   Sincroniza o nível da Skill de Resistência à Radiação
 * Auditado em: 2026 - Foco em Escalabilidade e Prevenção de Null Pointer
 */
class alpStatsRadResistance extends alpStatsBase
{
	void alpStatsRadResistance(PlayerBase player)
	{
		alp_Type = alpRPelements.RAD_RESIST;
		
		// 1. ESCALABILIDADE: Aumentado para 8 bits (0-255).
		// Garante que, se você expandir o sistema de níveis no futuro,
		// a sincronização de rede não "quebre" os valores.
		NUM_OF_BITS = 8; 
	}
	
	override void Update()
	{
		// 2. BLINDAGEM: Verifica se o objeto de estatística existe antes de acessar o valor
		if (alp_Player && alp_Player.GetStatPerkRadiationResistance())
		{
			alp_Value = alp_Player.GetStatPerkRadiationResistance().Get();
		}
		else
		{
			alp_Value = 0; // Failsafe para evitar lixo de memória
		}
	}
}