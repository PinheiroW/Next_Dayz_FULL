/**
 * @class   BrainDiseaseMdfr
 * @brief   Sincroniza a doença cerebral vanilla (Kuru) com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Ponteiros e Segurança de Memória
 */
modded class BrainDiseaseMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);

		// Segurança: Verifica se o player e o componente RPG existem antes de prosseguir
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.BRAINDISEASE);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante integridade durante a limpeza do modificador (Ex: Morte ou Logoff)
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.BRAINDISEASE);
		}
	}
};