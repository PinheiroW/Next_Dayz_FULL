/**
 * ZombieBase.c
 * * MODDED ENTITY (INFECTADOS) - Módulo ND_MISSIONS
 * Gerencia o tempo de vida de zumbis de missão e proteção contra ataques em SafeZones.
 */

modded class ZombieBase extends DayZInfected
{
	// Define um tempo de vida padrão quase infinito para zumbis nativos
	float m_LifeTimeZed = 2147483647; // int.MAX - 1
	
	/**
	 * Handler chamado após o processamento de comandos de movimento/animação.
	 * Utilizado aqui para gerenciar o cronômetro de vida da entidade.
	 */
	override bool ModCommandHandlerAfter(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		bool ret = super.ModCommandHandlerAfter(pDt, pCurrentCommandID, pCurrentCommandFinished);	
		
		// Reduz o tempo de vida baseado no tempo decorrido
		m_LifeTimeZed -= pDt;
		
		if ( IsAlive() && m_LifeTimeZed <= 0 )
		{
			// Mata o zumbi silenciosamente se o tempo expirar (limpeza de missão)
			SetHealth("", "", 0);
		}				
		
		return ret;
	}
	
	/**
	 * Define manualmente um tempo de vida (usado pelo sistema de missões ao spawnar).
	 */
	void SetLifeTimeZed(float t)
	{
		m_LifeTimeZed = t;
	}
	
	/**
	 * Lógica de ataque: Intercepta tentativas de ataque contra jogadores em SafeZones.
	 */
	override bool FightAttackLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{
		// Verifica se a proteção de SafeZone está ativa nas configurações
		auto traderOptions = GetND().GetMS().GetOptoinsTrader();
		if ( traderOptions && traderOptions.KillZombiesWhileAttackAtTrader )
		{
			EntityAI target = pInputController.GetTargetEntity();
			PlayerBase player;
			
			// Se o alvo for um jogador e ele estiver sob proteção de "No Damage" (Trader)
			if ( Class.CastTo(player, target) && !player.GetRP().IsAllowedDamage() )
			{
				// Limpa referências de alvos para evitar erros de processamento no motor
				m_AllTargetObjects.Clear();
				
				// O zumbi morre instantaneamente ao tentar violar a SafeZone
				SetHealth01("", "", 0);
				
				return false; // Interrompe o ataque
			}
		}
		
		return super.FightAttackLogic(pCurrentCommandID, pInputController, pDt);
	}
}