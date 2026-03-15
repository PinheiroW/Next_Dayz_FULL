/**
 * cacontinuousfill.c
 * * COMPONENTE DE AÇÃO CONTÍNUA (ENCHIMENTO) - Módulo ND_MISSIONS
 * Gerencia a física de enchimento gradual de recipientes em poços d'água e postos de combustível customizados.
 */

modded class CAContinuousFill : CAContinuousBase
{
	override int Execute(ActionData action_data)
	{
		// OTIMIZAÇÃO E SEGURANÇA: Prevenção imediata de crash caso a ação seja corrompida pela rede/física
		if (!action_data || !action_data.m_Target || !action_data.m_MainItem)
		{
			return UA_ERROR;
		}

		Well well;
		FuelStation station;
		
		bool enableWell = false;
		bool enableFuel = false;

		// OTIMIZAÇÃO DE PERFORMANCE: Cache das opções globais fora das avaliações de frame contínuo
		if (GetND() && GetND().GetResources() && GetND().GetResources().GetOptions())
		{
			auto options = GetND().GetResources().GetOptions();
			enableWell = options.EnableWellManagement;
			enableFuel = options.EnableFuelstationManagement;
		}
		
		// ----- LÓGICA DE POÇOS DE ÁGUA (WELLS) -----
		if (enableWell && Class.CastTo(well, action_data.m_Target.GetObject())) 
		{
			if (!action_data.m_Player)
			{
				return UA_ERROR;
			}
						
			if (action_data.m_MainItem.GetQuantity() >= action_data.m_MainItem.GetQuantityMax() || !well.HasWaterALP())
			{
				return UA_FINISHED;
			}			
			
			if (m_SpentQuantity_total < m_TargetUnits)
			{
				m_SpentQuantity += m_AdjustedQuantityFilledPerSecond * action_data.m_Player.GetDeltaT();
				m_TimeElpased += action_data.m_Player.GetDeltaT();
								
				if (m_TimeElpased >= m_DefaultTimeStep)
				{						
					float water = well.GetWaterAmmount();
					
					if (m_SpentQuantity <= water)
					{					
						well.DrainWaterALP(m_SpentQuantity);
						CalcAndSetQuantity(action_data);
					}
					else
					{							
						m_SpentQuantity = water;					
						well.DrainWaterALP(m_SpentQuantity);
						CalcAndSetQuantity(action_data);
					}
					m_TimeElpased = 0;	
				}
				
				return UA_PROCESSING;
			}
			else
			{
				CalcAndSetQuantity(action_data);
				// A grafia 'OnCompletePogress' é intencional para herdar corretamente do código Vanilla
				OnCompletePogress(action_data); 
				return UA_FINISHED;
			}			
		}
		
		// ----- LÓGICA DE POSTOS DE COMBUSTÍVEL (FUEL STATIONS) -----
		else if (enableFuel && Class.CastTo(station, action_data.m_Target.GetObject()))
		{
			if (!action_data.m_Player)
			{
				return UA_ERROR;
			}
						
			if (action_data.m_MainItem.GetQuantity() >= action_data.m_MainItem.GetQuantityMax() || !station.HasFuelALP())
			{
				return UA_FINISHED;
			}			
			
			if (m_SpentQuantity_total < m_TargetUnits)
			{
				m_SpentQuantity += m_AdjustedQuantityFilledPerSecond * action_data.m_Player.GetDeltaT();
				m_TimeElpased += action_data.m_Player.GetDeltaT();
								
				if (m_TimeElpased >= m_DefaultTimeStep)
				{						
					float fuel = station.GetFuelAmmount();
					
					if (m_SpentQuantity <= fuel)
					{					
						station.DrainFuelALP(m_SpentQuantity);
						CalcAndSetQuantity(action_data);
					}
					else
					{							
						m_SpentQuantity = fuel;					
						station.DrainFuelALP(m_SpentQuantity);
						CalcAndSetQuantity(action_data);
					}
					m_TimeElpased = 0;	
				}
				
				return UA_PROCESSING;
			}
			else
			{
				CalcAndSetQuantity(action_data);
				OnCompletePogress(action_data);
				return UA_FINISHED;
			}			
		}
		
		// ----- FALLBACK -----
		// Se as mecânicas customizadas estiverem desligadas ou o alvo for outro, retorna ao comportamento base do DayZ
		return super.Execute(action_data);
	}			
};