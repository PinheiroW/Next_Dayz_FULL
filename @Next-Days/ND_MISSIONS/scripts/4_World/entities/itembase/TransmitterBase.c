/**
 * TransmitterBase.c
 * * MODDED ENTITY (TRANSMISSORES/RÁDIOS) - Módulo ND_MISSIONS
 * Adiciona controle de estado de funcionamento para integração com sistemas de missão e RP.
 */

modded class TransmitterBase 
{
	protected bool alp_Working;
	
	/**
	 * Identifica se este é um rádio de base (estático).
	 * @return bool false para transmissores portáteis.
	 */
	bool IsBaseRadio()
	{
		return false;
	}
	
	/**
	 * Chamado quando o rádio é ligado ou começa a consumir energia.
	 */
	override void OnWorkStart()
	{
		super.OnWorkStart();
		alp_Working = true;
	}
	
	/**
	 * Chamado quando o rádio é desligado ou a bateria acaba.
	 */
	override void OnWorkStop()
	{	
		super.OnWorkStop();
		alp_Working = false;
	}	
	
	/**
	 * Retorna se o rádio está ligado e funcional no momento.
	 */
	bool IsWorking()
	{
		return alp_Working;
	}

	/* BLOCO DE INTEGRAÇÃO RP (DESATIVADO NO ORIGINAL)
	   Mantido para futura implementação de vinculação de rádio ao jogador.
	   
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
		PlayerBase player;		
		if ( Class.CastTo( player, GetHierarchyRootPlayer()) )
		{ 				
			player.GetRP().SetWalkieTalkie( this );						
		}					
	}
	
	override void OnWork( float consumed_energy )
	{	
		super.OnWork( consumed_energy );
	
		if ( GetGame().IsClient() )
		{
			PlayerBase player;		
			if ( Class.CastTo( player, GetHierarchyRootPlayer()) )
			{ 				
				player.GetRP().SetWalkieTalkie( this );						
			}					
		}
	}		
	*/
};