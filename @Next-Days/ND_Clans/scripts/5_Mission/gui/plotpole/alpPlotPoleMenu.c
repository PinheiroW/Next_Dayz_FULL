modded class alpInfoPlayerMenu
{
	// UI Widgets
	Widget alp_WindowClan;
	EditBoxWidget alp_NameOfClan;
	TextListboxWidget alp_ClanMembers;
	TextWidget alp_ClanName;

	ButtonWidget alp_ButtonNewClan;
	ButtonWidget alp_ButtonLeaveClan;
	ButtonWidget alp_ButtonKickMember;
	
	int alp_MembersCount;
	ref array<ButtonWidget> alp_ClanButtons; // CORREÇÃO: Adicionado ";"
	
	alpClanData alp_Clan;
			
	override Widget Init()
	{
		Widget root = super.Init();
		
		// CORREÇÃO: Failsafe para o plugin core
		if ( GetND() && GetND().GetClans() && GetND().GetClans().GetOptions().EnableClans )
		{
			// Ativa o botão do menu de clãs (ID 13 padrão do layout Next-Days)
			ButtonWidget menu = ButtonWidget.Cast( root.FindAnyWidgetById(13) );
			if (menu) menu.Show(true);	
			
			Class.CastTo(alp_WindowClan, root.FindAnyWidget("BodyWindowClan")); 	
			
			// Registro na lista de janelas (presumindo que alp_WindowRegister existe na base)
			if (alp_WindowClan) alp_WindowRegister.Insert( alp_WindowClan );	
					
			Class.CastTo(alp_NameOfClan, root.FindAnyWidget("NameOfNewClan"));
			Class.CastTo(alp_ClanMembers, root.FindAnyWidget("ClanMembers"));
			Class.CastTo(alp_ClanName, root.FindAnyWidget("ClanName"));			
			
			alp_ClanButtons = new array<ButtonWidget>;

			// Mapeamento de botões por ID
			Class.CastTo(alp_ButtonNewClan, root.FindAnyWidgetById(304));
			if (alp_ButtonNewClan) alp_ClanButtons.Insert(alp_ButtonNewClan);
            
			Class.CastTo(alp_ButtonLeaveClan, root.FindAnyWidgetById(305));
			if (alp_ButtonLeaveClan) alp_ClanButtons.Insert(alp_ButtonLeaveClan);
            
			Class.CastTo(alp_ButtonKickMember, root.FindAnyWidgetById(306));			
			if (alp_ButtonKickMember) alp_ClanButtons.Insert(alp_ButtonKickMember);
			
			InitCLan();		
		}	
		
		return root;
	}	

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (alp_WindowClan && alp_WindowClan.IsVisible())
		{
			// CORREÇÃO: Garantindo que alp_Player exista antes do acesso
			if (!alp_Player || !alp_Player.GetRP()) return;

			alp_Clan = alp_Player.GetRP().GetClan();
			
			if ( alp_Clan )
			{
				if ( alp_MembersCount != alp_Clan.Members.Count() )
				{
					InitCLan();
				}			
			}
			else if ( alp_MembersCount > 0 )
			{
				alp_MembersCount = 0;
				InitCLan();
			}
		}
	}	
		
	void InitCLan()
	{
		if (alp_Player && alp_Player.GetRP())
			alp_Clan = alp_Player.GetRP().GetClan();
				
		DisableAllClanButtons();
		InitClanList();
		SetDisplayTMIcon();
	}		

	void InitClanList()
	{
		if (!alp_ClanMembers) return;
		alp_ClanMembers.ClearItems();
		
		if ( alp_Clan )
		{
			ShowButtonALP( alp_ButtonLeaveClan );
			ShowButtonALP( alp_ButtonKickMember );
			
			if (alp_ClanName) alp_ClanName.SetText(alp_Clan.Name);	
			alp_MembersCount = alp_Clan.Members.Count();
			
			for (int i = 0; i < alp_MembersCount; i++)
			{			
				// Adiciona o nome do membro (Elemento do mapa)
				alp_ClanMembers.AddItem(alp_Clan.Members.GetElement(i), null, 0);		
				ColorizedMember(i, alp_Clan.Members.GetKey(i));				
			}			
		}	
		else
		{
			if (alp_ClanName) alp_ClanName.SetText("...");	
			ShowButtonALP( alp_ButtonNewClan );
		}		
	}	
	
	void ColorizedMember(int line, int playerID)
	{
		if (!alp_Clan || !alp_ClanMembers) return;

		if ( alp_Clan.MembersOnline.Find( playerID ) >= 0 )
		{		
			alp_ClanMembers.SetItemColor(line, 0, COLOR_AVAILABLE_POSITIVE);
		}
		else
		{
			alp_ClanMembers.SetItemColor(line, 0, COLOR_UNAVAILABLE);
		}
	}	
	
	void ShowButtonALP( ButtonWidget btn, bool state = true)
	{
		if (!btn) return;
		btn.Show(state);
		btn.Enable(state);	
		
		if (state) btn.SetColor( COLOR_AVAILABLE_POSITIVE );
		else btn.SetColor( COLOR_AVAILABLE_NEGATIVE );
	}
	
	override bool OnClickALP(Widget w)
	{
		if (!super.OnClickALP(w))
		{
			if (!w) return false;

			switch (w.GetUserID())
			{
				case 13: // Aba Clã
					HideWindows();
					if (alp_WindowClan) alp_WindowClan.Show(true);
					return true;

				case 304: // Criar
					CreateNewClan();
					return true;	

				case 305: // Sair/Disband
					LeaveClan();
					return true;		

				case 306: // Expulsar
					KickPlayer();	
					return true;	

				case 310: // Toggle Ícones
					SetDisplayTMIcon(true);	
					return true;				
			}	
			return false;		
		}
		return true;
	}	
	
	void DisableAllClanButtons()
	{
		if (!alp_ClanButtons) return;
		for(int i = 0; i < alp_ClanButtons.Count(); i++)
		{
			ShowButtonALP( alp_ClanButtons.Get(i), false );
		}
	}
		
	void SetDisplayTMIcon(bool change = false)
	{	
		CheckBoxWidget displaIcon = CheckBoxWidget.Cast(layoutRoot.FindAnyWidgetById(310));
		if (displaIcon && alp_Player && alp_Player.GetRP())
		{
			auto clientData = alp_Player.GetRP().GetClientData();
			if (!clientData) return;

			bool state = clientData.ShowPlayersIcontem;
			
			if ( change )
			{
				state = !state;
				clientData.ShowPlayersIcontem = state;
				alp_Player.GetRP().SaveClientData();
			}
			displaIcon.SetChecked(state);
		}
	}		
	
	void CreateNewClan()
	{
		if (!alp_NameOfClan || !alp_Player) return;
		string name = alp_NameOfClan.GetText();
		
		if ( name == "" )
			name = alp_Player.GetIdentity().GetName();

		GetND().GetClans().CreateNewClanRPC( alp_Player, name );
	}
	
	void LeaveClan()
	{
		if ( alp_Clan && alp_Player )
		{
			if ( alp_Player.GetPlayerID() == alp_Clan.ClanID )
				GetND().GetClans().DisbandClanRPC( alp_Player, alp_Clan.ClanID );
			else
				GetND().GetClans().LeaveClanRPC( alp_Player, alp_Clan.ClanID );
		}
	}
	
	void KickPlayer()
	{
		if ( alp_Clan && alp_ClanMembers )
		{
			int id = alp_ClanMembers.GetSelectedRow();
			if (id >= 0)
			{	
				int playerID = alp_Clan.Members.GetKey(id);
				if ( alp_Clan.ClanID != playerID )
					GetND().GetClans().KickHimRPC( alp_Player, alp_Clan.ClanID, playerID );
			}
		}
	}	
}