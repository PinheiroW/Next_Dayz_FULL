/**
 * ActionConstructor.c
 * * REGISTRO GLOBAL DE AÇÕES - Módulo ND_MISSIONS
 * Este arquivo registra todas as ações customizadas no motor do jogo.
 */

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		// Garante que as ações nativas do DayZ sejam registradas primeiro
		super.RegisterActions(actions);

		if (!actions) return;

		// --- CATEGORIA: VEÍCULOS E CHAVES ---
		actions.Insert(alpLockVehicle);
		actions.Insert(alpUnlockVehicle);
		actions.Insert(alpCreateDuplicate);		
		actions.Insert(alpLockpicking);
		
		// --- CATEGORIA: INTERAÇÃO COM MUNDO (BARREIS / DINAMITE) ---
		actions.Insert(alpActionOpenBarrel);
		actions.Insert(alpActionCloseBarrel);
		actions.Insert(alpActionDecontaminate);		
		actions.Insert(alpActionDigInRadioactiveBarrel);
		actions.Insert(alpActionIgniteDynamite);

		// --- CATEGORIA: ECONOMIA E QUESTS (TRADER / ATM) ---
		actions.Insert(alpActionBuy);
		actions.Insert(alpActionSell);
		actions.Insert(alpActionATM);			
		actions.Insert(alpActionQuestBringMe);	

		// --- CATEGORIA: SAÚDE E DESCONTAMINAÇÃO ---
		actions.Insert(ActionDecontamineTarget);			
		actions.Insert(ActionDecontamineSelf);		
		
		// --- CATEGORIA: MISSÕES E NPCs ---
		actions.Insert(alpActionStartMission);	

		// --- CATEGORIA: TERMINAIS DE SERVIDOR (CONSOLES) ---
		actions.Insert(alpActionServerConsole);	
		actions.Insert(alpActionServerConsoleLocked);	
		actions.Insert(alpActionServerConsoleLock);
		actions.Insert(alpActionServerConsoleUnlock);
		actions.Insert(alpActionServerConsoleRepair);
		actions.Insert(alpActionServerConsoleDownloadData);	
		actions.Insert(alpActionServerConsoleDeleteData);	
	}
}