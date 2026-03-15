/**
 * alp_Dynamite.c
 * * ENTIDADE DE ITEM (DINAMITE) - Módulo ND_MISSIONS
 * Gerencia o ciclo de vida, ignição e detonação de explosivos de missão.
 */

class alp_Dynamite : alp_Dynamite_Base
{
	void alp_Dynamite()
	{
		SetAmmoType("alp_DynamiteExplosion");
		SetFuseDelay(15); // Tempo de pavio: 15 segundos
		SetParticleExplosion(ParticleList.EXPLOSION_LANDMINE);
	}

	void ~alp_Dynamite() {}
}

class alp_Dynamite_Base : InventoryItemSuper
{
	protected const float DEFAULT_FUSE_DELAY = 10;
	protected const string DEFAULT_AMMO_TYPE = "Explosion_NonLethal";

	protected ref Timer m_FuseTimer;
	protected ref Timer m_DeleteTimer;
	protected float m_FuseDelay;
	protected float m_RemainingFuseTime;
	
	protected bool m_Pinned;
	protected bool m_Pinnable;
	protected bool m_Explodable;
	
	protected EGrenadeType m_GrenadeType;
	protected string m_AmmoType;
	
	protected Particle m_ParticleExplosion;
	protected int m_ParticleExplosionId;
	protected vector m_ParticlePosition;
	
	protected Particle m_ParticleIgnited;
	protected vector m_ParticlePositionKnot;
	
	protected GrenadeLight m_Light;

	void alp_Dynamite_Base()
	{
		m_Pinned = true;
		m_FuseTimer = new Timer;
		m_DeleteTimer = new Timer;
		m_RemainingFuseTime = -1;
		m_AmmoType = DEFAULT_AMMO_TYPE;
		m_FuseDelay = DEFAULT_FUSE_DELAY;
	}
	
	/**
	 * Destruidor: Limpa timers e efeitos para evitar vazamento de memória.
	 */
	void ~alp_Dynamite_Base()
	{
		if (m_FuseTimer) m_FuseTimer.Stop();
		if (m_DeleteTimer) m_DeleteTimer.Stop();
		if (m_ParticleIgnited) m_ParticleIgnited.Stop();
	}

	// --- Configurações da Explosão ---

	void SetAmmoType(string ammo) { m_AmmoType = ammo; }
	void SetFuseDelay(float delay) { m_FuseDelay = delay; }
	void SetParticleExplosion(int particle) { m_ParticleExplosionId = particle; }

	// --- Lógica de Pavio (Ignition) ---

	void Activate()
	{
		if (GetGame().IsServer())
		{
			if (m_RemainingFuseTime > 0)
				m_FuseTimer.Run(m_RemainingFuseTime, this, "OnExplode");
			else
				m_FuseTimer.Run(m_FuseDelay, this, "OnExplode");
		}
		
		// Inicia efeitos visuais (fumaça/faíscas no estopim)
		if (!GetGame().IsDedicatedServer())
		{
			m_ParticleIgnited = Particle.PlayOnObject(ParticleList.GRENADE_M67, this, m_ParticlePositionKnot);
		}
	}

	void OnExplode()
	{
		if (GetGame().IsServer())
		{
			// Cria a explosão física no mundo
			GetGame().ExplosionEffects(this, m_AmmoType, m_AmmoType, m_ParticleExplosionId);
			
			// Agenda a deleção do objeto para o frame seguinte
			m_DeleteTimer.Run(0.1, GetGame(), "ObjectDelete", new Param1<EntityAI>(this));
		}
	}

	override bool CanExplodeInFire()
	{
		return true;
	}

	override void SetActions()
	{
		super.SetActions();
		
		// Essencial para permitir que a dinamite seja usada em armadilhas de porta ou tripwires
		AddAction(ActionAttach);
		AddAction(ActionDetach);
	}
}