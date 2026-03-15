/**
 * @class   alpActionExamination
 * @brief   Ação de exame médico via NPC com cobrança e sincronização de dados
 * Auditado em: 2026 - Foco em Integridade Financeira e Sincronização de HUD
 */
class alpActionExamination: ActionInteractBase
{
	string alp_Text;
	
	void alpActionExamination()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(4);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return alp_Text;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsClient() && GetGame().GetUIManager().FindMenu(ALP_MENU_EXAMINATION))
			return false;		
		
		alpNPC ntarget = alpNPC.Cast(target.GetObject());
		if (ntarget && ntarget.IsAlive() && ntarget.IsMedic())
		{
			int fee = GetND().GetRP().GetInteractions().MedicalFees.Fee;
			
			// Verifica se o jogador tem saldo suficiente no sistema de RP
			if (player.GetRP() && player.GetRP().GetCurrency() < fee)
				return false;

			alp_Text = "#npc_medicalexamination " + fee.ToString();
			return true;
		}
		return false;		
	}

	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );
		PlayerBase player = action_data.m_Player;

		if (npc && player && player.GetRP())
		{
			// 1. Cobrança do serviço (Adicionado: Faltava subtrair o valor)
			int fee = GetND().GetRP().GetInteractions().MedicalFees.Fee;
			player.GetRP().ChangeCurrency(-fee);

			// 2. Revelação de Tipo Sanguíneo (Se configurado)
			if ( !player.HasBloodTypeVisible() && GetND().GetRP().GetInteractions().MedicalFees.EnabledBloodTest )
			{
				PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
				if (module_lifespan)
				{
					int blood_type = player.GetStatBloodType().Get();
					module_lifespan.UpdateBloodType( player, blood_type );
					module_lifespan.UpdateBloodTypeVisibility( player, true );
				}
			}					
			
			// 3. Sincronização de Diagnóstico
			// Registra para estatísticas para que o cliente receba os dados de doenças
			player.GetSyncData().RegisterToStats( true );					
			player.GetSyncData().ForceSync();

			// 4. Interface de Estoque/Relatório
			// Abre a interface de relatório médico via ID de estoque do NPC
			GetND().GetMS().GetTrader().GiveMeStock( npc.alp_StockID , player, true );
		}		
	}
};