/**
 * @class   CholeraMdfr
 * @brief   Sincroniza a cólera vanilla com o sistema RPG
 * Auditado em: 2024 - Foco em Estabilidade de Ponteiros
 */
modded class CholeraMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Verifica a validade do player e do componente RPG antes de acessar
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.CHOLERA);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante integridade durante a remoção da doença (Ex: Cura ou Morte)
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.CHOLERA);
		}
	}
};