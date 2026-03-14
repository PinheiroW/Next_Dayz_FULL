class alpEstateSetting
{
	string	ObjectID;	// house id	
	string	ObjectName;	// house type/name	
	int 	OwnerID;	// owner
	int 	ClanID;		// owner clan
	int		KeyID;	 	// key
	int    	Setting;	// setting
	
	int 	RoomMates[32];
	int 	ClaimedBeds;
	int		ValidThru;
	int 	Permission;

	void alpEstateSetting(string houseid, string type, int ownerid)
	{
		ObjectID = houseid;
		ObjectName = type;
		OwnerID = ownerid;
	}
	
	bool ReleaseOldBed(int index, int playerID)
	{
		// 1. Prevenção contra Array Out of Bounds Crash
		if (index < 0 || index >= 32) return false;

		// 2. Otimização: Substituição de Math.Pow(float) por Bitwise Shift (int nativo)
		int b = 1 << index; 
		
		if (RoomMates[index] == playerID)
		{
			ClaimedBeds = ~b & ClaimedBeds;
			RoomMates[index] = 0;		
			return true;
		}
		
		return false;
	}	
	
	void Clear()
	{
		OwnerID = 0;
		ClanID = 0;
		KeyID = 0;
		Setting = 0;
		ClaimedBeds = 0;
		ValidThru = 0;		
		Permission = 0;	
		
		// 3. Correção: Limpeza profunda do array de inquilinos (Previne invasões ou bug de camas ocupadas)
		for (int i = 0; i < 32; i++)
		{
			RoomMates[i] = 0;
		}
	}
	
	void PrintValues()
	{
		Print("ObjectID " + ObjectID + " ObjectName " + ObjectName + " OwnerID " + OwnerID + " ClanID " + ClanID + " ClaimedBeds " + ClaimedBeds);
	}
}