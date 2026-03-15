/**
 * @class   alpRadiationSickMdfr (Stages 1-5)
 * @brief   Gerencia a exibição da doença de radiação no sistema RPG por estágios
 * Auditado em: 2024 - Foco em Segurança de Memória e Estabilidade de Modificadores
 */

// --- ESTÁGIO 1 ---
modded class alpRadiationSick1Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.RADIATION);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.RADIATION);
		}
	}
};

// --- ESTÁGIO 2 ---
modded class alpRadiationSick2Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.RADIATION);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.RADIATION);
		}
	}
};

// --- ESTÁGIO 3 ---
modded class alpRadiationSick3Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.RADIATION);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.RADIATION);
		}
	}
};

// --- ESTÁGIO 4 ---
modded class alpRadiationSick4Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.RADIATION);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.RADIATION);
		}
	}
};

// --- ESTÁGIO 5 ---
modded class alpRadiationSick5Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().SetDisease(alpDiseases.RADIATION);
		}
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		if (player && player.GetRP())
		{
			player.GetRP().UnsetDisease(alpDiseases.RADIATION);
		}
	}
};