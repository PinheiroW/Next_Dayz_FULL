/**
 * MissionEffects.c
 * * ENTIDADES DE EFEITOS DE MISSÃO - Módulo ND_MISSIONS
 * Gerencia spawns de sons e partículas para ambientação de eventos dinâmicos.
 */

class alp_MissionEffects_Base : House {}

// --- EFEITO: ALARME DE AVISO ---
class alp_MissionEffects_Alarm : alp_MissionEffects_Base
{
	protected EffectSound m_SoundEff;
	
	override void EEInit()
	{	
		super.EEInit();
		if (GetGame() && GetGame().IsClient())
		{
			// Toca o som de alarme em loop na posição do objeto
			m_SoundEff = SEffectManager.PlaySoundOnObject("alp_WarningAlarmEffect_SoundSet", this, 0, 0, true);	
		}		
	}

	override void EEDelete(EntityAI parent)
	{	
		if (m_SoundEff)
		{	
			m_SoundEff.SoundStop();					
			m_SoundEff = null;
		}	
		super.EEDelete(parent);
	}
}

// --- EFEITO: FUMAÇA DE QUEDA DE HELICÓPTERO ---
class alp_MissionEffects_HeliSmoke : alp_MissionEffects_Base
{
	protected Particle m_ParticleEfx;

	override void EEInit()
	{	
		super.EEInit();
		if (GetGame() && GetGame().IsClient())
		{
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, Vector(0, 0, 0));
		}			
	}

	override void EEDelete(EntityAI parent)
	{				
		if (m_ParticleEfx) 
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
		super.EEDelete(parent);
	}
}

// --- EFEITO: FOGUEIRA / FUMAÇA DE ACAMPAMENTO ---
class alp_MissionEffects_BonfireSmoke : alp_MissionEffects_Base
{
	protected Particle m_ParticleEfx;

	override void EEInit()
	{	
		super.EEInit();
		if (GetGame() && GetGame().IsClient())
		{
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.BONFIRE_SMOKE, this, Vector(0, 0, 0));
		}			
	}

	override void EEDelete(EntityAI parent)
	{				
		if (m_ParticleEfx) 
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
		super.EEDelete(parent);
	}
}

// --- EFEITO: MOTOR EM CHAMAS ---
class alp_MissionEffects_EngineFire : alp_MissionEffects_Base
{
	protected Particle m_ParticleEfx;

	override void EEInit()
	{	
		super.EEInit();
		if (GetGame() && GetGame().IsClient())
		{
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.SMOKING_CAR_ENGINE, this, Vector(0, 0, 0));
		}			
	}

	override void EEDelete(EntityAI parent)
	{				
		if (m_ParticleEfx) 
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
		super.EEDelete(parent);
	}
}

// --- EFEITO: SINALIZADOR (FLARE) ---
class alp_MissionEffects_Flare : alp_MissionEffects_Base
{
	protected Particle m_ParticleEfx;

	override void EEInit()
	{	
		super.EEInit();
		if (GetGame() && GetGame().IsClient())
		{
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.FLAREPROJ_FIRE, this, Vector(0, 0, 0));
		}			
	}

	override void EEDelete(EntityAI parent)
	{				
		if (m_ParticleEfx) 
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
		super.EEDelete(parent);
	}
}