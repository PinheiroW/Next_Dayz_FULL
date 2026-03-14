class alpTaxesItem
{
	protected int alp_Price;
	protected int alp_Radius;
	protected int alp_Validity;
	protected Widget alp_Root;
	protected ButtonWidget alp_ActionBtn;
	
	void alpTaxesItem(int balance, int rank, int radius, int validity, int landTax, int estateTax = 0)
	{
		alp_Radius = radius;
		alp_Validity = validity;
		alp_Price = landTax + estateTax;
		
		// Criação do Widget
		alp_Root = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/TaxItem.layout");	
		if (!alp_Root) return; // Failsafe contra erro de layout

		// Configuração da Imagem de Tier/Reputação
		string iconReputation = "ND_MISSIONS/gui/images/Reputation/r" + rank.ToString() + ".paa";			
		ImageWidget tierImg = ImageWidget.Cast(alp_Root.FindAnyWidget("TierImage"));
		if (tierImg) tierImg.LoadImageFile(0, iconReputation);
		
		// Configuração do Botão de Ação
		alp_ActionBtn = ButtonWidget.Cast(alp_Root.FindAnyWidget("ActionButton"));
		ImageWidget actionIcon = ImageWidget.Cast(alp_Root.FindAnyWidget("ActionIcon"));
		
		if (alp_ActionBtn && actionIcon)
		{
			actionIcon.LoadImageFile(0, "ND_MISSIONS/gui/Images/Confirm.paa");
			actionIcon.SetColor(COLOR_AVAILABLE_POSITIVE);
		}
		
		// Preenchimento dos Dados na UI
		TextWidget radiusTxt = TextWidget.Cast(alp_Root.FindAnyWidget("Radius"));
		if (radiusTxt) radiusTxt.SetText(radius.ToString());
		
		TextWidget validityTxt = TextWidget.Cast(alp_Root.FindAnyWidget("Validity"));
		if (validityTxt) validityTxt.SetText(validity.ToString());
		
		TextWidget landTaxTxt = TextWidget.Cast(alp_Root.FindAnyWidget("LandTax"));
		if (landTaxTxt) landTaxTxt.SetText(alpUF.NumberToString(landTax, 1));
		
		TextWidget propTaxTxt = TextWidget.Cast(alp_Root.FindAnyWidget("PropertyTax"));
		if (propTaxTxt) propTaxTxt.SetText(alpUF.NumberToString(estateTax, 1));
		
		// CORREÇÃO 1: Verificação segura de Reputação e Saldo
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		int reputation = 0;
		
		if (player && player.GetSyncData())
		{
			auto syncElement = player.GetSyncData().GetElement(alpRPelements.REPUTATION);
			if (syncElement)
			{
				reputation = Math.AbsInt(syncElement.GetValue());
			}
		}
		
		// Exibe o botão apenas se cumprir os requisitos
		if (alp_ActionBtn && balance >= alp_Price && reputation >= rank)
		{
			alp_ActionBtn.Show(true);	
		}
		else if (alp_ActionBtn)
		{
			alp_ActionBtn.Show(false);
		}
	}

	// CORREÇÃO 2: Destrutor para prevenir vazamento de memória (Memory Leak)
	void ~alpTaxesItem()
	{
		if (alp_Root)
		{
			alp_Root.Unlink();
		}
	}

	Widget GetWidget()	
	{
		return alp_Root;
	}
	
	ButtonWidget GetActionBtn()	
	{
		return alp_ActionBtn;
	}	

	int GetPrice()
	{
		return alp_Price;
	}

	int GetRadius()
	{
		return alp_Radius;
	}	

	int GetValidity()
	{
		return alp_Validity;
	}		
}