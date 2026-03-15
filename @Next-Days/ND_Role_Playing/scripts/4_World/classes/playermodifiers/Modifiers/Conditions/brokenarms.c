/**
 * @class   BrokenArmsMdfr
 * @brief   Sincroniza o estado de braço quebrado com o sistema RPG
 * Auditado em: 2024 - Foco em Segurança de Ponteiros
 */
modded class BrokenArmsMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);

		// Segurança: Verifica se o player e o componente RPG existem antes de prosseguir
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.BROKEN_ARMS);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Verifica se o player e o componente RPG existem antes de remover o estado
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.BROKEN_ARMS);
		}
	}
};