class alpSpreadRumoursMenu extends UIScriptedMenu
{
    const int alp_UPDATE = 1;
    float alp_Update;
    
    protected PlayerBase alp_Player;
    protected bool m_IsInitialized = false;

    Widget layoutRoot;
    Widget alp_WindowGossip;
    Widget alp_BodyWindowGossip;

    TextWidget alp_SaveGossipNegativeCost;
    TextWidget alp_SaveGossipNegativeGain;
    TextWidget alp_SaveGossipPositiveCost;
    TextWidget alp_SaveGossipPositiveGain;

    ButtonWidget alp_GossipNegativeBtn;
    ButtonWidget alp_GossipPositiveBtn;
    
    ref map<int, string> alp_CurrencyMapped;
    
    TextWidget alp_BalanceText;
    int alp_MyCash;
    ref alpSpreadRumoursFees alp_Fees;

    override Widget Init()
    {
        if (m_IsInitialized) return layoutRoot;

        Class.CastTo(alp_Player, GetGame().GetPlayer());
        
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/SpreadRumour.layout");
        
        alp_BodyWindowGossip = Widget.Cast(layoutRoot.FindAnyWidget("BodyWindowGossip"));
        alp_SaveGossipNegativeCost = TextWidget.Cast(layoutRoot.FindAnyWidget("TextWidgetNegativeCost"));
        alp_SaveGossipNegativeGain = TextWidget.Cast(layoutRoot.FindAnyWidget("TextWidgetNegativeGain"));
        alp_SaveGossipPositiveCost = TextWidget.Cast(layoutRoot.FindAnyWidget("TextWidgetPositiveCost"));
        alp_SaveGossipPositiveGain = TextWidget.Cast(layoutRoot.FindAnyWidget("TextWidgetPositiveGain"));
        
        alp_GossipNegativeBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidgetNegative"));
        alp_GossipPositiveBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidgetPositive"));
        
        alp_BalanceText = TextWidget.Cast(layoutRoot.FindAnyWidget("BalanceText"));
        
        // Inicialização de Moedas (Padrão Otimizado)
        alp_CurrencyMapped = new map<int, string>;
        auto currenciesConfig = alpBANK.GetCurencies();
        if (currenciesConfig)
        {
            map<int, ref alpCurrency> currencies = currenciesConfig.GetCurrencies();
            if (currencies)
            {
                for (int i = 0; i < currencies.Count(); i++)
                {
                    alp_CurrencyMapped.Set(i, currencies.GetElement(i).Name);
                }
            }
        }

        RefreshBalance();
        
        m_IsInitialized = true;
        return layoutRoot;
    }

    void ~alpSpreadRumoursMenu()
    {
        // Limpeza de memória para evitar Leaks
        if (alp_CurrencyMapped)
        {
            alp_CurrencyMapped.Clear();
            delete alp_CurrencyMapped;
        }

        if (GetND() && GetND().GetMS() && GetND().GetMS().GetTrader())
            GetND().GetMS().GetTrader().SetValidTraderData(false);
    }

    override void OnShow()
    {
        super.OnShow();
        SetFocus(layoutRoot);
        GetGame().GetInput().ChangeGameFocus(1);
        PPEffects.SetBlurMenu(GetND().GetMS().GetOptoinsTrader().NPC_Menu_blur);
        MissionGameplay.Cast(GetGame().GetMission()).PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetMission().GetHud().ShowHudUI(false);
    }

    override void OnHide()
    {
        super.OnHide();
        SetFocus(null);
        PPEffects.SetBlurMenu(0);
        GetGame().GetInput().ChangeGameFocus(-1);
        MissionGameplay.Cast(GetGame().GetMission()).PlayerControlEnable(true);
        GetGame().GetMission().GetHud().ShowHudUI(true);
    }

    void RefreshBalance()
    {
        if (!alp_Player) return;
        alp_MyCash = alp_Player.GetRP().GetCart().GetTotalBalance();
        
        int currencyID = alp_Player.GetRP().GetCart().GetCurrencyID();
        string currencyName = "Currency";
        if (alp_CurrencyMapped.Contains(currencyID))
            currencyName = alp_CurrencyMapped.Get(currencyID);

        alp_BalanceText.SetText(alpUF.NumberToString(alp_MyCash, 1) + " " + currencyName);
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);
        
        alp_Update += timeslice;
        if (alp_Update >= alp_UPDATE)
        {
            alp_Update = 0;
            if (GetND().GetMS().GetTrader().IsTraderSet())
            {
                RefreshBalance();
                UpdateGossipStat();
            }
        }
    }

    void UpdateGossipStat()
    {
        alp_Fees = GetND().GetMS().GetTrader().GetSpreadRumoursFees();
        if (!alp_Fees) return;

        int currencyID = alp_Player.GetRP().GetCart().GetCurrencyID();
        string curName = alp_CurrencyMapped.Get(currencyID);

        // Atualização Visual de Custos
        alp_SaveGossipNegativeCost.SetText("- " + alpUF.NumberToString(alp_Fees.NegativeGossipCost, 1) + " " + curName);
        alp_SaveGossipNegativeGain.SetText(alpUF.NumberToString(alp_Fees.NegativeGossipGain, 1));
        
        alp_SaveGossipPositiveCost.SetText("- " + alpUF.NumberToString(alp_Fees.PositiveGossipCost, 1) + " " + curName);
        alp_SaveGossipPositiveGain.SetText(alpUF.NumberToString(alp_Fees.PositiveGossipGain, 1));

        // Validação de Botões (Check de Saldo)
        alp_GossipNegativeBtn.Enable(alp_MyCash >= alp_Fees.NegativeGossipCost);
        alp_GossipPositiveBtn.Enable(alp_MyCash >= alp_Fees.PositiveGossipCost);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (super.OnClick(w, x, y, button)) return true;

        switch (w.GetUserID())
        {
            case 1: // Close Button
                Close();
                return true;
        }

        return OnClickALP(w);
    }

    bool OnClickALP(Widget w)
    {
        if (CheckGossip_Buttons(w)) return true;
        return false;
    }

    bool CheckGossip_Buttons(Widget w)
    {
        if (!alp_Fees) return false;

        if (w == alp_GossipNegativeBtn && alp_MyCash >= alp_Fees.NegativeGossipCost)
        {
            GetND().GetMS().GetTrader().SpreadRumoursRPC(alp_Fees.NegativeGossipGain, (int)alp_Fees.NegativeGossipCost, alp_Player);
            return true;
        }

        if (w == alp_GossipPositiveBtn && alp_MyCash >= alp_Fees.PositiveGossipCost)
        {
            GetND().GetMS().GetTrader().SpreadRumoursRPC(alp_Fees.PositiveGossipGain, (int)alp_Fees.PositiveGossipCost, alp_Player);
            return true;
        }

        return false;
    }
}