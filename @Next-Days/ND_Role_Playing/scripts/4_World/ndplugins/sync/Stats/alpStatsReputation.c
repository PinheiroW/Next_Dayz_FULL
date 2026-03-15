/**
 * @class   alpStatsReputation
 * @brief   Sincroniza o valor de Reputação (Herói/Bandido)
 * Auditado em: 2026 - Foco em Integridade de Dados e Performance de Rede
 */
class alpStatsReputation extends alpStatsBase
{
	void alpStatsReputation(PlayerBase player)
	{
		alp_Type = alpRPelements.REPUTATION;
		
		// 1. ESCALABILIDADE: Aumentado para 16 bits.
		// Permite valores de 0 a 65535. 
		// Nota: Se você usa reputação negativa, o sistema de sincronização de bits 
		// da base deve estar preparado para 'signed ints', caso contrário, 
		// manteremos o AbsInt apenas se a lógica de 'Hero/Bandit' for tratada por outro Stat.
		NUM_OF_BITS = 16; 
	}
	
	override void Update()
	{
		// 2. DEFESA E LÓGICA:
		if (alp_Player && alp_Player.GetStatPerkReputation())
		{
			// Removido AbsInt para que o cliente receba a polaridade (Positivo/Negativo)
			// Se o seu sistema de sincronização de bits (alpStatsBase) não suportar negativos,
			// a recomendação é sincronizar o valor absoluto e ter um Stat separado para a Facção.
			int currentReputation = alp_Player.GetStatPerkReputation().Get();
			
			if (alp_Value != currentReputation)
			{
				alp_Value = currentReputation;
				
				// 3. PERFORMANCE: Só atualiza a Identidade se o valor realmente mudou
				if (alp_Player.GetIdentity())
				{
					// O motor do DayZ espera um int positivo para o Level
					alp_Player.GetIdentity().SetPlayerLevel(Math.AbsInt(alp_Value));
				}
			}
		}
		else
		{
			alp_Value = 0;
		}
	}
}