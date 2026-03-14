class alpBBHIVE
{
	static string PATH = "$profile:Next-Days/DB/";  
	static string PATH_TOFILE = "$profile:Next-Days/DB/estates_";

	static int m_SaveRequestCounter;
	static bool m_WasInited;

	static protected ref map<string, ref alpEstateSetting> m_EstatesByID; 

	static protected void LoadHive()
	{		
		if (!FileExist(ALP_ROOTFOLDER)) MakeDirectory(ALP_ROOTFOLDER);
		if (!FileExist(PATH)) MakeDirectory(PATH);
		
		string path = PATH_TOFILE + "0.dat";		
		m_EstatesByID = new map<string, ref alpEstateSetting>;	
			
		if (FileExist(path)) 
		{
			FileSerializer file = new FileSerializer();
			
			if (file.Open(path, FileMode.READ))
			{
				bool end = false;
				int failsafe = 0; // Prevenção contra loop infinito em caso de corrupção
				
				while (!end && failsafe < 50000)
				{
					alpEstateSetting estate;	
					file.Read(estate);
					
					if (estate) 
					{
						string key = estate.ObjectID;
						m_EstatesByID.Set(key, estate);	
					} 
					else 
					{
						end = true;
					}
					failsafe++;
				}
				
				if (failsafe >= 50000)
				{
					Error("[ND_Clans] CRITICAL: LoadHive loop reached failsafe limit. Possible database corruption in: " + path);
				}
				
				file.Close();
			}
		}		
	}
	
	static protected void SaveHive()
	{
		if (m_SaveRequestCounter > 0) 
		{
			m_SaveRequestCounter = 0;
			string path_origo = PATH_TOFILE + "0.dat";				
			string path = PATH_TOFILE + "1.dat";	
			
			FileSerializer file = new FileSerializer();
			bool hasData = false;
			
			if (file.Open(path, FileMode.WRITE))
			{
				int count = m_EstatesByID.Count();
				for (int i = 0; i < count; i++)
				{
					alpEstateSetting element = m_EstatesByID.GetElement(i);
					if (element && element.OwnerID)
					{
						file.Write(element);
						hasData = true; // Garante que pelo menos 1 registro válido foi escrito
					} 
				}
				file.Close();
				
				// Otimização e Segurança: Só sobrescreve o arquivo principal se a escrita foi bem sucedida
				if (hasData)
				{
					CopyFile(path, path_origo);
				}
				else
				{
					Print("[ND_Clans] SaveHive warning: No valid estates to save, backup overwrite aborted to prevent data loss.");
				}
			}			
		}
	}
	
	static void RegisterEstate(string id, alpEstateSetting estate) 
	{		
		// Null check de segurança
		if (!m_EstatesByID) LoadHive();
		
		if (estate)
		{
			m_EstatesByID.Set(id, estate); 
		}
	}
	
	static alpEstateSetting Get(string id, string type) 
	{
		if (!m_EstatesByID)
		{
			LoadHive();
		}		
		
		alpEstateSetting estate;		
		if (!m_EstatesByID.Find(id, estate)) 
		{
			// CORREÇÃO: Removida a vírgula extra (trailing comma) que causava erro de compilação
			estate = new alpEstateSetting(id, type, 0);
			// NOTA: Certifique-se de chamar RegisterEstate() depois caso esse novo estate deva ser salvo!
		}
		
		return estate;
	}
		
	static void Save() 
	{
		if (!m_WasInited) 
		{
			m_WasInited = true;
			m_SaveRequestCounter++;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(alpBBHIVE.SaveHive, 60000, true);	
		} 
		else 
		{
			m_SaveRequestCounter++;		
		}
	}
}