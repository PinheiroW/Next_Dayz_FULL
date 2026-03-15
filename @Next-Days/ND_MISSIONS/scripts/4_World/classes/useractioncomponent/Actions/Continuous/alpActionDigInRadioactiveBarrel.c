/**
 * alpActionDigInRadioactiveBarrel.c
 * * AÇÃO CONTÍNUA CUSTOMIZADA (ENTERRAR BARRIL RADIOATIVO)
 * Gerencia o enterro de barris, aplicação de radiação e bônus de reputação.
 */

class alpActionDigInRadioactiveBarrelCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DIG_STASH);
	}
};

class alpActionDigInRadioactiveBarrel: ActionContinuousBase
{	
	static float m_DigStashSlopeTolerance = 0.6;
	
	void alpActionDigInRadioactiveBarrel()
	{
		m_CallbackClass		= alpActionDigInRadioactiveBarrelCB;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_DIGMANIPULATE;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight	= UASoftSkillsWeight.ROUGH_LOW;
		m_Text 				= "#bury";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget	= new CCTObject(UAMaxDistances.DEFAULT);
		m_ConditionItem		= new CCINonRuined();
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !target) return false;

		ItemBase targetIB;
		if (Class.CastTo(targetIB, target.GetObject()) && targetIB.CanBeDiggedAlp())
		{
			if (player.IsPlacingLocal())
				return false;
			
			// LÓGICA MANTIDA: Verifica a inclinação do terreno para permitir o enterro
			vector surface_normal = GetGame().GetSurfaceNormal(targetIB.GetPosition()[0], targetIB.GetPosition()[2]);
			if (surface_normal[1] < m_DigStashSlopeTolerance)
				return false;

			return true;
		}
		
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		super.OnExecuteServer(action_data);
		
		// LÓGICA MANTIDA: Gera partículas de terra durante a ação
		if (GetGame().IsMultiplayer())
			return;

		SpawnParticleShovelRaise(action_data);
	}
	
	void SpawnParticleShovelRaise(ActionData action_data)
	{
		if (action_data && action_data.m_Player)
			ParticleManager.GetInstance().PlayOnObject(ParticleList.DIGGING_STASH, action_data.m_Player);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target || !action_data.m_Player) return;

		EntityAI targetEntity = EntityAI.Cast(action_data.m_Target.GetObject());
		if (!targetEntity) return;
		
		// CRIAÇÃO DO STASH (ESCONDERIJO)
		UndergroundStash stash = UndergroundStash.Cast(GetGame().CreateObjectEx("UndergroundStash", targetEntity.GetPosition(), ECE_PLACE_ON_SURFACE));  
		
		if (stash)
		{
			stash.PlaceOnGround();
			stash.SetLifetimeMax(180);
			
			// SEGURANÇA: Só deleta o barril se o stash foi criado com sucesso
			GetGame().ObjectDelete(targetEntity);
		}
		else
		{
			// Se falhou ao criar o stash, interrompe para não sumir com o item do player
			return;
		}

		// APLICAÇÃO DE DANO NA FERRAMENTA
		if (action_data.m_MainItem)
		{
			MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, 10);
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
		}
		
		// SISTEMA DE REPUTAÇÃO E RADIAÇÃO (ND_MISSIONS)
		if (action_data.m_Player.GetRP())
		{
			float rep = GetReputationBonus(action_data.m_Player);
			action_data.m_Player.GetRP().ChangeReputation(rep);
			
			// Cálculo de exposição radioativa ao manipular o barril
			float radH = action_data.m_Player.GetRP().GetRadiation() * GetRadiationRate();
			action_data.m_Player.GetRP().SetRadiation(radH);
		}
	}

	// Métodos Auxiliares de Equilíbrio (Configuração Interna)
	float GetReputationBonus(PlayerBase player)
	{
		return 5.0; // Valor de bônus por enterrar lixo radioativo
	}

	float GetRadiationRate()
	{
		return 1.10; // Aumenta em 10% a radiação atual do jogador pelo contato
	}
};