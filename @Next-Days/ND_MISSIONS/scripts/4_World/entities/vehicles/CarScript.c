/**
 * CarScript.c
 * * MODDED VEHICLE ENTITY - Módulo ND_MISSIONS
 * Gerencia lógica de trancamento, alarmes, colisões e persistência para veículos.
 */

modded class CarScript extends Car
{
	// Propriedades de Segurança
	bool alp_Lock;
	int alp_CarID;
	bool alp_AlarmSound;
	
	// Configurações de Colisão e Dano
	bool alp_EnableCutDownTrees = false; 
	float alp_RequiredImpulseToCutDown = 100000;
	float alp_DamageRatioWhenHitTree = 0.065;	
	float alp_DamageRatioWhenHitAI = 0.065;	
	float alp_DamageRatioWhenHitAnyOther = 0.065;

	float alp_DamageLight = 150;		
	float alp_DamageHeavy = 750;			
	float alp_DamageToKillCrew = 3000;	
	
	bool alp_HasCustomProperties;
	protected bool alp_IsMissionObject = false;

	void CarScript()
	{
		alp_AlarmSound = false;

		// Sincronização de rede para estados críticos
		RegisterNetSyncVariableInt("alp_CarID");
		RegisterNetSyncVariableBool("alp_AlarmSound");
	}

	// --- Persistência de Dados (Storage) ---

	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		super.OnStoreSave(ctx);
		ctx.Write(alp_IsMissionObject);
		ctx.Write(alp_CarID);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (super.OnStoreLoad(ctx, version))
		{
			if (!ctx.Read(alp_IsMissionObject)) alp_IsMissionObject = false;
			if (!ctx.Read(alp_CarID)) alp_CarID = 0;
			return true;
		}
		return false;
	}

	// --- Lógica de Identificação e Estado ---

	/**
	 * Gera uma assinatura única do estado do veículo (Tipo, Saúde, Anexos e Carga).
	 */
	string GetNameALP()
	{		
		string name = GetType() + "_" + GetQuantityALP().ToString() + "_" + GetHealthLevelALP().ToString() + "_" + GetAttachmentCountALP().ToString() + "_" + GetCargoCountALP().ToString();
		return name;
	}

	/**
	 * Conta quantos anexos do veículo possuem inventário próprio (ex: barris ou caixas anexadas).
	 */
	int GetAttachmentCountALP()
	{		
		EntityAI attachment;
		int attcount = GetInventory().AttachmentCount();
		int count = 0;
		for (int att = 0; att < attcount; att++)
		{	
			attachment = GetInventory().GetAttachmentFromIndex(att);
			if (attachment && attachment.IsItemBase() && attachment.GetInventory().GetCargo())
			{
				count++;
			}
		}							
		return count;
	}

	int GetCargoCountALP()
	{
		if (GetInventory() && GetInventory().GetCargo())
			return GetInventory().GetCargo().GetItemCount();		
		return 0;
	}

	float GetHealthLevelALP()
	{
		float level = 1.0;
		switch (GetHealthLevel())
		{
			case 1: level = 0.75; break;
			case 2: level = 0.50; break;			
			case 3: level = 0.25; break;
			case 4: level = 0.0;  break;			
		}
		return level;
	}

	float GetQuantityALP() { return 1.0; }
}