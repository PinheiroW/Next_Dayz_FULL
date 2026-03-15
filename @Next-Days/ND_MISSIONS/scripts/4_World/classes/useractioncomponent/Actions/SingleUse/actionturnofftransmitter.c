/**
 * actionturnofftransmitter.c
 * * MODDED ACTIONS (LIGAR/DESLIGAR TRANSMISSOR) - Módulo ND_MISSIONS
 * Sincroniza o estado do rádio com os sistemas de missão do Next-Days.
 */

modded class ActionTurnOffTransmitter: ActionTurnOffWhileInHands
{
	override void OnExecuteServer(ActionData action_data)
	{
		// Executa a lógica nativa primeiro (desligar bateria/energia)
		super.OnExecuteServer(action_data);
		
		if (!action_data || !action_data.m_MainItem) return;
				
		PersonalRadio radio;
		if ( Class.CastTo( radio, action_data.m_MainItem ) )
		{
			// Notifica o sistema Next-Days que o rádio foi desligado voluntariamente
			radio.SetWorkingStateALP(false);	
		}
	}
}

modded class ActionTurnOnTransmitter : ActionTurnOnWhileInHands
{
	override void OnExecuteServer(ActionData action_data)
	{
		// Executa a lógica nativa primeiro (ligar bateria/energia)
		super.OnExecuteServer(action_data);
		
		if (!action_data || !action_data.m_MainItem) return;

		PersonalRadio radio;
		if ( Class.CastTo( radio, action_data.m_MainItem ) )
		{
			// Notifica o sistema Next-Days que o rádio está ativo para recepção de dados/missões
			radio.SetWorkingStateALP(true);	
		}
	}
}