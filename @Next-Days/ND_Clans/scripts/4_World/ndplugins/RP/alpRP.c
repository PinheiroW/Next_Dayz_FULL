modded class alpRP 
{
	// Dados de território do cliente
	bool alp_IamHome = false;
	bool alp_Camera3rdPerson;	
	
	string alp_CLIENT_DATA = "$profile:nextdays.json";
	
	ref alpClanData alp_Clan;
	ref alpCLANoptionsClient alp_ClanClient;
	
	override void Init()
	{
		super.Init();
				
		if ( GetGame().IsClient() )
		{
			alp_ClanClient = new alpCLANoptionsClient();
			// Inicializa o carregamento no frame seguinte para garantir que o player exista
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.LoadClientData, 0 );	
		}
	}
	
	void LoadClientData()
	{
		// Verifica se o player local é o dono desta instância de RP
		if ( GetGame().GetPlayer() && GetGame().GetPlayer() == GetPlayer() )
		{
			if ( !FileExist(alp_CLIENT_DATA) )
			{ 			
				// Se não existe, cria o arquivo com valores padrão
				JsonFileLoader<alpCLANoptionsClient>.JsonSaveFile(alp_CLIENT_DATA, alp_ClanClient);
			}
			else 
			{
				// Se existe, apenas carrega
				JsonFileLoader<alpCLANoptionsClient>.JsonLoadFile(alp_CLIENT_DATA, alp_ClanClient);	
			}
			// CORREÇÃO: Removido o save redundante que existia após o load.
		}		
	}

	alpCLANoptionsClient GetClientData()
	{
		return alp_ClanClient;
	}
	
	void SetClan(alpClanData clan)
	{
		alp_Clan = clan;
	}
	
	alpClanData GetClan()
	{
		return alp_Clan;
	}
		
	void SaveClientData()
	{
		JsonFileLoader<alpCLANoptionsClient>.JsonSaveFile(alp_CLIENT_DATA, alp_ClanClient);	
	}
	
	bool IsHome()
	{
		return alp_IamHome;
	}	
	
	void SetHome(bool state, bool camera)
	{
		alp_IamHome = state;
		
		// CORREÇÃO 1: Failsafe para evitar Crash de script
		if ( !GetND() || !GetND().GetClans() || !GetND().GetClans().GetOptions() )
			return;

		auto options = GetND().GetClans().GetOptions();

		// Gerenciamento de Câmera em áreas restritas (1ª vs 3ª pessoa)
		if ( GetGame().GetWorld().Is3rdPersonDisabled() && (options.Enable3rdPersonCameraAtHome || options.Enable3rdPersonCameraAtSafeZone || options.Enable3rdPersonCameraInVehicle) )
		{
			PlayerBase player = PlayerBase.Cast(GetPlayer());
			if (!player) return;

			if ( camera && alp_Camera3rdPerson )
			{
				// CORREÇÃO 2: Uso da referência direta ao player para evitar Null Pointer
				player.Set3DcameraALP( true );	
			}
			else
			{
				player.Set3DcameraALP( false );	
				if ( alp_Camera3rdPerson )
				{
					alp_Camera3rdPerson = false;					
				}
			}
		}
	}	
	
	bool HasPDA()
	{
		return true;
	}
}