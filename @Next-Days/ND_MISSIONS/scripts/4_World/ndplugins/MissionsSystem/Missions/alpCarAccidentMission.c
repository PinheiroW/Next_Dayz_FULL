/**
 * alpCarAccidentMission.c
 * * MISSION LOGIC: CAR ACCIDENT - Módulo ND_MISSIONS
 * Gerencia o spawn de veículos danificados e as condições de resgate/roubo.
 */

class alpCarAccidentMission extends alpMission
{
	// --- Configurações Iniciais ---
	override void OnInit()
	{
		// Configuração de strings de mensagens (referenciadas no sistema de tradução)
		alp_SendInfoStart   = ALPMSTYPE.MMMISSIONCARSTART;
		alp_SendInfoEnd     = ALPMSTYPE.MMMISSIONCAREND;
		alp_AlertInfoIn     = ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut    = ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn     = ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut    = ALPMSTYPE.MMPERSONAL;		
	}
	
	// --- Verificações de Estado ---

	override protected bool CheckFailedCondition(float timeslice) 
	{	
		// Se todos os veículos da missão forem destruídos, a missão falha
		if ( IsVehiclesRuined() ) 
		{
			return true;
		}
		return false;
	}

	override protected bool CheckSecuredCondition(float timeslice) 
	{	
		// A missão é garantida se a condição base for aceita e o veículo for "reclamado" (roubado)
		if ( super.CheckSecuredCondition( timeslice ) && IsVehicleTheft() ) 
		{
			return true;
		}
		return false;
	}

	// --- Lógica de Spawn e Dano ---

	override protected bool SpawnVehicles(bool missionSecured = false)
	{
		if (super.SpawnVehicles(missionSecured))
		{ 
			CarScript car;
			foreach (alpMissionElement e : alp_Vehicles)
			{
				if ( Class.CastTo( car, e.Get() ) ) 
				{
					// Aplica danos aleatórios para simular o impacto
					float damage = Math.RandomFloat(0.1, 0.8);
					car.SetHealth("", "Health", car.GetMaxHealth("", "Health") * damage);
					
					// Esvazia o tanque de combustível
					car.GetFluidFraction(CarFluid.FUEL);
					car.Fill(CarFluid.FUEL, 0); 

					// Danifica a bateria se houver uma
					EntityAI battery = car.GetInventory().FindAttachmentBySlotName("CarBattery");
					if (battery)
					{
						battery.SetHealth("", "Health", battery.GetMaxHealth("", "Health") * 0.2);
					}
				}
			}
			return true;
		}
		return false;
	}

	/**
	 * Verifica se o veículo ainda pertence à missão ou se foi "limpo" por um jogador.
	 */
	private bool IsVehicleTheft()
	{
		CarScript car;
		foreach (alpMissionElement e : alp_Vehicles)
		{	
			Transport vehicle;
			if ( Class.CastTo( vehicle, e.Get() ) ) 
			{
				if ( Class.CastTo( car, vehicle) )
				{
					// Se o carro não é mais um objeto de missão, ele foi "roubado"/conquistado
					if (car.IsMissionObject())
						return false;
				}
				
				HelicopterScript heli;
				if ( Class.CastTo( heli, vehicle) )
				{
					if (heli.IsMissionObject())
						return false;				
				}				
			}		
		}	
		return true;
	}

	/**
	 * Verifica se os veículos foram completamente arruinados.
	 */
	private bool IsVehiclesRuined()
	{
		bool ruined = true;
		CarScript car;
		
		for( int i = 0; i < alp_Vehicles.Count(); i++)
		{
			alpMissionElement e = alp_Vehicles.Get(i);
			Transport vehicle;
			if ( Class.CastTo( vehicle, e.Get() ) ) 
			{
				if ( Class.CastTo( car, vehicle) )
				{
					if (!car.IsRuined())
					{
						ruined = false; // Se pelo menos um carro estiver inteiro, a missão continua
					}
				}
			}		
		}	
		return ruined;
	}
}