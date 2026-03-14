class alpActionLockDoorsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);//UATimeSpent.LOCK
	}
};

class alpActionLockDoors: ActionContinuousBase
{	
	void alpActionLockDoors()
	{
		m_CallbackClass = alpActionLockDoorsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor;
	}
		
	// NOTA DE ARQUITETURA: Em DayZ, Actions são Singletons. 
	// Usar variáveis globais de classe como 'alp_DoorIndex' pode causar race conditions no UI,
	// mas como é apenas para o GetText() no client, mantivemos com reset preventivo na ActionCondition.
	int alp_DoorIndex = -1;
	
	override string GetText()
	{
		return "#lock_door - ID:" + alp_DoorIndex.ToString();
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		alp_DoorIndex = -1;
		if( !target || !item ) return false;
		if( !IsBuilding(target) ) return false;
		if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;

		BuildingBase building;
		if( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				alp_DoorIndex = doorIndex;
				
				if (!building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex) )
				{					
					alp_HouseKey_Base key = alp_HouseKey_Base.Cast(item);
					
					// CORREÇÃO 1: Proteção contra Null Pointer Exception (NPE)
					if ( !key ) return false;
															
					if ( ( key.GetHouseID() == building.GetKeyID() && (key.GetKeyID() == -1 || key.GetKeyID() == doorIndex  ) ) || key.IsAdminKey() )
					{
						return true;
					}
				}
				return false;
			}
		}		
		return false;
	}

	protected void LockDoor(ActionTarget target, alp_HouseKey_Base key)
	{
		// CORREÇÃO 2: Proteção dupla no servidor contra Null Pointer Crash
		if (!key) return; 

		BuildingBase building;

		if ( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			
			// CORREÇÃO 3: Exploit de Segurança resolvido. 
			// O servidor agora verifica OBRIGATORIAMENTE se a chave pertence àquela casa antes de trancar.
			if ( doorIndex != -1 )
			{
				bool isKeyValid = ( key.GetHouseID() == building.GetKeyID() && (key.GetKeyID() == -1 || key.GetKeyID() == doorIndex) ) || key.IsAdminKey();
				
				if ( isKeyValid )
				{
					building.LockDoor(doorIndex);
				}
			}		
		}
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		// O Cast seguro foi blindado pelo Null Check interno na primeira linha do método LockDoor
		LockDoor(action_data.m_Target, alp_HouseKey_Base.Cast(action_data.m_MainItem) );
	}
	
	override protected void OnStartAnimationLoopClient( ActionData action_data )
	{
		super.OnStartAnimationLoopClient(action_data);
		LockingClient(action_data.m_Player, action_data.m_Target, alp_HouseKey_Base.Cast(action_data.m_MainItem) );		
	}
	
	protected void LockingClient(PlayerBase player, ActionTarget target, alp_HouseKey_Base key)
	{
		// CORREÇÃO 4: Proteção contra Crash no Client
		if (!key) return;
	
		BuildingBase building;

		if ( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				// CORREÇÃO 5: Replica da validação rigorosa também nos sons do client
				bool isKeyValid = ( key.GetHouseID() == building.GetKeyID() && (key.GetKeyID() == -1 || key.GetKeyID() == doorIndex) ) || key.IsAdminKey();
				
				if ( isKeyValid )
				{
					SEffectManager.PlaySound("alp_LockingHouse_SoundSet", player.GetPosition() );	
				}
				else
				{
					SEffectManager.PlaySound("lockpicker_move_out_SoundSet", player.GetPosition() );	
				}
			}		
		}	
	}
};