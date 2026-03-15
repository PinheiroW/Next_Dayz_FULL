/**
 * @class   alpDiseasesOptions
 * @brief   Template de configuração para o sistema de doenças do ND_Role_Playing
 * * Auditado em: 2024
 * Versão de compatibilidade DayZ: 1.25+
 */
class alpDiseasesOptions 
{
	// Controle de versão para evitar incompatibilidades em atualizações futuras
	int ConfigVersion = 1;

	// Se verdadeiro, gera o relatório médico após exames
	bool MedicalTestReport = true;
	
	// Ativa/Desativa a febre como sintoma de Influenza
	bool FeverActive = true; 
	
	// Chance de infecção de ferida (Wound Infection) ao ser ferido por AI ou ambiente
	// Intervalo: 0.0 a 1.0 (Ex: 0.5 = 50%)
	float WoundInfectionChance = 0.5; 
	
	// Tempo de imunidade após curar Influenza (em segundos)
	// Padrão: 1800s (30 minutos)
	int ImmunityInfluenza = 1800; 

	// Construtor para garantir integridade na inicialização
	void alpDiseasesOptions()
	{
		// Valores padrão já definidos acima
	}
}