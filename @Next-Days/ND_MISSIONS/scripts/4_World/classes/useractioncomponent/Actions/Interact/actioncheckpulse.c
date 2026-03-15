/**
 * actioncheckpulse.c
 * * AÇÃO DE INTERAÇÃO (VERIFICAR PULSO) - Módulo ND_MISSIONS
 * Permite checar os sinais vitais de outro jogador.
 */

modded class ActionCheckPulse: ActionInteractBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// SEGURANÇA: Valida primeiro a condição base do motor do jogo
		if ( !super.ActionCondition(player, target, item) )
			return false;

		// OTIMIZAÇÃO: Tenta o cast para PlayerBase apenas se o alvo existir
		PlayerBase ntarget = PlayerBase.Cast( target.GetObject() );
		
		if ( ntarget && ntarget.IsAlive() )
		{
			// Garante que o alvo é um jogador humano e não o próprio executor
			if ( ntarget.IsPlayer() && ntarget != player )
			{
				return true;
			}
		}

		return false;
	}
};