/**
 * @class   alpPerkToxicResistance
 * @brief   Configurações de progressão e bônus para Resistência Tóxica (Gás/Químico)
 * Auditado em: 2024 - Foco em Estabilidade de Carregamento e Versionamento
 */
class alpPerkToxicResistance 
{
	int ConfigVersion = 1;

	/**
	 * @brief Penalidade de XP após a morte.
	 * Indice 0: Base de perda.
	 * Indice 1: Multiplicador de retenção (0.99 = mantém 99% da XP se nível > 0).
	 */
	float PenalizedResistanceSkillAfterDeath[2];

	// Modificadores de resistência química por nível
	ref array<float> LevelMdf;
	
	// Experiência necessária para cada nível
	ref array<float> RequiredExp;

	void alpPerkToxicResistance()
	{
		// Inicialização segura dos valores padrão
		PenalizedResistanceSkillAfterDeath = {0, 0.99};

		LevelMdf = new array<float>;
		LevelMdf = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95};

		RequiredExp = new array<float>;
		// Progressão linear (pode ser alterada para exponencial no futuro)
		RequiredExp = {0, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
	}
}