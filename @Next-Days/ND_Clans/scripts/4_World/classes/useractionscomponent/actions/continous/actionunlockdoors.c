modded class ActionUnlockDoorsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		BuildingBase building;
		
		// CORREÇÃO: Prevenção de Null Pointer e verificação do Target
		if( m_ActionData && m_ActionData.m_Target && Class.CastTo(building, m_ActionData.m_Target.GetObject() ) && building.IsEstateProtected() )
		{
			float time = GetTimeToBrekageLock(building);
			m_ActionData.m_ActionComponent = new CAContinuousTime(time);
		} 
		else 
		{	
			m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.UNLOCK);
		}
	}
	
	float GetTimeToBrekageLock(BuildingBase building)
	{
		// CORREÇÃO: Cacheamento de variáveis e Failsafe
		alpClanBasesOptions bases = GetND().GetClans().GetBases();
		if (!bases) return UATimeSpent.UNLOCK; // Failsafe fallback
		
		if (building.HasLockProtection())
		{
			return bases.Raid_Picklock_Tier2[0];				
		} 
		else 
		{
			return bases.Raid_Picklock_Tier1[0];		
		}
	}
};

modded class ActionUnlockDoors: ActionContinuousBase
{
	void ActionUnlockDoors()
	{
		m_CallbackClass = ActionUnlockDoorsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}	
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (super.ActionCondition(player, target, item))
		{
			BuildingBase building;
			if( Class.CastTo(building, target.GetObject()) && building.GetOwnerID() > 0 && building.HasLockProtection() )
			{	
				// CORREÇÃO: Proteção de memória na leitura
				alpClanBasesOptions bases = GetND().GetClans().GetBases();
				if (bases && !bases.IsPossibleToBreakLockTier2)
				{
					return false;								
				}
			}		
			return true;
		}
		return false;
	}
	
	override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);
		BuildingBase building;
		
		if( action_data.m_Target && Class.CastTo(building, action_data.m_Target.GetObject()) && building.IsEstateProtected() ) 
		{					
			GetND().GetClans().SendAlertMessage( building.GetPosition(), building.GetOwnerID() , building.GetClanID() );
		}		
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		BuildingBase building;
		if( action_data.m_Target && Class.CastTo(building, action_data.m_Target.GetObject()) && building.IsEstateProtected() )
		{	
			// CORREÇÃO DE PERFORMANCE: Acessamos o plugin apenas 1 vez e salvamos na memória local (Otimização pesada)
			alpClanBasesOptions bases = GetND().GetClans().GetBases();
			if (!bases) return; // Segurança caso a configuração ainda não tenha carregado

			float chance, damage;			
			
			if ( GetND().GetClans().IsPlayerInGame( building.GetOwnerID() ) || ( building.GetClanID() > 0 &&  GetND().GetClans().IsClanInGame( building.GetClanID() ) ) ) 
			{				
				if (building.HasLockProtection())
				{
					chance = bases.Raid_Picklock_Tier2[1];
					damage = bases.Raid_Picklock_Tier2[3];		
				}
				else
				{
					chance = bases.Raid_Picklock_Tier1[1];		
					damage = bases.Raid_Picklock_Tier1[3];	
				}
			} 
			else 
			{
				if (building.HasLockProtection())
				{
					chance = bases.Raid_Picklock_Tier2[2];
					damage = bases.Raid_Picklock_Tier2[3];		
				} 
				else 
				{
					chance = bases.Raid_Picklock_Tier1[2];	
					damage = bases.Raid_Picklock_Tier1[3];
				}						
			}
			
			if ( chance >= Math.RandomFloat01() ) 
			{			
				UnlockDoor(action_data.m_Target);				
				
				// CORREÇÃO DE SEGURANÇA: Null Check no RP Engine
				if(action_data.m_Player && action_data.m_Player.GetRP())
				{
					if (action_data.m_Player.GetRP().IsHero() ) 
					{
						action_data.m_Player.GetRP().ChangeReputation( GetND().GetRP().GetReputationBonusLockPicking(ALP_RP_HERO) );				
					} 
					else 
					{	
						action_data.m_Player.GetRP().ChangeReputation( GetND().GetRP().GetReputationBonusLockPicking(ALP_RP_BANDIT) );
					}								
				}					
			}
			
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
			
			if ( action_data.m_MainItem ) 
			{
				damage = damage * action_data.m_MainItem.GetMaxHealth("","Health");
				action_data.m_MainItem.DecreaseHealth("","Health",damage);
			}					
		}			
		else
		{
			// Chamada Vanilla caso o prédio não pertença ao sistema de Base
			super.OnFinishProgressServer( action_data );
		}		
	}	
};