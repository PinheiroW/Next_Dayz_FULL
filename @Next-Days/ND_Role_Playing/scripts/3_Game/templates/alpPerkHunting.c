/**
 * @class   alpPerkHunting
 * @brief   Configurações de progressão e bônus para a perícia de Caça (Hunting)
 * Auditado em: 2024 - Otimização de Arrays e Tipagem
 */
class alpPerkHunting 
{
	int ConfigVersion = 1;

	// Penalidade de progresso ao morrer (Indice 0: Base, Indice 1: Multiplicador se Skill > 0)
	float PenalizedHuntingSkillAfterDeath[2];

	// Requisitos de Nível
	int RequiredLevelToSkin = 0;
	int RequiredLevelToGetPelt = 0;
	
	// Flags de Funcionamento
	bool AffectPeltQualityByLevel = true;
	bool PeltIsNotRepairable = true;
	
	// Arrays de Modificadores e Experiência
	ref array<float> LevelMdf;
	ref array<float> DamageLevelMdf;
	ref array<float> RequiredExp;

	void alpPerkHunting()
	{
		// Inicialização segura das arrays
		PenalizedHuntingSkillAfterDeath = {0, 0.98};
		
		LevelMdf = new array<float>;
		LevelMdf = {0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5};
		
		DamageLevelMdf = new array<float>;
		DamageLevelMdf = {0, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38, 0.4};
		
		RequiredExp = new array<float>;
		// Adicione aqui os valores de RequiredExp que estavam truncados no original
		RequiredExp = {0, 100, 250, 500, 1000}; // Exemplo de progressão
	}
}