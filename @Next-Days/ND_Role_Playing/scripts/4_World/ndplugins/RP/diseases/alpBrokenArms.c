/**
 * @class   alpBrokenArms
 * @brief   Gerencia a cobrança e a cura de braços quebrados no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Restauração Dinâmica de Vida
 */
class alpBrokenArms extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas de carregamento de Configs/Traders
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().BrokenArm;
	}
	
	override void CureDisease()
	{
		// 2. Proteção do ponteiro do Jogador
		if (!alp_Player) return;

		// 3. Segurança: Cura de vida e remoção de modificadores deve ser feita no Servidor
		if (GetGame().IsServer())
		{
			// 4. Melhoria: Usa o valor máximo dinâmico em vez de forçar o número 100
			float maxHealthRight = alp_Player.GetMaxHealth("RightArm", "Health");
			float maxHealthLeft = alp_Player.GetMaxHealth("LeftArm", "Health");
			
			alp_Player.SetHealth("RightArm", "Health", maxHealthRight);
			alp_Player.SetHealth("LeftArm", "Health", maxHealthLeft);
			
			// Remoção do modificador de dor/tremedeira de forma segura
			if (alp_Player.GetModifiersManager())
			{
				if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_ARMS))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_ARMS);
				}	
			}
		}
	}
}