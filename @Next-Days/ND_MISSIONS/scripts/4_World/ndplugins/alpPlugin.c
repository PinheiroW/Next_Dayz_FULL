/**
 * alpPlugin.c
 * * PLUGIN INTERFACE BASE - Módulo ND_MISSIONS
 * Padroniza o tratamento de eventos de ciclo de vida do jogador para todos os plugins.
 */

class alpPlugin : alpPluginBase
{
	// --- Overrides do Motor do Jogo (Redirecionamento para Métodos Gerenciados) ---

	/**
	 * Chamado quando um jogador entra no servidor.
	 */
	override void OnConnect(Man player)
	{
		PlayerBase p = PlayerBase.Cast(player);
		if (p) OnConnectManaged(p);
	}

	/**
	 * Chamado quando o personagem do jogador é instanciado no mundo (Spawn).
	 */
	override void OnSpawn(Man player)
	{
		PlayerBase p = PlayerBase.Cast(player);
		if (p) OnSpawnManaged(p);
	}

	/**
	 * Chamado quando o jogador morre.
	 */
	override void OnDeath(Man player)
	{
		PlayerBase p = PlayerBase.Cast(player);
		if (p) OnDeathManaged(p);
	}

	/**
	 * Chamado quando o jogador desconecta do servidor.
	 */
	override void OnDisconnect(Man player)
	{
		PlayerBase p = PlayerBase.Cast(player);
		if (p) OnDisconnectManaged(p);
	}

	// --- Métodos Virtuais para Implementação em Plugins Filhos ---

	/**
	 * Implementar lógica de conexão (ex: sincronização de configurações RPC).
	 */
	void OnConnectManaged(PlayerBase player) {}

	/**
	 * Implementar lógica de nascimento (ex: carregamento de dados da Hive).
	 */
	void OnSpawnManaged(PlayerBase player) {}

	/**
	 * Implementar lógica de morte (ex: limpeza de status ou variáveis de sessão).
	 */
	void OnDeathManaged(PlayerBase player) {}

	/**
	 * Implementar lógica de desconexão (ex: salvamento de estado final).
	 */
	void OnDisconnectManaged(PlayerBase player) {}
}