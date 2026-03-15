/**
 * PlayerStats.c
 * * SISTEMA DE ESTATÍSTICAS RPG - Módulo ND_MISSIONS
 * Define habilidades, reputação, resistência e estatísticas dinâmicas dos jogadores.
 */

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
}; // Enum mantido como original, fechamento correto

class PlayerStatsND extends PlayerStatsPCO_Base
{
	override void Init()
	{
		RegisterStat(EPlayerStats_ALP.SKILL_SPECIALTY_SOFT, new PlayerStatAlp<float>(-1, 0, 0, "SpecialtySoft", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_SPECIALTY_HARD, new PlayerStatAlp<float>(0, 1, 0, "SpecialtyHard", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_STAMINA, new PlayerStatAlp<float>(0, 100, 0, "Stamina", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_STAMINAPROGRESS, new PlayerStatAlp<float>(0, 100, 0, "StaminaProgress", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_RADIATIONIMMUNITY, new PlayerStatAlp<float>(0, 100, 0, "RadiationImmunity", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_RADIATIONPROGRESS, new PlayerStatAlp<float>(0, 100, 0, "RadiationProgress", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_TOXICIMMUNITY, new PlayerStatAlp<float>(0, 100, 0, "ToxicImmunity", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_TOXICIMMUNITYPROGRESS, new PlayerStatAlp<float>(0, 100, 0, "ToxicProgress", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_HUNTING, new PlayerStatAlp<float>(0, 100, 0, "Hunting", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_HUNTINGPROGRESS, new PlayerStatAlp<float>(0, 100, 0, "HuntingProgress", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_REPUTATION, new PlayerStatAlp<float>(-100, 100, 0, "Reputation", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_REPUTATIONPROGRESS, new PlayerStatAlp<float>(0, 100, 0, "ReputationProgress", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.COUNTPLAYERS, new PlayerStatAlp<int>(0, int.MAX, 0, "CountPlayers", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.COUNTZOMBIES, new PlayerStatAlp<int>(0, int.MAX, 0, "CountZombies", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.COUNTANIMALS, new PlayerStatAlp<int>(0, int.MAX, 0, "CountAnimals", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.COUNTSKINNED, new PlayerStatAlp<int>(0, int.MAX, 0, "CountSkinned", EPSstatsFlags.EMPTY));

		RegisterStat(EPlayerStats_ALP.CURRENT_SCORE, new PlayerStatAlp<int>(0, int.MAX, 0, "Score", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.TIREDNESS, new PlayerStatAlp<float>(0, 100, 0, "Tiredness", EPSstatsFlags.EMPTY));
	}
}; // Adicionado ponto e vírgula obrigatório

class PlayerStatAlp<Class T> extends PlayerStat<T>
{
	void PlayerStatAlp(T min, T max, T init, string name, int flags)
	{
		m_MinValue = min;
		m_MaxValue = max;
		m_Value = init;
		m_Name = name;
		m_Flags = flags;
	}

	override bool IsSynced()
	{
		return m_Flags & EPSstatsFlags.SYNCED == EPSstatsFlags.SYNCED;
	}
	
	override void OnRPC(ParamsReadContext ctx)
	{
		if (IsSynced())
		{			
			// CORREÇÃO: Alocação prévia do objeto com 'ref' para evitar vazamento ou crash na desserialização
			ref Param2<int, T> data = new Param2<int, T>(0, m_Value);
			
			if (ctx.Read(data))
			{
				int type = data.param1;
				T value = data.param2;

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

	void Add(T value, string system = "")
	{
		Set(m_Value + value, system);
	}

	override float Get()
	{
		return m_Value;
	}
}; // Adicionado ponto e vírgula obrigatório