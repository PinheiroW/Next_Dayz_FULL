/**
 * @class   PoisoningMdfr
 * @brief   Sincroniza o envenenamento vanilla com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Ponteiros
 */
modded class PoisoningMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Verifica a validade do player e do componente RPG antes de acessar
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.POISONING);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante que não haja tentativa de acesso em ponteiros nulos durante a limpeza
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.POISONING);
		}
	}
};