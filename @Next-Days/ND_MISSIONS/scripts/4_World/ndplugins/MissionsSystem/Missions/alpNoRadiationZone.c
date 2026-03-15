/**
 * alpNoRadiationZone.c
 * * MISSION LOGIC: NO RADIATION ZONE - Módulo ND_MISSIONS
 * Define áreas dinâmicas onde os jogadores estão protegidos contra efeitos radioativos.
 */

class alpNoRadiationZone extends alpMission
{
	// --- Configurações Iniciais ---

	override void OnInit()
	{
		// Configuração de strings de mensagens (Broadcast e Pessoal)
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn     = ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut    = ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}

	// --- Gatilhos de Área ---

	/**
	 * Chamado quando um objeto (jogador/veículo) entra na zona livre de radiação.
	 */
	override protected void OnEnter(Object obj)
	{
		super.OnEnter(obj);
		
		// A lógica de remoção de dano por radiação é processada pelo alpPluginNDRadiation,
		// que verifica se o jogador está dentro de uma instância desta classe.
	}

	/**
	 * Nota: O comportamento de "Secured" ou "Failed" para esta missão geralmente
	 * depende do tempo de vida (Lifetime) definido no JSON da missão, 
	 * já que é uma zona de utilidade e não de combate direto.
	 */
}