/**
 * ZombieBase.c
 * * MODDED ENTITY (INFECTED) - Módulo ND_MISSIONS
 * Gerencia o ciclo de vida de entidades de missão e a integridade de SafeZones.
 */

modded class ZombieBase extends DayZInfected
{
	// Cronómetro de vida (Fallback para valor máximo para evitar morte de zumbis nativos)
	protected float m_LifeTimeZed = 2147483647; 
	
	/**
	 * Atualização lógica por frame de animação.
	 * Gerencia a contagem regressiva para expiração da entidade.
	 */
	override bool ModCommandHandlerAfter(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		bool ret = super.ModCommandHandlerAfter(pDt, pCurrentCommandID, pCurrentCommandFinished);	
		
		// Processa o tempo de vida baseado no tempo real decorrido
		m_LifeTimeZed -= pDt;
		
		if (IsAlive() && m_LifeTimeZed <= 0)
		{
			// Eliminação silenciosa por expiração de tempo (Cleanup de Missão)
			SetHealth("", "", 0);
		}				
		
		return ret;
	}
	
	/**
	 * Define o tempo de persistência desta entidade no mundo.
	 * @param t: Tempo em segundos.
	 */
	void SetLifeTimeZed(float t)
	{
		m_LifeTimeZed = t;
	}
	
	/**
	 * Intercepta a lógica de ataque para aplicar regras de SafeZone.
	 */
	override bool FightAttackLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{
		auto traderOptions = GetND().GetMS().GetOptoinsTrader();
		
		// Verifica se a punição para invasores de SafeZone está ativa
		if (traderOptions && traderOptions.KillZombiesWhileAttackAtTrader)
		{
			EntityAI target = pInputController.GetTargetEntity();
			PlayerBase player;
			
			// Se o alvo for um jogador protegido pelo sistema de RP do Next-Days
			if (Class.CastTo(player, target) && player.GetRP() && !player.GetRP().IsAllowedDamage())
			{
				// Limpa a lista de alvos para evitar conflitos na IA antes da morte
				m_AllTargetObjects.Clear();
				
				// Executa a morte instantânea do infectado ao violar a área de paz
				SetHealth01("", "", 0);
				
				return false; // Bloqueia a execução do golpe
			}
		}
		
		return super.FightAttackLogic(pCurrentCommandID, pInputController, pDt);
	}
}