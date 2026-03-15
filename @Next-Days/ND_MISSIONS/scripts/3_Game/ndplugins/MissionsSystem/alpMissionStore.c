/**
 * alpMissionStore.c
 * * ESTRUTURA DE ARMAZENAMENTO DE MISSÕES - Módulo ND_MISSIONS
 * Define como os dados das missões são organizados para salvamento no Hive.
 */

// Classe base para elementos individuais dentro de uma missão
class alpMissionElementStore_Base
{
	string 	m_Type;
	int 	m_ID;
	int 	m_Index; // Index do template no array
	vector 	m_Position;
	vector 	m_YPR;
	int     m_Stance;
	
	void alpMissionElementStore_Base(string name, int id, int index, vector pos, vector ypr, int stance)
	{
		m_Type = name;
		m_ID = id;
		m_Index = index;
		m_Position = pos;
		m_YPR = ypr;
		m_Stance = stance;	
	}
}

// Classe principal de armazenamento de uma missão completa
class alpMissionStore
{
	int m_Id;
	int m_ParendId;
	string m_Name;
	
	int m_Setting;

	int	m_SafeRadius;	
	int	m_CleanRadius;
	int	m_DamageRadius;
	
	vector	m_Position;
	vector	m_Angle;
	
	float	m_Radiation;	
	
	ref array<ref alpMissionElementStore_Base>	m_ControlPanels;
	ref array<ref alpMissionElementStore_Base> 	m_Loots;
	ref array<ref alpMissionElementStore_Base> 	m_NPCs;
	ref array<ref alpMissionElementStore_Base> 	m_Cars;
	ref array<ref alpMissionElementStore_Base> 	m_Structures;
	ref array<ref alpMissionElementStore_Base> 	m_ContaminedAreas;
	ref array<ref alpMissionElementStore_Base> 	m_ContaminedAreasDynamic;

	// CONSTRUTOR: Garante a inicialização dos arrays para evitar Null Pointer Exceptions
	void alpMissionStore()
	{
		m_ControlPanels 		= new array<ref alpMissionElementStore_Base>;
		m_Loots 				= new array<ref alpMissionElementStore_Base>;
		m_NPCs 					= new array<ref alpMissionElementStore_Base>;
		m_Cars 					= new array<ref alpMissionElementStore_Base>;
		m_Structures 			= new array<ref alpMissionElementStore_Base>;
		m_ContaminedAreas 		= new array<ref alpMissionElementStore_Base>;
		m_ContaminedAreasDynamic = new array<ref alpMissionElementStore_Base>;
	}

	bool IsPersistent()
	{
		return (m_Setting & alpMISSION_SETTING.SAVE_STAGE);
	}

	void Save()
	{
		alpMHIVE.Save();
	}

	// --- MÉTODOS DE ADIÇÃO (PRESERVAÇÃO DE LÓGICA) ---

	void AddNPC(string name, int id, int index, vector pos, vector ypr, int stance = 0)
	{
		if (IsPersistent())
		{		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base(name, id, index, pos, ypr, stance);
			m_NPCs.Insert(element);
			Save();	
		}			
	}

	void AddStructure(string name, int id, int index, vector pos, vector ypr, int stance = 0)
	{
		if (IsPersistent())
		{		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base(name, id, index, pos, ypr, stance);
			m_Structures.Insert(element);
			Save();	
		}			
	}

	void AddArea(string name, int id, int index, vector pos, vector ypr, int stance = 0)
	{
		if (IsPersistent())
		{		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base(name, id, index, pos, ypr, stance);
			m_ContaminedAreas.Insert(element);
			Save();	
		}			
	}

	void AddAreaDynamic(string name, int id, int index, vector pos, vector ypr, int stance = 0)
	{
		if (IsPersistent())
		{		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base(name, id, index, pos, ypr, stance);
			m_ContaminedAreasDynamic.Insert(element);
			Save();	
		}			
	}

	// --- MÉTODOS DE REMOÇÃO (OTIMIZAÇÃO E SEGURANÇA) ---

	void RemoveLoot(int id)
	{
		if (m_Loots)
		{
			for (int i = 0; i < m_Loots.Count(); i++)
			{
				if (m_Loots.Get(i) && m_Loots.Get(i).m_ID == id)
				{
					m_Loots.Remove(i);
					break;
				}
			}
		}
		Save();
	}

	void RemoveCar(int id)
	{
		if (m_Cars)
		{
			for (int i = 0; i < m_Cars.Count(); i++)
			{
				if (m_Cars.Get(i) && m_Cars.Get(i).m_ID == id)
				{
					m_Cars.Remove(i);
					break;
				}
			}
		}
		Save();
	}

	void RemoveNPC(int id)
	{
		if (m_NPCs)
		{
			for (int i = 0; i < m_NPCs.Count(); i++)
			{
				if (m_NPCs.Get(i) && m_NPCs.Get(i).m_ID == id)
				{
					m_NPCs.Remove(i);
					break;
				}
			}
		}
		Save();
	}
}