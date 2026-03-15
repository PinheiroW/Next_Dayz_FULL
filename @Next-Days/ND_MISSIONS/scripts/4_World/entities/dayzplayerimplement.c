/**
 * dayzplayerimplement.c
 * * PLAYER PHYSICS IMPLEMENTATION - Módulo ND_MISSIONS
 * Controla restrições de movimento (pulo e escalada) para balanceamento de gameplay.
 */

modded class DayZPlayerImplement extends DayZPlayer
{
	/**
	 * Valida se o jogador pode escalar o objeto à frente.
	 */
	override bool CanClimb(int climbType, SHumanCommandClimbResult climbRes)
	{
		if (super.CanClimb(climbType, climbRes))
		{
			// Verifica se a restrição de escalar veículos está ativa nas opções do servidor
			if (GetND().GetRP().GetPlayerOptions().DisableClimbOverVehicle && climbRes)
			{	
				CarScript car;
				// Bloqueia se o ponto de garra ou apoio for um veículo
				if (climbRes.m_GrabPointParent && Class.CastTo(car, climbRes.m_GrabPointParent))
					return false;	

				if (climbRes.m_ClimbStandPointParent && Class.CastTo(car, climbRes.m_ClimbStandPointParent))
					return false;					
				
				if (climbRes.m_ClimbOverStandPointParent && Class.CastTo(car, climbRes.m_ClimbOverStandPointParent))
					return false;	
			}
			
			return true;
		}
		
		return false;
	}

	/**
	 * Valida se o jogador pode iniciar um pulo.
	 */
	override bool CanJump()
	{
		if (super.CanJump())
		{
			// Se a restrição global estiver ativa, verifica proximidade com veículos
			if (GetND().GetRP().GetPlayerOptions().DisableClimbOverVehicle)
			{
				autoptr array<Object> nearest_objects = new array<Object>;
				autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
		
				// Raio de detecção de 2 metros ao redor do jogador
				GetGame().GetObjectsAtPosition(GetPosition(), 2.0, nearest_objects, proxy_cargos);

				for (int i = 0; i < nearest_objects.Count(); i++)
				{
					CarScript car;
					if (Class.CastTo(car, nearest_objects.Get(i)))
					{
						// Bloqueia o pulo se houver um veículo colado ao jogador
						return false;
					}
				}
			}
			return true;
		}
		
		return false;
	}
}