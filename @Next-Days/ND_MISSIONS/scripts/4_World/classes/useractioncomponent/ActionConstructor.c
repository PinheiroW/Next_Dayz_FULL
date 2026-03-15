/**
 * ActionConstructor.c
 * * USER ACTION REGISTRATION - Módulo ND_MISSIONS
 * Centraliza o registro de todas as ações customizadas de interação do mod.
 */

modded class ActionConstructor
{
	/**
	 * Registra as ações customizadas do Next-Days na lista global de ações do DayZ.
	 */
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);

		// --- Ações de Infraestrutura e Economia ---
		actions.Insert(alpActionATM);                // Interação com Caixas Eletrônicos
		actions.Insert(alpActionBuy);                // Ação de Compra no Trader
		actions.Insert(alpActionSell);               // Ação de Venda no Trader
		actions.Insert(alpActionServerConsole);      // Acesso ao Console de Servidor
		
		// --- Ações de Missão e Eventos ---
		actions.Insert(alpActionStartMission);       // Iniciar Missão via objeto
		actions.Insert(alpActionQuestBringMe);       // Entrega de itens de Quest
		
		// --- Ações de Ambiente e Sobrevivência ---
		actions.Insert(alpActionDecontaminate);      // Uso do chuveiro de descontaminação
		actions.Insert(alpActionDigInRadioactiveBarrel); // Mineração em barris radioativos
		actions.Insert(alpActionOpenBarrel);         // Abrir barril customizado
		actions.Insert(alpActionCloseBarrel);        // Fechar barril customizado
		
		// --- Ações de Tecnologia e Equipamento ---
		actions.Insert(alpActionServerConsoleRepair);        // Reparo de Consoles
		actions.Insert(alpActionServerConsoleLock);          // Trancar Console
		actions.Insert(alpActionServerConsoleUnlock);        // Destrancar Console
		actions.Insert(alpActionServerConsoleLocked);        // Estado Trancado
		actions.Insert(alpActionServerConsoleDownloadData);  // Baixar Dados
		actions.Insert(alpActionServerConsoleDeleteData);    // Deletar Dados
		
		// --- Ações de Manuseio de Itens ---
		actions.Insert(alpActionIgniteDynamite);     // Acender Dinamite
		actions.Insert(alpCreateduplicate);          // Criação de chaves/duplicatas
		actions.Insert(alpLockvehicle);              // Trancar Veículo (Manual)
		actions.Insert(alpUnlockvehicle);            // Destrancar Veículo (Manual)
		actions.Insert(alpLockpicking);              // Arrombamento (Lockpick custom)
	}
}