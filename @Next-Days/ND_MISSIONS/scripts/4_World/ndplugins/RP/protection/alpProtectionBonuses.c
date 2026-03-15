/**
 * alpProtectionBonuses.c
 * * ITEM PROTECTION CALCULATOR - Módulo ND_MISSIONS (RP)
 * Gerencia os bônus individuais de cada peça de equipamento e sua degradação.
 */

class alpProtectionBonuses 
{
	protected bool  alp_HasDosimeter;
	protected float alp_Biological;
	protected float alp_Chemical;
	protected float alp_Radiation;
	protected float alp_FilterEfficiency;
	
	protected float alp_HealtLevel;
	protected float alp_Quantity = 1;
	
	protected ItemBase alp_Item;
	
	// --- Inicialização ---

	void alpProtectionBonuses(ItemBase itm)
	{
		alp_Item = itm;
		
		// Tenta obter bônus customizados via Plugin de Missões (JSON)
		alpProtectionItem item = GetND().GetMS().GetProtectionBonuses( alp_Item.GetType() );
		
		if (!item)
		{
			// Fallback: Lê diretamente das configurações do arquivo .cpp do objeto
			string subclass_path = "CfgVehicles " + alp_Item.GetType() + " Protection ";		
			
			alp_HasDosimeter     = GetGame().ConfigGetInt(subclass_path + "hasdosimeter");
			alp_Radiation        = GetGame().ConfigGetFloat(subclass_path + "radiation");		
			alp_Chemical         = GetGame().ConfigGetFloat(subclass_path + "chemical");			
			alp_Biological       = GetGame().ConfigGetFloat(subclass_path + "biological");		
			alp_FilterEfficiency = GetGame().ConfigGetFloat(subclass_path + "filterefficiency");						
		}
		else
		{
			// Aplica valores vindos da configuração do servidor
			alp_HasDosimeter     = item.hasdosimeter;
			alp_Radiation        = item.radiation;
			alp_Chemical         = item.chemical;
			alp_Biological       = item.biological;
			alp_FilterEfficiency = item.filterefficiency;
		}

		UpdateState();		
	}
	
	// --- Getters ---

	ItemBase GetItem() { return alp_Item; }
	
	bool HasDosimeter() { return alp_HasDosimeter; }

	float GetFilterEfficiency() { return alp_FilterEfficiency; }	

	// --- Lógica de Estado e Proteção ---

	/**
	 * Atualiza a eficiência baseada na saúde do item e quantidade disponível.
	 */
	void UpdateState()
	{
		// Obtém multiplicador de eficiência baseado no estado (Pristine, Worn, Damaged, etc.)
		alp_HealtLevel = GetND().GetMS().GetNBCefficiency( alp_Item.GetHealthLevel() );
		
		// Se o item for um consumível (ex: Filtro) e estiver vazio, anula a proteção
		if ( alp_Item.HasQuantity() && alp_Item.GetQuantity() <= 0 )
		{
			alp_Quantity = 0;
		}
		else
		{
			alp_Quantity = 1;
		}
	}
	
	/**
	 * Retorna o valor de proteção real para o tipo solicitado.
	 * Cálculo: Valor Base * Multiplicador de Saúde * Multiplicador de Quantidade.
	 */
	float GetProtection(int type)
	{	
		UpdateState(); // Garante que o cálculo use o estado de saúde mais recente
				
		switch (type)
		{
			case alpPROTECTION.RADIATION:				
				return alp_Radiation * alp_HealtLevel * alp_Quantity;

			case alpPROTECTION.BIOLOGICAL:
				return alp_Biological * alp_HealtLevel * alp_Quantity;

			case alpPROTECTION.CHEMICAL:
				return alp_Chemical * alp_HealtLevel * alp_Quantity;
		}	
		return 0;
	}
}