/**
 * alpActionServerConsoleLocked.c
 * * INFORMATIVE ACTION (LOCKED TERMINAL) - Módulo ND_MISSIONS
 * Notifica o jogador sobre os requisitos de acesso ao terminal (Cor do Cartão).
 */

class alpActionServerConsoleLocked: ActionInteractBase
{
	protected string alp_Title;

	void alpActionServerConsoleLocked()
	{
		m_CommandUID    = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask    = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem   = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject()) return false;

		// Validação de foco: Painel de interface (Index 1)
		if (target.GetComponentIndex() != 1) return false;

		alp_ServerConsole console;
		alp_AccessCard_Base card;
		
		if (Class.CastTo(console, target.GetObject()))
		{
			// Tenta identificar se o jogador já segura um cartão (mesmo que errado)
			Class.CastTo(card, item);

			// Condições para exibir o aviso de bloqueio:
			// 1. Terminal suporta trancas e está atualmente bloqueado.
			// 2. Hardware não está destruído.
			// 3. O jogador NÃO possui a credencial correta ativa.
			if (console.CanBeLockedALP() && console.IsLockedALP() && !console.IsRuinedALP())
			{
				if (!card || card.GetKeyID() != console.GetAccesCardID())
				{
					// Lado do Cliente: Processa a mensagem informativa do HUD
					if (GetGame().IsClient())
					{
						SetActionTextALP(console.GetAccesCardID());
					}
					return true;
				}
			}
		}
		
		return false;
	}
	
	/**
	 * Constrói dinamicamente a string de exibição baseada no ID de segurança do console.
	 * @param id: Identificador da cor/nível do cartão de acesso.
	 */
	void SetActionTextALP(int id)
	{
		alp_Title = "#alp_action_console_requirescard"; // Prefixo: "Requer Cartão"
		
		string cardColorName = "";
		switch(id)
		{
			case 0: cardColorName = alpUF.GetDisplayName("alp_AccessCardRed"); break;
			case 1: cardColorName = alpUF.GetDisplayName("alp_AccessCardBlue"); break;
			case 2: cardColorName = alpUF.GetDisplayName("alp_AccessCardYellow"); break;
			case 3: cardColorName = alpUF.GetDisplayName("alp_AccessCardGreen"); break;
			case 4: cardColorName = alpUF.GetDisplayName("alp_AccessCardBlack"); break;
			default: cardColorName = "???"; break;
		}
		
		// Exemplo de saída: "Requer Cartão (Cartão de Acesso Vermelho)"
		alp_Title += " (" + cardColorName + ")";
	}

	// Lógica de servidor nula para ações puramente visuais
	override void OnExecuteServer(ActionData action_data) {}
};