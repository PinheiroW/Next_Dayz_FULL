/**
 * @class   alpPerkResistanceCold
 * @brief   Configurações de progressão e bônus para Resistência ao Frio
 * Auditado em: 2024 - Padronização de estrutura de Perks
 */
class alpPerkResistanceCold
{
	int ConfigVersion = 1;

	/**
	 * @brief Percentual de progresso de Resistência ao Frio mantido após a morte.
	 * Padrão: 0.75 (Mantém 75% da experiência atual).
	 */
	float PenalizedSkillAfterDeath = 0.75;

	// Bônus de isolamento térmico ou HeatBuffer por nível
	ref array<float> LevelMdf;
	
	// Experiência necessária para cada nível
	ref array<float> RequiredExp;

	void alpPerkResistanceCold()
	{
		// Inicialização segura - Exemplo de progressão de 5 níveis
		// Se não quiser usar níveis agora, pode deixar as arrays vazias, 
		// mas o construtor evita erros de VME.

		LevelMdf = new array<float>;
		LevelMdf = {0.0, 0.05, 0.10, 0.15, 0.20}; // Bônus de isolamento em %

		RequiredExp = new array<float>;
		RequiredExp = {0, 1000, 2500, 5000, 10000};
	}
}