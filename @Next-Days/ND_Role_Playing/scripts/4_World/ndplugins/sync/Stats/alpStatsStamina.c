/**
 * @class   alpStatsStamina
 * @brief   Sincroniza o nível da Skill de Stamina
 * Auditado em: 2026 - Foco em Padronização de Bits e Estabilidade
 */
class alpStatsStamina extends alpStatsBase
{
	void alpStatsStamina(PlayerBase player)
	{
		alp_Type = alpRPelements.STAMINA;
		
		// 1. PADRONIZAÇÃO: Aumentado de 6 para 8 bits.
		// Segue o padrão estabelecido para Hunting e RadResistance.
		// Permite até 255 níveis, garantindo expansões futuras do mod.
		NUM_OF_BITS = 8; 
	}
	
	override void Update()
	{
		// 2. FILTRO DE SEGURANÇA:
		// Verifica se o player e o componente específico de Stamina existem.
		if (alp_Player && alp_Player.GetStatPerkStamina())
		{
			alp_Value = alp_Player.GetStatPerkStamina().Get();
		}
		else
		{
			// Caso o sistema ainda esteja carregando, define 0 para evitar crash.
			alp_Value = 0;
		}
	}
}