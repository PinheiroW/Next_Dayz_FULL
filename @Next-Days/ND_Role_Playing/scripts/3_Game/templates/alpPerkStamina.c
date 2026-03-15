/**
 * @class   alpPerkStamina
 * @brief   Configurações de progressão de Stamina e modificadores de movimento
 * Auditado em: 2024 - Foco em Estabilidade de Memória e Balanceamento
 */
class alpPerkStamina 
{
	int ConfigVersion = 1;

	// Se verdadeiro, o bônus de perk é ignorado ao mirar (foco em realismo)
	bool DisableStaminaPerkWhenAiming = false;

	/**
	 * Indice 0: Perda base de XP.
	 * Indice 1: Multiplicador de retenção (0.98 = mantém 98% da XP após a morte).
	 */
	float PenalizedStaminaSkillAfterDeath[2];

	// Modificadores de consumo de Stamina por nível (1.0 = 100% consumo / 0.12 = 12% consumo)
	ref array<float> LevelMdf;
	
	// Experiência necessária para progressão
	ref array<float> RequiredExp;

	// Modificador aplicado sob efeito de Anabolizantes (Sugerido: Multiplicador de Regeneração)
	float AnabolicMdf = 4.0;

	// Custos de Stamina para ações específicas (Independente de nível)
	float MoveRun = 1.0;
	float MoveSprint = 1.5;
	float ClimbFast = 3.0;

	void alpPerkStamina()
	{
		PenalizedStaminaSkillAfterDeath = {0, 0.98};

		LevelMdf = new array<float>;
		LevelMdf = {1, 0.96, 0.92, 0.88, 0.84, 0.8, 0.76, 0.72, 0.68, 0.64, 0.6, 0.56, 0.52, 0.48, 0.44, 0.4, 0.36, 0.32, 0.28, 0.24, 0.2, 0.16, 0.12};
		
		RequiredExp = new array<float>;
		RequiredExp = {0, 2400, 2600, 2800, 3000, 3200, 3400, 3600, 3800, 4000, 4200, 4400, 4600, 4800, 5000, 5200, 5400, 5600, 5800, 6000, 6200, 6400, 6600};
	}
}