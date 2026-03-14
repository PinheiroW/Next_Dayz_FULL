#ifndef EXPANSIONMODBASEBUILDING

// CORREÇÃO 1: Remoção do "extends ItemBase" redundante
modded class BaseBuildingBase
{
	int m_OwnerID;
	int m_ClanID;
	float ALP_MAX_HEALTH = 1;
	
	string alp_PlayerGUID = "";
	
	int alp_LastAttack;
	ref map<string,float> alp_Damage;
	
	void BaseBuildingBase()
	{
		RegisterNetSyncVariableInt("m_OwnerID");
		RegisterNetSyncVariableInt("m_ClanID");
		if (GetGame().IsServer() )
		{	
			if ( m_DamageZoneMap )
			{
				alp_Damage = new map<string,float>;
				
				for (int d = 0; d < m_DamageZoneMap.Count(); d++)
				{
					string zone = m_DamageZoneMap.GetKey(d);			
					alp_Damage.Set( zone, ALP_MAX_HEALTH );
				}		
			}
		}	
	}
	
	void SetPlotPoleID(int ownerID, int clanID )
	{
		m_OwnerID = ownerID;
		m_ClanID = clanID;
	}
	
	float GetDynamiteDamage(int ammoType)
	{
		// CORREÇÃO 2: Failsafe para evitar NPE Crash no acesso aos Core Plugins
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetBases()) return 1.0;

		string owneris;
		bool ownerIsON = false;
		if ( GetND().GetClans().IsPlayerInGame( m_OwnerID ) || ( m_ClanID > 0 && GetND().GetClans().IsClanInGame( m_ClanID ) ) ) 
		{
			int currentTime = GetGame().GetTime() - (180 * 1000);	
			if ( alp_LastAttack > currentTime )
			{	
				GetND().GetClans().SendAlertMessage( GetPosition(), m_OwnerID , m_ClanID );				
				alp_LastAttack = GetGame().GetTime();				
			}			
			owneris	= " DynamiteDamageRatioOwnerOn";
			ownerIsON = true;
		} 
		else 
		{
			owneris	= " DynamiteDamageRatioOwnerOff";
		}
		
		string path = "CfgVehicles " + GetType() + owneris;	
		float ratio = GetGame().ConfigGetFloat(path);

		if ( GetND().GetClans().GetBases().Override_Raid_TNT_BaseBuilding )
		{
			string type = GetType();
			foreach( alpRaidTNT_BaseBuilding settings : GetND().GetClans().GetBases().Override_Raid_TNT_BaseBuilding ) 
			{
				if (settings.Name == type)
				{
					if (ownerIsON) ratio = settings.OwnerON;
					else ratio = settings.OwnerOFF;
					break;
				}
			}
		}		
		return ratio;
	}
	
	override void OnPartBuiltServer( notnull Man player, string part_name, int action_id )
	{
		super.OnPartBuiltServer(player, part_name, action_id);
		PlayerBase p = PlayerBase.Cast( player );
		if ( p )
		{
			int clan = p.GetClanID();
			int pid = p.GetPlayerID();
			SetPlotPoleID(pid, clan);
		}
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult,  damageType,  source,  component,  dmgZone,  ammo,  modelPos,  speedCoef);	
		
		// CORREÇÃO 3: Blindagem da chamada contra Null Pointers
		if ( GetGame() && GetGame().IsServer() && GetND() && GetND().GetClans() && GetND().GetClans().GetBases() && GetND().GetClans().GetBases().EnableNextDaysRaidMechanics )
		{			
			if ( IsOwnedByPlayer() )
			{				
				if ( damageType == DT_EXPLOSION )
				{
					float allowedDamage = 0;
					int ammoType = GetAmmoType( ammo );
					if ( ammoType )
					{				
						allowedDamage = GetDynamiteDamage(ammoType);
					}
					SetBaseBuildingHealth( allowedDamage );
				} 
				else 
				{
					float damage = damageResult.GetDamage(dmgZone,"Health");	
					float health = GetHealth(dmgZone,"Health");	
					
					// Nota de Design: Como você está somando (+ damage) ao health, 
					// isso efetivamente curará a base do dano de bala, tornando-a imune a tiros (Apenas C4 destrói).
					health += damage;
					SetHealth(dmgZone,"Health",health);	
				}					
			}	
		}		
	}	
	
	int GetAmmoType(string ammo )
	{
		switch (ammo)
		{
			case "alp_DynamiteExplosion": return alpAMMOTYPE.L2;		
			case "Plastic_Explosive_Ammo": return alpAMMOTYPE.L1;		
		}
		return 0;
	}	
	
	bool IsOwnedByPlayer()
	{
		return m_OwnerID;
	}
	
	void SetBaseBuildingHealth(float damage )
	{
		if ( alp_Damage )
		{
			string name;
			float last_health, health, maxhealth;
			for(int i = 0; i < alp_Damage.Count(); i++)
			{
				name = alp_Damage.GetKey(i);
				health = GetHealth01(name,"Health");
				last_health = alp_Damage.GetElement(i);

				if ( health != last_health )
				{
					last_health -= damage;

					if ( last_health > 0 )
					{
						alp_Damage.Set( name  , last_health );	
						maxhealth =  GetMaxHealth(name,"Health");	
						maxhealth *= last_health;						
						SetHealth(name,"Health",maxhealth);										
					}					
					else
					{
						GetGame().ObjectDelete( this );
						// CORREÇÃO 4: EVITA CRASH CRÍTICO (Access Violation)
						// O objeto acaba de ser apagado. O loop DEVE ser quebrado imediatamente, 
						// caso contrário tentará acessar memória morta e derrubará o servidor.
						return; 
					}						
				}				
			}
		}	
	}	
	
	override bool IsBuildingALP()
	{
		return true;
	}
}

