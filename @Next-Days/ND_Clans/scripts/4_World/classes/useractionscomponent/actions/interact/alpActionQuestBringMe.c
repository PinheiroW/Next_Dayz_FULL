// Script File
modded class alpActionQuestBringMe: ActionInteractBase
{
	override void ReputationReward(PlayerBase player, float exp)
	{
		// 1. CORREÇÃO: Failsafe para evitar Crash no Servidor caso o Mod Core não carregue
		if ( !player || !GetND() || !GetND().GetClans() || !GetND().GetClans().GetOptions() )
		{
			super.ReputationReward(player, exp);
			return;
		}

		if ( GetND().GetClans().GetOptions().SplitQuestReward )
		{
			int clanID = player.GetClanID();
			
			// 2. CORREÇÃO: Null check rigoroso no RP do jogador principal
			if ( clanID > 0 && player.GetRP() && player.GetRP().GetClan() )
			{
				// 3. CORREÇÃO: Remoção do 'autoptr' depreciado
				array<PlayerBase> playersToReward = new array<PlayerBase>;
					
				// 4. CORREÇÃO DE PERFORMANCE: Fim do Server Lag. 
				// Buscamos apenas jogadores vivos, evitando scan de milhares de objetos do mapa.
				array<Man> allPlayers = new array<Man>;
				GetGame().GetPlayers(allPlayers);
				
				for (int i = 0; i < allPlayers.Count(); i++)
				{
					PlayerBase man = PlayerBase.Cast(allPlayers.Get(i));
					
					// 5. CORREÇÃO: Proteção de memória (NPE) na leitura do RP de aliados próximos
					if ( man && man != player && man.IsAlive() && man.GetRP() && man.GetRP().GetClan() && man.GetClanID() == clanID )
					{
						// Cálculo matemático direto de distância (Extremamente mais leve para a CPU)
						if ( vector.Distance(player.GetPosition(), man.GetPosition()) <= 20.0 )
						{
							playersToReward.Insert( man );
						}
					}
				}
				
				exp = Math.Round (exp / (playersToReward.Count() + 1) );
				
				foreach (PlayerBase mate : playersToReward)
				{
					// Dupla checagem antes de distribuir a recompensa
					if (mate && mate.GetRP())
					{
						mate.GetRP().ChangeReputation(exp);
					}
				}
			}
		}
		
		super.ReputationReward(player, exp);
	}
}