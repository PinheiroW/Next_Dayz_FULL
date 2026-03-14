  

enum EPlayerStats_ALP
{
	
	SKILL_SPECIALTY_SOFT,
	SKILL_SPECIALTY_HARD,

	SKILL_STAMINA,
	SKILL_STAMINAPROGRESS,
		
	SKILL_RADIATIONIMMUNITY,
	SKILL_RADIATIONPROGRESS,

	SKILL_TOXICIMMUNITY,
	SKILL_TOXICIMMUNITYPROGRESS,

	SKILL_HUNTING,
	SKILL_HUNTINGPROGRESS,

	SKILL_REPUTATION,
	SKILL_REPUTATIONPROGRESS,
	COUNTPLAYERS,
	COUNTZOMBIES,
	COUNTANIMALS,
	COUNTSKINNED,
	CURRENT_SCORE,
	TIREDNESS,
};


class PlayerStatsND extends PlayerStatsPCO_Base
{
	override void Init()
	{
		//RegisterStat(EPlayerStats_ALP.HASONCONNECTDATA, new PlayerStatAlp<int>(0, int.MAX , 0, "HasOnConnectData", EPSstatsFlags.EMPTY));
		
		RegisterStat(EPlayerStats_ALP.SKILL_SPECIALTY_SOFT, new PlayerStatAlp<float>(-1, 0, 0, "SpecialtySoft", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_SPECIALTY_HARD, new PlayerStatAlp<float>(0, 1, 0, "SpecialtyHard", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_STAMINA, new PlayerStatAlp<int>(0,64,0,"LevelStamina",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_STAMINAPROGRESS, new PlayerStatAlp<float>(0,999999999,0,"LevelStaminaProgress",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.SKILL_RADIATIONIMMUNITY, new PlayerStatAlp<int>(0,64,0,"LevelImmunity",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_RADIATIONPROGRESS, new PlayerStatAlp<float>(0,999999999,0,"LevelImmunityProgress",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.SKILL_TOXICIMMUNITY, new PlayerStatAlp<int>(0,64,0,"ToxicImmunity",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_TOXICIMMUNITYPROGRESS, new PlayerStatAlp<float>(0,999999999,0,"ToxicImmunityProgress",EPSstatsFlags.EMPTY) );	
		
		RegisterStat(EPlayerStats_ALP.SKILL_HUNTING, new PlayerStatAlp<int>(0,64,0,"LevelHunting",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_HUNTINGPROGRESS, new PlayerStatAlp<float>(0,999999999,0,"LevelHuntingProgress",EPSstatsFlags.EMPTY) );

		RegisterStat(EPlayerStats_ALP.SKILL_REPUTATION, new PlayerStatAlp<int>(-64,64,0,"LevelReputation",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_REPUTATIONPROGRESS, new PlayerStatAlp<float>(-999999999,999999999,0,"LevelReputationProgress",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.COUNTPLAYERS, new PlayerStatAlp<int>(0,999999999,0,"CountPlayers",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.COUNTZOMBIES, new PlayerStatAlp<int>(0,999999999,0,"CountZombies",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.COUNTANIMALS, new PlayerStatAlp<int>(0,999999999,0,"CountAnimals",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.COUNTSKINNED, new PlayerStatAlp<int>(0,999999999,0,"CountSkinned",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.TIREDNESS, new PlayerStatAlp<float>(0, 100, 100, "Tiredness", EPSstatsFlags.EMPTY));
		
		RegisterStat(EPlayerStats_ALP.CURRENT_SCORE, new PlayerStatAlp<float>(-999999999,999999999,0,"CurrentScore",EPSstatsFlags.EMPTY) );
	}	
};

class PlayerStatsALP
{
	
	ref PlayerStatsPCO_Base			m_PCO_base = new PlayerStatsND();

	Man m_Player;

	void PlayerStatsALP(Man player)
	{
		m_PCO_base.SetPlayer(player);
		m_PCO_base.Init();
		m_Player = player;		
	}

	PlayerStatsPCO_Base GetPCO()
	{
		return m_PCO_base;
	}
	
	void ~PlayerStatsALP()
	{
		
	}
	
	
	PlayerStatBase GetStatObject(int id)
	{
		PlayerStatsPCO_Base pco = GetPCO();
		if ( pco )
		{
			return pco.GetStatObject(id);
		}
		else
		{
			return null;
		}
	}
	


	
	void SaveStats( ParamsWriteContext ctx )
	{

		PlayerStatsPCO_Base pco = GetPCO();
		
		if ( pco )
		{
			pco.OnStoreSave(ctx);

		}
		else
		{
			return;
		}
	}

	bool LoadStats( ParamsReadContext ctx, int version )
	{
		PlayerStatsPCO_Base pco = GetPCO();
		if (pco && pco.OnStoreLoad(ctx))
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}


}



class PlayerStatAlp<Class T> extends PlayerStatBase
{
	protected T 		m_MinValue;
	protected T 		m_MaxValue;
	protected T 		m_Value;
	protected T 		m_ValueLastSynced;
	protected string 	m_ValueLabel;
	protected int		m_Flags;
	

	void PlayerStatAlp(T min, T max, T init, string label, int flags)
	{
		m_MinValue 		= min;
		m_MaxValue 		= max;
		m_Value			= init;
		m_ValueLabel 	= label;
		m_Flags			= flags;
		
	}
		
	override void Init(int id)
	{
		m_Type = id;
	}
	
	override void SerializeValue(array<ref StatDebugObject> objects, int flags)
	{
		objects.Insert(new StatDebugObject(GetLabel(), Get(), eRemoteStatType.PLAYER_STATS));
	}
	
	override bool IsSynced()
	{
		return m_Flags & EPSstatsFlags.SYNCED == EPSstatsFlags.SYNCED;
	}
	
	override void OnRPC(ParamsReadContext ctx)
	{
		if (IsSynced())
		{			
			Param2<int, T> data;
			if (ctx.Read(data))
			{
				int type 	= data.param1;
				T value 	= data.param2;

				if (m_Type == type)
					Set(value);
			}
		}
	}
	
	void Set(T value, string system = "")
	{
		if (value > m_MaxValue)
		{
			m_Value = m_MaxValue;
		}
		else if (value < m_MinValue)
		{
			m_Value = m_MinValue;
		}
		else
		{
			m_Value = value;
		}
		
	}
	
	void SetByFloat(float value, string system = "")
	{
		T f = value;
		Set(f, system);
	}

	override void SetByFloatEx(float value, string system = "")
	{
		SetByFloat(value, system);
	}

	void Add( T value, string system = "" )
	{
		Set(m_Value+value, system);
	}

	override float Get()
	{
		return m_Value;
	}
	
	override string GetLabel()
	{
		return m_ValueLabel;
	}

	override float GetMax()
	{
		return m_MaxValue;
	}

	override float GetMin()
	{
		return m_MinValue;
	}
	
	override float GetNormalized()
	{
		return Math.InverseLerp(GetMin(), GetMax(), Get());
	}

	
	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		ctx.Write(m_Value);
	}

	override bool OnStoreLoad( ParamsReadContext ctx)
	{
		T value;
		if (ctx.Read(value))
		{
			m_Value = value;
		}
		else
		{
			return false;
		}

		return true;
	}
	
	override void OnAfterStoreLoad()
	{
		// forces the sync
		Set(Get());
	}
}