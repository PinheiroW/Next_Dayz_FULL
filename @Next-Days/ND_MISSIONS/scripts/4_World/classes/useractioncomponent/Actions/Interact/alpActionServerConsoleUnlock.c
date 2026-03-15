/**
 * alpActionServerConsoleUnlock.c
 * * USER INTERACTION (CONSOLE LOGIN / UNLOCK) - Módulo ND_MISSIONS
 * Autentica o acesso ao terminal utilizando cartões de acesso eletrónicos.
 */

class alpActionServerConsoleUnlock: ActionInteractBase
{
	void alpActionServerConsoleUnlock()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override void CreateConditionComponents()  
	{
		// O chip do cartão deve estar íntegro (Não Arruinado) para permitir a leitura
		m_ConditionItem   = new CCINonRuined;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return "#alp_action_console_login";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;
		
		// Validação geométrica: Exige interagir com o leitor frontal (Index 1)
		if (target.GetComponentIndex() != 1) return false;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Verifica se o alvo é um terminal e se o jogador segura um cartão de acesso válido
		if (Class.CastTo(console, target.GetObject()) && Class.CastTo(card, item))
		{
			// Requisitos de estado: Trancado, Inteiro (Não destruído) e funcional
			if (console.IsLockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP())
			{
				// Verificação Crítica: Pareamento de IDs entre Cartão e Terminal
				if (card.GetKeyID() == console.GetAccesCardID())
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Revalidação de segurança no lado do servidor antes de aplicar a mudança de estado
		if (Class.CastTo(console, action_data.m_Target.GetObject()) && Class.CastTo(card, action_data.m_MainItem))
		{
			if (card.GetKeyID() == console.GetAccesCardID())
			{
				// Altera o estado lógico para DESBLOQUEADO (Replicado para a rede)
				console.LockALP(false);
			}
		}
	}
};