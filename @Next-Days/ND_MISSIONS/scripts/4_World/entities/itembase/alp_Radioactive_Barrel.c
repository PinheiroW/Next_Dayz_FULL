/**
 * alp_Radioactive_Barrel.c
 * * ENTIDADE DE MISSÃO (BARRIL RADIOATIVO) - Módulo ND_MISSIONS
 * Container especializado com efeitos de radiação e abertura temporizada.
 */

class alp_Radioactive_Barrel : Container_Base
{
	protected bool m_IsLocked = false;
	protected ref Timer m_BarrelOpener;
	protected ref OpenableBehaviour m_Openable;
	protected Particle m_ParticleEfx;
	
	protected int alp_MissionID = -1;
	protected float m_Strength = 1;

	void alp_Radioactive_Barrel()
	{
		m_BarrelOpener = new Timer();
		m_Openable = new OpenableBehaviour(false);

		// Registro de variáveis para replicação na rede
		RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsPlaceSound");
	}

	/**
	 * Destruidor e Limpeza: Garante que os efeitos parem ao deletar o objeto.
	 */
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		StopRadiationParticles();
	}

	void ~alp_Radioactive_Barrel()
	{
		StopRadiationParticles();
	}

	void StopRadiationParticles()
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
		}
	}

	// --- Lógica de Abertura e Bloqueio ---

	override bool IsOpen() { return m_Openable.IsOpened(); }

	override void Open()
	{
		if (m_IsLocked) return;
		m_Openable.Open();
		SoundBarrelOpenPlay();
		SetSynchDirty();
	}

	override void Close()
	{
		m_Openable.Close();
		SoundBarrelClosePlay();
		SetSynchDirty();
	}

	/**
	 * Inicia o processo de abertura forçada (lockpicking/esforço).
	 * @param actiontime Tempo em segundos até o destrave.
	 */
	void Lock(float actiontime)
	{
		m_IsLocked = true;
		m_BarrelOpener.Run(actiontime, this, "Unlock", null, false);
	}

	void Unlock()
	{
		m_IsLocked = false;
		Open();
	}

	// --- Sons e Feedback ---

	void SoundBarrelOpenPlay()
	{
		EffectSound sound = SEffectManager.PlaySound("barrel_open_SoundSet", GetPosition());
		if (sound) sound.SetSoundAutodestroy(true);
	}

	void SoundBarrelClosePlay()
	{
		EffectSound sound = SEffectManager.PlaySound("barrel_close_SoundSet", GetPosition());
		if (sound) sound.SetSoundAutodestroy(true);
	}

	// --- Restrições de Movimentação ---

	override bool CanPutInCargo(EntityAI parent) { return false; }
	override bool CanPutIntoHands(EntityAI parent) { return false; }
	
	override bool CanDisplayCargo() { return IsOpen(); }
	override bool CanReceiveItemIntoCargo(EntityAI cargo) { return IsOpen(); }
	override bool CanReleaseCargo(EntityAI attachment) { return IsOpen(); }

	// --- Missão e Identificação ---

	void SetMissionID(int id) { alp_MissionID = id; }
	int GetMissionID() { return alp_MissionID; }
}