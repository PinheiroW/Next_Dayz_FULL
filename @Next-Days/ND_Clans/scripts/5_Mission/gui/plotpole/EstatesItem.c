class alpEstatesItem
{
	int alp_Id;
	Widget alp_Root;
	int alp_PriceEstate;
	ButtonWidget alp_ActionBtn;

	void alpEstatesItem(int balance, int validity, BuildingBase building, float exchange)
	{
		// CORREÇÃO 1: Failsafe para evitar Crash de Cliente
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if (!player || !building || !GetND() || !GetND().GetClans()) return;
		
		auto baseSettings = GetND().GetClans().GetBases();
		if (!baseSettings) return;

		int pID = player.GetPlayerID();
		int pcID = player.GetClanID();
		
		alp_Id = building.GetWorldID();
		
		alp_Root = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/EstateItem.layout");	
		if (!alp_Root) return;

		TextWidget nameWidget = TextWidget.Cast( alp_Root.FindAnyWidget("Estate") );
		if (nameWidget) nameWidget.SetText( building.GetDisplayName() );	
		
		int olwOwner = 1;
		int boId = building.GetOwnerID();
		int bcId = building.GetClanID();
		
		// Lógica de multiplicador para compra de propriedade alheia
		if ( boId && ( boId != pID && bcId != pcID ) ) {
			olwOwner = 2;
		}
		
		float volume = building.GetVolumeALP();
		
		// CORREÇÃO 2: Cálculo seguro usando cache de configurações
		alp_PriceEstate = (volume * baseSettings.EstateValuePerCubicMeter + volume * baseSettings.BuildingTaxPerCubicMeterPerDay * validity) * exchange;
		alp_PriceEstate *= olwOwner;
		
		TextWidget priceWidget = TextWidget.Cast( alp_Root.FindAnyWidget("Price") );
		if (priceWidget) priceWidget.SetText( alpUF.NumberToString(alp_PriceEstate, 1) );
		
		int tax = volume * baseSettings.BuildingTaxPerCubicMeterPerDay * exchange;
		TextWidget taxWidget = TextWidget.Cast( alp_Root.FindAnyWidget("Tax") );
		if (taxWidget) taxWidget.SetText( alpUF.NumberToString(tax, 1) );
		
		int daysRemain = Math.Max(0, building.GetDaysRemain());
		TextWidget daysWidget = TextWidget.Cast( alp_Root.FindAnyWidget("DaysRemain") );
		if (daysWidget) daysWidget.SetText( alpUF.NumberToString(daysRemain, 1) );
		
		alp_ActionBtn = ButtonWidget.Cast( alp_Root.FindAnyWidget("ActionButton") );
		ImageWidget actionIcon = ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") );
		
		if (alp_ActionBtn && actionIcon)
		{
			actionIcon.LoadImageFile(0, "ND_MISSIONS/gui/Images/Confirm.paa");
			
			// Caso 1: Disponível para compra (Verde)
			if ( ( boId != pID && bcId != pcID ) && balance >= alp_PriceEstate )
			{		
				alp_ActionBtn.Show( true );	
				actionIcon.SetColor(COLOR_AVAILABLE_POSITIVE);
			}
			// Caso 2: Já pertence ao jogador ou clã (Vermelho - Venda/Ação)
			else if ( boId && ( boId == pID || bcId == pcID ) ) 
			{
				alp_ActionBtn.Show( true );	
				actionIcon.SetColor(COLOR_AVAILABLE_NEGATIVE);
			}
			else
			{
				alp_ActionBtn.Show( false );
			}
		}
	}

	// CORREÇÃO 3: Destrutor para prevenir vazamento de memória
	void ~alpEstatesItem()
	{
		if ( alp_Root )
		{
			alp_Root.Unlink();
		}
	}

	int GetWorldID()
	{
		return alp_Id;
	}
	
	Widget GetWidget()	
	{
		return alp_Root;
	}

	ButtonWidget GetActionBtn()	
	{
		return alp_ActionBtn;
	}
	
	int GetEstatePrice()
	{
		return alp_PriceEstate;
	}
}