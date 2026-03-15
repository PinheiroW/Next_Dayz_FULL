/**
 * @class   FeverMdfr
 * @brief   Sincroniza o estado de febre vanilla com o sistema RPG do Next Days
 * Auditado em: 2024 - Foco em Estabilidade de Cadeia de Ponteiros
 */
modded class FeverMdfr: ModifierBase
{
	override bool ActivateCondition(PlayerBase player)
	{
		// Segurança: Verifica se o plugin central e as opções de RPG estão acessíveis
		// Isso evita Null Pointer Exceptions se o mod estiver desativado ou carregando.
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetDiseases())
		{
			if (!GetND().GetRP().GetDiseases().FeverActive)
				return false;
		}
		
		// Se passar na verificação acima ou se o plugin não estiver pronto, 
		// segue a condição nativa do DayZ.
		return super.ActivateCondition(player);
	}	
	
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Segurança: Garante que o player e o componente RPG existem antes de definir o estado
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.FEVER);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Segurança: Garante que o player e o componente RPG existem antes de remover o estado
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.FEVER);
		}
	}	
}