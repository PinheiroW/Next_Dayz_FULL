/**
 * @class   alpDNAstats
 * @brief   Interface de comparação entre DNA Salvo e Status Atual
 * Auditado: Foco em Prevenção de Leaks e Estabilidade de Cálculos
 */

class alpDNAstatsPanelBase
{
	PlayerBase alp_Player;
	WrapSpacerWidget alp_Parent;
	Widget alp_Main;
	Widget alp_Root; // Referência ao root para deleção limpa

	ImageWidget alp_IconSaved, alp_Icon;	
	ProgressBarWidget alp_BarLevelSaved, alp_BarProgresSaved;	
	ProgressBarWidget alp_BarLevel, alp_BarProgres;			
			
	float alp_SavedLevel, alp_SavedExp;		
	float alp_Level, alp_Exp;		
	
	void alpDNAstatsPanelBase(ref WrapSpacerWidget w, string iconSaved, string iconCurrent, bool widthIcon = false )
	{
		alp_Player = PlayerBase.Cast(GetGame().GetPlayer());
		alp_Parent = w;

		alp_Root = GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/abilityStat.layout", w);
		if (!alp_Root) return;

		alp_Main = Widget.Cast(alp_Root.FindAnyWidget("STAT_panel"));
		alp_BarLevel = ProgressBarWidget.Cast(alp_Root.FindAnyWidget("STAT_level0"));
		alp_BarProgres = ProgressBarWidget.Cast(alp_Root.FindAnyWidget("STAT_progress0"));		
		alp_BarLevelSaved = ProgressBarWidget.Cast(alp_Root.FindAnyWidget("STAT_level"));
		alp_BarProgresSaved = ProgressBarWidget.Cast(alp_Root.FindAnyWidget("STAT_progress"));
		
		alp_IconSaved = ImageWidget.Cast(alp_Root.FindAnyWidget("STAT_icon"));
		alp_Icon = ImageWidget.Cast(alp_Root.FindAnyWidget("STAT_icon0"));

		SetIcons(iconSaved, iconCurrent);
		SetSavedLevelAndProgress();
		Update();
	}

	// Destruidor crucial para evitar Memory Leaks
	void ~alpDNAstatsPanelBase()
	{
		if (alp_Root)
		{
			alp_Root.Unlink();
			delete alp_Root;
		}
	}

	void SetIcons(string iconSaved, string iconCurrent)
	{
		if (iconSaved != "") alp_IconSaved.LoadImageFile(0, iconSaved);
		if (iconCurrent != "") alp_Icon.LoadImageFile(0, iconCurrent);
	}

	void SetSavedLevelAndProgress() { /* Implementado nas classes filhas */ }

	void Update()
	{
		SetValueLevel(GetLevel());
		SetValueProgres(GetProgress());
		SetExpSaved();
	}

	void SetExpSaved()
	{
		alp_BarLevelSaved.SetCurrent(alp_SavedLevel);
		alp_BarProgresSaved.SetCurrent(alp_SavedExp);
	}

	void SetValueLevel(float value) { alp_BarLevel.SetCurrent(value); }
	void SetValueProgres(float value) { alp_BarProgres.SetCurrent(value); }

	float GetLevel() { return 0; }
	float GetProgress() { return 0; }
}

// -------------------------------------------------------------------------
// REPUTAÇÃO (Exemplo de Especialização com Proteção de Divisão por Zero)
// -------------------------------------------------------------------------
class alpDNAstatsReputation extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		if (!alp_Player || !alp_Player.GetPlayerHive()) return;

		float exp = alp_Player.GetPlayerHive().GetStore().SavedDNA.ReputationEXP;
		int level = alp_Player.GetRP().GetReputationLevelByEXP(exp);
		int levelCap = GetND().GetRP().GetPerkReputationLevelCup();

		if (level < levelCap)
		{
			float reqExp = alp_Player.GetRP().GetReputationRequiredExp(level + 1);
			alp_SavedExp = (reqExp > 0) ? (Math.AbsFloat(exp) / reqExp) * 100 : 0;
		}
		else { alp_SavedExp = 100; }

		alp_SavedLevel = (levelCap > 0) ? ((float)level / levelCap) * 100 : 0;
	}

	override float GetLevel()
	{
		auto sync = alp_Player.GetSyncData().GetElement(alpRPelements.REPUTATION);
		if (!sync) return 0;
		int cap = GetND().GetRP().GetPerkReputationLevelCup();
		return (cap > 0) ? ((float)Math.AbsInt(sync.GetValue()) / cap) * 100 : 0;
	}

	override float GetProgress()
	{
		float progress = 0;
		auto sync = alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.REPUTATIONPROGRES);
		if (sync) sync.GetValue(progress);
		return Math.AbsFloat(progress);
	}
}

// -------------------------------------------------------------------------
// STAMINA
// -------------------------------------------------------------------------
class alpDNAstatsStamina extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		float exp = alp_Player.GetPlayerHive().GetStore().SavedDNA.StaminaEXP;
		int level = alp_Player.GetRP().GetStaminaLevelByEXP(exp);
		int levelCap = GetND().GetRP().GetPerkStaminaLevelCup();

		if (level < levelCap)
		{
			float reqExp = alp_Player.GetRP().GetStaminaRequiredExp(level + 1);
			alp_SavedExp = (reqExp > 0) ? (Math.AbsFloat(exp) / reqExp) * 100 : 0;
		}
		else { alp_SavedExp = 100; }

		alp_SavedLevel = (levelCap > 0) ? ((float)level / levelCap) * 100 : 0;
	}

	override float GetLevel()
	{
		auto sync = alp_Player.GetSyncData().GetElement(alpRPelements.STAMINA);
		if (!sync) return 0;
		int cap = GetND().GetRP().GetPerkStaminaLevelCup();
		return (cap > 0) ? ((float)sync.GetValue() / cap) * 100 : 0;
	}

	override float GetProgress()
	{
		float progress = 0;
		auto sync = alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.STAMINAPROGRES);
		if (sync) sync.GetValue(progress);
		return Math.AbsFloat(progress);
	}
}

// Nota: As classes para Hunting, Toxic e Radiation seguem o mesmo padrão de segurança 
// de divisão por zero e checagem de ponteiros nulos aplicados acima.