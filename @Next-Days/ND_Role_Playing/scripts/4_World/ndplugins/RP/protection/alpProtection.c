/**
 * @class   alpProtection
 * @brief   Gerencia a resistência passiva do jogador contra Radiação e Gás no Next Days
 * Auditado em: 2026 - Foco em Segurança de SyncData (Rede) e Prevenção de Null Pointers
 */
modded class alpProtection 
{
	override float GetNaturalResistanceAgainstRadiation()
	{	
		// 1. Failsafe Global: Garante que as configurações centrais do mod carregaram
		if ( !GetND() || !GetND().GetRP() || !GetND().GetRP().GetPerksOptions() ) 
		{
			return 0.0;
		}

		if ( !GetND().GetRP().GetPerksOptions().EnablePerkRadiationResistance )
		{		
			return 0.0;
		}		
			
		// 2. Proteção do Jogador e dos Dados Sincronizados
		if ( !alp_Player || !alp_Player.GetSyncData() ) 
		{
			return 0.0;
		}
		
		// 3. Busca Segura no Dicionário (Evita Crash se o elemento não existir)
		auto syncElement = alp_Player.GetSyncData().GetElement( alpRPelements.RAD_RESIST );
		if ( !syncElement ) 
		{
			return 0.0;
		}
		
		int level = syncElement.GetValue();
		float resistance = GetND().GetRP().GetPerkRadiationResistanceMdf( level );

		// 4. Divisão com tipagem explícita de ponto flutuante
		return resistance / 100.0;
	}	
	

	override float GetNaturalResistanceAgainstChemical()
	{	
		// 1. Failsafe Global
		if ( !GetND() || !GetND().GetRP() || !GetND().GetRP().GetPerksOptions() ) 
		{
			return 0.0;
		}

		if ( !GetND().GetRP().GetPerksOptions().EnablePerkToxicResistance )
		{		
			return 0.0;
		}
			
		// 2. Proteção do Jogador e dos Dados Sincronizados
		if ( !alp_Player || !alp_Player.GetSyncData() ) 
		{
			return 0.0;
		}
		
		// 3. Busca Segura no Dicionário
		auto syncElement = alp_Player.GetSyncData().GetElement( alpRPelements.TOXIC_RESIST );
		if ( !syncElement ) 
		{
			return 0.0;
		}
		
		int level = syncElement.GetValue();
		float resistance = GetND().GetRP().GetPerkToxicResistanceMdf( level );

		// Corrigido typo (resitance -> resistance) e aplicada tipagem de ponto flutuante
		return resistance / 100.0;
	}	
}