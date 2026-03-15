/**
 * @class   SoftSkillsManager
 * @brief   Gerencia a persistência e evolução das habilidades de Precisão e Força
 * Auditado em: 2026 - Foco em Estabilidade Matemática e Persistência de Dados
 */
modded class SoftSkillsManager
{	
	float alp_SpecialtyLevelSoft;
	float alp_SpecialtyLevelHard;
	
	override void InitSpecialty( float specialty_level )
	{
		// 1. Failsafe de segurança para o objeto jogador
		if (!m_Player) return;

		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			// Carrega os valores salvos nos Stats do banco de dados do Next Days
			float soft = m_Player.GetStatPerkSoft().Get();
			float hard = m_Player.GetStatPerkRough().Get();
			
			SetSpecialtyLevelSoft( soft );
			SetSpecialtyLevelHard( hard );
			
			SynchSpecialtyLevel();	
		}
		else
		{
			super.InitSpecialty( specialty_level );	
		}
	}	

	// 2. Encapsulamento de Atributos
	void SetSpecialtyLevelSoft( float specialty_level )
	{
		alp_SpecialtyLevelSoft = Math.Clamp(specialty_level, -1.0, 1.0);
	}	

	void SetSpecialtyLevelHard( float specialty_level )
	{
		alp_SpecialtyLevelHard = Math.Clamp(specialty_level, -1.0, 1.0);
	}

	override float GetSpecialtyLevelSoft()
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
			return alp_SpecialtyLevelSoft;
		
		return super.GetSpecialtyLevelSoft();
	}

	// 3. Evolução de Precisão (Soft Skill Azul)
	override float AddExponentialPrecise( float specialty_weight )
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{	
			m_UserActionsCounter -= 1;
	
			// Proteção contra contador Zero (Evita divisão por zero no Sqrt)
			int safeCounter = Math.AbsInt( m_UserActionsCounter );
			if (safeCounter == 0) safeCounter = 1; 
			
			float adjusted_weight = specialty_weight / Math.Sqrt( safeCounter );
			
			alp_SpecialtyLevelSoft += adjusted_weight;
			alp_SpecialtyLevelSoft = Math.Clamp( alp_SpecialtyLevelSoft, -1.0, 1.0 );
	
			SetLastUAValue( adjusted_weight );
			return alp_SpecialtyLevelSoft;
		}
		
		return super.AddExponentialPrecise( specialty_weight );	
	}	
	
	// 4. Evolução de Força (Soft Skill Laranja)
	override float AddExponentialRough( float specialty_weight )
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{	
			m_UserActionsCounter += 1;
				
			int safeCounter = Math.AbsInt( m_UserActionsCounter );
			if (safeCounter == 0) safeCounter = 1;

			float adjusted_weight = specialty_weight / Math.Sqrt( safeCounter );
		
			alp_SpecialtyLevelSoft += adjusted_weight;
			alp_SpecialtyLevelSoft = Math.Clamp( alp_SpecialtyLevelSoft, -1.0, 1.0 );

			SetLastUAValue( adjusted_weight );
			return alp_SpecialtyLevelSoft;
		}
		
		return super.AddExponentialRough( specialty_weight );
	}
};