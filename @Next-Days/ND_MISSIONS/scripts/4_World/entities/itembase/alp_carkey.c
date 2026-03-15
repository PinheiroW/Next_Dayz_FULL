/**
 * alp_carkey.c
 * * ENTIDADE DE ITEM (CHAVES DE VEÍCULO) - Módulo ND_MISSIONS
 * Gerencia a vinculação de chaves a veículos e ações de trava/destrava.
 */

class alp_CarKey_Base: Inventory_Base
{
	protected int alp_KeyID;
	
	override void SetActions()
	{
		super.SetActions();
		
		// Ações de interação com o veículo
		AddAction(alpLockVehicle);
		AddAction(alpUnlockVehicle);
	}
	
	bool IsAdminKey()
	{
		return false;
	}
	
	int GetAlpKeyID()
	{
		return alp_KeyID;
	}
	
	void SetAlpKeyID(int keyid)
	{
		alp_KeyID = keyid;
		SetSynchDirty(); // Notifica o cliente sobre a mudança de ID
	}
}

// Chave mestra de administrador (ignora IDs de veículos)
class alp_AdminCarKey extends alp_CarKey_Base
{
	override bool IsAdminKey()
	{
		return true;
	}	
}

// Chave de veículo padrão
class alp_CarKey extends alp_CarKey_Base
{
	void alp_CarKey()
	{
		// Registra a variável para sincronização entre Servidor e Cliente
		RegisterNetSyncVariableInt("alp_KeyID");
	}

	override void EOnInit(IEntity other, int extra)
	{
		super.EOnInit(other, extra);
		
		// Aguarda o frame seguinte para garantir que a hierarquia de objetos foi carregada
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.CreateKeyForVehicle, 100);
	}
	
	/**
	 * Tenta vincular a chave ao veículo se ela for gerada dentro dele.
	 */
	void CreateKeyForVehicle()
	{
		CarScript car;
		
		if ( alp_KeyID == 0 && Class.CastTo( car, GetHierarchyRoot() ) )
		{
			alp_KeyID = car.GetAlpCarID();
		}
		else if ( alp_KeyID == 0 )
		{
			alp_KeyID = -1; // Estado de "sem vínculo"
		}
		
		SetSynchDirty();
	}
	
	/**
	 * Exibe o ID da chave no menu de contexto do inventário.
	 */
	override string GetTooltip()
	{
		string tooltip = super.GetTooltip();
		int key = alp_KeyID;
		
		if ( key == -1 )
			key = 0;
		
		tooltip += " \nID: " + key.ToString();
		
		return tooltip;
	}
}