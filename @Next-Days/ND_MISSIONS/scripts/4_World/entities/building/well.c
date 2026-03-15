/**
 * well.c
 * * MODDED ENTITY (FONTE DE ÁGUA / POÇO) - Módulo ND_MISSIONS
 * Gerencia a água como recurso finito e persistente no mapa.
 */

modded class Well extends BuildingSuper
{
	ref alpResourcesStation alp_Setting;
	
	float alp_LastAmmount;
	float alp_Ammount = 99999999;
	float alp_AmmountMax = 99999999;
	float alp_RefreshPerRestart;
	float alp_ChanceRefresh;	
	
	string ALP_WELLS_FOLDER = "$profile:NextDays/Wells/";
	
	void Well()
	{
		// Inicialização tardia para garantir a disponibilidade do ID da entidade
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitALP, 100);
	}	

	/**
	 * Reduz a quantidade de água disponível no poço.
	 */
	void DrainWaterALP(float ammount)
	{
		alp_Ammount -= ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0, alp_AmmountMax);
		
		// Sugestão de salvamento automático após grandes drenagens
		if (Math.AbsFloat(alp_LastAmmount - alp_Ammount) > 10)
			SaveWellALP();
	}

	/**
	 * Adiciona água ao poço (ex: via caminhão pipa ou evento).
	 */
	void AddWaterALP(float ammount)
	{
		alp_Ammount += ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0, alp_AmmountMax);
		SaveWellALP();
	}	

	/**
	 * Persiste os dados atuais no arquivo JSON.
	 */
	void SaveWellALP()
	{
		if (GetGame().IsServer() && alp_LastAmmount != alp_Ammount)
		{
			if (alp_Setting)
			{		
				alp_Setting.Ammount = alp_Ammount;
				JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(ALP_WELLS_FOLDER + GetID().ToString() + ".json", alp_Setting);
				alp_LastAmmount = alp_Ammount; // Atualiza o cache de controle
			}
		}
	}
	
	void InitALP()
	{
		if (GetGame().IsServer() && GetGame().IsMultiplayer() && GetND().GetResources().GetOptions().EnableWellManagement)		
		{
			if (!FileExist(ALP_WELLS_FOLDER))
				MakeDirectory(ALP_WELLS_FOLDER);
				
			string path = ALP_WELLS_FOLDER + GetID().ToString() + ".json";
			
			if (!FileExist(path))
			{
				float amount = GetND().GetResources().GetDefaultWell().DefaultAmmount;
				float max = GetND().GetResources().GetDefaultWell().DefaultAmmountMax;
				float refresh = GetND().GetResources().GetDefaultWell().DefaultRefreshPerRestart;
				float chance = GetND().GetResources().GetDefaultWell().DefaultChanceRefresh;
							
				alp_Setting = new alpResourcesStation(GetID(), GetND().GetNotf().GetLocationsLabels().GetLocation(GetPosition()), GetPosition(), amount, max, refresh, chance);
				JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(path, alp_Setting);
			}		
			
			JsonFileLoader<ref alpResourcesStation>.JsonLoadFile(path, alp_Setting);
			
			if (alp_Setting)
			{
				// Lógica de reabastecimento no Restart
				float roll = Math.RandomFloat01() * 100;
				if (roll <= alp_Setting.ChanceRefresh)
				{
					alp_Setting.Ammount += alp_Setting.RefreshPerRestart;
				}

				alp_Ammount = Math.Clamp(alp_Setting.Ammount, 0, alp_Setting.AmmountMax);
				alp_AmmountMax = alp_Setting.AmmountMax;
				alp_RefreshPerRestart = alp_Setting.RefreshPerRestart;
				alp_ChanceRefresh = alp_Setting.ChanceRefresh;	
				
				alp_LastAmmount = alp_Ammount;
				SaveWellALP();
			}
		}
	}
}