#else		

modded class BaseBuildingBase 
{
	int alp_OwnerID;
	int m_ClanID;
	float ALP_MAX_HEALTH = 1;
	
	string alp_PlayerGUID = "";
	
	int alp_LastAttack;
	ref map<string,float> alp_Damage;
	
	void BaseBuildingBase()
	{
		RegisterNetSyncVariableInt("alp_OwnerID");
		RegisterNetSyncVariableInt("m_ClanID");
		if (GetGame().IsServer() )
		{	
			if ( m_DamageZoneMap )
			{
				alp_Damage = new map<string,float>;
				
				for (int d = 0; d < m_DamageZoneMap.Count(); d++)
				{
					string zone = m_DamageZoneMap.GetKey(d);			
					alp_Damage.Set( zone, ALP_MAX_HEALTH );
				}		
			}
		}	
	}

	void SetPlotPoleID(int ownerID, int clanID )
	{
		alp_OwnerID = ownerID;
		m_ClanID = clanID;
	}
	
	float GetDynamiteDamage(int ammoType)
	{
		// Null Check replicado para versão Expansion
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetBases()) return 1.0;

		string owneris;
		bool ownerIsON = false;
		if ( GetND().GetClans().IsPlayerInGame( alp_OwnerID ) || ( m_ClanID > 0 && GetND().GetClans().IsClanInGame( m_ClanID ) ) ) 
		{
			int currentTime = GetGame().GetTime() - (180 * 1000);	
			if ( alp_LastAttack > currentTime )
			{	
				GetND().GetClans().SendAlertMessage( GetPosition(), alp_OwnerID , m_ClanID );				
				alp_LastAttack = GetGame().GetTime();				
			}			
			owneris	= " DynamiteDamageRatioOwnerOn";
			ownerIsON = true;
		} 
		else 
		{
			owneris	= " DynamiteDamageRatioOwnerOff";
		}
		
		string path = "CfgVehicles " + GetType() + owneris;	
		float ratio = GetGame().ConfigGetFloat(path);

		if ( GetND().GetClans().GetBases().Override_Raid_TNT_BaseBuilding )
		{
			string type = GetType();
			foreach( alpRaidTNT_BaseBuilding settings : GetND().GetClans().GetBases().Override_Raid_TNT_BaseBuilding ) 
			{
				if (settings.Name == type)
				{
					if (ownerIsON) ratio = settings.OwnerON;
					else ratio = settings.OwnerOFF;
					break;
				}
			}
		}		
		return ratio;
	}
	
	override void OnPartBuiltServer( notnull Man player, string part_name, int action_id )
	{
		super.OnPartBuiltServer(player, part_name, action_id);
		PlayerBase p = PlayerBase.Cast( player );
		if ( p )
		{
			int clan = p.GetClanID();
			int pid = p.GetPlayerID();
			SetPlotPoleID(pid, clan);
		}
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult,  damageType,  source,  component,  dmgZone,  ammo,  modelPos,  speedCoef);	
		
		// Null Check replicado para versão Expansion
		if ( GetGame() && GetGame().IsServer() && GetND() && GetND().GetClans() && GetND().GetClans().GetBases() && GetND().GetClans().GetBases().EnableNextDaysRaidMechanics )
		{			
			if ( IsOwnedByPlayer() )
			{				
				if ( damageType == DT_EXPLOSION )
				{
					float allowedDamage = 0;
					int ammoType = GetAmmoType( ammo );
					if ( ammoType )
					{				
						allowedDamage = GetDynamiteDamage(ammoType);
					}
					SetBaseBuildingHealth( allowedDamage );
				} 
				else 
				{
					float damage = damageResult.GetDamage(dmgZone,"Health");	
					float health = GetHealth(dmgZone,"Health");	
					
					health += damage;
					SetHealth(dmgZone,"Health",health);	
				}					
			}	
		}		
	}	
	
	int GetAmmoType(string ammo )
	{
		switch (ammo)
		{
			case "alp_DynamiteExplosion": return alpAMMOTYPE.L2;		
			case "Plastic_Explosive_Ammo": return alpAMMOTYPE.L1;		
		}
		return 0;
	}	
	
	bool IsOwnedByPlayer()
	{
		return alp_OwnerID;
	}
	
	void SetBaseBuildingHealth(float damage )
	{
		if ( alp_Damage )
		{
			string name;
			float last_health, health, maxhealth;
			for(int i = 0; i < alp_Damage.Count(); i++)
			{
				name = alp_Damage.GetKey(i);
				health = GetHealth01(name,"Health");
				last_health = alp_Damage.GetElement(i);

				if ( health != last_health )
				{
					last_health -= damage;

					if ( last_health > 0 )
					{
						alp_Damage.Set( name  , last_health );	
						maxhealth =  GetMaxHealth(name,"Health");	
						maxhealth *= last_health;						
						SetHealth(name,"Health",maxhealth);										
					}					
					else
					{
						GetGame().ObjectDelete( this );
						// Crash Prevent
						return;
					}						
				}				
			}
		}	
	}	
	
	override bool IsBuildingALP()
	{
		return true;
	}
}	
		
#endif

modded class Watchtower extends BaseBuildingBase
{	
	override bool PerformRoofCheckForBase( string partName, PlayerBase player, out bool result )
	{
		return false;
	}
}