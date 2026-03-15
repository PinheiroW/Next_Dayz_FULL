/**
 * @class   alpAbilityStatToxicResistance
 * @brief   Interface Visual (GUI) para Resistência Tóxica/Química
 * Auditado em: 2026 - Foco em Precisão Visual e Segurança de Sincronização
 */
class alpAbilityStatToxicResistance extends alpAbilityStat
{
	override void SetValueProgres(float progress)
	{
		// 1. Atualiza a barra de experiência (XP) vinda do StatsEnhanced
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		// 2. Proteção de Sincronização: Garante que o player e os dados existam
		if (player && player.GetSyncData())
		{
			auto syncElem = player.GetSyncData().GetElement(alpRPelements.TOXIC_RESIST);
			if (!syncElem) return; // Aguarda a sincronização para evitar crash

			// 3. CORREÇÃO: Forçando conversão para float para permitir decimais
			float level = (float)syncElem.GetValue();		
			int cap = GetND().GetRP().GetPerkToxicResistanceLevelCup();
			
			// 4. Prevenção de erro matemático de divisão por zero
			if (cap > 0)
			{
				// Calcula a porcentagem do nível atual em relação ao limite total
				float rate = (level / cap) * 100;	
				
				// Atualiza o preenchimento visual do ícone de nível (0-100%)
				SetValueLevel(rate);
			}
		}
	}	
}