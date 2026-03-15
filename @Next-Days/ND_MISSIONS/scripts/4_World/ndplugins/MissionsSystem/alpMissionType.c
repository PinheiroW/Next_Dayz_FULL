/**
 * alpMissionType.c
 * Mapeamento de tipos de missão para IDs internos.
 */
class alpMissionType 
{
	ref map<string,int>	alp_MissionType;
	
	void alpMissionType()
	{
		alp_MissionType = new map<string,int>;
		Init();
	}

	void ~alpMissionType()
	{
		delete alp_MissionType;
	}
	
	void Init()
	{
		// Missões sem radiação
		alp_MissionType.Set("noradiationMission", ALP_MISSIONTYPEID.noradiationMission );		
		alp_MissionType.Set("mission", ALP_MISSIONTYPEID.noradiationMission );		
		
		// Áreas estáticas
		alp_MissionType.Set("noradiation", ALP_MISSIONTYPEID.noradiation );		
		alp_MissionType.Set("static", ALP_MISSIONTYPEID.noradiation );			

		// Eventos específicos
		alp_MissionType.Set("carAccident", ALP_MISSIONTYPEID.carAccident );				
		alp_MissionType.Set("radiation", ALP_MISSIONTYPEID.radiation );
		alp_MissionType.Set("radiationMission", ALP_MISSIONTYPEID.radiationMission );	
		
		// Comércio e Resgate
		alp_MissionType.Set("trader", ALP_MISSIONTYPEID.trader );	
		alp_MissionType.Set("fuelstation", ALP_MISSIONTYPEID.fuelstation );
		alp_MissionType.Set("savesurvivors", ALP_MISSIONTYPEID.savesurvivors );
		alp_MissionType.Set("savemerchants", ALP_MISSIONTYPEID.savemerchants );
		alp_MissionType.Set("conquerdefend", ALP_MISSIONTYPEID.conquerdefend );
	}
}