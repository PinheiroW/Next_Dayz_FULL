
modded class ActionLockedDoors: ActionOpenDoors
{


	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;
		//if( IsDamageDestroyed(action_data.m_Target) ) return false;
		if( !IsBuilding(target) ) return false;
		if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;

		Building building;
		if( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				if  (building.IsDoorLocked(doorIndex))
				{
					int idPP = player.GetPlayerID();	
					BuildingBase bb = BuildingBase.Cast( building );
					if ( bb  && bb.IsEnabledFingerPringLock() && ( bb.GetOwnerID() == idPP ||  VerifyClanPermission( player , bb ) ) )
					{					

						return false;	
					}
					return true;
				}
								
			}
		}
		return false;
	}

	override void OnStartServer(ActionData action_data)
	{
	
		Building building;
		if (Class.CastTo(building, action_data.m_Target.GetObject()))
		{
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			if (doorIndex != -1)
			{
				building.OpenDoor(doorIndex);
			}
		}
	}
	
	override void OnEndServer(ActionData action_data)
	{
		m_NoisePar = new NoiseParams();
		m_NoisePar.LoadFromPath("CfgVehicles SurvivorBase NoiseActionDefault");
		NoiseSystem noise = GetGame().GetNoiseSystem();
		if (noise)
		{
			if (action_data.m_Player)
				noise.AddNoisePos(action_data.m_Player, action_data.m_Target.GetObject().GetPosition(), m_NoisePar);
		}
	}	
	override void OnStartClient( ActionData action_data )
	{

	}		
};

