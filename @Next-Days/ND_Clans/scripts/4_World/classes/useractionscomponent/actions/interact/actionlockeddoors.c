// CORREÇÃO 1: Herança corrigida para respeitar a estrutura Vanilla do DayZ
modded class ActionLockedDoors: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// 2. Proteções de Null Pointer
		if( !target || !player ) return false;
		if( !IsBuilding(target) ) return false;
		if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;

		Building building;
		if( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				if (building.IsDoorLocked(doorIndex))
				{
					int idPP = player.GetPlayerID();	
					BuildingBase bb = BuildingBase.Cast( building );
					
					// Prevenção de NPE no BuildingBase
					if ( bb && bb.IsEnabledFingerPringLock() )
					{
						// Se o player for membro/dono, ele NÃO usa a ação "Locked Door". 
						// Ele usa a ação de abrir (ActionOpenDoors) por ter a biometria.
						if ( bb.GetOwnerID() == idPP || VerifyClanPermission( player, bb ) )
						{					
							return false;	
						}
					}
					
					// Se for INIMIGO, a ação aparece apenas para gerar o barulho da maçaneta forçada.
					return true;
				}								
			}
		}
		return false;
	}

	// CORREÇÃO 3: O método OnStartServer com `building.OpenDoor()` FOI DELETADO.
	// Inimigos não poderão mais usar esse exploit para abrir as bases magicamente.
	
	override void OnEndServer(ActionData action_data)
	{
		// Mantém apenas a mecânica Vanilla de fazer barulho para alertar os donos da base
		m_NoisePar = new NoiseParams();
		m_NoisePar.LoadFromPath("CfgVehicles SurvivorBase NoiseActionDefault");
		NoiseSystem noise = GetGame().GetNoiseSystem();
		
		if (noise && action_data.m_Player && action_data.m_Target.GetObject())
		{
			noise.AddNoisePos(action_data.m_Player, action_data.m_Target.GetObject().GetPosition(), m_NoisePar);
		}
	}	
	
	override void OnStartClient( ActionData action_data )
	{
		// Comportamento vazio do Vanilla mantido
	}		
	
	// CORREÇÃO 4: Inserção do método de verificação para corrigir o Compile Error de escopo
	bool VerifyClanPermission( PlayerBase player, BuildingBase building )
	{
		if (!player || !building) return false;

		int clanID = player.GetClanID();		
		if ( clanID < 0 ) return false;
		if ( clanID != building.GetClanID() ) return false;
		if ( !building.CanUseFingerPrints() ) return false;
		
		return true;
	}
};