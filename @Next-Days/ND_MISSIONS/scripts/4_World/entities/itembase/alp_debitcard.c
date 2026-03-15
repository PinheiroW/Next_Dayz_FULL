/**
 * alp_debitcard.c
 * * ENTIDADE DE ITEM (CARTÃO DE DÉBITO) - Módulo ND_MISSIONS
 * Faz a ponte entre o item físico e a conta bancária no sistema ND_RP.
 */

class alp_Debitcard extends ItemBase
{
	protected int alp_BANK_GUID; // ID da conta bancária vinculada
	protected int alp_CARD_ID;   // Número único do cartão
	protected int alp_CARD_PIN;  // Código de segurança

	void alp_Debitcard()
	{	
		// Sincroniza dados essenciais para a interface do ATM
		RegisterNetSyncVariableInt("alp_CARD_PIN");		
		RegisterNetSyncVariableInt("alp_CARD_ID");	
	}	

	/**
	 * Vincula o cartão a uma conta bancária específica.
	 */
	void SetBankID(int id)
	{
		alp_CARD_PIN = 1234; // PIN inicial padrão
		alp_BANK_GUID = id;
		SetSynchDirty();
	}

	int GetBankID()
	{
		return alp_BANK_GUID;
	}	

	/**
	 * Gera ou retorna o ID único do cartão.
	 */
	int GetCardID()
	{
		if (!alp_CARD_ID)
		{
			alp_CARD_ID = Math.RandomInt(1, int.MAX - 1);
		}
		return alp_CARD_ID;
	}

	int GetCardPIN()
	{
		return alp_CARD_PIN;
	}

	void SetCardPIN(int pin)
	{
		alp_CARD_PIN = pin;
		SetSynchDirty();
	}	

	// --- PERSISTÊNCIA ---

	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		super.OnStoreSave(ctx);
		ctx.Write(alp_CARD_ID);
		ctx.Write(alp_BANK_GUID);
		ctx.Write(alp_CARD_PIN);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(alp_CARD_ID))
			return false;

		if (!ctx.Read(alp_BANK_GUID))
			return false;

		if (!ctx.Read(alp_CARD_PIN))
			return false;

		return true;
	}

	/**
	 * Exibe informações básicas do cartão no inventário.
	 */
	override string GetTooltip()
	{
		string tooltip = super.GetTooltip();
		tooltip += "\nCard ID: " + GetCardID().ToString();
		return tooltip;
	}
}