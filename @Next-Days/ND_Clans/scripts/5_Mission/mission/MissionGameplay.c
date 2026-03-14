modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate( timeslice );	
	
		// CORREÇÃO: Failsafe para evitar crash se os plugins não estiverem inicializados
		if (!GetGame() || !GetND() || !GetND().GetClans() || !GetND().GetClans().GetOptions())
			return;

		auto options = GetND().GetClans().GetOptions();

		// Gerenciamento de Câmera 3ª Pessoa em servidores que a desabilitam (Hardcore)
		if ( GetGame().GetWorld().Is3rdPersonDisabled() && ( options.Enable3rdPersonCameraAtHome || options.Enable3rdPersonCameraAtSafeZone || options.Enable3rdPersonCameraInVehicle ) )
		{
			Input input = GetGame().GetInput();
		
			if ( input && input.LocalPress("UAPersonView", false) )
			{
				PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
				
				if ( player && player.GetRP() )
				{
					// Alterna o estado da câmera no plugin de RP do jogador
					player.GetRP().alp_Camera3rdPerson = !player.GetRP().alp_Camera3rdPerson;							
				}			
			}	
		}
	}
	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if (key == KeyCode.KC_ESCAPE)
		{
			// CORREÇÃO: Validação do UI Manager antes de tentar fechar o menu
			auto uiManager = GetUIManager();
			if (uiManager && uiManager.FindMenu(ALP_MENU_MANAGE_PLOTPOLE))
			{
				uiManager.CloseMenu(ALP_MENU_MANAGE_PLOTPOLE);
			}			
		}
	}
}