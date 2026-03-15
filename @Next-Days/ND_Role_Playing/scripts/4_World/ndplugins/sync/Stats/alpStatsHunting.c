/**
 * @class   alpStatsHunting
 * @brief   Sincroniza o nível da Skill de Caça (Hunting)
 * Auditado em: 2026 - Foco em Escalabilidade e Estabilidade de Stats
 */
class alpStatsHunting extends alpStatsBase
{
	void alpStatsHunting(PlayerBase player)
	{
		alp_Type = alpRPelements.HUNTING;
		
		// 1. ESCALABILIDADE: Alterado de 6 para 8 bits.
		// Permite níveis de 0 a 255. Mesmo que use apenas 20 ou 50 agora,
		// você não precisará mexer aqui se decidir expandir o sistema de progressão.
		NUM_OF_BITS = 8; 
	}
	
	override void Update()
	{
		// 2. DEFESA DE PONTEIRO: Verifica se o player e o sistema de stats estão prontos
		if (alp_Player && alp_Player.GetStatPerkHunting())
		{
			alp_Value = alp_Player.GetStatPerkHunting().Get();
		}
		else
		{
			alp_Value = 0;
		}
	}
}