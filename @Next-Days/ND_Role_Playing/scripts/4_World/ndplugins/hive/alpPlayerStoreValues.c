/**
 * @class   alpPlayerStoreValues & alpSavedDNA
 * @brief   Esquema de dados para salvamento no Hive (XP, Perks, Scores) do Next Days
 * Auditado em: 2026 - Foco em Integridade de Serialização e Macros de Mapa
 */

modded class alpStoreValues 
{
	float								PerkStaminaEXP;
	float								PerkSoftEXP;
	float								PerkRoughEXP;
	
#ifdef NAMALSK_SURVIVAL		
	float								PerkResistanceColdEXP;
#endif 

	float								PerkReputationEXP;
	float								PerkHuntingEXP;
	float								PerkRadiationResistanceEXP;
	float								PerkToxicResistanceEXP;

	float								BestScore;	
	
	ref alpSavedDNA 					SavedDNA = new alpSavedDNA();
}

class alpSavedDNA 
{
	float StaminaEXP;
	float SpecialtySoftEXP;
	float SpecialtyRoughEXP;
	float ResistanceEXP;
	float ResistanceToxicEXP;

// 1. Correção Crítica: A proteção do Namalsk deve espelhar a classe principal
#ifdef NAMALSK_SURVIVAL	
	float ResistanceColdEXP;
#endif

	float ReputationEXP;
	float HuntingEXP;
	
	// Nota da Auditoria: Antigas variáveis de Level e Progress foram removidas. 
	// O sistema atual salva apenas o EXP e deduz o nível no carregamento (LoadDNA).
}