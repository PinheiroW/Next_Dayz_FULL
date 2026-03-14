class alpDefaultItem
{
	int alp_Id;
	Widget alp_Root;
	int alp_Price;
	ButtonWidget alp_ActionBtn;

	void alpDefaultItem(int balance, int price, BuildingBase building)
	{
		// CORREÇÃO 1: Failsafe contra prédio nulo
		if (!building) return;

		alp_Id = building.GetWorldID();
		alp_Price = price;
		
		alp_Root = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/defaultItem.layout");	
		if (!alp_Root) return; // Failsafe se o layout falhar

		TextWidget nameWidget = TextWidget.Cast( alp_Root.FindAnyWidget("Estate") );
		if (nameWidget) nameWidget.SetText( building.GetDisplayName() );	
		
		TextWidget priceWidget = TextWidget.Cast( alp_Root.FindAnyWidget("Price") );
		if (priceWidget) priceWidget.SetText( alpUF.NumberToString(price, 1) );
		
		// CORREÇÃO 2: Localização segura do botão de ação
		alp_ActionBtn = ButtonWidget.Cast( alp_Root.FindAnyWidget("ActionButton") );
		
		if ( alp_ActionBtn )
		{
			if ( balance >= price )
			{		
				alp_ActionBtn.Show( true );	
				ImageWidget icon = ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") );
				if (icon)
				{
					icon.LoadImageFile(0, "ND_MISSIONS/gui/Images/Confirm.paa");
					icon.SetColor(COLOR_AVAILABLE_POSITIVE);
				}
			}
			else
			{
				alp_ActionBtn.Show( false ); // Esconde se não houver saldo
			}
		}
	}

	// CORREÇÃO 3: Destrutor para prevenir memory leak
	void ~alpDefaultItem()
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

	int GetPrice()
	{
		return alp_Price;
	}

	void SetSortedIcon()
	{
		if (alp_ActionBtn) alp_ActionBtn.Show( false );	
		
		Widget sortedIcon = alp_Root.FindAnyWidget("IconSorted");
		if (sortedIcon) sortedIcon.Show( true );	
	}
}