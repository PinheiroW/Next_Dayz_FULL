class alpMedicExaminationMenu extends UIScriptedMenu
{
    const int alp_HEADERID = -1;
    const int alp_UPDATE = 1;
    float alp_Update;
    
    protected PlayerBase alp_Player;
    protected bool m_IsInitialized = false;

    Widget layoutRoot;
    Widget alp_Window;
    Widget alp_WindowDNA;
    Widget alp_WindowMedic;

    WrapSpacerWidget alp_MedListContainer; 
    ref map<int, ref alpDiseaseItem> alp_Diseases = new map<int, ref alpDiseaseItem>;

    WrapSpacerWidget alp_StatsGroupHealtContainer;
    WrapSpacerWidget alp_StatsGroupAbility;
    WrapSpacerWidget alp_StatsGroupAbilityContainer; 
    
    Widget alp_StatsGroupReputation;
    WrapSpacerWidget alp_StatsGroupReputationContainer;  

    ref map<int, ref alpHealhtStat> alp_HealthStats = new map<int, ref alpHealhtStat>;
    ref array<ref alpDNAstatsPanelBase> alp_AbilityStats = new array<ref alpDNAstatsPanelBase>;
    
    TextWidget alp_BalanceText;
    int alp_MyCash;

    TextWidget alp_SaveDNAprice;
    TextWidget alp_LoadDNAprice;
    ButtonWidget alp_SaveDNAbtn;
    ButtonWidget alp_LoadDNAbtn;
    
    ref map<int, string> alp_CurrencyMapped;

    override Widget Init()
    {
        if (m_IsInitialized) return layoutRoot;

        Class.CastTo(alp_Player, GetGame().GetPlayer());

        // FIX de Contaminação ao abrir o menu
        bool hasContItem = alp_Player.GetRP().HasAnyContaminedItems();              
        alp_Player.GetRP().SetDecontaminationEvent(!hasContItem); 
                        
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/MedicExamination.layout");

        ImageWidget.Cast(layoutRoot.FindAnyWidget("BalanceIcon")).LoadImageFile(0, "ND_MISSIONS/gui/images/Cash.paa");     
        alp_BalanceText = TextWidget.Cast(layoutRoot.FindAnyWidget("BalanceText"));
        
        // Mapeamento de Moedas
        alp_CurrencyMapped = new map<int, string>;
        auto currenciesConfig = alpBANK.GetCurencies();
        if (currenciesConfig)
        {
            map<int, ref alpCurrency> currencies = currenciesConfig.GetCurrencies();  
            if (currencies)
            {
                for (int c = 0; c < currencies.Count(); c++)
                {
                    alpCurrency currency = currencies.GetElement(c);
                    alp_CurrencyMapped.Set(c, currency.Name);
                }           
            }   
        }
        
        alp_Window = Widget.Cast(layoutRoot.FindAnyWidget("BodyWindow"));
        
        RefreshBalance();

        // Inicialização Condicional do DNA
        if (GetND().GetRP().GetInteractions().MedicalFees.EnabledCloneDNA)
        {
            InitDNA();  
        }
        else
        {
            ButtonWidget.Cast(layoutRoot.FindAnyWidget("Menu2")).Show(false);
        }
        
        InitExamination();
        
        m_IsInitialized = true;
        return layoutRoot;
    }
    
    void ~alpMedicExaminationMenu()
    {
        if (alp_Player && alp_Player.GetSyncData())
            alp_Player.GetSyncData().RegisterToEnhancedStatsSync(false);

        if (GetND() && GetND().GetMS() && GetND().GetMS().GetTrader())
            GetND().GetMS().GetTrader().SetValidTraderData(false);
            
        if (alp_Player && alp_Player.GetRP())
            alp_Player.GetRP().SetDecontaminationEvent(false);

        // Limpeza de Memória (Anti-Leak)
        if (alp_Diseases) alp_Diseases.Clear();
        if (alp_HealthStats) alp_HealthStats.Clear();
        if (alp_AbilityStats) alp_AbilityStats.Clear();
        if (alp_CurrencyMapped) alp_CurrencyMapped.Clear();
    }   
    
    int GetCashBalance()
    {
        return alp_MyCash;
    }
    
    override void OnShow()
    {
        super.OnShow();
        SetFocus(layoutRoot);
        GetGame().GetInput().ChangeGameFocus(1);    
        PPEffects.SetBlurMenu(GetND().GetMS().GetOptoinsTrader().NPC_Menu_blur);
        MissionGameplay.Cast(GetGame().GetMission()).PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetMission().GetHud().ShowHudUI(false);
        GetGame().GetMission().GetHud().ShowQuickbarUI(false);    
    }   

    override void OnHide()
    {
        super.OnHide();
        SetFocus(null);
        PPEffects.SetBlurMenu(0);
        GetGame().GetInput().ChangeGameFocus(-1);
        MissionGameplay.Cast(GetGame().GetMission()).PlayerControlEnable(true);   
        GetGame().GetMission().GetHud().ShowHudUI(true);
        GetGame().GetMission().GetHud().ShowQuickbarUI(true); 
    }   

    void RefreshBalance()
    {   
        if (!alp_Player || !alp_BalanceText) return;

        alp_MyCash = alp_Player.GetRP().GetCart().GetTotalBalance();
        int currencyID = alp_Player.GetRP().GetCart().GetCurrencyID();
        
        string currencyName = "Currency";
        if (alp_CurrencyMapped && alp_CurrencyMapped.Contains(currencyID))
            currencyName = alp_CurrencyMapped.Get(currencyID);

        alp_BalanceText.SetText(alpUF.NumberToString(alp_MyCash, 1) + " " + currencyName);         
    }

    void InitDNA()
    {   
        alp_WindowDNA = Widget.Cast(layoutRoot.FindAnyWidget("BodyWindowDNA"));
        alp_StatsGroupAbility = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("BL_groupAbility"));
        alp_StatsGroupAbilityContainer = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("Bl_groupStatsContainer"));  
        
        alp_SaveDNAprice = TextWidget.Cast(layoutRoot.FindAnyWidget("TextWidgetSave"));
        alp_LoadDNAprice = TextWidget.Cast(layoutRoot.FindAnyWidget("TextWidgetRecovery"));
        alp_SaveDNAbtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidgetSave"));
        alp_LoadDNAbtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonWidgetRecovery"));    

        InitAbilityStats();
    }   
        
    void InitExamination()
    {   
        alp_WindowMedic = Widget.Cast(layoutRoot.FindAnyWidget("BodyWindowMedic"));
        alp_MedListContainer = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("Bl_groupMedListContainer"));
        alp_StatsGroupHealtContainer = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("Bl_groupHealthContainer"));
            
        InitHeathlStats();
        InitMedicList();    
    }       

    void InitMedicList()
    {   
        if (!alp_Player || !alp_Player.GetRP().alp_MedicList) return;
            
        for(int i = 0; i < alp_Player.GetRP().alp_MedicList.Count(); i++)
        {
            alpDisease dis = alp_Player.GetRP().alp_MedicList.GetElement(i);
            if (dis && dis.GetPrice() >= 0)
            {
                alpDiseaseItem disItem = alp_Diseases.Get(dis.GetID());
                if (!disItem)
                {
                    disItem = new alpDiseaseItem(alpDISEASEITEMTYPE.ITEM, dis.GetIcon(), alp_MedListContainer, dis.GetName(), dis.IsInfected(), dis.GetPrice(), dis.CanBeCured());
                    alp_Diseases.Insert(dis.GetID(), disItem);
                }

                bool shouldShow = (dis.IsInfected() && dis.IsEnable());
                disItem.GetRoot().Show(shouldShow);

                if (shouldShow)
                {
                    disItem.SetValue(dis.GetPrice());
                    bool canPay = (dis.GetPrice() <= GetCashBalance() && dis.CanBeCured());
                    disItem.GetButton().Show(canPay);
                }
            }
        }
    }
    
    override void Update(float timeslice)
    {
        super.Update(timeslice);    
        
        alp_Update += timeslice;
        
        if (GetND().GetMS().GetTrader().IsTraderSet())
        {
            if (!alp_Window.IsVisible()) alp_Window.Show(true);
            
            if (alp_Update >= alp_UPDATE)
            {
                alp_Update = 0;
                RefreshBalance();
                UpdateAbilityStat();
                InitMedicList(); // Atualiza estados de cura e preços                
            }
            UpdateHealhtStat();
        }
        else
        {
            if (alp_Window.IsVisible()) alp_Window.Show(false);
        }
    }

    float GetSaveDNAprice() { return GetND().GetMS().GetTrader().GetFees().SaveDNA; }
    float GetLoadDNAprice() { return GetND().GetMS().GetTrader().GetFees().RecoverDNA; }   

    void UpdateAbilityStat()
    {
        if (!alp_SaveDNAbtn || !alp_LoadDNAbtn) return;

        int currentBalance = GetCashBalance();
        alp_SaveDNAbtn.Enable(GetSaveDNAprice() <= currentBalance);
        alp_LoadDNAbtn.Enable(GetLoadDNAprice() <= currentBalance);             
        
        int currencyID = alp_Player.GetRP().GetCart().GetCurrencyID();
        string curName = alp_CurrencyMapped.Get(currencyID);

        alp_SaveDNAprice.SetText(alpUF.NumberToString(GetSaveDNAprice(), 1) + " " + curName);
        alp_LoadDNAprice.SetText(alpUF.NumberToString(GetLoadDNAprice(), 1) + " " + curName);       
        
        for (int i = 0; i < alp_AbilityStats.Count(); i++)
        {
            if (alp_AbilityStats.Get(i)) alp_AbilityStats.Get(i).Update();
        }       
    }       

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (super.OnClick(w, x, y, button)) return true;

        switch (w.GetUserID())
        {       
            case 1:
                Close();
                return true;
            case 11:
                alp_WindowDNA.Show(false);
                alp_WindowMedic.Show(true);
                return true;                
            case 12:
                alp_WindowDNA.Show(true);
                alp_WindowMedic.Show(false);
                return true;                                
        }
        return OnClickALP(w);
    }   
    
    bool OnClickALP(Widget w)
    {
        if (CheckME_Buttons(w)) return true;                
        if (CheckDNA_Buttons(w)) return true;        
        return false;
    }

    bool CheckME_Buttons(Widget w)
    {
        if (!alp_Diseases) return false;
        for (int i = 0; i < alp_Diseases.Count(); i++)
        {
            alpDiseaseItem itm = alp_Diseases.GetElement(i);
            if (itm && itm.GetButton() == w && GetCashBalance() >= itm.GetFee())
            {
                int disease = alp_Diseases.GetKey(i);
                if (disease == alpDiseases.DECONTAMINATION)
                {
                    alp_Player.GetRP().SetDecontaminationEvent(true);
                }
                GetND().GetMS().GetTrader().CureDiseaseRPC(disease, itm.GetFee(), alp_Player);
                return true;            
            }
        }
        return false;
    }

    bool CheckDNA_Buttons(Widget w)
    {   
        if (alp_SaveDNAbtn == w)
        {
            GetND().GetMS().GetTrader().SaveDNARPC(GetSaveDNAprice(), alp_Player);
            return true;
        }
        if (alp_LoadDNAbtn == w)
        {   
            GetND().GetMS().GetTrader().LoadDNARPC(GetLoadDNAprice(), alp_Player);
            return true;
        }                   
        return false;
    }

    void UpdateHealhtStat()
    {
        for (int i = 0; i < alp_HealthStats.Count(); i++)
        {
            int type = alp_HealthStats.GetKey(i);
            float value;
            if (alp_Player.GetSyncData().GetElementEnhanced(type).GetValue(value))
            {
                alp_HealthStats.GetElement(i).SetValue(value);          
            }               
        }
    }   
    
    void InitHeathlStats()
    {
        float value;
        auto sync = alp_Player.GetSyncData();
        
        sync.GetElementEnhanced(alpRPelementsEnahnced.TEMPERATURE).GetValue(value);
        alp_HealthStats.Set(alpRPelementsEnahnced.TEMPERATURE, new alpHealhtStat("set:dayz_gui image:iconTemperature0", alp_StatsGroupHealtContainer, value, true, " C"));        
        
        sync.GetElementEnhanced(alpRPelementsEnahnced.HEALTH).GetValue(value);
        alp_HealthStats.Set(alpRPelementsEnahnced.HEALTH, new alpHealhtStat("set:dayz_gui image:iconHealth0", alp_StatsGroupHealtContainer, value));
        
        sync.GetElementEnhanced(alpRPelementsEnahnced.BLOOD).GetValue(value);
        alp_HealthStats.Set(alpRPelementsEnahnced.BLOOD, new alpHealhtStat("set:dayz_gui image:iconBlood0", alp_StatsGroupHealtContainer, value));

        sync.GetElementEnhanced(alpRPelementsEnahnced.WATER).GetValue(value);
        alp_HealthStats.Set(alpRPelementsEnahnced.WATER, new alpHealhtStat("set:dayz_gui image:iconThirsty0", alp_StatsGroupHealtContainer, value));

        sync.GetElementEnhanced(alpRPelementsEnahnced.FOOD).GetValue(value);
        alp_HealthStats.Set(alpRPelementsEnahnced.FOOD, new alpHealhtStat("set:dayz_gui image:iconHungry0", alp_StatsGroupHealtContainer, value));      
        
        sync.GetElementEnhanced(alpRPelementsEnahnced.STOMACH).GetValue(value);
        alp_HealthStats.Set(alpRPelementsEnahnced.STOMACH, new alpHealhtStat("set:dayz_gui image:iconStomach2", alp_StatsGroupHealtContainer, value));  
        
        if (GetND().GetRP().GetPerksOptions().EnableFatigue)
        {
            sync.GetElementEnhanced(alpRPelementsEnahnced.FATIGUE).GetValue(value);        
            alp_HealthStats.Set(alpRPelementsEnahnced.FATIGUE, new alpHealhtStat("set:nd_dayz_gui image:iconTiredness0", alp_StatsGroupHealtContainer, value));                
        }       
    }   
        
    void InitAbilityStats()
    {
        StaminaSkills();
        SoftSkills();
        HuntingSkills();                
        RadiationResistanceSkills();
        ToxicResistanceSkills();
        FrostResistanceSkills();
        
        if (!GetND().GetRP().GetPerksOptions().ExcludeReputationFromCloning)
        {
            ReputationSkills(); 
        }       
    }
    
    private void ReputationSkills()
    {   
        if (GetND().GetRP().GetPerksOptions().EnablePerkReputation)
        {
            alpDNAstatsReputation skill = new alpDNAstatsReputation(alp_StatsGroupAbilityContainer, "ND_MISSIONS/gui/images/Reputation/r0.paa", "ND_MISSIONS/gui/images/Reputation/r0.paa", true);      
            alp_AbilityStats.Insert(skill);           
        }       
    }   
    
    private void HuntingSkills()
    {
        if (GetND().GetRP().GetPerksOptions().EnablePerkHunting)
        {
            alpDNAstatsHunting hunting = new alpDNAstatsHunting(alp_StatsGroupAbilityContainer, "ND_MISSIONS/gui/images/HuntingIcon.paa", "ND_MISSIONS/gui/images/HuntingIcon.paa");     
            alp_AbilityStats.Insert(hunting);
        }   
    }

    private void SoftSkills()
    {
        if (GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills)
        {
            alpDNAstatsDayzSoft specialtySoft = new alpDNAstatsDayzSoft(alp_StatsGroupAbilityContainer, "set:dayz_gui image:icon_needle", "set:dayz_gui image:icon_needle"); 
            alpDNAstatsDayzHard specialtyHard = new alpDNAstatsDayzHard(alp_StatsGroupAbilityContainer, "set:dayz_gui image:icon_hammer", "set:dayz_gui image:icon_hammer"); 
            alp_AbilityStats.Insert(specialtySoft);
            alp_AbilityStats.Insert(specialtyHard);
        }       
    }
    
    private void RadiationResistanceSkills()
    {   
        if (GetND().GetRP().GetPerksOptions().EnablePerkRadiationResistance)
        {
            alpDNAstatsRadiationResistance skill = new alpDNAstatsRadiationResistance(alp_StatsGroupAbilityContainer, "ND_MISSIONS/gui/images/RadiationShield.paa", "ND_MISSIONS/gui/images/RadiationShield.paa");       
            alp_AbilityStats.Insert(skill);           
        }       
    }

    private void ToxicResistanceSkills()
    {   
        if (GetND().GetRP().GetPerksOptions().EnablePerkToxicResistance)
        {
            alpDNAstatsToxicResistance skill = new alpDNAstatsToxicResistance(alp_StatsGroupAbilityContainer, "ND_MISSIONS/gui/images/ToxicShield.paa", "ND_MISSIONS/gui/images/ToxicShield.paa");       
            alp_AbilityStats.Insert(skill);           
        }       
    }   
    
    private void StaminaSkills()
    {   
        if (GetND().GetRP().GetPerksOptions().EnablePerkStamina)
        {
            alpDNAstatsStamina skill = new alpDNAstatsStamina(alp_StatsGroupAbilityContainer, "set:dayz_gui image:iconShock", "set:dayz_gui image:iconShock");       
            alp_AbilityStats.Insert(skill);           
        }       
    }

    void FrostResistanceSkills()
    {
#ifdef NAMALSK_SURVIVAL         
        alpDNAstatsColdResistance resitance = new alpDNAstatsColdResistance(alp_StatsGroupAbilityContainer, "set:nam_gui_icons image:coldresistfull2", "set:nam_gui_icons image:coldresistfull2");       
        alp_AbilityStats.Insert(resitance);       
#endif  
    }
}