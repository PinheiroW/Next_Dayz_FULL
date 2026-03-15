/**
 * Misc_cargo_cont_net1.c
 * * ENTIDADE DE MISSÃO (CONTAINER DE CARGA) - Módulo ND_MISSIONS
 * Container com sinalização de fumaça dinâmica para eventos em Namalsk.
 */

#ifdef NAMALSK_TERRAIN
class alp_Misc_cargo_cont_net1 : Container_Base
{
	protected int alp_SmokeType = 0;
	protected Particle m_ParticleEfx;

	void alp_Misc_cargo_cont_net1()
	{
		// Sincroniza o tipo de fumaça entre servidor e clientes
		RegisterNetSyncVariableInt("alp_SmokeType");
		
		if (GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
			UpdateVisualState();
		}
	}

	/**
	 * Destruidores: Garante a remoção da fumaça ao deletar o container.
	 */
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		StopSmokeParticle();
	}

	void ~alp_Misc_cargo_cont_net1()
	{
		StopSmokeParticle();
	}

	protected void StopSmokeParticle()
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
		}
	}

	// --- Restrições de Manuseio ---

	override bool CanPutInCargo(EntityAI parent) { return false; }
	override bool CanPutIntoHands(EntityAI parent) { return false; }

	/**
	 * Gerencia a ativação visual das partículas no lado do cliente.
	 */
	protected void UpdateVisualState()
	{
		if (!GetGame().IsClient()) return;

		switch (alp_SmokeType)
		{
			case 0:
				break;
			
			case 1: // Fumaça Vermelha
				if (!m_ParticleEfx) 
					m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_RED_LOOP, this, Vector(0, 1, 0));
				alp_SmokeType = 0;
				break;

			case 2: // Fumaça Roxa
				if (!m_ParticleEfx) 
					m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_PURPLE_LOOP, this, Vector(0, 1, 0));
				alp_SmokeType = 0;
				break;

			case 3: // Fumaça Branca
				if (!m_ParticleEfx) 
					m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_WHITE_LOOP, this, Vector(0, 1, 0));
				alp_SmokeType = 0;
				break;
		}
	}

	/**
	 * Chamado quando uma variável sincronizada muda de valor.
	 */
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		UpdateVisualState();
	}
}
#endif