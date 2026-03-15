/**
 * alpNDInfoTemplate.c
 * * INFO SYSTEM TEMPLATES - Módulo ND_MISSIONS
 * Define as classes de dados para o sistema de guias, tutoriais e informações multilingue.
 */

class alpISitem
{
	ref array<string>               Menu;
	ref array<ref array<string>>    Text;

	void alpISitem()
	{
		Menu = new array<string>;
		Text = new array<ref array<string>>;
	}
}

class alpInfoSitesTemplate
{
	int                             LanID  = 0;
	int                             MenuID = 0;
	
	ref array<string>               Language;
	ref array<string>               Button1;
	ref array<string>               Button2;
	ref array<string>               Button3;
	ref array<string>               Button4;
	ref array<string>               Button5;
	ref array<ref alpISitem>        Items;

	void alpInfoSitesTemplate()
	{
		Language = new array<string>;
		Button1  = new array<string>;
		Button2  = new array<string>;
		Button3  = new array<string>;
		Button4  = new array<string>;
		Button5  = new array<string>;
		Items    = new array<ref alpISitem>;
	}
}

class alpInfoSitesTemplateInput
{
	ref array<string>               Language;
	ref array<string>               Button1;
	ref array<string>               Button2;
	ref array<string>               Button3;
	ref array<string>               Button4;
	ref array<string>               Button5;
	ref array<ref alpISitem>        Items;

	void alpInfoSitesTemplateInput()
	{
		Language = new array<string>;
		Button1  = new array<string>;
		Button2  = new array<string>;
		Button3  = new array<string>;
		Button4  = new array<string>;
		Button5  = new array<string>;
		Items    = new array<ref alpISitem>;
	}
}