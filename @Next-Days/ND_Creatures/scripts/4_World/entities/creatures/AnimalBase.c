modded class AnimalBase
{
    override void EEInit()
    {
        super.EEInit();

        // Executa validação apenas no Servidor
        if (GetGame().IsServer())
        {
            if (IsAnimalCustomed())
            {
                // Verifica se a posição de spawn é permitida pelas missões/zonas ND
                // Usamos um pequeno delay (1ms) para garantir que a entidade está registrada no mundo antes de deletar
                if (!alpPluginNDmissionsSystem.CansSpawnAI(this)) 
                {
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 50, false, this);
                    return;
                }
            }
        }
    }
    
    bool IsAnimalCustomed()
    {
        // Null checks encadeados para evitar Server Crash (NPE)
        auto nd = GetND();
        if (nd && nd.GetCreatures() && nd.GetCreatures().GetOptions())
        {
            // Corrigido para "EnableCreatures" conforme auditoria do 3_Game
            return nd.GetCreatures().GetOptions().EnableCreatures;
        }
        return false;
    }    
    
    // Removida a lógica de verificação do ModCommandHandlerBefore para otimização de CPU (Server FPS)
    override bool ModCommandHandlerBefore(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
    {
        return super.ModCommandHandlerBefore(pDt, pCurrentCommandID, pCurrentCommandFinished);
    }
}