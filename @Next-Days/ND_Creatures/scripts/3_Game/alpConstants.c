/**
 * NDCreatureConstants
 * * Gerenciamento centralizado de caminhos de arquivos para o módulo de criaturas.
 * Depende da definição global de ALP_ROOTFOLDER presente no módulo base/core.
 */
class NDCreatureConstants
{
    // Pastas
    static const string FOLDER_BASE      = ALP_ROOTFOLDER + "Creatures/";

    // Arquivo Principal de Configuração
    static const string FILE_MAIN        = ALP_ROOTFOLDER + "ND_3_Creatures.json";

    // Arquivos de Definição de Zumbis
    static const string FILE_ZOMBIE_C    = FOLDER_BASE + "ZombieCivil.json";
    static const string FILE_ZOMBIE_C_NBC= FOLDER_BASE + "ZombieCivilNBC.json";
    static const string FILE_ZOMBIE_M    = FOLDER_BASE + "ZombieMilitary.json";
    static const string FILE_ZOMBIE_M_NBC= FOLDER_BASE + "ZombieMilitaryNBC.json";

    // Arquivos de Monstros/Especiais
    static const string FILE_MONSTER     = FOLDER_BASE + "ZombieMonster.json";
}

// Mantenha as globais abaixo APENAS para compatibilidade com scripts antigos (Legacy Support)
// Caso deseje refatorar completamente o mod, remova as linhas abaixo e atualize as referências.
const string ALP_CREATURES_FOLDER          = NDCreatureConstants.FOLDER_BASE;
const string ALP_CREATURES_FILE            = NDCreatureConstants.FILE_MAIN;
const string ALP_CREATURES_ZED_C_FILE      = NDCreatureConstants.FILE_ZOMBIE_C;
const string ALP_CREATURES_ZED_C_NBC_FILE  = NDCreatureConstants.FILE_ZOMBIE_C_NBC;
const string ALP_CREATURES_ZED_M_FILE      = NDCreatureConstants.FILE_ZOMBIE_M;
const string ALP_CREATURES_ZED_M_NBC_FILE  = NDCreatureConstants.FILE_ZOMBIE_M_NBC;
const string ALP_CREATURES_ZED_MONSTER_FILE = NDCreatureConstants.FILE_MONSTER;