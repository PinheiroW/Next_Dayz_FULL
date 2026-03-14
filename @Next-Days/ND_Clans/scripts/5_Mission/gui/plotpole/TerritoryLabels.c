class alpBuildingLabels
{
	static int LAST_COLOR;
	static float TerritoryRadius;
	static int COLOR_SELECTED = COLOR_GREEN;
	static int COLOR_DESELECTED = ARGB(255, 255, 255, 255);
	
	static ref array<Widget> alp_Labels;
	static ref map<int, Widget> alp_LabelsSelecet;
	static ref array<Widget> alp_Borders;
	static ref array<vector> alp_BordersVectors;
	static ref array<vector> alp_Vectors;

	static void AddItem(int id, string label, vector pos, bool bought = false)
	{
		Widget root = GetLabelPanel();
		if (!root) return;
		
		SetPosition(root, pos);
		SetLabel(root, id, label, bought);
		
		if (!alp_Labels)
		{
			alp_Labels = new array<Widget>;
			alp_Vectors = new array<vector>;
		}
		
		alp_Labels.Insert(root);
		alp_Vectors.Insert(pos);
	}
	
	static void ClearLabels()
	{
		if (alp_Labels)
		{
			foreach (Widget lbl : alp_Labels)
			{
				if (lbl) lbl.Unlink();
			}
			alp_Labels.Clear();			
			alp_Vectors.Clear();	
		}

		if (alp_LabelsSelecet)
		{
			alp_LabelsSelecet.Clear();
		}
		
		if (alp_Borders)
		{
			foreach (Widget bdr : alp_Borders)
			{
				if (bdr) bdr.Unlink();
			}
			alp_Borders.Clear();	
			alp_BordersVectors.Clear();						
		}		
		TerritoryRadius = 0;
	}
	
	static void ClearBorders()
	{
		if (alp_Borders)
		{
			foreach (Widget bdr : alp_Borders)
			{
				if (bdr) bdr.Unlink();
			}
			alp_Borders.Clear();						
		}	
		
		alp_Borders = new array<Widget>;		
		alp_BordersVectors = new array<vector>;
	}
	
	static Widget GetLabelPanel()
	{
		return GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/BuildingIcon.layout");
	}

	static Widget GetBorderSign()
	{
		return GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/TerritoryBorder.layout");
	}
	
	static void SetPosition(Widget w, vector pos)
	{
		if (!w) return;

		vector screen_pos = GetGame().GetScreenPos(pos);
		
		// CORREÇÃO: Verifica se o ponto está na frente da câmera (Z > 0)
		if (screen_pos[2] > 0)
		{
			w.Show(true);
			w.SetPos(screen_pos[0], screen_pos[1]);
		}
		else
		{
			w.Show(false);
		}
	}
	
	static void SetLabel(Widget w, int id, string label, bool bought)
	{
		if (!w) return;

		TextWidget text = TextWidget.Cast(w.FindAnyWidget("Label"));
		if (text) text.SetText(label);
		
		Widget selectedWidget = w.FindAnyWidget("Selected");
		if (selectedWidget)
		{
			if (bought)
				selectedWidget.SetColor(COLOR_AVAILABLE_POSITIVE);						
			else
				selectedWidget.SetColor(COLOR_UNAVAILABLE);	

			if (!alp_LabelsSelecet)
				alp_LabelsSelecet = new map<int, Widget>;
			
			alp_LabelsSelecet.Set(id, selectedWidget);		
		}
	}	
	
	static void SelectLabel(int id)
	{
		if (!alp_LabelsSelecet) return;

		Widget label = alp_LabelsSelecet.Get(id);
		if (label)
		{
			LAST_COLOR = label.GetColor();
			label.SetColor(COLOR_RED);		
		}
	}

	static void UnSelectLabel(int id)
	{
		if (!alp_LabelsSelecet) return;

		Widget label = alp_LabelsSelecet.Get(id);
		if (label)
		{
			label.SetColor(LAST_COLOR);		
		}
	}	
	
	static void Update()
	{
		if (alp_Labels)
		{
			for (int i = 0; i < alp_Labels.Count(); i++)
			{
				SetPosition(alp_Labels.Get(i), alp_Vectors.Get(i));
			}
		}

		if (alp_Borders)
		{
			for (int j = 0; j < alp_Borders.Count(); j++)
			{
				SetPosition(alp_Borders.Get(j), alp_BordersVectors.Get(j));
			}
		}			
	}
	
	static void SetBorders(float range)
	{
		TerritoryRadius = range;
		if (TerritoryRadius <= 0) return;
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());		
		if (!player || !player.alp_PlotPoleManage) return;

		vector ppPos = player.alp_PlotPoleManage.GetWorldPosition();
		ClearBorders();
		
		// Otimização: Define densidade de pontos baseada no raio
		int countPoints = Math.Max(12, TerritoryRadius * 2 * Math.PI / 5);
		float angleStep = 360.0 / countPoints;

		for (int i = 0; i < countPoints; i++)
		{			
			float currentAngle = i * angleStep;				
			vector posDir = "0 0 0";				
			posDir[0] = Math.NormalizeAngle(currentAngle);
			
			vector dir = posDir.AnglesToVector();	
			vector finalPos = ppPos;
			finalPos[0] = finalPos[0] + (dir[0] * TerritoryRadius);
			finalPos[2] = finalPos[2] + (dir[2] * TerritoryRadius);	
			
			Widget border = GetBorderSign();
			if (border)
			{
				alp_BordersVectors.Insert(finalPos);
				alp_Borders.Insert(border);
			}
		}		
	}
}