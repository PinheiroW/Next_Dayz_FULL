/**
 * tentbase.c
 * * MODDED ENTITY (BARRACAS) - Módulo ND_MISSIONS
 * Garante a persistência do status de missão para todas as variantes de tendas/barracas.
 */

modded class TentBase extends ItemBase
{
	/**
	 * Salva os dados customizados no storage do servidor.
	 */
	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		// Salva os dados originais da barraca (inventário, estado, etc.)
		super.OnStoreSave(ctx);

		// Salva se a barraca é um objeto de missão (Next-Days)
		ctx.Write(alp_IsMissionObject);
	}	

	/**
	 * Carrega os dados customizados do storage do servidor após um restart.
	 */
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		// Carrega os dados originais primeiro
		if (super.OnStoreLoad(ctx, version))
		{
			// Lê o status de objeto de missão
			if (!ctx.Read(alp_IsMissionObject))
			{
				alp_IsMissionObject = false; // Valor padrão caso a leitura falhe
			}
						
			return true;
		}
		
		return false;
	}
};