modded class SyncPlayerList
{
	override void CreatePlayerList()
	{
		if (GetGame().IsServer())
		{
			m_PlayerList = new array<ref SyncPlayer>();
			
			array<PlayerIdentity> identities = new array<PlayerIdentity>();
			// CORREÇÃO: Nome correto da função vanilla
			GetGame().GetPlayerIdentities(identities);

			foreach (auto identity : identities)
			{
				if (!identity) continue; // Segurança contra identidades nulas

				SyncPlayer sync_player = new SyncPlayer();
				sync_player.m_Identity = identity;
				sync_player.m_UID = identity.GetPlainId();
				sync_player.m_PlayerName = identity.GetPlainName();
				
				// CORREÇÃO: GetSessionId() retorna o ID inteiro único da sessão
				sync_player.m_PlayerUniqueID = identity.GetSessionId();
				
				m_PlayerList.Insert(sync_player);
			}
		}
	}
}