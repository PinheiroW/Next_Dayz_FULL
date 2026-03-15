/**
 * alpActionServerConsoleLock.c
 * * AÇÃO DE INTERAÇÃO (LOGOUT/BLOQUEIO DE CONSOLE) - Módulo ND_MISSIONS
 * Permite trancar o terminal utilizando um cartão de acesso compatível.
 */

class alpActionServerConsoleLock: ActionInteractBase
{
	void alpActionServerConsoleLock()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined; // Exige que o cartão de acesso não esteja arruinado
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return "#alp_action_console_logout";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;
		
		// O jogador deve estar operando o painel de interface (Componente 1)
		if ( target.GetComponentIndex() != 1 ) return false;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Tenta realizar o cast de ambos: o console alvo e o cartão na mão do jogador
		if ( Class.CastTo(console, target.GetObject()) && Class.CastTo(card, item) )
		{
			// Condições para trancar:
			// 1. Console permite ser trancado.
			// 2. Está atualmente destrancado.
			// 3. Não está destruído ou danificado.
			// 4. O ID do cartão coincide com o ID de acesso do console.
			if ( console.CanBeLockedALP() && console.IsUnlockedALP() )
			{
				if ( !console.IsRuinedALP() && !console.IsDamagedALP() )
				{
					if ( card.GetKeyID() == console.GetAccesCardID() )
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if ( !action_data || !action_data.m_Target ) return;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		// Validação final no servidor antes de alterar o estado do objeto
		if ( Class.CastTo(console, action_data.m_Target.GetObject()) && Class.CastTo(card, action_data.m_MainItem) )
		{
			if ( card.GetKeyID() == console.GetAccesCardID() )
			{
				// Tranca o console e atualiza o estado global da missão
				console.LockALP( true );
			}
		}
	}
};