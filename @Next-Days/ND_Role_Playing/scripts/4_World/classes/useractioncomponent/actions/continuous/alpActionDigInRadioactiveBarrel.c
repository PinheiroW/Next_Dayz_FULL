/**
 * @class   alpActionDigInRadioactiveBarrel
 * @brief   Ação de escavar em barris radioativos com bônus de reputação Next Days
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Alinhamento Neutro
 */
modded class alpActionDigInRadioactiveBarrel: ActionContinuousBase
{	
	override float GetReputationBonus(PlayerBase player)
	{
		float rep = 0;

		// 1. Validação do Jogador e do Sistema de RPG
		if (player && player.GetRP() && GetND() && GetND().GetRP())
		{
			// 2. Determinação do bônus baseada no alinhamento real
			if (player.GetRP().IsHero())
			{
				rep = GetND().GetRP().GetReputationBonusDigInRadioactiveBarrel(ALP_RP_HERO);
			}
			else if (player.GetRP().IsBandit())
			{
				rep = GetND().GetRP().GetReputationBonusDigInRadioactiveBarrel(ALP_RP_BANDIT);
			}
			else // Caso para Sobreviventes Neutros / Civis
			{
				// Geralmente metade do bônus de Herói ou um valor fixo de 'Sucateiro'
				rep = 5.0; 
			}
		}
		
		return rep;
	}
}