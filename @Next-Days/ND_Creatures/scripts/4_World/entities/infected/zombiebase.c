/**
 * NDCreatures - zombiebase.c (Parte 1 de 2)
 * Auditoria Técnica: Pró-Gamer / IA Modding Specialist
 */

class alpZombieBehavior
{
	int Speed;
	float Armor;
	float HeavyDamageBonus;
	float DamageBonus;
	float ChanceToBreakBone;
	float RadiationTouch;
	float ChemicalTouch;
	float HealingFactor;
	float ReputationBonus;
	
	// OTIMIZAÇÃO: Tornamos a array estática para não recriar na memória a cada chamada de GetSpeed
	static ref array<float> speedLimits = {1.7, 2.2, 3.5, 6.0};

	void alpZombieBehavior(int speed, float armor, float heavy, float light, float bone, float exp = 0, float chemicals = 0, float radiation = 0, float healing = 0)
	{
		Speed = Math.Clamp(speed, 0, 3);
		Armor = armor;
		HeavyDamageBonus = heavy;
		DamageBonus = light;
		ChanceToBreakBone = bone;
		RadiationTouch = radiation;
		ChemicalTouch = chemicals;
		HealingFactor = healing;
		ReputationBonus = exp;
	}

	float GetToxic() { return ChemicalTouch; }
	float GetRadiation() { return RadiationTouch; }
	float GetHealing() { return HealingFactor; }
	float GetArmor() { return Armor; }

	float GetSpeed()
	{
		int idx = Math.Clamp(Speed, 0, speedLimits.Count() - 1);
		return speedLimits.Get(idx);
	}
}

modded class ZombieBase
{
	private float m_ND_DoorTimer = 0; // Timer para otimização de portas
	
	override void EEInit()
	{
		super.EEInit();

		if (GetGame().IsServer())
		{
			// OTIMIZAÇÃO: Verifica zona apenas no spawn. Se não puder existir aqui, deleta imediatamente.
			// Isso economiza CPU ao não precisar rodar checagem de zona em cada frame.
			if (IsZombieCustomed() && !alpPluginNDmissionsSystem.CansSpawnAI(this))
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 50, false, this);
				return;
			}
		}
	}

	bool IsZombieCustomed()
	{
		auto nd = GetND();
		if (nd && nd.GetCreatures() && nd.GetCreatures().GetOptions())
		{
			// Corrigido typo de "EnableCretures" para "EnableCreatures"
			return nd.GetCreatures().GetOptions().EnableCreatures;
		}
		return false;
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		if (!GetGame().IsServer() || !IsZombieCustomed()) return;

		// OTIMIZAÇÃO CRÍTICA: Verifica portas apenas a cada 2 segundos. 
		// Antes rodava a cada frame (60fps = 60 buscas físicas por segundo por zumbi).
		m_ND_DoorTimer += timeslice;
		if (m_ND_DoorTimer >= 2.0)
		{
			if (GetND().GetCreatures().GetOptions().ZombiesCanOpenUnlockedDoor)
			{
				CheckDoors();
			}
			m_ND_DoorTimer = 0;
		}
	}

	// SEGURANÇA: Prevenção de Crash ao atacar objetos não-humanos
	override void OnDamageInflicted(int dmgType, EntityAI source, string zone, string ammo, vector speed)
	{
		super.OnDamageInflicted(dmgType, source, zone, ammo, speed);

		if (!GetGame().IsServer()) return;

		PlayerBase targetPlayer = PlayerBase.Cast(source);
		if (!targetPlayer) return; // Se o alvo não for um jogador, encerra aqui (evita NPE Crash)

		alpZombieBehavior behavior = GetND().GetCreatures().GetZombieBehavior(this.GetType());
		if (behavior)
		{
			if (behavior.GetRadiation() > 0)
				targetPlayer.GetModifiersManager().ActivateModifier(ALP_MODIFIER_RADIATION);
			
			if (behavior.GetToxic() > 0)
				targetPlayer.GetModifiersManager().ActivateModifier(ALP_MODIFIER_CHEMICAL);
		}
	}
}

/**
 * NDCreatures - zombiebase.c (Parte 2 de 2)
 */

modded class ZombieBase
{
    // ... (outros métodos anteriores) ...

    void CheckDoors()
    {
        Building alp_Building;
        int index;
        if (IsNearDoor(alp_Building, index))
        {
            // O index da porta para funções de script é 0-based (Porta 1 = ID 0)
            if (alp_Building.CanOpenDoor(index) && !alp_Building.IsDoorOpen(index) && !alp_Building.IsDoorLocked(index))
            {
                alp_Building.OpenDoor(index);
            }
        }
    }

    bool IsContaminatedZombie()
    {
        // ToLower() garante que "nbc", "NBC" ou "Nbc" sejam detectados corretamente
        string type = this.GetType();
        type.ToLower();
        return type.Contains("nbc");
    }

    bool IsNearDoor(out Building alp_Building, out int index)
    {
        vector zed_pos = GetPosition();
        array<Object> entList = new array<Object>;
        // Raio de 2 metros é ideal para IA
        GetGame().GetObjectsAtPosition3D(zed_pos, 2, entList, null);

        float last_distance = 2.1;
        bool found = false;

        for (int i = 0; i < entList.Count(); ++i)
        {
            Building building = Building.Cast(entList.Get(i));
            if (building)
            {
                // OTIMIZAÇÃO: Em vez de varrer seleções de P3D, usamos o sistema de portas do prédio
                // Prédios comuns têm um número limitado de portas (geralmente < 10)
                int doorCount = building.GetDoorCount();
                for (int d = 0; d < doorCount; d++)
                {
                    vector doorPos = building.GetDoorSoundPos(d); // Posição aproximada da porta
                    float dist = vector.Distance(zed_pos, doorPos);
                    
                    if (dist <= 2.0 && dist < last_distance)
                    {
                        last_distance = dist;
                        alp_Building = building;
                        index = d; // O índice da porta já é o correto aqui
                        found = true;
                    }
                }
            }
        }
        return found;
    }

    // Nota: O método GetDoorIndex original pode ser removido se usar a lógica acima,
    // que é muito mais leve e precisa por usar os dados nativos de portas da classe Building.
}

// Extensão para compatibilidade de dano e armadura
modded class ZombieMaleBase
{
	override bool DamageEntity(EntityAI source, string zone, string ammo, vector speed, float dmg, int type)
	{
		alpZombieBehavior behavior = GetND().GetCreatures().GetZombieBehavior(this.GetType());
		if (behavior)
		{
			dmg = dmg - (dmg * behavior.GetArmor());
		}
		return super.DamageEntity(source, zone, ammo, speed, dmg, type);
	}
}