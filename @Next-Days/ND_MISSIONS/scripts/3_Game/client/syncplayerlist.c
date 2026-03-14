modded class SyncPlayerList
{
	

	override void CreatePlayerList()
	{
		if (GetGame().IsServer())
		{
			m_PlayerList = new array<ref SyncPlayer>();
			
			array<PlayerIdentity> identities = new array<PlayerIdentity>();
			GetGame().GetPlayerIndentities(identities);

			foreach (auto identity : identities)
			{
				SyncPlayer sync_player = new SyncPlayer;
				sync_player.m_Identity = identity;
				sync_player.m_UID = identity.GetPlainId();
				sync_player.m_PlayerName = identity.GetPlainName();
				sync_player.m_PlayerUniqueID = identity.GetPlayerUniqueID();
				m_PlayerList.Insert(sync_player);
			}
		}
	}

}