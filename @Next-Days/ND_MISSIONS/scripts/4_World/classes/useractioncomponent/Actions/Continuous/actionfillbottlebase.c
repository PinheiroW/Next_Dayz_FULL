

modded class ActionFillBottleBase: ActionContinuousBase
{
/*
#ifdef NAMALSK_SURVIVAL	
	protected float m_TargetWet = 2.0;

	override int GetLiquidType( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// liquid sources on objects
		if (target.GetObject() && (target.GetObject().IsWell()))
		{
			// wells do not have ice nor freezing water
			m_TargetWet = 0.0;
			
			if  ( player.GetRP().IsRadiationHigh() )
			{
				return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
			}
			else
			{
			
				return LIQUID_WATER; 
			}			
			
		} 
		if (target.GetObject() && target.GetObject().IsFuelStation())
		{
			// gas is also just fine (freezing point different than water (-40C), lets not complicate things more)
			m_TargetWet = 0.0;
			return LIQUID_GASOLINE;
		}

		// liquid sources on surface
		vector pos_cursor = target.GetCursorHitPos();
		string surface_type = "";
		GetGame().SurfaceGetType(pos_cursor[0], pos_cursor[2], surface_type);
		switch (surface_type) 
		{
			case "nam_seaice":
			case "nam_lakeice_ext":
			case "nam_snow":
			{
				m_TargetWet = 3.0;
				if  ( player.GetRP().IsRadiationHigh() )
				{
					return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
				}
				else
				{
				
					return LIQUID_WATER; 
				}
				break;
			}
			case "nam_lakewater_ext":
			{
				m_TargetWet = 2.0;
				if  ( player.GetRP().IsRadiationHigh() )
				{
					return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
				}
				else
				{
				
					return LIQUID_WATER; 
				}
				break;
			}
			default:
			{
				return -1;
			}
		}
		return -1;
	}	
	
#else	
	*/
	override int GetLiquidType( PlayerBase player, ActionTarget target, ItemBase item )
	{
		int liquidType = LIQUID_NONE;
		if ( target.GetObject() )
		{
			liquidType = target.GetObject().GetLiquidSourceType();							
		}
		else
		{
			string surfaceType;
			vector hit_pos = target.GetCursorHitPos();
			GetGame().SurfaceGetType3D(hit_pos[0], hit_pos[1], hit_pos[2], surfaceType);
			if (surfaceType == "")
			{
				if ( hit_pos[1] <= g_Game.SurfaceGetSeaLevel() + 0.001 )
				{
					liquidType = LIQUID_SALTWATER;
				}
			}
			else
			{
				liquidType = SurfaceInfo.GetByName(surfaceType).GetLiquidType();
			}
		}
		int liguidMask = LIQUID_WATER | LIQUID_RIVERWATER | LIQUID_FRESHWATER | LIQUID_STILLWATER | LIQUID_HOTWATER | LIQUID_CLEANWATER;
		
		if (liquidType & liguidMask)
		{
			if  ( player.GetRP().IsRadiationHigh() )
			{
				liquidType = LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
			}	
		}			
				
		return liquidType & m_AllowedLiquidMask;		
	}
//#endif		
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Well well;
		FuelStation station;
		
		if ( GetND().GetResources().GetOptions().EnableWellManagement &&  Class.CastTo( well, target.GetObject() )  && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}
		else if ( GetND().GetResources().GetOptions().EnableFuelstationManagement && Class.CastTo( station, target.GetObject() )  && GetGame().IsServer() && !station.HasFuelALP()  )
		{
			return false;
		}
		
		return super.ActionCondition(  player,  target,  item );
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{
		Well well;
		FuelStation station;
		
		if ( GetND().GetResources().GetOptions().EnableWellManagement && Class.CastTo( well, action_data.m_Target.GetObject() )  && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}
		else if ( GetND().GetResources().GetOptions().EnableFuelstationManagement && Class.CastTo( station, action_data.m_Target.GetObject() )  && GetGame().IsServer() && !station.HasFuelALP() )
		{
			return false;	
		}
		return super.ActionConditionContinue(action_data ) ;
	}
	
	
	override void OnStartServer(ActionData action_data)
	{
		
		super.OnStartServer(action_data);
		Well well;
		if ( GetND().GetResources().GetOptions().EnableWellManagement && Class.CastTo( well, action_data.m_Target.GetObject() )  ) 
		{
			well.SaveCurrentAmmount();
		}

		FuelStation station;
		if ( GetND().GetResources().GetOptions().EnableFuelstationManagement &&  Class.CastTo( station, action_data.m_Target.GetObject() )  ) 
		{
			station.SaveCurrentAmmount();
		}			
	}
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		Well well;
		if ( GetND().GetResources().GetOptions().EnableWellManagement  &&  Class.CastTo( well, action_data.m_Target.GetObject() ) ) 
		{
			well.SaveWellALP();
		}		
		FuelStation station;
		if ( GetND().GetResources().GetOptions().EnableFuelstationManagement &&  Class.CastTo( station, action_data.m_Target.GetObject() )  ) 
		{
			station.SaveFuelStationALP();
		}			
	}	
	

	

};