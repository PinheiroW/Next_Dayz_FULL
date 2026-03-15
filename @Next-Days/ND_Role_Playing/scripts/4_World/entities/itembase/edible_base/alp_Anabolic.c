/**
 * @class   alp_Anabolic
 * @brief   Item de injeção anabolizante para restauração instantânea de Stamina
 * Auditado em: 2026 - Foco em Estabilidade de Modificadores e Segurança de Ponteiros
 */
class alp_Anabolic: Epinephrine
{
	override void OnApply(PlayerBase player)
	{
		if (!player) return;

		// 1. Restaura a Stamina atual para o máximo permitido pelo peso do jogador
		if (player.GetStaminaHandler())
		{
			player.GetStaminaHandler().SetStamina(100);
		}
		
		// 2. Gerenciamento do Modificador de Status
		// Nota: O modificador rModifiers.MDF_ANABOLIC deve conter a lógica de 
		// redução de fadiga ou aumento de força de transporte (Rough Skill).
		if (player.GetModifiersManager())
		{
			// Verifica se já está ativo para resetar o tempo de duração (Stacking prevention)
			if (player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ANABOLIC))
			{
				player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ANABOLIC);
			}
			
			player.GetModifiersManager().ActivateModifier(rModifiers.MDF_ANABOLIC);
		}
		
		// 3. Efeito Visual/Sonoro (Opcional)
		// Você pode adicionar um som de batimento cardíaco ou efeito de túnel aqui se desejar.
	}
};