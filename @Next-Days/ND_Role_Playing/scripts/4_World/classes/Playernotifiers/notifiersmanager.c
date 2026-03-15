/**
 * @class   NotifiersManager
 * @brief   Gerencia o registro de elementos visuais (Notifiers) na HUD
 * Auditado em: 2024 - Foco em Padrão de Inicialização e Estabilidade da HUD
 */
modded class NotifiersManager
{
	/**
	 * @brief SoftInit é o local correto para inserir novos notificadores.
	 * Ele roda logo após a criação da lista m_Notifiers original.
	 */
	override void SoftInit()
	{
		// 1. Chama a inicialização vanilla primeiro (Fome, Sede, Saúde, etc.)
		super.SoftInit();

		// 2. Adiciona os notificadores customizados do Next Days
		if (m_Notifiers)
		{
			// Notificador de Fadiga/Cansaço
			m_Notifiers.Insert(new alpTirednessNotfr(this));
			
			// Nota: Se você criar notificadores para Radiação ou outros status 
			// visuais de tendência no futuro, eles devem ser inseridos aqui.
		}
	}
}