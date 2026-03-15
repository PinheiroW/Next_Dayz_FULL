/**
 * @class   Epinephrine
 * @brief   Modifica a Epinefrina vanilla para restaurar energia (Tiredness) no Next Days
 * Auditado em: 2026 - Foco em Estabilidade de Stats e Balanceamento
 */
modded class Epinephrine
{
	override void OnApply(PlayerBase player)
	{
		// 1. Executa o comportamento vanilla primeiro (Efeito de choque/stamina do DayZ)
		super.OnApply(player);

		if (!player || !GetGame().IsServer()) return;

		// 2. Validação do Sistema de Fadiga do Next Days
		// Verifica se o stat customizado existe antes de tentar adicionar valor
		if (player.GetStatTiredness())
		{
			float boostValue = GetND().GetRP().GetFatigue().EpinephrineEnergyBoost;
			
			// Failsafe: garante que o boost não seja negativo (o que cansaria o jogador)
			if (boostValue > 0)
			{
				player.GetStatTiredness().Add(boostValue);
			}
		}
		else
		{
			// Log de erro silencioso para o admin caso o Stat de Fadiga suma
			// Print("[NextDays] Error: StatTiredness not found for player: " + player.GetIdentity().GetName());
		}
	}
}