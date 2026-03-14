modded class IngameHud
{
	float alp_TimeUpdateIcon;
	int alp_NICK_DISTANCE;
			
	override void Update( float timeslice )
	{
		super.Update( timeslice );

		// Atualização de ícones de membros do clã (Otimizado para 20Hz)
		alp_TimeUpdateIcon += timeslice;
		if ( alp_TimeUpdateIcon > 0.05 )
		{
			ShowMembersIcon();
			alp_TimeUpdateIcon = 0;
		}
	}	
	
	ref map<int, ref alpMemberIcon> alp_MemberIcons = new map<int, ref alpMemberIcon>;
	
	void HideAllIcons()
	{
		if (!alp_MemberIcons) return;
		foreach( alpMemberIcon icon : alp_MemberIcons)
		{
			if (icon) icon.Show( false, 0, 0, 0);
		}
	}
	
	void ShowMembersIcon()
	{
		HideAllIcons();
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player || !player.GetRP() || !player.GetRP().GetClientData()) return;

		// CORREÇÃO 1: Failsafe para Trader Zone e Opções do Mod
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetOptions()) return;

		bool inTraderZone = false;
		if (player.GetSyncData())
		{
			auto syncElement = player.GetSyncData().GetElement( alpRPelements.ISINTRADERZONE );
			if (syncElement) inTraderZone = syncElement.GetValue();
		}

		if ( player.GetRP().GetClientData().ShowPlayersIcontem )
		{
			alpClanData clan = player.GetRP().GetClan();
			auto options = GetND().GetClans().GetOptions();
			
			if ( clan || inTraderZone )
			{
				float view = options.ShowIconDistance;
				alp_NICK_DISTANCE = options.ShowNickDistance;
				
				if ( player.IsInOptics() ) 
				{
					EntityAI entityInHands = player.GetItemInHands();
					ItemOptics optic;
					
					if ( entityInHands && Class.CastTo(optic, entityInHands) ) {}
					else if ( entityInHands && entityInHands.IsInherited(Weapon) )
					{
						optic = ItemOptics.Cast( Weapon.Cast( entityInHands ).GetAttachedOptics() );
					}
	
					if ( optic )
					{
						float viewInOptic = optic.GetZeroingDistanceZoomMax();						
						view = Math.Max( viewInOptic, view );
						alp_NICK_DISTANCE = Math.Max( view / 2, alp_NICK_DISTANCE);
					}					
				}
				
				// CORREÇÃO 2: Verificação de segurança no loop de jogadores
				foreach( Man man : ClientData.m_PlayerBaseList )
				{
					PlayerBase member;
					if (Class.CastTo(member, man) && member.IsAlive() && member.GetIdentity() && member != player && !member.IsInVehicle())
					{	
						float dist = vector.Distance( player.GetPosition(), member.GetPosition() );
						int memberID = member.GetPlayerID();	
												
						if ( clan && clan.IsMember(memberID) )
						{					
							if ( dist <= view ) SetPlayerIconALP(member, dist, view, options);
						}
						else if ( inTraderZone && options.ShowIconsInTradeZone )
						{
							if ( dist < 20 ) SetPlayerIconALP(member, dist, 20, options, true);
						}
					}
				}	
			}
		}
	}

	protected void SetPlayerIconALP(PlayerBase player, float dist, float view, alpClans_BasisOptions options, bool nofade = false )
	{
		if (!player || !player.GetIdentity()) return;

		int playerID = player.GetPlayerID();
		string name  = player.GetIdentity().GetName();
		
		int a = options.ClanMemberIconColor[0];
		int r = options.ClanMemberIconColor[1];
		int g = options.ClanMemberIconColor[2];
		int b = options.ClanMemberIconColor[3];
		
		bool head = dist < alp_NICK_DISTANCE;
		vector partPos;
		int indexPart; // CORREÇÃO: Ponto e vírgula adicionado
		
		if ( head ) indexPart = player.GetBoneIndexByName( "Head" );
		else indexPart = player.GetBoneIndexByName( "Spine3" );
		
		partPos = player.GetBonePositionWS( indexPart );		

		vector screnPos = GetScreenPosALP( partPos );
		if (screnPos != vector.Zero )
		{
			if ( !nofade )
			{
				float colorCoef = Math.Clamp( 1 - dist / ( view + 0.01 ), 0, 1 );
				a = (colorCoef * ( a * 0.7)) + (0.3 * a);		
			}
			
			int colorA = ARGB( a, r, g, b );
			alpMemberIcon icon;						
			float offset = head ? 30 : 0;
			
			if ( alp_MemberIcons.Find( playerID, icon ) && icon )
			{
				icon.Show( true, (screnPos[0] - offset), screnPos[1], colorA, head);
			}
			else
			{
				icon = new alpMemberIcon( name, colorA );
				icon.Show( true, (screnPos[0] - offset ), screnPos[1], colorA, head);
				alp_MemberIcons.Set( playerID, icon );								
			}
		}	
	}
		
	protected vector GetScreenPosALP(vector pWorldPos)
	{
		vector screen_pos = GetGame().GetScreenPosRelative( pWorldPos + "0 0.3 0");
		if( screen_pos[0] >= 1 || screen_pos[0] <= 0 || screen_pos[1] >= 1 || screen_pos[1] <= 0 || screen_pos[2] < 0) 
			return vector.Zero;
		
		return GetGame().GetScreenPos( pWorldPos + "0 0.3 0");
	}	
}

class alpMemberIcon
{
	Widget alp_Icon;
	TextWidget alp_PlayerNameText;
	Widget alp_PlayerBod;
	
	void alpMemberIcon(string name, int color )
	{
		alp_Icon = GetGame().GetWorkspace().CreateWidgets( "ND_Clans/gui/layouts/PlayerIcon.layout" );			
		if (!alp_Icon) return;

		Class.CastTo(alp_PlayerNameText, alp_Icon.FindAnyWidget("PlayerName"));
		Class.CastTo(alp_PlayerBod, alp_Icon.FindAnyWidget("PlayerBod"));
		
		string displayName = name;
		if (displayName.Length() > 6 ) displayName = displayName.Substring(0, 5) + ".";
		
		if (alp_PlayerNameText)
		{
			alp_PlayerNameText.SetText( displayName );
			alp_PlayerNameText.SetColor(color);
		}
		if (alp_PlayerBod) alp_PlayerBod.SetColor(color);
	}

	void ~alpMemberIcon()
	{
		if ( alp_Icon ) alp_Icon.Unlink();
	}
	
	void Show(bool state, float x, float y, int color, bool nick = true)
	{
		if (!alp_Icon) return;
		alp_Icon.SetPos(x, y);
		alp_Icon.Show(state);
		
		if (alp_PlayerNameText)
		{
			alp_PlayerNameText.Show(nick);
			alp_PlayerNameText.SetColor(color);
		}
		if (alp_PlayerBod)
		{
			alp_PlayerBod.Show(!nick);
			alp_PlayerBod.SetColor(color);
		}
	}
}