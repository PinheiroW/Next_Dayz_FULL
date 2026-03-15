/**
 * @class   Pelt_Base
 * @brief   Gerencia a manutenção de peles animais integrando ao Perk de Caça
 * Auditado em: 2026 - Foco em Progressão de Habilidade
 */
modded class Pelt_Base
{	
	override bool CanBeRepairedByCrafting()
	{
		// 1. Verifica a configuração global do servidor
		bool isRepairDisabled = GetND().GetRP().GetPerkHunting().PeltIsNotRepairable;
		
		if ( !isRepairDisabled )
		{
			return super.CanBeRepairedByCrafting();
		}

		// 2. Lógica de RPG: Se o reparo estiver desativado globalmente, 
		// um mestre caçador ainda pode ser capaz de reparar?
		// Exemplo de implementação futura:
		/*
		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (player && player.GetStatPerkHunting().Get() > 0.8) // 80% de XP
		{
			return true; 
		}
		*/

		return false;
	}

	// 3. Impede o uso de peles completamente destruídas em receitas de craft
	override bool CanPutAsAttachment(EntityAI parent)
	{
		if ( IsDamageDestroyed() )
			return false;
			
		return super.CanPutAsAttachment(parent);
	}
}