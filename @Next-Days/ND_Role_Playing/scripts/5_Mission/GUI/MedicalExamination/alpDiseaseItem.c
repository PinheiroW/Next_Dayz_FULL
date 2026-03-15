/**
 * @class   alpDiseaseItem
 * @brief   Representa um item individual (doença ou cabeçalho) na lista médica.
 * Auditado: Foco em performance de UI e limpeza de memória.
 */

enum alpDISEASEITEMTYPE
{
	HEADER,
	ITEM
}

class alpDiseaseItem
{
	protected WrapSpacerWidget alp_Parent;
	protected Widget alp_Root;
	protected Widget alp_Main;
	protected ImageWidget alp_Icon;	
	protected TextWidget alp_NameText;
	protected TextWidget alp_ExamineText;
	protected TextWidget alp_PriceText;
	protected ButtonWidget alp_Heal;
	protected Widget alp_HeaderPanel;

	protected float alp_Price;
	protected bool alp_State;
	protected bool alp_CanBeCured;
	
	void alpDiseaseItem(int type, string img, WrapSpacerWidget w, string name, bool state, float price, bool canBeCured = true)
	{
		alp_Parent = w;
		alp_CanBeCured = canBeCured;
		
		// Criação do layout
		alp_Root = GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/Disease.layout", w);
		if (!alp_Root) return;

		// Cache de Widgets para evitar buscas repetitivas no Update
		alp_Main = alp_Root.FindAnyWidget("Disease_panel");
		alp_Icon = ImageWidget.Cast(alp_Root.FindAnyWidget("Disease_icon"));
		alp_NameText = TextWidget.Cast(alp_Root.FindAnyWidget("Disease_text"));		
		alp_ExamineText = TextWidget.Cast(alp_Root.FindAnyWidget("Disease_examine"));
		alp_PriceText = TextWidget.Cast(alp_Root.FindAnyWidget("Disease_price"));
		alp_Heal = ButtonWidget.Cast(alp_Root.FindAnyWidget("ButtonPlus"));
		alp_HeaderPanel = alp_Root.FindAnyWidget("HeadTitlePanel");

		if (type == alpDISEASEITEMTYPE.ITEM)
		{
			if (alp_Icon) alp_Icon.LoadImageFile(0, img);
			if (alp_NameText) alp_NameText.SetText(name);
			
			SetPrice(price);
			SetState(state);			
		}
		else if (type == alpDISEASEITEMTYPE.HEADER)
		{
			if (alp_Icon) alp_Icon.Show(false);
			if (alp_NameText) alp_NameText.Show(false);
			if (alp_HeaderPanel) alp_HeaderPanel.Show(true);
		}
	}

	// Destruidor para garantir que o widget saia da memória quando o objeto for deletado
	void ~alpDiseaseItem()
	{
		if (alp_Root)
		{
			alp_Root.Unlink();
			delete alp_Root;
		}
	}

	Widget GetRoot() { return alp_Root; }	
	
	ButtonWidget GetButton() { return alp_Heal; }

	float GetFee() { return alp_Price; }

	void SetPrice(float value)
	{
		alp_Price = value;
		if (!alp_PriceText) return;

		if (alp_Price <= 0)
		{
			alp_PriceText.Show(false);
		}
		else
		{
			alp_PriceText.Show(true);
			alp_PriceText.SetText(alpUF.NumberToString(alp_Price, 1));
		}
	}

	void SetValue(float value)
	{
		SetPrice(value);
	}

	void SetState(bool state)
	{
		alp_State = state;
		if (!alp_ExamineText || !alp_Heal) return;

		if (alp_State)
		{
			alp_ExamineText.SetText("#ip_infected");
			alp_ExamineText.SetColor(0xFFFF0000); // Vermelho
			alp_Heal.Show(alp_CanBeCured);
		}
		else
		{
			alp_ExamineText.SetText("#ip_healthy");
			alp_ExamineText.SetColor(0xFF00FF00); // Verde
			alp_Heal.Show(false);
		}
	}
}