/**
 * @class   alpInfoPlayerMenu
 * @brief   Extensão do Menu de Informações do Jogador (GUI)
 * Auditado: Foco em Hall of Fame, Reputação e Prevenção de Crashes por CallLater.
 */
modded class alpInfoPlayerMenu extends UIScriptedMenu
{
	protected Widget alp_WindowHoF;
	protected TextListboxWidget alp_HOFlist;
	
	protected ref alpReputationStat alp_ReputationExtraPanel;
	protected float alp_ScoreMax;

	override Widget Init()
	{
		Widget root = super.Init();
		if (!root) return null;
		
		// Inicialização do Hall of Fame
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetPerkReputation().EnableHallOfFame)
		{
			alp_WindowHoF = Widget.Cast(root.FindAnyWidget("BodyWindowHallOfFame")); 
			if (alp_WindowHoF) alp_WindowRegister.Insert(alp_WindowHoF);	
			
			ButtonWidget btnHoF = ButtonWidget.Cast(root.FindAnyWidgetById(14));
			if (btnHoF) btnHoF.Show(true);
			
			alp_HOFlist = TextListboxWidget.Cast(root.FindAnyWidget("HallOfFameList"));
			InitHOF();
		}	
		
		return root;
	}

	void ~alpInfoPlayerMenu()
	{
		// Limpeza segura do painel de reputação extra
		if (alp_ReputationExtraPanel)
		{
			delete alp_ReputationExtraPanel;
		}
		
		// Remove chamadas pendentes da fila para evitar acesso a ponteiro nulo
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).RemoveByName(this, "FillHintReputation");
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).RemoveByName(this, "FillReputationRecord");
	}

	void InitHOF()
	{
		if (!alp_HOFlist || !GetND().GetRP().GetHallOfFame()) return;

		alp_HOFlist.ClearItems();
		auto players = GetND().GetRP().GetHallOfFame().GetPlayers();
		
		if (players)
		{
			for (int i = 0; i < players.Count(); i++)
			{
				alpReputationPlayer p = players.Get(i);
				if (p)
				{
					int row = alp_HOFlist.AddItem(p.Name, null, 0);
					alp_HOFlist.SetItem(row, p.Score.ToString(), null, 1);
				}
			}
		}
	}

	override void InitReputation()
	{
		super.InitReputation();

		if (GetND().GetRP().GetPerksOptions().EnablePerkReputation)
		{
			float progres;
			auto syncProgres = alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.REPUTATIONPROGRES);
			if (syncProgres) syncProgres.GetValue(progres);

			auto syncRep = alp_Player.GetSyncData().GetElement(alpRPelements.REPUTATION);
			if (syncRep)
			{
				int levelExp = syncRep.GetValue();
				string icon = "ND_MISSIONS/gui/images/Reputation/r" + levelExp.ToString() + ".paa";
				float levelRate = 0;
				int levelCap = GetND().GetRP().GetPerkReputationLevelCup();
				
				if (levelCap > 0)
					levelRate = (Math.AbsFloat(levelExp) / levelCap) * 100;

				// Criação do painel de habilidade de reputação
				alpAbilityStat reputationPanel = new alpAbilityStat(icon, alp_StatsGroupReputationContainer, levelRate, progres, true);
				alp_ReputationStats.Set(alpRPelementsEnahnced.REPUTATIONPROGRES, reputationPanel);
				
				// Proteção: Remove chamadas antigas antes de agendar nova
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).RemoveByName(this, "FillHintReputation");
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintReputation", 500, false, new Param1<alpAbilityStat>(reputationPanel));
			}

			// Lógica de Score / Recorde Pessoal
			float score;			
			auto elemScore = alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.SCORE);
			if (elemScore)
			{
				elemScore.GetValue(score);
				alp_ScoreMax = alp_Player.GetPlayerHive().GetStore().BestScore;
				
				if (alp_ReputationExtraPanel) delete alp_ReputationExtraPanel;
				alp_ReputationExtraPanel = new alpReputationStat(alp_StatsGroupReputationContainer, score, alp_ScoreMax);
				
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).RemoveByName(this, "FillReputationRecord");
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillReputationRecord", 500, false, new Param1<alpReputationStat>(alp_ReputationExtraPanel));
			}
		}
	}

	// Handlers de preenchimento com verificações de segurança de estado
	void FillHintReputation(alpAbilityStat panel)
	{
		if (!panel || !this || !alp_Player || !alp_Player.GetSyncData()) return;
		
		auto elem = alp_Player.GetSyncData().GetElement(alpRPelements.REPUTATION);
		if (elem)
		{
			panel.AddHint(new TStringArray{"#ip_reputation"});
			panel.AddHint(new TStringArray{alpUF.NumberToString(elem.GetValue(), 0)});
		}
	}

	void FillReputationRecord(alpReputationStat panel)
	{
		if (!panel || !this) return;
		panel.SetLabels("#ip_score", "#ip_record");
	}
}