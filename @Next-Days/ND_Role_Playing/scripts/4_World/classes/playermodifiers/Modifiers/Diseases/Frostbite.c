#ifdef NAMALSK_SURVIVAL	
/**
 * @class   Frostbite
 * @brief   Integração do sistema de Frostbite (Namalsk) com o RPG Next Days
 * Auditado em: 2024 - Foco em Segurança de Ponteiros e Estabilidade
 */
modded class Frostbite : ModifierBase
{
	bool alp_FrostBiteSickShowed = false;
	
	override void OnTick(PlayerBase player, float deltaT)
	{	
		// 1. Verificação de segurança de ponteiro primária
		if (!player) return;

		// 2. Otimização de multiplicador de sono
		float mltp = 1.0;
		ModifiersManager mngr = player.GetModifiersManager();
		if (mngr && mngr.IsModifierActive(rModifiers.MDF_SLEEPING))
		{
			mltp = 5.0; // Frostbite progride 5x mais rápido ao dormir exposto
		}	
		
		// Lógica base de Namalsk (mantida para funcionalidade)
		float currHeatComf = player.GetStatHeatComfort().Get();
		bool isFrostiteApplicable = false;
		if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
		{
			isFrostiteApplicable = true;
		}

		// Cálculo do timer de frostbite
		float frostbite_timer = (0.01675 * currHeatComf * mltp);

		for (int i = 0; i < m_SlotCount; i++)
		{
			if (m_FrostbiteTimers[i] > -1.0)
			{
				if (!CheckSlotOfInterest(player, m_SlotsOfInterest[i]) && isFrostiteApplicable)
				{
					m_FrostbiteTimers[i] = m_FrostbiteTimers[i] + frostbite_timer;
					if (m_FrostbiteTimers[i] < -1.0)
					{
						player.GetStatFrostbiteZones().Set(player.GetStatFrostbiteZones().Get() + 1);
						m_FrostbiteTimers[i] = -1.1; // Marca zona como congelada
					}
				}
				else if (m_FrostbiteTimers[i] > 0.0)
				{
					m_FrostbiteTimers[i] = Math.Max(0, (m_FrostbiteTimers[i] - 0.1));
				}
			}
		}

		// 3. Integração Segura com o Sistema RPG Next Days
		if (m_LastFrostbiteValue != player.GetStatFrostbiteZones().Get())
		{
			player.ForceUpdateFrostbiteZones();
			m_LastFrostbiteValue = player.GetStatFrostbiteZones().Get();
			
			// Verifica se o componente RPG existe antes de operar
			auto rpComponent = player.GetRP();
			if (rpComponent)
			{
				if (m_LastFrostbiteValue > 0)
				{
					if (!alp_FrostBiteSickShowed)
					{
						player.IncreaseDiseaseCount();
						alp_FrostBiteSickShowed = true;
					}
					rpComponent.SetDisease(alpDiseases.FROSTBITE);
				}
				else
				{
					rpComponent.UnsetDisease(alpDiseases.FROSTBITE);
					m_FrostbiteTimers = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
					player.DecreaseDiseaseCount();
					alp_FrostBiteSickShowed = false;
				}
			}
		}
	}
};
#endif