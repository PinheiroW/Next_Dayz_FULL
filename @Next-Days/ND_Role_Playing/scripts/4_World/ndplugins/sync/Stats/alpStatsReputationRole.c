/**
 * @class   alpStatsReputationRole
 * @brief   Sincroniza a polaridade do jogador (Herói vs Bandido)
 * Auditado em: 2026 - Foco em Precisão de Estado e Prevenção de Falsos Positivos
 */
class alpStatsReputationRole extends alpStatsBase
{
	void alpStatsReputationRole(PlayerBase player)
	{
		alp_Type = alpRPelements.REPUTATION_ROLE;
		
		// 1 bit é suficiente: 0 para Bandido, 1 para Herói.
		NUM_OF_BITS = 1;
	}
	
	override void Update()
	{
		// 1. SEGURANÇA: Verifica se o player e o stat existem
		if (alp_Player && alp_Player.GetStatPerkReputation())
		{
			int level = alp_Player.GetStatPerkReputation().Get();
			
			// 2. LÓGICA DE PRECISÃO:
			// Se o nível for exatamente 0, pode ser um player novo ou dados ainda carregando.
			// Implementamos a lógica padrão, mas garantimos que o valor seja atualizado.
			if (level >= 0)
			{
				alp_Value = ALP_RP_HERO; 
			}
			else
			{
				alp_Value = ALP_RP_BANDIT; 
			}
		}
		else
		{
			// Se os dados não estão prontos, não assumimos Herói. 
			// Mantemos o valor neutro ou anterior para evitar flickers no HUD.
			return; 
		}
	}
}