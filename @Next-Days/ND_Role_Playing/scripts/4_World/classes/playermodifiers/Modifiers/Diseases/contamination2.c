/**
 * @class   ContaminationStage2Mdfr
 * @brief   Sincroniza o estágio 2 de contaminação química vanilla com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Ponteiros e Segurança de VM
 */
modded class ContaminationStage2Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);

		// Segurança: Verifica se o player e o componente RPG existem antes de definir o estado
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.POISONING_CHEMICAL_2);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante integridade durante a remoção ou transição para o estágio 3
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.POISONING_CHEMICAL_2);
		}
	}
};