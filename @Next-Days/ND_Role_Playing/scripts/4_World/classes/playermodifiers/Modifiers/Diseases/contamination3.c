/**
 * @class   ContaminationStage3Mdfr
 * @brief   Sincroniza o estágio terminal de contaminação química com o sistema RPG
 * Auditado em: 2024 - Foco em Segurança de Memória e Correção de Lógica de Proteção
 */
modded class ContaminationStage3Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);

		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.POISONING_CHEMICAL_3);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.POISONING_CHEMICAL_3);
		}
	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		// 1. Verificações de segurança iniciais
		if (!player || !player.GetRP() || !player.GetRP().GetProtection())
			return;

		// 2. Obtenção da resistência (0.0 a 1.0)
		float protection = player.GetRP().GetProtection().GetNaturalResistanceAgainstChemical();
		
		// 3. Otimização do SymptomManager
		SymptomBase primarySymptom = player.GetSymptomManager().GetCurrentPrimaryActiveSymptom();
		bool isVomiting = (primarySymptom && primarySymptom.GetType() == SymptomIDs.SYMPTOM_VOMIT);

		// 4. Lógica de dano de choque baseada no tempo e resistência
		// Removido o 'if(protection)' para que proteção 0.0 também processe o dano
		if (GetAttachedTime() > 4 && !isVomiting)
		{
			// Se o player não tiver proteção 100% (1.0), há chance de choque
			if (Math.RandomFloat01() > protection)
			{
				// Quanto menor a proteção, maior o dano de choque
				float shockDamage = -100 * (1.0 - protection);
				player.AddHealth("", "Shock", shockDamage);
			}
			
			SetAttachedTime(0); // Reseta o timer interno do modificador
		}
		
		// 5. Verificação de inconsciência (mecanismo de segurança/morte progressiva)
		if (player.IsUnconscious())
		{
			// Lógica adicional para jogadores desmaiados no gás pode ser inserida aqui
		}
	}
};