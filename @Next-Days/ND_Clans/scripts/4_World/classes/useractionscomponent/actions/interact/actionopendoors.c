modded class ActionOpenDoors: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if( target && IsBuilding(target) )
		{				
			BuildingBase building;
			if( Class.CastTo(building, target.GetObject()) )
			{
				int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
				
				if ( doorIndex != -1 && building.IsDoorLocked(doorIndex) )
				{
					// Se a porta estiver TRANCADA, injetamos a lógica de biometria do mod (Fingerprint)
					if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;
					
					int idPP = player.GetPlayerID();
					if ( building.IsEnabledFingerPringLock() && (building.GetOwnerID() == idPP || VerifyClanPermission(player, building)) )
					{																		
						return true; // Biometria aceita: Permite abrir a porta.
					} 	
					
					return false; // Biometria negada ou não configurada: Barra a ação.
				}
			}
		}
		
		// CORREÇÃO 1: Fallback para a Engine (Garante estabilidade e compatibilidade com outros Mods)
		// Caso não seja porta de base ou não esteja trancada, o Vanilla assume as regras.
		return super.ActionCondition(player, target, item);
	}

	override void OnStartServer( ActionData action_data )
	{
		// CORREÇÃO 2: Proteção da Engine contra Memory Crash
		if (!action_data.m_Target || !action_data.m_Player) return;

		BuildingBase building;
		if( Class.CastTo(building, action_data.m_Target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			
			if( doorIndex != -1 && building.IsDoorLocked(doorIndex) )
			{
				// CORREÇÃO 3: Fim do Exploit. O Servidor agora OBRIGATORIAMENTE testa 
				// a permissão biométrica antes de ceder o destrancamento a um RPC aleatório.
				int idPP = action_data.m_Player.GetPlayerID();
				
				if ( building.IsEnabledFingerPringLock() && (building.GetOwnerID() == idPP || VerifyClanPermission(action_data.m_Player, building)) )
				{
					building.UnlockDoor(doorIndex);
				}
				else
				{
					// Cheater tentou forçar pacote de rede em base inimiga. Cancelamos.
					return;
				}
			}
		}
		
		super.OnStartServer( action_data );
	}

	override void OnStartClient( ActionData action_data )
	{
		if (!action_data.m_Target || !action_data.m_Player) return;

		BuildingBase building;
		if( Class.CastTo(building, action_data.m_Target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			
			if( doorIndex != -1 && building.IsDoorLocked(doorIndex) )
			{
				// CORREÇÃO 4: O destrancamento mecânico do Client foi deletado para 
				// evitar o bug do "Door Desync". Aqui roda apenas os sons visuais/locais.
				int idPP = action_data.m_Player.GetPlayerID();
				
				if ( building.IsEnabledFingerPringLock() && (building.GetOwnerID() == idPP || VerifyClanPermission(action_data.m_Player, building)) )
				{
					SEffectManager.PlaySound("alp_UnLockingHouse_SoundSet", action_data.m_Player.GetPosition() );	
				}
			}
		}
		
		super.OnStartClient( action_data );
	}	
	
	bool VerifyClanPermission( PlayerBase player, BuildingBase building )
	{
		// CORREÇÃO 5: Proteção de Memória
		if (!player || !building) return false;

		int clanID = player.GetClanID();		
		
		if ( clanID < 0 ) return false;
		if ( clanID != building.GetClanID() ) return false;
		if ( !building.CanUseFingerPrints() ) return false;
		
		return true;
	}
};