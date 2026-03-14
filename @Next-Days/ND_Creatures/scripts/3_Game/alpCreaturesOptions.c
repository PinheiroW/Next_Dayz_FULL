/**
 * alpCreaturesOptions
 * Classe de configuração serializável para o módulo de criaturas.
 */
class alpCreaturesOptions 
{
    // Atributos de Controle
    bool EnableCreatures;                 // Corrigido typo "Cretures"
    bool ZombiesCanOpenUnlockedDoor;

    // Listas de Definição
    ref array<string> CannotSpawnInMissions; 
    ref array<string> ZombiesMonster;

    // Construtor: Garante integridade das referências e valores padrão
    void alpCreaturesOptions()
    {
        SetDefault();
    }

    // Define os valores padrão (Fallback)
    void SetDefault()
    {
        EnableCreatures              = true;
        ZombiesCanOpenUnlockedDoor   = true;

        // Inicialização segura das arrays para evitar Null Pointer Exception
        if (!CannotSpawnInMissions)
            CannotSpawnInMissions    = new array<string>;
            
        if (!ZombiesMonster)
            ZombiesMonster           = new array<string>;

        // Exemplo de preenchimento padrão (opcional)
        // ZombiesMonster.Insert("ZmbM_ClerkFat_Grey"); 
    }
}