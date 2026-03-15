/**
 * alpRadiationBlockMdfr.c
 * * MODIFICADOR DE BLOQUEIO DE RADIAÇÃO (PÍLULAS) - Módulo ND_MISSIONS
 * Controla o efeito curativo contínuo, reduzindo a radiação acumulada ao longo do tempo.
 */

class alpRadiationBlockMdfr: ModifierBase
{
	float m_RegenTime;
	float m_RadiationReductionPerTick; // Cache para otimização de performance
	
	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_ID 					= rModifiers.MDF_ALPRADIATIONBLOCK;
		m_TickIntervalInactive 	= 3;
		m_TickIntervalActive 	= 1; // DEFAULT_TICK_TIME_ACTIVE
		m_IsPersistent			= true;
		
		// Valores padrão de fallback
		m_RegenTime 					= 180;
		m_RadiationReductionPerTick 	= 0.0; 

		// OTIMIZAÇÃO E SEGURANÇA: Verificação de ponteiros para as configurações globais
		if (GetND() && GetND().GetMS() && GetND().GetMS().GetOptionsRadiation())
		{
			auto radOptions = GetND().GetMS().GetOptionsRadiation();
			m_RegenTime = radOptions.AntiRadBlockDurationEffect;	
			
			// CORREÇÃO MATEMÁTICA: Evita arredondamento de inteiros usando 3600.0 
			// O valor é pré-calculado no Init() para economizar processamento por segundo no OnTick
			m_RadiationReductionPerTick = (radOptions.EffectAntiRadBlockPills / 3600.0) * -1000.0;
		}		
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return false; // A ativação ocorre de forma forçada pelo consumo do item, não via condição orgânica
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;
		
		if (player.GetNotifiersManager()) 
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);	
	}

	override void OnDeactivate(PlayerBase player)
	{
		if (!player) return;
		
		if (player.GetNotifiersManager()) 
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		// Simplificação limpa do retorno booleano
		return (GetAttachedTime() >= m_RegenTime);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{		
		if (!player) return;
		
		// SEGURANÇA: Previne NPE caso o jogador não tenha módulo de RPG atrelado ainda
		if (player.GetRP())
		{
			float doses = player.GetRP().GetRecievedRadiation();
			
			if (doses > 0)
			{
				// OTIMIZAÇÃO: Usa o valor estático do cache para garantir performance estável no server
				player.GetRP().SetRecievedRadiation(m_RadiationReductionPerTick);
			}	
		}						
	}
}