/**
 * NDCreatures - alpND.c
 * Auditoria Técnica: Pró-Gamer / IA Modding Specialist
 * OTIMIZAÇÃO: Cache de instância para acesso ultra-rápido ao plugin de criaturas.
 */

modded class alpND_world extends alpND_base
{
	// Variável de cache para evitar buscas repetitivas no map de plugins
	private ref alpCreaturesPlugin m_CreaturesPluginCache;

	override protected void Init()
	{	
		super.Init();

		// O plugin deve ser instanciado em ambos os lados se houver lógica de efeitos/UI,
		// mas a lógica pesada interna deve ser protegida por IsServer() (já fizemos isso no Plugin).
		m_CreaturesPluginCache = new alpCreaturesPlugin(alpPLUGIN_BASE_ID.CREATURES, 0);
		AddPlugin(m_CreaturesPluginCache);	
	}

	/**
	 * GetCreatures
	 * @return alpCreaturesPlugin
	 * OTIMIZADO: Retorna a instância em cache, eliminando o custo de busca (map.Get) e Cast.
	 */
	alpCreaturesPlugin GetCreatures()
	{
		// Se por algum motivo o cache estiver nulo (ex: falha na inicialização), tenta recuperar uma vez
		if (!m_CreaturesPluginCache)
		{
			m_CreaturesPluginCache = alpCreaturesPlugin.Cast(alp_ActivePlugins.Get(alpPLUGIN_BASE_ID.CREATURES));
		}
		
		return m_CreaturesPluginCache;
	}
}