/**
 * alpRadiationSick1Mdfr.c
 * * MODIFICADOR DE DOENÇA DE RADIAÇÃO (ESTÁGIO 1) - Módulo ND_MISSIONS
 * Controla a ativação e desativação do primeiro estágio de envenenamento radioativo.
 */

class alpRadiationSick1Mdfr: ModifierBase
{
	override void Init()
	{
		m_ID 					= rModifiers.MDF_ALPRADIATIONSICK1;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L1 && player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L2 );
	}

	override void OnActivate(PlayerBase player)
	{
		if (!player) return;
		
		/*
		if( player.m_NotifiersManager ) 
			player.m_NotifiersManager.ActivateByType(alpeNotifiers.NTF_RADIATIONSICK);		
		*/
		
		player.IncreaseDiseaseCount();
		
		// OTIMIZAÇÃO: Verificação de segurança para evitar Null Pointer Exception
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.L1);
		}
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override void OnDeactivate(PlayerBase player)
	{
		if (!player) return;
		
		player.DecreaseDiseaseCount();
		
		// OTIMIZAÇÃO: Verificação de segurança para evitar Null Pointer Exception
		if (player.GetRP())
		{
			player.GetRP().SetRadiationSickStage(ALP_RADIATION_SICKSTAGE.NONE);
		}
		
		/*
		if( player.m_NotifiersManager ) 
			player.m_NotifiersManager.DeactivateByType(alpeNotifiers.NTF_RADIATIONSICK);	
		*/		
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		if (!player) return false;
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L1 || player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L2 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		// Mantido vazio conforme o comportamento original do estágio 1
	}
}