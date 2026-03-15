/**
 * @class   alpPerkReputation
 * @brief   Configurações de Reputação e Hall of Fame
 * Auditado em: 2024 - Foco em Correção Matemática e Balanceamento
 */
class alpPerkReputation
{
	int ConfigVersion = 1;

	// --- Configurações do Hall of Fame ---
	bool EnableHallOfFame = true;
	bool StoreLastSessionInHoF = false;
	int MaxCountRecords = 30;	
	
	// --- Penalidade de Morte ---
	// Indice 0: Perda base, Indice 1: Retenção (0.95 = mantém 95% da XP)
	float PenalizedReputationSkillAfterDeath[2];

	// Modificadores de preço ou benefícios por nível
	ref array<float> LevelMdf;
	
	// Progressão de Experiência Necessária
	ref array<float> RequiredExp;
	
	// --- Ganho de Reputação (Multiplicadores ou Valores Fixos) ---
	float KillPlayerBonus = 0.05;
	float BuyProductBonus = 0.01;
	float SellProductBonus = 0.01;
	float SpreadGossipBonus = 0.02;

	void alpPerkReputation()
	{
		PenalizedReputationSkillAfterDeath = {0, 0.95};

		LevelMdf = new array<float>;
		LevelMdf = {0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.20};
		
		RequiredExp = new array<float>;
		// CORREÇÃO: Valor 3600000 corrigido para 360000 para manter a progressão linear de +20k
		RequiredExp = {0, 20000, 40000, 60000, 80000, 100000, 120000, 140000, 160000, 180000, 200000, 220000, 240000, 260000, 280000, 300000, 320000, 340000, 360000, 380000};
	}
}