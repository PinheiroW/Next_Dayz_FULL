/**
 * @class   alpFrostbite
 * @brief   Gerencia a cobrança dinâmica e a cura do Congelamento (Namalsk) no Next Days
 * Auditado em: 2026 - Foco em Failsafes, Segurança de Compilação e Execução de Servidor
 */
class alpFrostbite extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia de configuração financeira
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().FrostbiteSick;
	}
	
	override void CureDisease()
	{
		// 2. Proteção do ponteiro do Jogador
		if (!alp_Player) return;
		
		// 3. Segurança: Ajustes de Stats do Namalsk DEVEM ser rodados apenas no Servidor
		if (GetGame().IsServer())
		{
#ifdef NAMALSK_SURVIVAL		
			// Verificações extras para garantir que o sistema de Stats do Namalsk foi carregado
			if (alp_Player.GetStatFrostbiteZones())
			{
				alp_Player.GetStatFrostbiteZones().Set(0);		
			}
			
			if (alp_Player.GetStatFrostbiteEffect())
			{
				alp_Player.GetStatFrostbiteEffect().Set(0);
			}
			
			alp_Player.ForceUpdateFrostbiteZones();
#endif	
		}		
	}
	
	override float GetPrice()
	{
		// Previne cálculos se o jogador desconectou
		if (!alp_Player) return 0.0;

		float price = super.GetPrice();	
		price = price * GetCoefPrice();
								
		return price;
	}
	
	float GetCoefPrice()
	{
		// 4. Inicialização segura da variável para evitar lixo de memória
		float ratio = 0.0;
		
		if (!alp_Player) return 1.0; // Failsafe para não multiplicar por 0 em caso de erro

#ifdef NAMALSK_SURVIVAL			
		int frostbite = alp_Player.GetFrostbiteZones();
		
		// Lógica Bitwise excelente para calcular as zonas congeladas
		if ( frostbite & 1 ) ratio += 20;
		if ( frostbite & 2 ) ratio += 20;		
		if ( frostbite & 4 ) ratio += 20;		
		if ( frostbite & 8 ) ratio += 20;		
		if ( frostbite & 16 ) ratio += 10;				
		if ( frostbite & 32 ) ratio += 10;		
		
		// Define um custo mínimo simbólico (10%) caso esteja doente mas a zona não pontue acima
		if ( ratio == 0.0 )
			ratio = 10.0;
			
#else
		// 5. Se não for Namalsk (Chernarus, por exemplo), a cura custa 100% do preço base
		ratio = 100.0;
#endif

		ratio /= 100;
		
		return ratio;
	}
}