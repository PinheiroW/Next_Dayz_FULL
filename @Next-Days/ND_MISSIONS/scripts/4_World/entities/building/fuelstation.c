/**
 * fuelstation.c
 * * MODDED ENTITY (POSTO DE COMBUSTÍVEL) - Módulo ND_MISSIONS
 * Gerencia o combustível como recurso finito, com persistência e eventos de missão.
 */

modded class FuelStation extends BuildingSuper
{
	bool alp_WAS_ADDED;
	int alp_MIN_FUEL = 500;
	ref alpResourcesStation alp_Setting;
	
	float alp_LastAmmount;
	float alp_Ammount = 99999999;
	float alp_AmmountMax = 99999999;
	float alp_RefreshPerRestart;
	float alp_ChanceRefresh;
	
	// Pasta de armazenamento definida no sistema Next-Days
	string ALP_FUELS_FOLDER = "$profile:NextDays/Fuels/";

	void FuelStation()
	{
		// Aguarda 100ms para garantir que o ID da entidade esteja pronto
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitALP, 100);	
	}

	void ~FuelStation()
	{
		if (alp_Setting)
			delete alp_Setting;
	}

	void InitALP()
	{
		if ( GetGame().IsServer() && GetGame().IsMultiplayer() && GetND().GetResources().GetOptions().EnableFuelstationManagement )
		{
			// Cria o diretório se não existir
			if (!FileExist(ALP_FUELS_FOLDER))
				MakeDirectory(ALP_FUELS_FOLDER);

			string path = ALP_FUELS_FOLDER + GetID().ToString() + ".json";

			if (!FileExist(path))
			{
				// Carrega padrões do Config do mod
				float amount = GetND().GetResources().GetDefaultFuelstations().DefaultAmmount;
				float max = GetND().GetResources().GetDefaultFuelstations().DefaultAmmountMax;
				float refresh = GetND().GetResources().GetDefaultFuelstations().DefaultRefreshPerRestart;
				float chance = GetND().GetResources().GetDefaultFuelstations().DefaultChanceRefresh;

				alp_Setting = new alpResourcesStation( GetID(), GetND().GetNotf().GetLocationsLabels().GetLocation(GetPosition()), GetPosition(), amount, max, refresh, chance );
				JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(path, alp_Setting);
			}
			
			JsonFileLoader<ref alpResourcesStation>.JsonLoadFile(path, alp_Setting);
			
			if (alp_Setting)
			{
				// Aplica a lógica de reabastecimento por sorteio no restart
				float roll = Math.RandomFloat01() * 100;
				if (roll <= alp_Setting.ChanceRefresh)
				{
					alp_Setting.Ammount += alp_Setting.RefreshPerRestart;
				}

				alp_Ammount = Math.Clamp(alp_Setting.Ammount, 0, alp_Setting.AmmountMax);
				alp_AmmountMax = alp_Setting.AmmountMax;
				alp_RefreshPerRestart = alp_Setting.RefreshPerRestart;
				alp_ChanceRefresh = alp_Setting.ChanceRefresh;
				
				SaveALP();
			}
		}
	}

	void DrainFuelALP(float ammount)
	{
		alp_Ammount -= ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0, alp_AmmountMax);
		
		// Verifica se o nível baixo deve disparar uma missão global
		CheckMissionCondition();
		
		// Salva o estado atualizado periodicamente ou após uso
		SaveALP();
	}

	void SaveALP()
	{
		if (alp_Setting)
		{
			alp_Setting.Ammount = alp_Ammount;
			JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(ALP_FUELS_FOLDER + GetID().ToString() + ".json", alp_Setting);
		}
	}

	void CheckMissionCondition()
	{		
		if ( GetGame().IsServer() && !alp_WAS_ADDED && alp_Ammount < alp_MIN_FUEL )
		{
			// Trigger para o sistema de missões do Next-Days
			GetND().GetMissions().OnFuelStationEmpty(this);
			alp_WAS_ADDED = true;
		}
	}
}