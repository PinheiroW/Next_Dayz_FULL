/**
 * @class   Constants
 * @brief   Definições globais de caminhos e estados do ND_Role_Playing
 * Auditado em: 2024 - Foco em Modularidade e Organização
 */

// --- Estados de RPG ---
const int ALP_RP_HERO 		= 0;
const int ALP_RP_BANDIT 	= 1;

// --- Definição de Pasta Raiz (Fallback de Segurança) ---
// Se ALP_ROOTFOLDER não estiver definido em outro lugar, use o caminho padrão
#ifndef ALP_ROOTFOLDER
const string ALP_ROOTFOLDER = "$profile:NextDays/";
#endif

// --- ARQUIVOS DE CONFIGURAÇÃO (Templates JSON) ---
// Estes arquivos definem como o mod se comporta no servidor
const string ALP_RP_PLAYERSPERKS_FILE		= ALP_ROOTFOLDER + "ND_1_RP_Options.json";	
const string ALP_RP_PERKSTAMINA_FILE		= ALP_ROOTFOLDER + "ND_1_RP_Perks_Stamina.json";
const string ALP_RP_PERKSDAYZ_FILE			= ALP_ROOTFOLDER + "ND_1_RP_Perks_DayzSkills.json";
const string ALP_RP_PERKCOLDRESIST_FILE		= ALP_ROOTFOLDER + "ND_1_RP_Perks_ColdResistance.json";
const string ALP_RP_PERKHUNTING_FILE		= ALP_ROOTFOLDER + "ND_1_RP_Perks_Hunting.json";
const string ALP_RP_PERKRADRESIST_FILE		= ALP_ROOTFOLDER + "ND_1_RP_Perks_RadiationResistance.json";
const string ALP_RP_PERKTOXICRESIST_FILE	= ALP_ROOTFOLDER + "ND_1_RP_Perks_ToxicResistance.json";
const string ALP_RP_FATIGUE_FILE			= ALP_ROOTFOLDER + "ND_1_RP_Fatigue.json";
const string ALP_RP_DISEASES_FILE			= ALP_ROOTFOLDER + "ND_1_RP_Diseases.json";
const string ALP_RP_INTERACTION_FILE		= ALP_ROOTFOLDER + "ND_1_RP_ExpandedInteraction.json";

// --- ARQUIVOS DE DADOS (Persistência / Hall of Fame) ---
// Estes arquivos guardam o progresso e estatísticas dos jogadores
const string ALP_RP_PERKREPUTATION_FILE		= ALP_ROOTFOLDER + "ND_1_RP_Perks_Reputation.json";
const string ALP_RP_DATA_REPUTATION_HOF		= ALP_ROOTFOLDER + "ND_1_RP_Data_Reputation_HoF.json";