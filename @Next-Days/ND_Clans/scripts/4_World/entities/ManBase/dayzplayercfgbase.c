//-----------------------------------------------------------------------------------------------
// DayZPlayerTypeCreate - Registro de IK Profiles para itens customizados
//-----------------------------------------------------------------------------------------------

modded class ModItemRegisterCallbacks 
{
	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior) 
	{
		// 1. OBRIGATÓRIO: Chama a execução das outras modded classes e do Vanilla
		super.RegisterTwoHanded(pType, pBehavior);
		
		// 2. CORREÇÃO: Programação Defensiva (Null Check)
		// Impede que o jogo sofra Crash caso os parâmetros venham nulos de outro mod corrompido
		if (pType && pBehavior)
		{
			// Registro do perfil de animação para o Kit do Plot Pole (Usa animação de Lança/Objeto longo)
			pType.AddItemInHandsProfileIK(
				"alp_PlotPoleKit", 
				"dz/anims/workspaces/player/player_main/player_main_2h.asi", 
				pBehavior,
				"dz/anims/anm/player/ik/two_handed/advanced_spear.anm"
			);
		}
	}	
}