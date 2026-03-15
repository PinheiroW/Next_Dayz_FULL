/**
 * alpActionServerConsoleLock.c
 * * USER INTERACTION (CONSOLE LOGOUT / LOCK) - Módulo ND_MISSIONS
 * Protege o terminal de missão contra acesso público utilizando o cartão de acesso correto.
 */

class alpActionServerConsoleLock: ActionInteractBase
{
	void alpActionServerConsoleLock()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override void CreateConditionComponents()  
	{
		// O cartão deve estar em boas condições para interagir com o chip do terminal
		m_ConditionItem   = new CCINonRuined;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return "#alp_action_console_logout";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;
		
		// Validação geométrica: Foco obrigatório no painel de interface (Index 1)
		if (target.GetComponentIndex() != 1) return false;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Valida a hierarquia de classes do alvo e do item em mãos
		if (Class.CastTo(console, target.GetObject()) && Class.CastTo(card, item))
		{
			// Condições lógicas para o bloqueio:
			// 1. O console está configurado para permitir bloqueio manual.
			// 2. O terminal está atualmente desbloqueado.
			// 3. O hardware não está arruinado ou danificado.
			if (console.CanBeLockedALP() && console.IsUnlockedALP())
			{
				if (!console.IsRuinedALP() && !console.IsDamagedALP())
				{
					// Requisito de Segurança: O ID do cartão deve ser compatível com o do terminal
					if (card.GetKeyID() == console.GetAccesCardID())
					{
						return true;
					}
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
		
		// Execução segura no servidor com revalidação de identidade
		if (Class.CastTo(console, action_data.m_Target.GetObject()) && Class.CastTo(card, action_data.m_MainItem))
		{
			if (card.GetKeyID() == console.GetAccesCardID())
			{
				// Transita o estado lógico para TRANCADO (Replicado para todos os clientes)
				console.LockALP(true);
			}
		}
	}
};