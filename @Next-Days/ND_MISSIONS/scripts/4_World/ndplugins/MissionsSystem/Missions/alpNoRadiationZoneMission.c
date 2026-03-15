/**
 * alpNoRadiationZoneMission.c
 * * MISSION LOGIC: NO RADIATION ZONE (EVENT) - Módulo ND_MISSIONS
 * Variante de missão para zonas dinâmicas de segurança radiológica.
 */

class alpNoRadiationZoneMission extends alpMission
{
	// --- Configurações Iniciais ---
	
	override void OnInit()
	{
		// Configuração de strings de mensagens padrão do sistema de missões
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut    = ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}
	
	/**
	 * Nota Técnica: Esta classe herda toda a lógica de gatilhos (Triggers) e 
	 * gerenciamento de insiders da classe base 'alpMission'.
	 * O comportamento específico de anulação de radiação é verificado pelo 
	 * plugin de radiação consultando instâncias ativas desta classe.
	 */
}