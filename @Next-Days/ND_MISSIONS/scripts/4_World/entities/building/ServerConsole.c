/**
 * ServerConsole.c
 * * ENTIDADE CENTRAL DE MISSÃO (CONSOLE DE DADOS) - Módulo ND_MISSIONS
 * Gerencia a ativação de eventos globais, segurança por cartões e download de dados.
 */

enum alpMMACTION {
	NONE,
	ACTIVE,
	DEACTIVE,
	SET_TIME_TO_ACTIVE,
	SET_TIME_TO_DEACTIVE,
	CANCEL_ACTIVE_TIME,	
	CANCEL_DEACTIVE_TIME,		
}

class alp_ServerConsole extends BuildingSuper  
{
	string                          m_DataAboutMission;
	string 							m_MissionWhileCountdowningON;
	string 							m_MissionWhileCountdowningOFf;	 
	
	int 							alp_ParentMission;
	int 							alp_MissionAccesCardID;
	
	ref alpMissionAddControlPanel	alp_MissionManage;

	int 							alp_MissionManaged;		
	int 							alp_MissionTriggerSetting;
	
	int 							alp_MissionSwitchCooldown;	

	int 							alp_MissionActionGameplayCountdownedON;
	int 							alp_MissionActionGameplayCountdownedOFF;
	
	string 							alp_CountdownMessageON;	
	string 							alp_CountdownMessageOFF;			
	string 							alp_MissionActionMessageON;	
	string 							alp_MissionActionMessageOFF;	
		
	protected ref Timer  			alp_ActionTimer;		
			
	// Efeitos visuais (Partículas)
	protected Particle 				alp_ParticleDamaged;
	protected Particle 				alp_ParticleRuined;
	protected vector				alp_ParticlePos = "0 1.2 0"; // Posição relativa do efeito no console

	void alp_ServerConsole()
	{
		alp_ActionTimer = new Timer();
	}

	void ~alp_ServerConsole()
	{
		if (alp_ActionTimer)
			alp_ActionTimer.Stop();
			
		StopVfxALP();
	}

	override bool IsBuilding()
	{
		return false;
	}

	/**
	 * Define as interações disponíveis baseadas no estado do console.
	 */
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionServerConsole);         // Ação base de interação
		AddAction(alpActionServerConsoleLocked);   // Feedback de trancado
		AddAction(alpActionServerConsoleLock);     // Trancar
		AddAction(alpActionServerConsoleUnlock);   // Destrancar com cartão
		AddAction(alpActionServerConsoleRepair);   // Reparar se danificado
		
		AddAction(alpActionServerConsoleDownloadData); // Baixar progresso de missão
		AddAction(alpActionServerConsoleDeleteData);   // Resetar console
	}

	/**
	 * Gerencia o download de dados para jogadores próximos.
	 */
	void DownloadData(PlayerBase player)
	{
		if ( !GetGame().IsServer() ) return;

		ref array<alpMission> ms = GetND().GetMS().GetMissionsByParent( alp_ParentMission );
		if ( !ms || ms.Count() == 0 ) return;

		int count = 0;
		array<PlayerBase> allMans = new array<PlayerBase>;
		
		// Coleta jogadores em um raio de 5 metros para sincronizar o progresso
		array<Object> objects_in_vicinity = new array<Object>;
		GetGame().GetObjectsAtPosition3D( player.GetPosition(), 5, objects_in_vicinity, null );
		
		for ( int i = 0; i < objects_in_vicinity.Count(); i++ )
		{
			PlayerBase man = PlayerBase.Cast( objects_in_vicinity.Get(i) );
			if ( man && man.IsPlayer() && allMans.Find(man) == -1 )
			{
				allMans.Insert(man);
			}
		}

		foreach(alpMission m : ms) 
		{
			if ( m.alp_MissionStarted ) 
			{
				count++;
				foreach(PlayerBase p : allMans) 
				{
					GetND().GetMS().SendRPC_RegisterMission( p, m.GetID(), m.alp_MissionStarted );
				}
			}
		}			
		
		// Notificações de sucesso ou erro
		if ( count > 0 ) 
		{
			GetND().GetNotf().SendMissionMessage( ALPMSTYPE.SMACTIVATE, alp_MissionManaged, "#alp_action_console_download1", player.GetPosition(), null, true );	
		} 
		else 
		{
			GetND().GetNotf().SendMissionMessage( ALPMSTYPE.SMERROR, alp_MissionManaged, "#alp_action_console_download2", player.GetPosition(), null, true );
		}
	}

	/**
	 * Controle de Efeitos Visuais de Dano
	 */
	void UpdateVfxALP()
	{
		if ( !GetGame().IsClient() ) return;

		float health = GetHealth("", "Health");
		StopVfxALP();

		if ( health <= 0 )
		{
			alp_ParticleRuined = Particle.PlayOnObject(ParticleList.SMOKING_CANISTER_FIRE, this, alp_ParticlePos);
		}
		else if ( health < 50 )
		{
			alp_ParticleDamaged = Particle.PlayOnObject(ParticleList.GRENADE_M18_GREEN_LOOP, this, alp_ParticlePos);
		}
	}

	void StopVfxALP()
	{
		if (alp_ParticleDamaged) { alp_ParticleDamaged.Stop(); alp_ParticleDamaged = null; }
		if (alp_ParticleRuined) { alp_ParticleRuined.Stop(); alp_ParticleRuined = null; }
	}
}