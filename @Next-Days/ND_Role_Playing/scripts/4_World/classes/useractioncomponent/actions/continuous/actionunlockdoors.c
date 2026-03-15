/**
 * @class   ActionUnlockDoors
 * @brief   Modifica a ação de destrancar portas integrando Soft Skills e Perks Next Days
 * Auditado em: 2024 - Foco em Recompensa de Habilidade Técnica
 */
modded class ActionUnlockDoors: ActionContinuousBase
{
	override void OnFinishProgressServer( ActionData action_data )
	{	
		// 1. Verifica se o sistema de Perks customizados está ativo
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			// Failsafe: Proteção contra item nulo
			if (!action_data.m_MainItem) return;

			// Executa a ação de destrancar
			UnlockDoor(action_data.m_Target);
			
			// 2. Evolução de Especialidade (Soft Skills)
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
			
			// 3. Cálculo de Dano Inteligente (Premiando o Especialista)
			// skillLevel varia de -1.0 (Força) a 1.0 (Precisão)
			float skillLevel = action_data.m_Player.GetSoftSkillsManager().GetSpecialtyLevelSoft();	
			
			// Nova fórmula: Base 5.0. Se mestre (1.0), reduz para 3.0. Se bruto (-1.0), aumenta para 7.0.
			float appliedDamage = 5.0 - (2.0 * skillLevel); 
			
			// Aplica o dano usando DecreaseHealth para maior compatibilidade visual no inventário
			action_data.m_MainItem.DecreaseHealth(appliedDamage, false);
		}	
		else 
		{
			// Se a perk estiver desativada, segue o fluxo padrão do jogo
			super.OnFinishProgressServer( action_data );
		}
	}
};