/**
 * @class   alp_Card
 * @brief   Gerencia o sistema de Seguro de Vida/Cartões com validade real no Next Days
 * Auditado em: 2026 - Foco em Persistência e Proteção contra Restarts
 */
class alp_Card extends Inventory_Base
{
	int alp_DateStamp;
	int alp_Validity = -1; // -1: Novo, 0: Inativo, 1: Ativo
	
	void alp_Card()
	{	
		RegisterNetSyncVariableInt("alp_Validity");
		// Nota: alp_DateStamp não é sincronizado para economizar tráfego, 
		// pois o cliente só precisa saber se é válido ou não.
	}	
	
	override void OnWorkStart()
	{
		if (GetGame().IsServer())
		{	
			// Só define o carimbo de data se for a primeira vez que é ativado
			if (alp_DateStamp == 0)
				SetTimeStampALP();
		}
	}
	
	override void OnWork(float consumed_energy)
	{
		super.OnWork(consumed_energy);
		alp_Validity = 1;
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		alp_Validity = 0;
	}

	override string GetTooltip()
	{
		string tooltip = super.GetTooltip();

		if ( alp_Validity == -1 )
			return "#STR_alp_lifeinsurance_notactive";
		
		if ( alp_Validity == 0 )
			return "#STR_alp_lifeinsurance_expired";
			
		return tooltip;
	}

	// 1. Sistema de Persistência Robusto
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		ctx.Write( alp_DateStamp );
		ctx.Write( alp_Validity );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

		if ( !ctx.Read( alp_DateStamp ) ) alp_DateStamp = 0;
		if ( !ctx.Read( alp_Validity ) ) alp_Validity = -1;
		
		return true;
	}	
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( GetGame().IsServer() && GetCompEM().IsWorking() )
		{
			if (alp_Validity == 1 && alp_DateStamp > 0)
			{
				SetEnergyALP();				
			}
		}
	}
	
	void SetEnergyALP()
	{
		int expiredDays = VerificationCardALP();		
		// Consome energia proporcionalmente ao tempo passado em dias reais
		float energyToConsume = expiredDays * (GetMaxEnergyALP() / 7);
								
		GetCompEM().ConsumeEnergy(energyToConsume);
	}

	// 2. Correção de Tempo Real (Substituindo GetTime por sistema de persistência de data)
	void SetTimeStampALP()
	{
		// Usamos o tempo do servidor convertido para dias para evitar bugs de restart
		// Em um ambiente ideal, você usaria CF_Date ou similar do Community Framework
		// Aqui simulamos com o tempo de sistema do servidor
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		
		// Converte para um número sequencial simples (Total de dias aproximado)
		alp_DateStamp = (year * 365) + (month * 30) + day;
	}
	
	int VerificationCardALP()
	{
		int year, month, day;
		GetYearMonthDay(year, month, day);
		int currentTotalDays = (year * 365) + (month * 30) + day;
		
		int diff = currentTotalDays - alp_DateStamp;
		return Math.Max(0, diff); // Retorna 0 se for o mesmo dia, ou a diferença
	}
};