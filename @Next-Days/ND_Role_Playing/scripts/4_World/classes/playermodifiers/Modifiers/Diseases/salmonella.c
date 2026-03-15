/**
 * @class   SalmonellaMdfr
 * @brief   Sincroniza a salmonela vanilla com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Ponteiros e Segurança
 */
modded class SalmonellaMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Verifica se o player e o componente RPG existem antes de prosseguir
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.SALMONELLA);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante integridade durante a limpeza do modificador (Ex: Cura ou Morte)
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.SALMONELLA);
		}
	}
};