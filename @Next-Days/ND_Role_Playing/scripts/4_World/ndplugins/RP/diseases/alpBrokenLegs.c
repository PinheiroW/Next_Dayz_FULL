/**
 * @class   alpBrokenLegs
 * @brief   Gerencia a cobrança e a cura de pernas quebradas no Next Days
 * Auditado em: 2026 - Foco em Failsafes, Vida Dinâmica e Limpeza de Modificadores (Talas)
 */
class alpBrokenLegs extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia do Trader
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().BrokenLeg;
	}
	
	override void CureDisease()
	{
		// 2. Proteção do ponteiro do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Tratamentos devem ser autoridade do Servidor
		if (GetGame().IsServer())
		{
			// 4. Cura Dinâmica: Busca a vida máxima real das pernas
			float maxHealthRight = alp_Player.GetMaxHealth("RightLeg", "Health");
			float maxHealthLeft = alp_Player.GetMaxHealth("LeftLeg", "Health");
			
			alp_Player.SetHealth("RightLeg", "Health", maxHealthRight);
			alp_Player.SetHealth("LeftLeg", "Health", maxHealthLeft);
			
			// 5. Limpeza de Modificadores Segura
			if (alp_Player.GetModifiersManager())
			{
				// Remove o status de perna quebrada
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_LEGS);
				}			
				
				// NOVO: Remove o modificador de regeneração caso o jogador esteja usando uma tala
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BONE_REGEN))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BONE_REGEN);
				}
			}
			
			// Restaura a capacidade de correr e andar normalmente
			alp_Player.UpdateBrokenLegs(eBrokenLegs.NO_BROKEN_LEGS);
		}
	}
}