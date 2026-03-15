/**
 * HelicopterScript.c
 * * MODDED HELICOPTER ENTITY - Módulo ND_MISSIONS
 * Define a lógica de ID, persistência e estatísticas para veículos aéreos.
 */

modded class HelicopterScript extends HelicopterAuto
{
	protected bool alp_IsMissionObject = false;
	bool alp_Lock;
	int alp_CarID;

	void HelicopterScript()
	{
		// Sincroniza o ID para que clientes saibam qual chave abre este helicóptero
		RegisterNetSyncVariableInt("alp_CarID");
		
		if (GetGame().IsServer()) 
		{
			// Adiciona o veículo às estatísticas globais do servidor
			alpPluginNDmissionsSystem.AddVehicleToStat(GetType());	
		}
	}

	void ~HelicopterScript()
	{
		if (GetGame() && GetGame().IsMultiplayer() && GetGame().IsServer()) 
		{
			// Remove das estatísticas ao ser destruído ou deletado
			alpPluginNDmissionsSystem.RemoveVehicleFromStat(GetType());
		}
	}	

	// --- Getters e Setters de Identificação ---

	int GetAlpCarID() { return alp_CarID; }
	
	void SetAlpCarID(int carid) { alp_CarID = carid; }	
	
	override void EEInit()
	{
		super.EEInit();
		
		if (GetGame().IsServer())
		{
			// Lógica adicional de inicialização pode ser inserida aqui
		}
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

	// --- Funções de Diagnóstico e Estado (Compatibilidade com Banco) ---

	string GetNameALP()
	{		
		return GetType() + "_" + GetQuantityALP().ToString() + "_" + GetHealthLevelALP().ToString() + "_" + GetAttachmentCountALP().ToString() + "_" + GetCargoCountALP().ToString();
	}

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
		// Converte o enum de dano vanilla em valores decimais para o sistema ND
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
	
	int GetDefaultPrice() { return 100000; } // Valor base para sistemas de seguro/venda
}