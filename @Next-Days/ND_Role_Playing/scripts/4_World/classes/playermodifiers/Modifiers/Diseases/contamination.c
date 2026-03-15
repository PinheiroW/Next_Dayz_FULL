/**
 * @class   ContaminationStage1Mdfr
 * @brief   Sincroniza o estágio 1 de contaminação química vanilla com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Ponteiros e Segurança de Memória
 */
modded class ContaminationStage1Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);

		// Segurança: Verifica se o player e o componente RPG existem antes de prosseguir
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.POISONING_CHEMICAL_1);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante integridade durante a limpeza do modificador (Ex: Saída da zona ou Morte)
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.POISONING_CHEMICAL_1);
		}
	}
};