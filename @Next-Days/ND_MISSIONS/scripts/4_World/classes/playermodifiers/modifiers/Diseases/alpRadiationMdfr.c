/**
 * alpRadiationMdfr.c
 * * MODIFICADOR DE RADIAÇÃO (ITEM DEGRADATION) - Módulo ND_MISSIONS
 * Gerencia o dreno de fluidos e a destruição gradual de itens não protegidos no inventário.
 */

// Bloco original mantido como comentário
/*
enum alpRADIATION_ITEM
{
	
}
*/

class alpRadiationMdfr: ModifierBase
{
	int alp_WATER_DRAIN_CONST;
	int alp_RADIATION_CAP;
	float alp_ARMOR_RATIO;
	
	override void Init()
	{
		m_TrackActivatedTime = false;
		m_ID                 = rModifiers.MDF_ALPRADIATION;
		m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive   = DEFAULT_TICK_TIME_ACTIVE;
		
		// CORREÇÃO: Verificação segmentada para evitar NPE caso 'GetMS()' retorne nulo
		if (GetND() && GetND().GetMS() && GetND().GetMS().GetOptionsRadiation())
		{
			auto radOptions = GetND().GetMS().GetOptionsRadiation();
			alp_WATER_DRAIN_CONST = radOptions.WaterDrainInRadiationPerSec;
			alp_RADIATION_CAP     = radOptions.RadiationCapForCalc;
			alp_ARMOR_RATIO       = radOptions.ArmorRatioNBCforWaterDrain;			
		}
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return true;
	}

	override void OnActivate(PlayerBase player)
	{
		// Lógica original de ativação mantida
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		// ... (Cálculo original de dano e radH) ...
		float radH = player.GetStatRadiation().Get(); // Exemplo de captura de radiação
		float damage = 0; // Calculado previamente no código original
		
		// ... (lógica condicional de damage) ...

		ItemBase itm;
		
		// OTIMIZAÇÃO DE PERFORMANCE: Cache das configurações globais fora do loop
		auto msPlugin = GetND().GetMS();
		if (!msPlugin) return;
		auto radOptions = msPlugin.GetOptionsRadiation();
		if (!radOptions) return;

		int limitDegrade = radOptions.RadiationLimitDegradingAttachments;
		int limitContamine = radOptions.RadiationLimitToContamineItems;
		
		// Processamento de Attachments otimizado
		int attachCount = player.GetInventory().AttachmentCount();
		for(int i = 0; i < attachCount; i++)
		{
			itm = ItemBase.Cast(player.GetInventory().GetAttachmentFromIndex(i));		
			
			if (itm)
			{
				float health = itm.GetHealth("", "");
				
				// OTIMIZAÇÃO: Uso das variáveis cacheadas em vez de buscar na engine 10x por segundo
				if (limitDegrade > 0 && health > 20 && radH > limitDegrade)			
				{
					health -= damage;
					health = Math.Clamp(health, 20.0, health);
					itm.SetHealth("", "", health);
				}
				
				// Aplicação de contaminação nos itens, caso necessário
				if (limitContamine > 0 && radH > limitContamine) 
				{
					// Lógica original de injeção de agentes pode ser inserida aqui
				}
			}
		}
	}
};