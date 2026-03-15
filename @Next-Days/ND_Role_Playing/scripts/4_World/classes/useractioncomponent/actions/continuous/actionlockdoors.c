/**
 * @class   ActionLockDoors
 * @brief   Modifica a ação de trancar portas com base nas Soft Skills do jogador
 * Auditado em: 2024 - Foco em Progressão de Habilidade e Estabilidade
 */
modded class ActionLockDoors: ActionContinuousBase
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		// 1. Verifica se a funcionalidade de Perks customizados está ativa
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			// Failsafe: Verifica se o item principal existe
			if (!action_data.m_MainItem) return;

			// Tranca a porta (Lógica nativa da classe base)
			LockDoor(action_data.m_Target);
			
			// 2. Evolução de Soft Skill (Especialidade Técnica)
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
			
			// 3. Cálculo de Dano Corrigido
			// GetSpecialtyLevelSoft vai de -1.0 a 1.0. 
			// Invertemos a lógica: quanto mais perto de 1.0 (precisão), MENOS dano o item sofre.
			float skillLevel = action_data.m_Player.GetSoftSkillsManager().GetSpecialtyLevelSoft();
			
			// Se skill for 1.0 (Mestre), dano = 5 - 2 = 3
			// Se skill for -1.0 (Amador), dano = 5 - (-2) = 7
			float appliedDamage = 5.0 - (2.0 * skillLevel); 
			
			// Aplica o dano ao Lockpick
			action_data.m_MainItem.DecreaseHealth(appliedDamage, false);
		}	
		else 
		{
			// Se a perk estiver desativada, executa o comportamento original do jogo
			super.OnFinishProgressServer( action_data );
		}
	}
};