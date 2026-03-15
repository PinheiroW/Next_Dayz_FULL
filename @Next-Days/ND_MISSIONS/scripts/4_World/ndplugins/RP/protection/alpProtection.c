/**
 * alpProtection.c
 * * PROTECTION SYSTEM - Módulo ND_MISSIONS (RP)
 * Calcula a resistência ambiental baseada no inventário e slots ativos.
 */

class alpProtection 
{
	protected PlayerBase alp_Player;
	protected ref map<int, ref alpProtectionBonuses> alp_WearingAttachment;
	protected ref map<string, int> alp_InventoryMap;
	protected int alp_HasDosimeter = 0;

	// Configuração de Slots baseada no mapa (Padrão vs Namalsk)
	#ifdef NAMALSK_SURVIVAL	
		static const int alp_InventorySlots[7] = {
			InventorySlots.GetSlotIdFromString("Headgear"),
			InventorySlots.GetSlotIdFromString("Mask"),
			InventorySlots.GetSlotIdFromString("Gloves"),
			InventorySlots.GetSlotIdFromString("Body"),
			InventorySlots.GetSlotIdFromString("Feet"),
			InventorySlots.GetSlotIdFromString("Legs"),
			InventorySlots.GetSlotIdFromString("LEHS")
		};
	#else
		static const int alp_InventorySlots[6] = {
			InventorySlots.GetSlotIdFromString("Headgear"),
			InventorySlots.GetSlotIdFromString("Mask"),
			InventorySlots.GetSlotIdFromString("Gloves"),
			InventorySlots.GetSlotIdFromString("Body"),
			InventorySlots.GetSlotIdFromString("Feet"),
			InventorySlots.GetSlotIdFromString("Legs")
		};	
	#endif		

	// --- Inicialização ---

	void alpProtection(PlayerBase player)
	{
		alp_Player = player;
		alp_WearingAttachment = new map<int, ref alpProtectionBonuses>;
		alp_InventoryMap = new map<string, int>;
		
		foreach(int loc : alp_InventorySlots)
		{
			alp_InventoryMap.Set(InventorySlots.GetSlotName(loc), loc);
		}		
	}
	
	bool HasDosimeter() { return (alp_HasDosimeter > 0); }
	
	// --- Gerenciamento de Itens ---

	void ItemAttached(EntityAI item, string slot_name)
	{
		int slot_id;
		if (alp_InventoryMap.Find(slot_name, slot_id))
		{
			ItemBase itm = ItemBase.Cast(alp_Player.GetInventory().FindAttachment(slot_id));
			if (itm)
			{
				alpProtectionBonuses protection = itm.GetProtectionBonuses();
				alp_WearingAttachment.Set(slot_id, protection);		
				
				if (protection.HasDosimeter()) alp_HasDosimeter++;
			}
		}
	}
	
	void ItemDetached(EntityAI item, string slot_name)
	{
		int slot_id;
		if (alp_InventoryMap.Find(slot_name, slot_id) && alp_WearingAttachment.Get(slot_id))
		{
			if (alp_WearingAttachment.Get(slot_id).HasDosimeter()) alp_HasDosimeter--;
			alp_WearingAttachment.Remove(slot_id);
		}	
	}	

	// --- Cálculos de Proteção ---

	/**
	 * Calcula a proteção para um tipo específico de ameaça em um slot determinado.
	 */
	float GetProtection(int type, int loc, bool noResistance = false)
	{
		float attProtection = 0;
		
		// Lógica Especial: Cabeça e Máscara (Proteção Somada)
		if (loc == InventorySlots.GetSlotIdFromString("Headgear") || loc == InventorySlots.GetSlotIdFromString("Mask"))
		{
			alpProtectionBonuses protHead = alp_WearingAttachment.Get(InventorySlots.GetSlotIdFromString("Headgear"));
			alpProtectionBonuses protMask = alp_WearingAttachment.Get(InventorySlots.GetSlotIdFromString("Mask"));
						
			float valHead = (protHead) ? protHead.GetProtection(type) : 0;
			float valMask = (protMask) ? protMask.GetProtection(type) : 0;
			
			attProtection = Math.Clamp((valHead + valMask), 0, 1);
		}
		else
		{
			// Verifica se a máscara/capacete provê proteção de corpo inteiro
			if (IsMaskFullBodyProtection())
			{
				attProtection = GetProtection(type, InventorySlots.GetSlotIdFromString("Headgear"));
			}
			else
			{
				alpProtectionBonuses protection = alp_WearingAttachment.Get(loc);
				#ifdef NAMALSK_SURVIVAL	
					if (!protection) protection = alp_WearingAttachment.Get(InventorySlots.GetSlotIdFromString("LEHS"));	
				#endif										
				
				if (protection) attProtection = protection.GetProtection(type);
			}
		}

		float naturalResist = (noResistance) ? 0 : GetNaturalResistance(type);
		return Math.Max(attProtection, naturalResist);
	}

	/**
	 * Calcula o escudo total de radiação usando médias ponderadas.
	 */
	float GetTotalRadiationShield()
	{
		float respiratory = (GetND().GetMS().GetOptionsRadiation().NotRequiredFilterForRadiation) ? 1.0 : GetProtectionRespiratory(alpPROTECTION.RADIATION);
		
		float head  = GetProtection(alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Headgear"));
		float body  = GetProtection(alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Body"));
		float hands = GetProtection(alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Gloves"));
		float legs  = GetProtection(alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Legs"));
		float feet  = GetProtection(alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Feet"));		
		
		float protection;
		if (IsMaskFullBodyProtection())
		{
			// Caso a máscara proteja tudo (ex: Traje NBC completo)
			protection = (GetND().GetMS().GetOptionsRadiation().NotRequiredFilterForRadiation) ? head : (respiratory * 0.3 + head * 0.7);
		}
		else
		{
			// Distribuição de pesos padrão (Pulmão 30%, Tronco 30%, Cabeça 20%, etc)
			if (GetND().GetMS().GetOptionsRadiation().NotRequiredFilterForRadiation)
				protection = head * 0.5 + body * 0.3 + hands * 0.05 + legs * 0.1 + feet * 0.05;
			else
				protection = respiratory * 0.3 + head * 0.2 + body * 0.3 + hands * 0.05 + legs * 0.1 + feet * 0.05;
		}
		
		return Math.Clamp(protection, 0, 1);
	}

	// --- Helpers ---

	bool IsMaskFullBodyProtection()
	{
		return GetND().GetMS().GetOptionsRadiation().HeadgearsDetermineBodyProtection;
	}

	float GetNaturalResistance(int type)
	{
		switch (type)
		{
			case alpPROTECTION.BIOLOGICAL: return 0; // Reservado para imunidade natural
			case alpPROTECTION.CHEMICAL:   return 0;
			case alpPROTECTION.RADIATION:  return 0;
		}		
		return 0;
	}
}