/**
 * alpActionServerConsoleLocked.c
 * * AÇÃO INFORMATIVA (CONSOLE BLOQUEADO) - Módulo ND_MISSIONS
 * Exibe no HUD qual cartão de acesso é necessário para interagir com o terminal.
 */

class alpActionServerConsoleLocked: ActionInteractBase
{
	string alp_Title;

	void alpActionServerConsoleLocked()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target || !target.GetObject() ) return false;

		// Verifica se o jogador está mirando no painel de comando (Componente 1)
		if ( target.GetComponentIndex() != 1 ) return false;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		if ( Class.CastTo(console, target.GetObject()) )
		{
			Class.CastTo(card, item); // Tenta castar o item em mãos (pode ser nulo)

			// Esta ação só é visível se:
			// 1. O console for trancável e estiver atualmente TRANCADO.
			// 2. O console não estiver destruído.
			// 3. O jogador NÃO tem o cartão ou o cartão que tem NÃO é o ID correto.
			if ( console.CanBeLockedALP() && console.IsLockedALP() && !console.IsRuinedALP() )
			{
				if ( !card || card.GetKeyID() != console.GetAccesCardID() )
				{
					// Lado do cliente: Prepara o texto informativo
					if ( GetGame().IsClient() )
					{
						SetActionTextALP( console.GetAccesCardID() );
					}
					return true;
				}
			}
		}
		
		return false;
	}
	
	// Constrói a string do HUD: "Requer Cartão (Cor do Cartão)"
	void SetActionTextALP(int id)
	{
		alp_Title = "#alp_action_console_requirescard"; // String base: "Requer Cartão"
		
		string cardColorName = "";
		switch(id)
		{
			case 0:
				cardColorName = alpUF.GetDisplayName("alp_AccessCardRed");
				break;
			case 1:
				cardColorName = alpUF.GetDisplayName("alp_AccessCardBlue");
				break;
			case 2:
				cardColorName = alpUF.GetDisplayName("alp_AccessCardYellow");
				break;
			case 3:
				cardColorName = alpUF.GetDisplayName("alp_AccessCardGreen");
				break;
			case 4:
				cardColorName = alpUF.GetDisplayName("alp_AccessCardBlack");
				break;
			default:
				cardColorName = "???";
				break;
		}
		
		alp_Title += " (" + cardColorName + ")";
	}

	// Esta ação não executa nada no servidor, pois é apenas um aviso visual.
	override void OnExecuteServer( ActionData action_data ) {}
};