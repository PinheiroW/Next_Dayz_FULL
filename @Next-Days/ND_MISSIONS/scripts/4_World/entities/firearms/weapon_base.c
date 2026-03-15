/**
 * weapon_base.c
 * * MODDED ENTITY (FIREARMS BASE) - Módulo ND_MISSIONS
 * Integra o uso de armamento ao sistema de Reputação, Dívidas e Rastreamento de Crimes.
 */

modded class Weapon_Base extends Weapon
{
	/**
	 * Handler de evento acionado em cada ciclo de disparo da arma.
	 */
	override void EEFired(int muzzleType, int mode, string ammoType)
	{	
		// Preserva a funcionalidade balística e sonora original do motor DayZ
		super.EEFired(muzzleType, mode, ammoType);
		
		// Lógica de monitoramento de crimes (Lado Servidor)
		if (GetGame().IsServer())
		{
			PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
			
			// Verifica se o atirador é um sobrevivente e se possui pendências no sistema financeiro
			if (player && player.GetRP() && player.GetRP().IsDebtor())
			{
				// Otimização: Só processa o alerta se o sistema Echo não estiver em tempo de espera (Cooldown)
				if (!player.GetRP().IsEchoCoolDown())
				{
					// Validação de segurança: Confirma que a arma disparada é a que está nas mãos do jogador
					if (player.GetItemInHands() == this)
					{
						// Identifica a presença de supressores para modular a detecção do crime
						ItemBase suppressor = GetAttachedSuppressor();
					
						// Reporta o disparo ao sistema de segurança bancário (Most Wanted System)
						player.GetRP().MakeEchoWatnedPerson(suppressor, alpMOST_WANTED.BANK);
					}
				}
			}
		}
	}
}