modded class alpND_world
{
    // Caching do plugin para evitar buscas repetitivas no Map de plugins
    protected alpClansPlugin m_ClansPlugin;

    override protected void Init()
    {	
        super.Init();

        // Inicializa as opções de bases de clãs
        alp_ClanBasesOptions = new alpClanBasesOptions();
        
        if (GetGame().IsServer() && GetGame().IsMultiplayer())
        {		
            if (!FileExist(ALP_CLANS_FOLDER))
            { 
                MakeDirectory(ALP_CLANS_FOLDER);		
            }	
            
            // Gerenciamento de Configuração: Carrega ou cria o arquivo padrão
            if (!FileExist(ALP_CLANS_BASES_FILE))
            { 			
                JsonFileLoader<alpClanBasesOptions>.JsonSaveFile(ALP_CLANS_BASES_FILE, alp_ClanBasesOptions);
            }
            else 
            {
                JsonFileLoader<alpClanBasesOptions>.JsonLoadFile(ALP_CLANS_BASES_FILE, alp_ClanBasesOptions);
                
                // Failsafe: Se o arquivo estiver corrompido, garante que as opções não fiquem nulas
                if (!alp_ClanBasesOptions)
                {
                    alp_ClanBasesOptions = new alpClanBasesOptions();
                    Error("[ND_Clans] WARNING: Base Options file corrupted. Using defaults.");
                }
            }			
        }
        
        // Registra o plugin de clãs no gerenciador core
        m_ClansPlugin = new alpClansPlugin(alpPLUGIN_BASE_ID.CLANS, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN | alpPLUGIN_BASE_EVENTS.ONDEATH | alpPLUGIN_BASE_EVENTS.ONDISCONNECT);
        AddPlugin(m_ClansPlugin);		
    }	

    alpClansPlugin GetClans()
    {
        // Se a referência em cache estiver disponível, retorna imediatamente (Alta performance)
        if (m_ClansPlugin)
            return m_ClansPlugin;

        // Failsafe: Busca no gerenciador global caso o cache falhe
        if (!alp_ActivePlugins)
        {
            Error("[ND_Clans] CRITICAL: alp_ActivePlugins is null!");
            return null;
        }

        m_ClansPlugin = alpClansPlugin.Cast(alp_ActivePlugins.Get(alpPLUGIN_BASE_ID.CLANS));
        return m_ClansPlugin;
    }	
}