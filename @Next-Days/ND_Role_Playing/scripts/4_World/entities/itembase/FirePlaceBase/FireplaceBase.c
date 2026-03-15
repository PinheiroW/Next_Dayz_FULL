/**
 * @class   FireplaceBase
 * @brief   Integração de Dinheiro e Banha como materiais de combustão no Next Days
 * Auditado em: 2026 - Foco em Performance e Lógica de Combustão
 */
modded class FireplaceBase extends ItemBase
{
	protected static int m_LardSlotId = -1;
	
	override void EEInit()
	{
		super.EEInit();

		// 1. Otimização de busca de Slot
		if (m_LardSlotId == -1)
			m_LardSlotId = InventorySlots.GetSlotIdFromString("LardALP");

		// 2. Registro de Dinheiro como Acendedor (Kindling)
		// Verificação de nulidade para evitar erros em lareiras internas (Indoor)
		if ( m_FireConsumableTypes )
		{
			RegisterMoneyAsKindling(alp_Money10);
			RegisterMoneyAsKindling(alp_Money20);
			RegisterMoneyAsKindling(alp_Money50);
			RegisterMoneyAsKindling(alp_Money100);
			RegisterMoneyAsKindling(alp_Money500);
			RegisterMoneyAsKindling(alp_Money1000);
		}
	}

	// Função auxiliar para evitar repetição de código
	protected void RegisterMoneyAsKindling(typename moneyType)
	{
		if (!m_FireConsumableTypes.Contains(moneyType))
		{
			m_FireConsumableTypes.Insert(moneyType, new FireConsumableType(moneyType, 5, true, "Paper"));
		}
	}

	override void CalculateCookingConditions()
	{
		super.CalculateCookingConditions();
		
		// 3. Integração da Banha na Temperatura
		// Se houver banha, o fogo queima mais quente e demora mais para perder calor
		if ( FindAttachmentBySlotName("LardALP") )
		{
			m_TemperatureMax = 1000; // Banha aumenta a temperatura máxima (Gordura queima forte)
			m_TemperatureLossThreshold = 0.5; 
		}
	}

	override int GetFuelCount()
	{
		int fuel_count = super.GetFuelCount();
		
		// 4. Correção Crítica: Se houver banha, ela deve contar como combustível
		// Isso impede que o fogo apague se houver apenas banha no slot customizado
		if ( FindAttachmentBySlotName("LardALP") )
		{
			fuel_count++;
		}
		
		return fuel_count;
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (!super.CanReleaseAttachment(attachment))
			return false;
		
		// Impede retirar a banha enquanto o fogo estiver aceso (Realismo: está derretendo/quente)
		if ( IsBurning() && attachment.GetInventory().GetSlotId(0) == m_LardSlotId )
		{
			return false;
		}
		
		return true;
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if (!super.CanReceiveAttachment(attachment, slotId))
			return false;

		// Impede colocar mais banha se já estiver queimando uma (Evita sobreposição visual)
		if ( IsBurning() && slotId == m_LardSlotId ) 
		{
			if ( FindAttachmentBySlotName("LardALP") )
				return false;
		}
		
		return true;
	}
};