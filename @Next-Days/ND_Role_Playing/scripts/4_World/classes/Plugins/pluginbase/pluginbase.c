/**
 * @class   PluginPlayerStatus
 * @brief   Mapeia os IDs dos notificadores para os ícones da HUD
 * Auditado em: 2024 - Foco em Ciclo de Vida de Plugin e Estabilidade Visual
 */

// Define a chave caso ela não exista globalmente para evitar erros de compilação
#ifndef NTFKEY_ALPTIREDNESS
const int NTFKEY_ALPTIREDNESS = 150; // Use um ID alto para evitar conflitos com vanilla
#endif

modded class PluginPlayerStatus extends PluginBase
{
	/**
	 * @brief Construtor modificado
	 */
	void PluginPlayerStatus()
	{
		// No DayZ, m_NotifiersIcons é instanciado no construtor da classe base.
		// Adicionamos nossos ícones customizados aqui com verificação de segurança.
		if (m_NotifiersIcons)
		{
			// Associa o ID do notificador ao nome da imagem no seu layout de HUD (ex: iconTiredness)
			m_NotifiersIcons.Insert( NTFKEY_ALPTIREDNESS, "iconTiredness" );
		}
	}
}