/**
 * @class   Environment
 * @brief   Extensão do sistema de ambiente para suporte ao ND_Role_Playing
 * Auditado em: 2024 - Foco em Performance e Compatibilidade
 */
modded class Environment
{
	/**
	 * @brief Verifica se o jogador está protegido (em abrigo)
	 * @return bool - Verdadeiro se estiver sob teto ou dentro de prédios
	 * * Nota: Adicionado prefixo 'ND' para evitar conflitos de compilação com outros mods.
	 * Certifique-se de atualizar as chamadas desta função no sistema de fadiga (alpFatigue).
	 */
	bool ND_IsInShelter()
	{
		if (!m_Player) return false;

		// Otimização: Retorno direto da expressão lógica
		// m_IsUnderRoof: Flag nativa da Engine para oclusão de chuva/neve
		// IsSoundInsideBuilding: Verifica oclusão sonora
		return m_IsUnderRoof || m_Player.IsSoundInsideBuilding();
	}

	// Mantendo compatibilidade caso o nome antigo seja necessário para o compilador não quebrar
	// mas recomendo migrar para o ND_IsInShelter acima.
	bool IsInShelter()
	{
		return ND_IsInShelter();
	}
};