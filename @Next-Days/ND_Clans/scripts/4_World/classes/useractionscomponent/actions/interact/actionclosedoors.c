modded class ActionCloseDoors: ActionInteractBase
{
	override void OnExecute( ActionData action_data )
	{
		// 1. OBRIGATÓRIO: Mantém o comportamento vanilla de fechar a porta
		super.OnExecute(action_data);

		// 2. CORREÇÃO: Proteção vital contra Null Pointer Crash
		if (!action_data.m_Target || !action_data.m_Player) return;

		BuildingBase building;
		
		if( Class.CastTo(building, action_data.m_Target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			
			if (doorIndex != -1 && building.IsEnabledFingerPringLock())
			{
				int idPP = action_data.m_Player.GetPlayerID();
				
				if ( idPP == building.GetOwnerID() || VerifyClanPermission( action_data.m_Player, building ) )
				{
					// 3. CORREÇÃO: Prevenção de Desync de Portas. 
					// Mudanças de estado físico OBRIGATORIAMENTE devem rodar apenas no Servidor.
					if (GetGame().IsServer())
					{
						building.LockDoor(doorIndex);
					}
					
					// Efeitos visuais/sonoros rodam no Client
					if (GetGame().IsClient())
					{
						SEffectManager.PlaySound("alp_LockingHouse_SoundSet", action_data.m_Player.GetPosition() );	
					}
				}
			}
		}		
	}
	
	bool VerifyClanPermission( PlayerBase player, BuildingBase building )
	{
		// 4. CORREÇÃO: Blindagem de memória no método auxiliar
		if (!player || !building) return false;

		int clanID = player.GetClanID();		
		
		if ( clanID < 0 ) 
		{
			return false;
		}		
		if ( clanID != building.GetClanID() ) 
		{
			return false;
		}				
		if ( !building.CanUseFingerPrints() ) 
		{
			return false;
		}
		
		return true;
	}
}