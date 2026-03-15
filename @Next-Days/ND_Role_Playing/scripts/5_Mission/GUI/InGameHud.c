modded class IngameHud extends Hud
{
    // Constante para facilitar manutenção do caminho das texturas
    const string ALP_TIREDNESS_SET = "set:nd_dayz_gui image:iconTiredness";

    override void Init( Widget hud_panel_widget )
    { 
        super.Init(hud_panel_widget);

        // Verifica se o painel já existe para evitar duplicação em re-init
        Widget notPanel = hud_panel_widget.FindAnyWidget("NotifiersPanel");
        if (notPanel)
        {
            notPanel.Unlink(); // Remove o original do DayZ para aplicar o layout personalizado
            
            // Cria o novo layout de fadiga/notificadores do Next-Days
            Widget newNot = GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/fatigue.layout", hud_panel_widget);
            
            // Re-mapeia as referências básicas do HUD
            m_Notifiers = hud_panel_widget.FindAnyWidget("NotifiersPanel");      
            m_BloodType = TextWidget.Cast( hud_panel_widget.FindAnyWidget("BloodType") );
            m_BloodPosType = TextWidget.Cast( hud_panel_widget.FindAnyWidget("BloodPosType") );      
            
            m_HeatBufferPlus = ImageWidget.Cast( m_HudPanelWidget.FindAnyWidget( "HeatBuffer" ) );
            if ( m_HeatBufferPlus )
                m_HeatBufferPlus.Show( false );

            // Ajuste de posição do BadgeSpacer para acomodar o novo ícone
            float x1, y1;   
            Widget badgeSpacer = hud_panel_widget.FindAnyWidget("BadgesSpacer");
            if (badgeSpacer)
            {
                badgeSpacer.GetPos(x1, y1);
                x1 += 35; // Abre espaço para o ícone de fadiga
                badgeSpacer.SetPos(x1, y1);
            }
        }
    }

    override void InitBadgesAndNotifiers()
    {
        // Em vez de dar Clear() e quebrar outros mods, apenas adicionamos nossos estados
        super.InitBadgesAndNotifiers();

        // Adicionamos o identificador de fadiga ao mapa de widgets se ele não existir
        if ( !m_StatesWidgetNames.Contains(NTFKEY_ALPTIREDNESS) )
        {
            m_StatesWidgetNames.Set( NTFKEY_ALPTIREDNESS, "Tiredness" );
        }

        // Re-inicializa os widgets para garantir que o ícone de fadiga seja capturado
        for ( int i = 0; i < m_StatesWidgetNames.Count(); i++ )
        {
            int key = m_StatesWidgetNames.GetKey(i);
            string widget_name = m_StatesWidgetNames.GetElement(i);
            
            ImageWidget w = ImageWidget.Cast( m_Notifiers.FindAnyWidget( "Icon" + widget_name ) );
            
            if (w)
            {
                m_StatesWidgets.Set( key, w );
                w.Show( true );

                // Lógica específica para carregar os frames do ícone de fadiga
                if ( key == NTFKEY_ALPTIREDNESS )
                {
                    for ( int y = 0; y < 5; y++ )
                    {
                        w.LoadImageFile( y, ALP_TIREDNESS_SET + y.ToString() );
                    }
                }
            }
        }
    }
}