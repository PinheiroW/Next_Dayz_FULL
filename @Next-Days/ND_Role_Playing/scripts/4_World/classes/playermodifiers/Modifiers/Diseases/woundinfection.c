/**
 * @class   WoundInfectStage1Mdfr / WoundInfectStage2Mdfr
 * @brief   Sincroniza os estágios de infecção de ferida vanilla com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Transição e Segurança de Ponteiros
 */

modded class WoundInfectStage1Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Verifica se o player e o componente RPG existem
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.WOUNDINFECTION_1);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		if (!player) return;

		// Verifica se está evoluindo para o estágio 2 para evitar 'flicker' na UI
		ModifiersManager manager = player.GetModifiersManager();
		bool evolvingToStage2 = (manager && manager.IsModifierActive(eModifiers.MDF_WOUND_INFECTION2));

		if (player.GetRP() && !evolvingToStage2)
		{
			player.GetRP().UnsetDisease(alpDiseases.WOUNDINFECTION_1);
		}
	}	
}

modded class WoundInfectStage2Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.WOUNDINFECTION_2);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.WOUNDINFECTION_2);
		}
	}	
}