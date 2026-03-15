/**
 * @class   alpOptionsRP_PlayersPerks
 * @brief   Configurações centrais do sistema de RPG ND_Role_Playing
 * Auditado em: 2024 - Foco em Integridade e Balanceamento
 */
class alpOptionsRP_PlayersPerks 
{
	// Controle de versão para compatibilidade de atualizações futuras
	int ConfigVersion = 1;

	// --- Sistema de Reputação ---
	// Se verdadeiro, a reputação não é restaurada no sistema de DNA/Clonagem
	bool ExcludeReputationFromCloning				= false;
	// Ativa notificações na UI quando o jogador ganha/perde reputação
	bool EnableGainedReputationNotification			= false;
	
	// --- Preservação de Progresso ---
	// Mantém o nível da skill alcançado mesmo sem Life Insurance
	bool SecureReachedSkill							= false;
	// Percentual de stats mantidos ao morrer SEM Life Insurance (0.0 a 1.0)
	// Exemplo: 0.5 = Retém 50% do progresso atual
	float SecureStatsWithoutLI						= 0.5;
	
	// --- Ativação de Perks (4_World) ---
	bool EnablePerkStamina							= true;
	bool EnablePerkCustomDayzSkills					= true;
	bool EnablePerkReputation						= true;
	bool EnablePerkHunting							= true;
	bool EnablePerkRadiationResistance				= true;
	bool EnablePerkToxicResistance					= true;
	
	// --- Ativação de Sistemas Globais ---
	bool EnableFatigue								= true;
	bool EnableDiseases								= true;

	// Construtor para garantir a inicialização segura dos parâmetros
	void alpOptionsRP_PlayersPerks()
	{
		// Valores padrão já inicializados nas declarações
	}
}