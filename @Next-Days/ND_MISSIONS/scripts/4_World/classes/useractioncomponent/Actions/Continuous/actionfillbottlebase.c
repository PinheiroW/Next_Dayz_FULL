/**
 * actionfillbottlebase.c
 * * AÇÃO BASE CONTÍNUA (ENCHER RECIPIENTES) - Módulo ND_MISSIONS
 * Controla o enchimento em fontes dinâmicas, limitando a água/gasolina e aplicando radiação.
 */

modded class ActionFillBottleBase: ActionContinuousBase
{
	/*
	// BLOCO DE COMPATIBILIDADE NAMALSK MANTIDO COMO REGISTRO HISTÓRICO
	#ifdef NAMALSK_SURVIVAL	
	... (Lógica original de Namalsk mantida no seu código fonte) ...
	#endif	
	*/
	
	override int GetLiquidType(PlayerBase player, ActionTarget target, ItemBase item)
	{
		int liquidType = LIQUID_NONE;
		
		// OTIMIZAÇÃO: Null check preventivo no alvo
		if (target && target.GetObject())
		{
			liquidType = target.GetObject().GetLiquidSourceType();							
		}
		else if (target)
		{
			string surfaceType;
			vector hit_pos = target.GetCursorHitPos();
			GetGame().SurfaceGetType3D(hit_pos[0], hit_pos[1], hit_pos[2], surfaceType);
			
			if (surfaceType == "")
			{
				if (hit_pos[1] <= g_Game.SurfaceGetSeaLevel() + 0.001)
				{
					liquidType = LIQUID_SALTWATER;
				}
			}
			else
			{
				liquidType = SurfaceInfo.GetByName(surfaceType).GetLiquidType();
			}
		}
		
		int liguidMask = LIQUID_WATER | LIQUID_RIVERWATER | LIQUID_FRESHWATER | LIQUID_STILLWATER | LIQUID_HOTWATER | LIQUID_CLEANWATER;
		
		if (liquidType & liguidMask)
		{
			// SEGURANÇA: Garante que o jogador e o módulo RP existem antes de avaliar a zona
			if (player && player.GetRP())
			{
				if (player.GetRP().IsRadiationHigh())
				{
					liquidType = LIQUID_RADIOACTIVEWATER; 
				}
			}	
		}			
				
		return liquidType & m_AllowedLiquidMask;		
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// SEGURANÇA BÁSICA
		if (!target) return false;

		Well well;
		FuelStation station;
		
		// OTIMIZAÇÃO: Validação segura em cascata das opções globais (Evita vazamento de CPU)
		if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
		{
			auto options = GetND().GetResources().GetOptions();
			
			// LÓGICA MANTIDA: Bloqueia a ação se o poço ou a bomba estiverem secos
			if (options.EnableWellManagement && Class.CastTo(well, target.GetObject()) && GetGame().IsServer() && !well.HasWaterALP()) 
			{		
				return false;	
			}
			else if (options.EnableFuelstationManagement && Class.CastTo(station, target.GetObject()) && GetGame().IsServer() && !station.HasFuelALP())
			{
				return false;
			}
		}
		
		return super.ActionCondition(player, target, item);
	}
	
	override bool ActionConditionContinue(ActionData action_data)
	{
		if (!action_data || !action_data.m_Target) return false;

		Well well;
		FuelStation station;
		
		if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
		{
			auto options = GetND().GetResources().GetOptions();
			
			if (options.EnableWellManagement && Class.CastTo(well, action_data.m_Target.GetObject()) && GetGame().IsServer() && !well.HasWaterALP()) 
			{		
				return false;	
			}
			else if (options.EnableFuelstationManagement && Class.CastTo(station, action_data.m_Target.GetObject()) && GetGame().IsServer() && !station.HasFuelALP())
			{
				return false;	
			}
		}

		return super.ActionConditionContinue(action_data);
	}
	
	override void OnStartServer(ActionData action_data)
	{
		super.OnStartServer(action_data);
		
		// SEGURANÇA: Impede execução se os dados da rede falharem
		if (!action_data || !action_data.m_Target) return;

		if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
		{
			auto options = GetND().GetResources().GetOptions();
			
			Well well;
			if (options.EnableWellManagement && Class.CastTo(well, action_data.m_Target.GetObject())) 
			{
				well.SaveCurrentAmmount();
			}

			FuelStation station;
			if (options.EnableFuelstationManagement && Class.CastTo(station, action_data.m_Target.GetObject())) 
			{
				station.SaveCurrentAmmount();
			}	
		}		
	}
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		if (!action_data || !action_data.m_Target) return;

		if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
		{
			auto options = GetND().GetResources().GetOptions();
			
			Well well;
			if (options.EnableWellManagement && Class.CastTo(well, action_data.m_Target.GetObject())) 
			{
				// Registra o esvaziamento do poço
				well.SaveWellALP();
			}		
			
			FuelStation station;
			if (options.EnableFuelstationManagement && Class.CastTo(station, action_data.m_Target.GetObject())) 
			{
				// Registra o esvaziamento da bomba
				station.SaveFuelStationALP();
			}
		}			
	}	
}; // Adicionado ponto e vírgula obrigatório