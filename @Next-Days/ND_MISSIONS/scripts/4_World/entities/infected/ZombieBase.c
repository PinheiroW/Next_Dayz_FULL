	
modded class ZombieBase extends DayZInfected
{
	float m_LifeTimeZed = int.MAX - 1;
	
	override bool	ModCommandHandlerAfter(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		bool ret = super.ModCommandHandlerAfter( pDt,  pCurrentCommandID,  pCurrentCommandFinished);	
		m_LifeTimeZed -= pDt;
		if ( IsAlive() && m_LifeTimeZed <= 0 ){
			SetHealth("","",0);
		}				
		return ret;
	}
	
	void SetLifeTimeZed(float t){
		m_LifeTimeZed = t;
	}
	
		
	override bool FightAttackLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{
		
		
		if ( GetND().GetMS().GetOptoinsTrader().KillZombiesWhileAttackAtTrader )
		{
			m_ActualTarget = pInputController.GetTargetEntity();
		
			PlayerBase player;
			
			if ( Class.CastTo( player, m_ActualTarget) && !player.GetRP().IsAllowedDamage() )
			{
				m_AllTargetObjects.Clear();
				SetHealth01("","",0);
				
				return false;
			}
		}
		
		return super.FightAttackLogic( pCurrentCommandID,  pInputController,  pDt);

		
	}	
	
	override bool ResistContaminatedEffect()
	{
		bool  isResisted = super.ResistContaminatedEffect();
		
		if ( GetND().GetMS().GetOptionsRadiation().ZombiesResistToxicity )
		{		
			return true;
		}	
		return isResisted;
	}

}
		