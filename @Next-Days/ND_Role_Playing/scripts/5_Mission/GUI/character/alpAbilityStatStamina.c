/**
 * @class   alpAbilityStatStamina
 * @brief   Interface Visual (GUI) para a Habilidade de Stamina
 * Auditado em: 2026 - Foco em Precisão de Cálculo e Estabilidade de UI
 */
class alpAbilityStatStamina extends alpAbilityStat
{
	override void SetValueProgres(float progress)
	{
		// 1. Atualiza a barra de XP/Progresso vinda do StatsEnhanced
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		// 2. Proteção de Sincronização
		if (player && player.GetSyncData())
		{
			auto syncElem = player.GetSyncData().GetElement(alpRPelements.STAMINA);
			if (!syncElem) return; // Aguarda a sincronização dos dados

			// 3. CORREÇÃO: Cast para float para garantir precisão decimal
			float level = (float)syncElem.GetValue();		
			int cap = GetND().GetRP().GetPerkStaminaLevelCup();
			
			// 4. Prevenção de Divisão por Zero
			if (cap > 0)
			{
				// Calcula a porcentagem real do nível em relação ao limite
				float rate = (level / cap) * 100;	
				
				// Atualiza o preenchimento visual do ícone de nível
				SetValueLevel(rate);
			}
		}
	}	
}