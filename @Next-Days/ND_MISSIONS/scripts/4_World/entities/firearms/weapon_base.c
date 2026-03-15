/**
 * weapon_base.c
 * * MODDED ENTITY (BASE DE ARMAS) - Módulo ND_MISSIONS
 * Integra o disparo de armas ao sistema de Reputação e Crimes (Echo System).
 */

modded class Weapon_Base extends Weapon
{
	/**
	 * Evento disparado sempre que a arma efetua um disparo.
	 */
	override void EEFired(int muzzleType, int mode, string ammoType)
	{	
		// Executa primeiro a lógica padrão do jogo (DayZ Vanilla)
		super.EEFired(muzzleType, mode, ammoType);
		
		// Lógica Next-Days: Monitoramento de Devedores e Sistema Echo
		if (GetGame().IsServer())
		{
			PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
			
			// Verifica se quem disparou é um jogador e se possui pendências bancárias
			if (player && player.GetRP() && player.GetRP().IsDebtor())
			{
				// Evita spam de registros se o sistema estiver em cooldown
				if (!player.GetRP().IsEchoCoolDown())
				{
					// Se o jogador estiver com esta arma em mãos (confirmação de posse)
					if (player.GetItemInHands() == this)
					{
						// Verifica acessórios (Supressores alteram a detecção do Echo)
						ItemBase suppressor = GetAttachedSuppressor();
					
						// Registra o disparo no sistema de procurados do banco
						player.GetRP().MakeEchoWatnedPerson(suppressor, alpMOST_WANTED.BANK);
					}
				}
			}
		}
	}
}