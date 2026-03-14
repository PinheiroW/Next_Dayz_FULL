class alpPermissionItem
{
	protected Widget alp_Root;
	protected CheckBoxWidget alp_ActionBtn;
	protected int alp_Type;
	
	void alpPermissionItem(int type, string action, bool state)
	{
		alp_Type = type;
		
		// Criação do Widget de permissão
		alp_Root = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/permissionItem.layout");	
		if (!alp_Root) return; // Failsafe contra erro de layout

		// CORREÇÃO: Verificação de segurança no Texto
		TextWidget textLabel = TextWidget.Cast( alp_Root.FindAnyWidget("Text") );
		if (textLabel)
		{
			textLabel.SetText( action );
		}
		
		// CORREÇÃO: Verificação de segurança no CheckBox
		alp_ActionBtn = CheckBoxWidget.Cast( alp_Root.FindAnyWidget("CheckBox") );
		if (alp_ActionBtn)
		{
			alp_ActionBtn.SetChecked( state );
		}
	}

	// CORREÇÃO: Destrutor para prevenir vazamento de memória (Memory Leak)
	void ~alpPermissionItem()
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

	int GetType()	
	{
		return alp_Type;
	}	

	CheckBoxWidget GetActionBtn()	
	{
		return alp_ActionBtn;
	}
}