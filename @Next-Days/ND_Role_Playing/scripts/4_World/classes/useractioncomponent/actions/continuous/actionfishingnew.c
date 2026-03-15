/**
 * @class   ActionFishingNew
 * @brief   Modifica a pesca vanilla para incluir bônus de Perk de Caça e Reputação
 * Auditado em: 2024 - Foco em Balanceamento de Perks e Estabilidade de Chance
 */
modded class ActionFishingNew: ActionContinuousBase
{
	override int EvaluateFishingResult(ActionData action_data)
	{
		// Se a perk de caça estiver desativada, segue o vanilla
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{			
			return super.EvaluateFishingResult(action_data);
		}
		
		PlayerBase player = action_data.m_Player;
		if (!player) return 0;

		// 1. Obtém o nível de caça e o modificador correspondente
		int level = player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue(); 
		float huntingModifier = GetND().GetRP().GetPerkHuntingMdf( level );		

		// 2. Atalho para QuickFishing (Admin/Debug)
		if (player.IsQuickFishing()) return 1;
		
		FishingActionData fad = FishingActionData.Cast(action_data);
		float rnd = player.GetRandomGeneratorSyncManager().GetRandom01(RandomGeneratorSyncUsage.RGSGeneric);
		
		// 3. Cálculo de Modificador de Horário
		float daytime = GetGame().GetDayTime();
		float daytime_modifier = 0.5; // Base 50% de chance fora do horário
		
		// Horários nobres: Amanhecer e Entardecer
		if ( (daytime > 18 && daytime < 22) || (daytime > 5 && daytime < 9) )
		{
			daytime_modifier = 1.0;
		}
		
		// 4. Modificador de Isca/Anzol
		float hook_modifier = 1.0;
		if (fad.m_Bait && !fad.IsBaitEmptyHook())
		{
			hook_modifier = 1.5; // Iscas dão 50% mais chance
		}

		// 5. Cálculo Final da Chance (Chance Base * Horário * Isca * Perk de Caça)
		// Supondo chance base de 0.2 (20%)
		float chance = (0.2 * daytime_modifier * hook_modifier) * huntingModifier;
		
		// Garante que a chance não seja impossível nem garantida demais
		chance = Math.Clamp(chance, 0.01, 0.95);

		if (rnd < chance)
		{
			// Sucesso: Atribui reputação por pescar (Valor menor que matar animal grande)
			ApplyFishingReputation(player);
			return 1; // Fisgou algo!
		}
		
		return 0; // Nada desta vez
	}

	/**
	 * @brief Aplica reputação específica para pesca
	 */
	protected void ApplyFishingReputation(PlayerBase player)
	{
		if (player.GetRP())
		{
			string role = ALP_RP_BANDIT;
			if (player.GetRP().IsHero()) role = ALP_RP_HERO;
			
			// Usamos um valor menor (50% do bônus de caça comum) para não quebrar a economia
			float bonus = GetND().GetRP().GetReputationBonusKillAnimal( role ) * 0.5;
			player.GetRP().ChangeReputation( bonus );
		}
	}
};