/**
 * dayzplayercfgbase.c
 * * ANIMATION CONFIG (IK) - Módulo ND_MISSIONS
 * Registra perfis de Inverse Kinematics para que os itens customizados 
 * sejam segurados corretamente pelas mãos do personagem.
 */

modded class ModItemRegisterCallbacks 
{
	/**
	 * Configura o comportamento de itens segurados com apenas uma mão.
	 */
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior) 
	{
		// Mantém o registro de todos os itens vanilla do jogo
		super.RegisterOneHanded(pType, pBehavior);
		
		// --- Registro de Cartões e Itens Planos ---
		pType.AddItemInHandsProfileIK("alp_Card", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		pType.AddItemInHandsProfileIK("alp_Debitcard", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		pType.AddItemInHandsProfileIK("alp_AccesCard_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		
		// --- Registro de Chaves (Carro e Casa) ---
		pType.AddItemInHandsProfileIK("alp_CarKey_Base", "dz/anims/workspaces/player/player_main/props/player_main_1h_keys.asi", pBehavior, "dz/anims/anm/player/ik/gear/handcuff_keys.anm");	
		pType.AddItemInHandsProfileIK("alp_HouseKey_Base", "dz/anims/workspaces/player/player_main/props/player_main_1h_keys.asi", pBehavior, "dz/anims/anm/player/ik/gear/handcuff_keys.anm");			
		
		// --- Registro de Dispositivos Eletrônicos ---
		pType.AddItemInHandsProfileIK("alp_geiger_counter", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/battery_charger.anm");
		
		// --- Registro de Moedas e Papel Moeda ---
		pType.AddItemInHandsProfileIK("alp_Coin", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/9v_battery.anm");
		pType.AddItemInHandsProfileIK("alp_Money", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
	}
}