/**
 * personalradio.c
 * * MODDED ENTITY (RADIO PESSOAL) - Módulo ND_MISSIONS
 * Implementa persistência de estado (ON/OFF) através de restarts do servidor.
 */

modded class PersonalRadio extends TransmitterBase
{
	protected bool alp_IsOn;
	
	/**
	 * Salva o estado atual do rádio no banco de dados.
	 */
	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		super.OnStoreSave(ctx);
		
		// Escreve se o rádio está ligado no momento do save
		ctx.Write(IsOnALP());
	}
	
	/**
	 * Carrega o estado salvo do rádio.
	 */
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(alp_IsOn))
		{
			SetWorkingStateALP(false);
		} 
		
		return true;
	}	

	/**
	 * Após o carregamento, reativa o consumo de energia se o rádio estava ligado.
	 */
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if (IsOnALP())
		{
			// Verifica se possui bateria e se está em posse de um jogador para religar
			if (HasEnergyManager() && !GetCompEM().IsWorking() && GetHierarchyRootPlayer()) 
			{
				GetCompEM().SwitchOn();
			} 
		}		 
	}
	
	// --- Getters e Setters de Estado ---

	void SetWorkingStateALP(bool state)
	{
		alp_IsOn = state;
	}
	
	bool IsOnALP()
	{
		return alp_IsOn;
	}	
}