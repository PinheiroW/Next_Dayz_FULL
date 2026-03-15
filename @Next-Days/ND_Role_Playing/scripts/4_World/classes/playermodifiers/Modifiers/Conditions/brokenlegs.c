/**
 * @class   BrokenLegsMdfr
 * @brief   Sincroniza o estado de perna quebrada com o sistema RPG
 * Auditado em: 2024 - Foco em Segurança de Execução e Estabilidade
 */
modded class BrokenLegsMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Garante que o player e o componente RPG existem antes de definir o estado
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.BROKEN_LEGS);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante que o player e o componente RPG existem antes de remover o estado
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.BROKEN_LEGS);
		}
	}
};