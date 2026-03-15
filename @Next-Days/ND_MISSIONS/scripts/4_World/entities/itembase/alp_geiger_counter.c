/**
 * alp_geiger_counter.c
 * * ENTIDADE DE ITEM (CONTADOR GEIGER) - Módulo ND_MISSIONS
 * Detecta níveis de radiação e fornece feedback sonoro progressivo.
 */

enum alpGEIGERSOUNTYPE
{
	NONE = 0,
	LOW,
	MEDIUM,
	HIGH,
	VERYHIGH,
	COUNT
}

class alpGeigerSound
{
	/**
	 * Traduz o enum de intensidade em um SoundSet definido no config.cpp.
	 */
	static string GetSoundSetByType(alpGEIGERSOUNTYPE ide)
	{
		switch (ide)
		{
			case alpGEIGERSOUNTYPE.LOW:      return "alp_Geiger_SoundSet_low";
			case alpGEIGERSOUNTYPE.MEDIUM:   return "alp_Geiger_SoundSet_medium";
			case alpGEIGERSOUNTYPE.HIGH:     return "alp_Geiger_SoundSet_high";
			case alpGEIGERSOUNTYPE.VERYHIGH: return "alp_Geiger_SoundSet_veryhigh";
		}
		return "alp_Geiger_SoundSet_low";
	} 
	
	/**
	 * Determina o nível de som com base nos limites configurados no servidor.
	 */
	static int GetSoundTypeValue(float radiation)
	{
		auto radOptions = GetND().GetMS().GetOptionsRadiation();
		if (!radOptions || radiation <= 0) return alpGEIGERSOUNTYPE.NONE;
		
		if (radiation <= radOptions.GeigerSoundEffect_Radiation_Low)      return alpGEIGERSOUNTYPE.LOW;
		if (radiation <= radOptions.GeigerSoundEffect_Radiation_Medium)   return alpGEIGERSOUNTYPE.MEDIUM;
		if (radiation <= radOptions.GeigerSoundEffect_Radiation_High)     return alpGEIGERSOUNTYPE.HIGH;
		
		return alpGEIGERSOUNTYPE.VERYHIGH;
	}
}



class alp_GeigerCounter : ItemBase
{
	protected bool m_Working;
	protected int  alp_SoundLoopType;
	protected int  alp_SoundLoopTypeLast;
	
	protected EffectSound m_EngineLoop;
	protected ref Timer   m_SoundLoopStartTimer;
	protected ItemBase    m_Battery;

	void alp_GeigerCounter()
	{
		m_SoundLoopStartTimer = new Timer;
		RegisterNetSyncVariableInt("alp_SoundLoopType");
	}

	/**
	 * Loop principal de funcionamento (Lado Servidor).
	 */
	override void OnWork(float consumed_energy)
	{
		if (GetGame().IsServer())
		{
			float radiation = GetND().GetMS().GetRadiationManager().GetRadiationAt(GetPosition());
			int currentSoundType = alpGeigerSound.GetSoundTypeValue(radiation);
			
			if (alp_SoundLoopType != currentSoundType)
			{
				alp_SoundLoopType = currentSoundType;
				SetSynchDirty();
			}
		}
		m_Working = true;
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
		m_Working = false;
		
		if (GetGame().IsClient())
		{
			if (m_EngineLoop && m_EngineLoop.IsSoundPlaying())
				m_EngineLoop.SoundStop();
				
			alp_SoundLoopTypeLast = alpGEIGERSOUNTYPE.NONE;
		}
		
		if (GetGame().IsServer())
			alp_SoundLoopType = alpGEIGERSOUNTYPE.NONE;
	}

	/**
	 * Gerenciamento de efeitos sonoros no Cliente via Sincronização.
	 */
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (alp_SoundLoopType != alp_SoundLoopTypeLast)
		{
			UpdateSoundLoop();
			alp_SoundLoopTypeLast = alp_SoundLoopType;
		}
	}

	void UpdateSoundLoop()
	{
		if (m_EngineLoop && m_EngineLoop.IsSoundPlaying())
			m_EngineLoop.SoundStop();

		if (alp_SoundLoopType != alpGEIGERSOUNTYPE.NONE)
		{
			string soundset = alpGeigerSound.GetSoundSetByType(alp_SoundLoopType);
			PlaySoundSetLoop(m_EngineLoop, soundset, 0, 0);
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTurnOnWeaponLight);  // Reutiliza ação de ligar eletrônicos
		AddAction(ActionTurnOffWeaponLight); // Reutiliza ação de desligar eletrônicos
	}
}