/**
 * wreck_heli.c
 * * MODDED ENTITY (HELICÓPTEROS CAÍDOS) - Módulo ND_MISSIONS
 * Diferencia destroços nativos de objetos gerados por missões dinâmicas.
 */

// Lógica para o UH1Y
modded class Wreck_UH1Y extends CrashBase
{
	protected bool alp_IsMissionObject = false;

	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		ctx.Write( alp_IsMissionObject );
	}	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		if ( !ctx.Read( alp_IsMissionObject ) )
			alp_IsMissionObject = false;
			
		return true;
	}		
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		// Se for um objeto de missão antiga, remove do mapa no carregamento
		if ( IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
		}				
	}	

	bool IsMissionObject()
	{
		return alp_IsMissionObject;
	}
	
	void SetMissionObjectState(bool state)
	{
		alp_IsMissionObject = state;
	}
	
	void EEOnALPCreate()
	{
		EEOnCECreate();
	}	
}

// Lógica para o Mi8 (Base e Crashed)
modded class Wreck_Mi8 extends CrashBase
{
	protected bool alp_IsMissionObject = false;

	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		ctx.Write( alp_IsMissionObject );
	}	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		if ( !ctx.Read( alp_IsMissionObject ) )
			alp_IsMissionObject = false;
			
		return true;
	}		
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
		}				
	}	

	bool IsMissionObject()
	{
		return alp_IsMissionObject;
	}
	
	void SetMissionObjectState(bool state)
	{
		alp_IsMissionObject = state;
	}
	
	void EEOnALPCreate()
	{
		EEOnCECreate();
	}
}

modded class Wreck_Mi8_Crashed extends CrashBase
{
	protected bool alp_IsMissionObject = false;

	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		ctx.Write( alp_IsMissionObject );
	}	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		if ( !ctx.Read( alp_IsMissionObject ) )
			alp_IsMissionObject = false;
			
		return true;
	}		
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
		}				
	}	

	bool IsMissionObject()
	{
		return alp_IsMissionObject;
	}
	
	void SetMissionObjectState(bool state)
	{
		alp_IsMissionObject = state;
	}
	
	void EEOnALPCreate()
	{
		EEOnCECreate();
	}
}