class alpClanData 
{
	int ClanID;
	string Name;
	ref array<int>					MembersOnline	= new array<int>; // GUID
	ref map<int,string>				Members 		= new map<int,string>; // GUID - Name	
	
	// CORREÇÃO 1: Adicionado 'ownerPlayerID' para gravar o jogador correto e não o ID numérico do clã
	void alpClanData(int clanID, string clanName, int ownerPlayerID, string playerName)
	{
		ClanID = clanID;
		Name = clanName;
		
		Members.Set(ownerPlayerID, playerName);
		MembersOnline.Insert(ownerPlayerID);
		
		if (GetGame().IsServer())
		{
			// CORREÇÃO 2: Proteção de IO - Garante que o diretório base existe
			if (!FileExist(ALP_CLANS_FOLDER))
			{
				MakeDirectory(ALP_CLANS_FOLDER);
			}

			string path = ALP_CLANS_FOLDER + ClanID.ToString() + ".json";
			
			if (FileExist(path)) 
			{
				DeleteFile(path);	
			}
			
			Save();			
		}
	}
	
	void SetMemberOnline(int id)
	{
		if (MembersOnline.Find(id) < 0)
		{
			MembersOnline.Insert(id);
		}
	}
	
	bool RemoveMemberOnline(int id)
	{
		MembersOnline.RemoveItem(id);
		
		if (MembersOnline.Count() > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}	
	
	bool IsMemberOnline(int playerID)
	{
		if (MembersOnline.Find(playerID) >= 0)
			return true;
			
		return false;
	}
	
	void RemoveMember(int playerID)
	{
		MembersOnline.RemoveItem(playerID);
		Members.Remove(playerID);
		
		Save();
	}
	
	void AddMember(int playerID, string name)
	{
		SetMemberOnline(playerID);
		Members.Set(playerID, name);
		
		Save();
	}
	
	bool IsMember(int playerID)
	{
		// CORREÇÃO 3: Substituição do .Find(k,v) pelo .Contains(k) (Custo computacional muito menor)
		if (Members && Members.Contains(playerID))
		{
			return true;
		}
		
		return false;
	}
		
	int GetCountOnline()
	{
		if (!MembersOnline) return 0; // Prevenção contra NPE
		
		return MembersOnline.Count();	
	}

	void Save()
	{
		// CORREÇÃO 2.1: Prevenção aplicada diretamente no Save
		if (!FileExist(ALP_CLANS_FOLDER))
		{
			MakeDirectory(ALP_CLANS_FOLDER);
		}
		
		string path = ALP_CLANS_FOLDER + ClanID.ToString() + ".json";
		JsonFileLoader<alpClanData>.JsonSaveFile(path, this);
	}	
	
	void Delete()
	{
		string path = ALP_CLANS_FOLDER + ClanID.ToString() + ".json";
		
		if (FileExist(path))
		{
			DeleteFile(path);
		}
	}
}