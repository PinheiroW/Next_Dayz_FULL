/**
 * @class   alpPerkRadResistance
 * @brief   Configurações de progressão e bônus para Resistência à Radiação
 * Auditado em: 2024 - Foco em Consistência de Dados e Versionamento
 */
class alpPerkRadResistance 
{
	int ConfigVersion = 1;

	/**
	 * @brief Penalidade de XP após a morte.
	 * Indice 0: Base de perda.
	 * Indice 1: Multiplicador de retenção (0.99 = mantém 99% da XP se nível > 0).
	 */
	float PenalizedResistanceSkillAfterDeath[2];

	// Bônus de resistência por nível (Ex: 5, 10, 15...)
	ref array<float> LevelMdf;
	
	// Experiência necessária para cada nível
	ref array<float> RequiredExp;

	void alpPerkRadResistance()
	{
		// Inicialização segura dos valores padrão
		PenalizedResistanceSkillAfterDeath = {0, 0.99};

		LevelMdf = new array<float>;
		LevelMdf = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95};

		RequiredExp = new array<float>;
		RequiredExp = {0, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
	}
}