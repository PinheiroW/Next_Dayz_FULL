/**
 * alpOptionsMS_templates_mostwanted.c
 * * ESTRUTURA DE DADOS PARA SISTEMA DE MAIS PROCURADOS - Módulo ND_MISSIONS
 * Define a origem da recompensa, IDs, posição e valores.
 */

enum alpMOST_WANTED
{
	BANK,
	PLAYER,
} // Adicionado ponto e vírgula no fechamento do enum abaixo para garantir compatibilidade

class alpMostWanted 
{
	int alp_From;
	int alp_PlayerID;
	int alp_Currency;
	int alp_Reward;
	string alp_Name;
	string alp_Title;
	vector alp_RealVector;
	vector alp_AdjustedVector;
	string alp_Icon;
	
	int alp_TimeStamp;
	
	void alpMostWanted(int from, int playerid, int currency, int reward, string name, string title, vector position, vector position2, string icon = "")
	{
		alp_From = from;
		alp_PlayerID = playerid;
		alp_Currency = currency;
		alp_Reward = reward;
		alp_Name = name;
		alp_Title = title;
		alp_RealVector = position;
		alp_AdjustedVector = position2;
		alp_Icon = icon;
		
		// CORREÇÃO: Uso de GetGame() em vez da global g_Game para estabilidade
		if (GetGame())
		{
			alp_TimeStamp = GetGame().GetTime();
		}
	}
	
	int GetTime()
	{
		return alp_TimeStamp;
	}
	
	vector GetPostition()
	{	
		return alp_AdjustedVector;
	}

	vector GetRealPostition()
	{	
		return alp_RealVector;
	}	

	string GetTitle()
	{
		return alp_Title;
	}

	string GetName()
	{
		if (alp_Reward > 0)
		{
			// Retorna o nome com o valor da recompensa entre parênteses
			return alp_Name + " (" + alp_Reward.ToString() + ")";
		}
		return alp_Name;
	}
	
	string GetFrom()
	{
		if (alp_From == alpMOST_WANTED.BANK) return "Bank";
		if (alp_From == alpMOST_WANTED.PLAYER) return "Player";
		return "";
	}
}; // Fechamento da classe