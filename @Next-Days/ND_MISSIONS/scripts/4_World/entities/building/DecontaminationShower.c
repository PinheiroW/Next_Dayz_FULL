/**
 * DecontaminationShower.c
 * * ENTIDADE DE INTERAÇÃO (CHUVEIRO DE DESCONTAMINAÇÃO) - Módulo ND_MISSIONS
 * Gerencia efeitos visuais, sonoros e sincronização de rede para a cura de radiação.
 */

class Land_Medical_Tent_Shower extends BuildingSuper
{
	string LOOP_SOUND = "alp_DecontaminationShower_SoundSet_On";
	protected EffectSound m_ShowerLoop;
	bool alp_IsShowerActive = false;
	
	// Referências de Partículas
	protected Particle m_ParticleEfx;
	protected Particle m_ParticleEfx_2;
	protected Particle m_ParticleEfx_3;

	void Land_Medical_Tent_Shower()
	{
		// Registra a variável para sincronização automática entre Servidor e Clientes
		RegisterNetSyncVariableBool("alp_IsShowerActive");
	}

	override bool IsBuilding()
	{
		return false;
	}

	override void SetActions()
	{
		super.SetActions();
		// Ação definida no Constructor para ligar/desligar ou usar o chuveiro
		AddAction(alpActionDecontaminate);
	}
	
	void StartShower()
	{
		if (GetGame().IsServer())
		{
			alp_IsShowerActive = true;
			SetSynchDirty(); // Notifica os clientes sobre a mudança de estado
		}
	}

	void StopShower()
	{
		if (GetGame().IsServer())
		{
			alp_IsShowerActive = false;
			SetSynchDirty();
		}
	}

	/**
	 * Lógica executada nos Clientes quando o estado do chuveiro muda no servidor.
	 */
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (alp_IsShowerActive)
		{
			// Inicia o som em loop
			PlaySoundSet(m_ShowerLoop, LOOP_SOUND, 0, 0, true);
			
			// Limpeza de segurança para evitar sobreposição de partículas
			StopAllParticles();

			// Ativa os efeitos de vapor/spray em diferentes posições da cabine
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(0.5, -0.7, 0.5), Vector(90, 0, 0));
			m_ParticleEfx_2 = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(-0.5, -0.7, 0.5), Vector(90, 0, 0));
			m_ParticleEfx_3 = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(0, -0.7, -0.5), Vector(90, 0, 0));
		}
		else
		{
			// Para o som
			if (m_ShowerLoop)
				m_ShowerLoop.Stop();

			// Para as partículas
			StopAllParticles();
		}
	}

	void StopAllParticles()
	{
		if (m_ParticleEfx) { m_ParticleEfx.Stop(); m_ParticleEfx = null; }
		if (m_ParticleEfx_2) { m_ParticleEfx_2.Stop(); m_ParticleEfx_2 = null; }
		if (m_ParticleEfx_3) { m_ParticleEfx_3.Stop(); m_ParticleEfx_3 = null; }
	}

	// Limpeza ao deletar o objeto
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		StopAllParticles();
		if (m_ShowerLoop) m_ShowerLoop.Stop();
	}
}