modded class DayZPlayerImplement
{
	bool alp_Is3rdPerson;
	
	override void HandleView()
	{	
		super.HandleView();
		
		// CORREÇÃO 1: Failsafe contra Null Pointer Exception (NPE)
		// Impede o fechamento do jogo caso o mod core não esteja pronto no frame atual
		if ( !GetND() || !GetND().GetClans() || !GetND().GetClans().GetOptions() )
			return;

		// CORREÇÃO 2: Verificação de configurações de mundo e permissões do clã
		if ( GetGame().GetWorld().Is3rdPersonDisabled() )
		{
			auto options = GetND().GetClans().GetOptions();
			
			// Se 3ª pessoa estiver desabilitada no servidor, permitimos apenas em zonas específicas configuradas
			if ( options.Enable3rdPersonCameraAtHome || options.Enable3rdPersonCameraAtSafeZone || options.Enable3rdPersonCameraInVehicle )
			{
				m_Camera3rdPerson = alp_Is3rdPerson;				
			}
		}
	}
	
	void Set3DcameraALP(bool state)
	{
		alp_Is3rdPerson = state;	
	}	
}