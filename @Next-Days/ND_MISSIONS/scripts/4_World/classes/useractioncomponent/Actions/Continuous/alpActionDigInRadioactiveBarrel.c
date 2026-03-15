/**
 * alpActionDigInRadioactiveBarrel.c
 * * CONTINUOUS ACTION (BURY RADIOACTIVE BARREL) - Módulo ND_MISSIONS
 * Gerencia o descarte de barris, aplicação de radiação e ganhos de reputação.
 */

class alpActionDigInRadioactiveBarrelCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		// Utiliza o tempo padrão de enterrar itens do DayZ
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DIG_STASH);
	}
};

class alpActionDigInRadioactiveBarrel: ActionContinuousBase
{	
	// Tolerância de inclinação do terreno (0.6 = padrão DayZ)
	static float m_DigStashSlopeTolerance = 0.6;
	
	void alpActionDigInRadioactiveBarrel()
	{
		m_CallbackClass   = alpActionDigInRadioactiveBarrelCB;
		m_CommandUID      = DayZPlayerConstants.CMD_ACTIONFB_DIGMANIPULATE;
		m_FullBody        = true;
		m_StanceMask      = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_LOW;
		m_Text            = "#bury";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
		m_ConditionItem   = new CCINonRuined(); // Exige ferramenta em bom estado
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!player || !target) return false;

		ItemBase targetIB;
		if (Class.CastTo(targetIB, target.GetObject()) && targetIB.CanBeDiggedAlp())
		{
			if (player.IsPlacingLocal()) return false;
			
			// Validação de inclinação para garantir que o enterro seja visualmente correto
			vector surface_normal = GetGame().GetSurfaceNormal(targetIB.GetPosition()[0], targetIB.GetPosition()[2]);
			if (surface_normal[1] < m_DigStashSlopeTolerance) return false;

			return true;
		}
		
		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		super.OnExecuteServer(action_data);
		
		// Efeitos de partículas apenas se não estiver em ambiente multiplayer direto (otimização)
		if (GetGame().IsMultiplayer()) return;

		SpawnParticleShovelRaise(action_data);
	}
	
	void SpawnParticleShovelRaise(ActionData action_data)
	{
		if (action_data && action_data.m_Player)
		{
			ParticleManager.GetInstance().PlayOnObject(ParticleList.DIGGING_STASH, action_data.m_Player);
		}
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target || !action_data.m_Player) return;

		EntityAI targetEntity = EntityAI.Cast(action_data.m_Target.GetObject());
		if (!targetEntity) return;
		
		// LÓGICA DE TRANSFORMAÇÃO: Barril -> Stash Subterrâneo
		UndergroundStash stash = UndergroundStash.Cast(GetGame().CreateObjectEx("UndergroundStash", targetEntity.GetPosition(), ECE_PLACE_ON_SURFACE));  
		
		if (stash)
		{
			stash.PlaceOnGround();
			stash.SetLifetimeMax(180); // O esconderijo dura 3 minutos (limpeza do servidor)
			
			// Deleta o barril original após o enterro
			GetGame().ObjectDelete(targetEntity);
		}
		else
		{
			return;
		}

		// Desgaste da ferramenta e progresso de Soft Skills
		if (action_data.m_MainItem)
		{
			MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, 10);
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty(m_SpecialtyWeight);
		}
		
		// IMPACTO NO ROLEPLAY E SOBREVIVÊNCIA
		if (action_data.m_Player.GetRP())
		{
			// Concede reputação positiva pela "limpeza" do ambiente
			float rep = GetReputationBonus(action_data.m_Player);
			action_data.m_Player.GetRP().ChangeReputation(rep);
			
			// Aplica penalidade de radiação (aumento de 10% sobre o total atual)
			float currentRad = action_data.m_Player.GetRP().GetRadiation();
			action_data.m_Player.GetRP().SetRadiation(currentRad * GetRadiationRate());
		}
	}

	// CONFIGURAÇÕES DE EQUILÍBRIO (ND_OPTIONS)
	float GetReputationBonus(PlayerBase player)
	{
		return 5.0; // Bônus de prestígio
	}

	float GetRadiationRate()
	{
		return 1.10; // Fator de multiplicação (10% de aumento)
	}
};