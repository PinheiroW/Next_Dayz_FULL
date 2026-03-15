/**
 * vppa_BuildingSet.c
 * * MISSION EXPORTER - Módulo ND_MISSIONS (VPPA Integration)
 * Converte construções do VPP Admin Tools para templates JSON do Next-Days.
 */

#ifdef VPPADMINTOOLS

/**
 * Define as classes de objetos utilizadas como gatilhos no editor do VPP.
 */
class VPPAKeyWordALP
{
	static string alp_ExportFolder = ALP_ROOTFOLDER + "Exports/";

	// Placeholders para conversão
	static string alp_NPC           = "vbldr_legs_dz";
	static string alp_AI            = "vbldr_legs_m";
	static string alp_LOOT          = "vbldr_barrel_holes";
	static string alp_LOOT2         = "StaticObj_Misc_WoodenCrate";
	static string alp_VEHICLE       = "Land_Wreck_Volha_Blue";	
	static string alp_CONSOLE       = "alp_ServerConsole";	
	static string alp_VEHICLE_SPAWN = "Land_Wreck_Lada_Green";	
}

modded class BuildingSet
{
	/**
	 * Sobrescreve o método de exportação padrão do VPP para gerar arquivos compatíveis com o ND.
	 */
	override void ExportBuildings()
	{
		super.ExportBuildings();
		
		// Garante a existência do diretório de exportação
		if (!FileExist(VPPAKeyWordALP.alp_ExportFolder)) 
		{
			MakeDirectory(VPPAKeyWordALP.alp_ExportFolder);
		}	
		
		alpMissionTemplate ms = new alpMissionTemplate;
		
		// Configurações padrão para novas missões exportadas
		ms.mapTitle     = m_Name;
		ms.active       = 1;
		ms.nominal      = 1;
		ms.lifeTime     = 3600;
		ms.restock      = 1;
		ms.safeRadius   = 100;
		ms.cleanRadius  = 200;
		ms.chance       = 1;
		ms.showInMap    = 1;
		ms.sendInfo     = 1;
		
		vector zeroPosition;

		foreach(SpawnedBuilding building : m_Buildings)
		{
			alpMissionAddSpawn structure = new alpMissionAddSpawn;	
			structure.className          = building.GetTypeName();
			structure.noPlaceOnSurface   = true;

			vector orientation           = building.GetOrientation();
									
			if (!zeroPosition)
			{
				// O primeiro objeto define o ponto central (0,0,0) da missão
				zeroPosition = building.GetPosition();
				
				array<float> mPos = {zeroPosition[0], zeroPosition[1], zeroPosition[2], 0};
				ms.position.Insert(mPos); 
				
				structure.position = "0 0 0";
				structure.yaw      = orientation[0];
				structure.pitch    = orientation[1];
				structure.roll     = orientation[2];	
			}
			else
			{
				// Calcula o offset relativo ao centro da missão
				structure.position = vector.Direction(zeroPosition, building.GetPosition());
				structure.yaw      = orientation[0];
				structure.pitch    = orientation[1];
				structure.roll     = orientation[2];				
			}
			
			// Lógica de conversão de Placeholders para tipos especializados do ND
			bool exception = false;			
			switch (structure.className)
			{
				case VPPAKeyWordALP.alp_NPC:
				{
					alpMissionAddNPC npc = new alpMissionAddNPC;
					npc.position = structure.position;
					npc.yaw      = structure.yaw;
					npc.pitch    = structure.pitch;
					npc.roll     = structure.roll;		
					
					ms.NPC.Insert(npc);
					exception = true;
					break;
				}
				case VPPAKeyWordALP.alp_AI:
				{
					CreateMissionAI_alp(structure.position);
					exception = true;
					break;
				}			
				case VPPAKeyWordALP.alp_LOOT2:
				case VPPAKeyWordALP.alp_LOOT:
				{
					alpMissionAddCargo loot = new alpMissionAddCargo;
					loot.chance    = 1;
					loot.className = "SeaChest"; // Classe de container padrão para loot de missão
					loot.position  = structure.position;
					loot.yaw       = structure.yaw;
					loot.pitch     = structure.pitch;
					loot.roll      = structure.roll;	
					
					ms.loot.Insert(loot);
					exception = true;
					break;
				}	
				case VPPAKeyWordALP.alp_VEHICLE:
				{
					alpMissionAddVehicle vehicle = new alpMissionAddVehicle;
					vehicle.chance   = 1;
					vehicle.title    = "MissionCars_1";
					vehicle.position = structure.position;
					vehicle.yaw      = structure.yaw;
					vehicle.pitch    = structure.pitch;
					vehicle.roll     = structure.roll;
					
					ms.vehicles.Insert(vehicle);					
					exception = true;
					break;
				}	
				case VPPAKeyWordALP.alp_CONSOLE:
				{
					alpMissionAddControlPanel console = new alpMissionAddControlPanel;
					console.className = "alp_ServerConsole";
					console.position  = structure.position;
					console.yaw       = structure.yaw;
					console.pitch     = structure.pitch;
					console.roll      = structure.roll;	
					
					ms.controlPanels.Insert(console);					
					exception = true;
					break;
				}	
				case VPPAKeyWordALP.alp_VEHICLE_SPAWN:
				{
					alpMissionAddSpawn spawn = new alpMissionAddSpawn;
					spawn.position = structure.position;
					spawn.yaw      = structure.yaw;
					spawn.pitch    = structure.pitch;
					spawn.roll     = structure.roll;	
					
					ms.spawnPlaceForVehicles.Insert(spawn);					
					exception = true;
					break;
				}									
			} 
									
			if (!exception)
			{
				ms.structures.Insert(structure);	
			}
		}
		
		// Salva o template principal da missão
		JsonFileLoader<ref alpMissionTemplate>.JsonSaveFile(VPPAKeyWordALP.alp_ExportFolder + m_Name + ".json", ms);
	}
	
	/**
	 * Gerencia a criação e persistência de dados de IA em um arquivo separado.
	 */
	void CreateMissionAI_alp(vector pos)
	{
		array<ref alpMissionAIsample> missionAI;
		string aiPath = VPPAKeyWordALP.alp_ExportFolder + m_Name + "_AI.json";
		
		if (!FileExist(aiPath))
		{
			JsonFileLoader<array<ref alpMissionAIsample>>.JsonSaveFile(aiPath, missionAI);	
		} 

		JsonFileLoader<array<ref alpMissionAIsample>>.JsonLoadFile(aiPath, missionAI);	
		
		alpMissionAIsample newAI = new alpMissionAIsample;		
		newAI.position = pos;
		
		missionAI.Insert(newAI);
		
		JsonFileLoader<array<ref alpMissionAIsample>>.JsonSaveFile(aiPath, missionAI);	
	}
}

#endif