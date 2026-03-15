/**
 * @class   alpBleedingDisease
 * @brief   Gerencia o diagnóstico, cobrança escalonada e cura de sangramentos no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Segurança de Nulidade
 */
class alpBleedingDisease extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas de carregamento de Configs/Traders
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().Bleeding;
	}
		
	override bool IsInfected()
	{
		// 2. Proteção contra desconexão ou morte súbita
		if (!alp_Player) return false;
		
		return alp_Player.IsBleeding();
	}

	override float GetPrice()
	{
		if (!alp_Player) return 0.0;

		float price = super.GetPrice();	
		int count = alp_Player.GetBleedingSourceCount();
		
		// Mecânica de RPG: O preço escala conforme a quantidade de cortes (bandagens necessárias)
		if (count > 0)
		{
			price = price * count;
		}
				
		return price;
	}	
		
	override void CureDisease()
	{
		if (!alp_Player) return;

		// 3. Segurança: Tratamentos médicos de status só devem ser processados pelo Servidor
		if (GetGame().IsServer())
		{
			if (alp_Player.GetBleedingManagerServer())
			{
				alp_Player.GetBleedingManagerServer().RemoveAllSources();	
			}	
		}
	}
}