/**
 * areaexposure.c
 * * MODIFICADOR DE EXPOSIÇÃO DE ÁREA - Módulo ND_MISSIONS
 * Gerencia a criação de cortes e envenenamento químico baseado na proteção RPG do jogador.
 */

modded class AreaExposureMdfr: ModifierBase
{
	override void BleedingSourceCreateCheck(PlayerBase player)
	{
		// OTIMIZAÇÃO: Verificação rigorosa contra Null Pointer Exceptions
		if (!player || !player.GetRP() || !player.GetRP().GetProtection() || !player.GetBleedingManagerServer())
			return;

		// Considera a resistência natural do jogador (RPG stats)
		float naturalProtection = player.GetRP().GetProtection().GetNaturalResistance(alpPROTECTION.CHEMICAL);
		if (naturalProtection >= Math.RandomFloat01())
		{
			return;
		}	
		
		int free_bs_locations = 0; // Bitmask: cada bit '1' representa um local disponível para sangramento
		
		// NOTA: Variável 'list' original removida pois não era utilizada. (Otimização de Memória)
		
		foreach(int location: alpProtection.alp_InventorySlots)
		{
			float prot_level = player.GetRP().GetProtection().GetProtection(DEF_CHEMICAL, location);
			
			float dice_throw = Math.RandomFloat01();
			if (dice_throw > prot_level)
			{
				free_bs_locations = player.GetBleedingManagerServer().GetFreeBleedingSourceBitsByInvLocation(location) | free_bs_locations;
			}
		}
		
		int num_of_free_bs = Math.GetNumberOfSetBits(free_bs_locations); // Quantidade de bits em '1'
		
		if (num_of_free_bs > 0)
		{
			int random_bs_index = Math.RandomIntInclusive(0, num_of_free_bs - 1); // -1 no máximo para converter count em index
			
			// CORREÇÃO: Conversão explícita para inteiro exigida em sintaxe moderna (Math.Pow retorna float)
			int random_bs_bit = (int)Math.Pow(2, Math.GetNthBitSet(free_bs_locations, random_bs_index));
			player.GetBleedingManagerServer().AttemptAddBleedingSourceDirectly(random_bs_bit, eBleedingSourceType.CONTAMINATED);
		}
	}

	override float TransmitAgents(PlayerBase player, float count)
	{
		// OTIMIZAÇÃO: Verificação rigorosa de segurança
		if (!player || !player.GetRP() || !player.GetRP().GetProtection()) 
			return count;
		
		float protection = player.GetRP().GetProtection().GetProtection(DEF_CHEMICAL, -1); // Calcula o nível geral (todos os slots juntos)
		float naturalProtection = player.GetRP().GetProtection().GetNaturalResistance(alpPROTECTION.CHEMICAL); // Subtrai a quantidade da proteção natural
		
		float result = count - (count * protection) - (count * naturalProtection);
		
		if (result > 0)
		{
			player.InsertAgent(eAgents.CHEMICAL_POISON, result);
		}
		
		return count;
	}
}