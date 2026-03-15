/**
 * @class   alpStatsToxicResistance
 * @brief   Sincroniza o nível da Skill de Resistência Tóxica/Química
 * Auditado em: 2026 - Foco em Escalabilidade e Segurança de Ponteiros
 */
class alpStatsToxicResistance extends alpStatsBase
{
	void alpStatsToxicResistance(PlayerBase player)
	{
		alp_Type = alpRPelements.TOXIC_RESIST;
		
		// 1. ESCALABILIDADE: Aumentado de 6 para 8 bits.
		// Permite níveis de 0 a 255. Mantém a simetria com as 
		// outras resistências do sistema Next Days.
		NUM_OF_BITS = 8; 
	}
	
	override void Update()
	{
		// 2. BLINDAGEM: Verifica se o player e o componente de stat estão prontos
		if (alp_Player && alp_Player.GetStatPerkToxicResistance())
		{
			alp_Value = alp_Player.GetStatPerkToxicResistance().Get();
		}
		else
		{
			// Failsafe para evitar lixo de memória durante o carregamento do player
			alp_Value = 0;
		}
	}
}