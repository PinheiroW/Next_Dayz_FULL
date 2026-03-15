/**
 * @class   alpAbilityStatRadResistance
 * @brief   Componente de Interface (GUI) para Resistência à Radiação
 * Auditado em: 2026 - Foco em Precisão Visual e Estabilidade de Sincronização
 */
class alpAbilityStatRadResistance extends alpAbilityStat
{
	override void SetValueProgres(float progress)
	{
		// 1. Atualiza a barra de progresso (XP) recebida do sistema StatsEnhanced
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		// 2. Proteção de Sincronização e Nulidade
		if (player && player.GetSyncData())
		{
			auto syncElem = player.GetSyncData().GetElement(alpRPelements.RAD_RESIST);
			if (!syncElem) return; // Aguarda a próxima atualização de rede

			// 3. Correção de Divisão Inteira: Convertendo para float
			float level = (float)syncElem.GetValue();		
			int cap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();
			
			if (cap > 0)
			{
				// Calcula a porcentagem do nível atual em relação ao máximo
				float rate = (level / cap) * 100;	
				
				// 4. Define o nível visual (geralmente altera a cor ou preenchimento do ícone)
				SetValueLevel(rate);
			}
		}
	}	
}