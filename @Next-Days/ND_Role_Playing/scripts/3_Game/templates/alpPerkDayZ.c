/**
 * @class   alpPerkDayZ
 * @brief   Configurações de penalidade de SoftSkills (DayZ Vanilla)
 * Auditado em: 2024 - Foco em Persistência e Documentação Técnica
 */
class alpPerkDayZ 
{
	// Controle de versão para garantir compatibilidade com futuras atualizações de skills
	int ConfigVersion = 1;

	/**
	 * @brief Percentual de progresso de SoftSkill mantido após a morte.
	 * Intervalo: 0.0 a 1.0
	 * Exemplo: 0.75 significa que o jogador mantém 75% da sua experiência atual.
	 * Exemplo: 0.0 significa perda total de progresso ao morrer.
	 */
	float PenalizedSkillAfterDeath = 0.75;

	// Construtor para inicialização segura
	void alpPerkDayZ()
	{
		// Valor padrão atribuído na declaração
	}
}