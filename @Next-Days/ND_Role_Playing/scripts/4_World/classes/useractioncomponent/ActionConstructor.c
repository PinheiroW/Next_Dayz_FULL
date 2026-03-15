/**
 * @class   ActionConstructor
 * @brief   Registra as novas ações do mod Next Days no motor do jogo
 * Auditado em: 2026 - Foco em Registro de Classes Customizadas
 */
modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		// 1. Mantém o registro das ações originais e de outros mods
		super.RegisterActions(actions);
		
		// 2. Registro de Ações de Interação (NPCs)
		actions.Insert(alpSpreadRumourAction);
		actions.Insert(alpActionExamination);

		// 3. Registro de Ações Contínuas Customizadas
		// Adicionando a ação de escavação de barris que auditamos anteriormente
		actions.Insert(alpActionDigInRadioactiveBarrel); 
		
		/** * @note: Se você criar novas ações de uso único ou contínuas 
		 * com nomes que começam com 'alp', elas DEVEM ser inseridas aqui.
		 */
	}
}