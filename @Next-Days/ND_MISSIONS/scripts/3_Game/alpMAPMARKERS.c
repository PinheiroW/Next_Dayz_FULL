/**
 * alpMAPMARKERS.c
 * * GERENCIADOR DE MARCADORES DE MAPA - Módulo ND_MISSIONS
 * Define ícones, bordas de territórios e marcadores de missões dinâmicas.
 */

enum alpRADIO
{
	NONE = 0,
	ALLOWED_BY_CONFIG_PERSONAL = 1,
	ALLOWED_BY_CONFIG_FIELD = 2,
	HAS_WALKIE_TALKIE = 4,
	HAS_BASE_RADIO = 8,
	HAS_GPS = 16,
	HAS_COMPASS = 32,	
}; // Adicionado ponto e vírgula

class alpQuestMarker
{
	float X;
	float Y;
	string Title;
	string MapTitle;
	int Count;
	
	void AddMarker(float x, float y, string maptitle, string title)
	{
		X = x;
		Y = y;
		MapTitle = maptitle;
		
		// CORREÇÃO: Garante inicialização da string para evitar "null" no início
		if (!Title) Title = "";
		
		Title += Widget.TranslateString(GetDisplayName(title)) + ", ";
	}
	
	string GetTitle() 
	{
		if (Title.Length() > 2)
		{
			return Widget.TranslateString("#trader_bring_me") + ": " + Title.Substring(0, Title.Length() - 2);
		}
		return Widget.TranslateString("#trader_bring_me");
	}
	
	static string GetDisplayName(string className)
	{
		string name;
		TStringArray cfg = {"CfgVehicles", "CfgWeapons", "CfgMagazines", "CfgAmmo"};
		foreach (string p : cfg)
		{
			GetGame().ConfigGetText(p + " " + className + " displayName", name);
			if (name != "")
			{
				className = name;
				break;
			}
		}
		className.Replace("$UNT$", "");
		return className;
	}
}; // Adicionado ponto e vírgula

class alpMapMarkers
{
	static void AddMarkerToMap(BasicMapMenu m, vector position, string title, int color, string icon)
	{
		if (!m) return; // Segurança contra Null Pointer
		m.AddUserMark(position, title, color, icon);
	}
	
	static void AddRadiusToMap(BasicMapMenu m, vector position, vector pointA, vector pointB, float len, int color)
	{
		if (!m) return; // CORREÇÃO: Verificação de segurança obrigatória
		
		int i;
		if (len > 0)
		{
			float angle = 360 / (len / 2);
			for (i = 0; i < (len / 2); i++)
			{
				float angle2 = i * angle;				
				vector pos = vector.Zero;				
				pos[0] = Math.NormalizeAngle(angle2);
				pos = pos.AnglesToVector();	
				pos[0] = pos[0] * len;
				pos[2] = pos[2] * len;
				m.AddUserMark((position + pos), "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			}			
		} 
		else 
		{
			float sideA = Math.AbsFloat(pointA[0] - pointB[0]);
			float sideB = Math.AbsFloat(pointA[2] - pointB[2]);	
		
			float pointsA = Math.Floor(sideA / 10);	
			float pointsB = Math.Floor(sideB / 10);	
			
			vector v;

			for (i = 0; i < pointsA; i++)
			{
				v = pointA;
				v[0] = pointA[0] - (i * 10);
				m.AddUserMark(v, "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");	
				v[2] = pointB[2]; 
				m.AddUserMark(v, "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			}
			
			v = pointA;
			v[0] = pointB[0]; 
			for (i = 0; i < pointsB; i++)
			{
				v[2] = pointA[2] - (i * 10);
				m.AddUserMark(v, "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
				v[0] = pointA[0];
				m.AddUserMark(v, "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			}
		}
	}
}; // Adicionado ponto e vírgula