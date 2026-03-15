/**
 * @class   alpAbilityStatHunting
 * @brief   Interface Visual (GUI) para a Skill de Caça
 * Auditado em: 2026 - Foco em Precisão Matemática e Performance de UI
 */
class alpAbilityStatHunting extends alpAbilityStat
{
	override void SetValueProgres(float progress)
	{
		// 1. Atualiza a barra de XP (0-100) vinda do StatsEnhanced
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.GetSyncData()) return;

		auto syncElem = player.GetSyncData().GetElement(alpRPelements.HUNTING);
		if (!syncElem) return;

		// 2. CORREÇÃO MATEMÁTICA: Forçando float para evitar divisão inteira
		float level = (float)syncElem.GetValue();		
		int cap = GetND().GetRP().GetPerkHuntingLevelCup();
		
		if (cap > 0)
		{
			// Calcula a proporção do nível atual em relação ao máximo
			float rate = (level / cap) * 100;	
			
			// 3. Atualiza o preenchimento visual do ícone ou nível
			SetValueLevel(rate);
		}
	}	
}