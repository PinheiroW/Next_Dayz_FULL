class alpAuthorize
{
	PlayerBase m_Player;
	
	void alpAuthorize(PlayerBase player)
	{
		m_Player = player;
	}
	
	bool IsAuthorized(ItemBase item)
	{
		// CORREÇÃO 1: Failsafe para evitar Crash de Memória
		if (!m_Player) return false;

		// CORREÇÃO 2: Verificação de Segurança no Servidor. 
		// O Servidor agora deve validar a posição REAL em vez de retornar true cegamente.
		// Nota: Se for uma criação administrativa via script, o admin contorna via parâmetros da ação.
		
		// Verificação de SafeZone de Trader
		if (m_Player.GetSyncData())
		{
			auto syncElement = m_Player.GetSyncData().GetElement(alpRPelements.ISINTRADERZONE);
			if (syncElement && syncElement.GetValue()) return false;
		}

		bool ispp = false;
		if ( item && (item.IsKindOf("alp_PlotPoleKit") || item.IsKindOf("alp_PlotPole")) )
		{			
			ispp = true;			
		}

		float dist;
		int pID = m_Player.GetPlayerID();
		int cID = m_Player.GetClanID();
		int r;

		// CORREÇÃO 3: Proteção contra Null no ClientData
		if (ClientData.PlotPoleList)
		{
			foreach (EntityAI ent : ClientData.PlotPoleList)
			{
				alp_PlotPole pp = alp_PlotPole.Cast(ent);
				
				if (pp && pp.alp_Radius)
				{				
					if (!pp.IsAuthorized(pID, cID) || (ispp && pp != item))
					{
						// CORREÇÃO 4: Uso de função nativa vector.Distance (Mais rápida)
						dist = vector.Distance(pp.GetPosition(), m_Player.GetPosition());
						
						if (ispp)
							r = pp.GetMaxRadius() * 2;
						else 	
							r = pp.GetRadius();
								
						if (dist <= r) return false;
					}					
				}
			}
		}
		
		// CORREÇÃO 5: Blindagem de acesso ao Core Plugin
		if (!GetND() || !GetND().GetClans() || !GetND().GetClans().GetBases()) return true;
		
		auto baseSettings = GetND().GetClans().GetBases();

		if (baseSettings.DisablePlacingObjectOutsideClaimedArea)
		{
			if (m_Player.GetRP() && m_Player.GetRP().IsHome())
				return true;

			// Checking Restricted Areas
			if (baseSettings.EnableRestrictedArea && baseSettings.RestrictedAreas && baseSettings.RestrictedAreas.Count() > 0)
			{
				foreach(vector v : baseSettings.RestrictedAreas)
				{
					vector tempV = Vector(v[0], 0, v[1]);
					dist = vector.Distance(tempV, m_Player.GetPosition());
					if (dist <= v[2]) return false;				
				}							
			}									

			// Searching for exceptions
			if (baseSettings.PlacingExceptions)
			{
				foreach(string exception : baseSettings.PlacingExceptions)
				{
					if (item && (item.GetType() == exception || item.IsKindOf(exception))) return true;
					
					// Hotfix otimizado para mods externos
					if (exception.Contains("TentBase") && item.IsItemTent()) return true;
					if (exception.Contains("Container") && item.IsContainer()) return true;
				}
			}											
			return false;
		}
		return true;
	}	
	
	bool IsAuthorized()
	{
		if (!m_Player) return false;

		float dist;
		int pID = m_Player.GetPlayerID();
		int cID = m_Player.GetClanID();		
		int r;
		
		if (!ClientData.PlotPoleList) return true;

		foreach (EntityAI ent : ClientData.PlotPoleList)
		{
			alp_PlotPole pp = alp_PlotPole.Cast(ent);
			
			if (pp && pp.alp_Radius && !pp.IsAuthorized(pID, cID))
			{
				// Verificação de SafeZone integrada
				bool inSafeZone = false;
				if (m_Player.GetSyncData())
				{
					auto syncElement = m_Player.GetSyncData().GetElement(alpRPelements.ISINTRADERZONE);
					if (syncElement) inSafeZone = syncElement.GetValue();
				}

				if (!inSafeZone)
				{
					dist = vector.Distance(pp.GetPosition(), m_Player.GetPosition());
					r = pp.GetRadius();
					if (dist <= r) return false;
				}
			}
		}
		return true;
	}
}