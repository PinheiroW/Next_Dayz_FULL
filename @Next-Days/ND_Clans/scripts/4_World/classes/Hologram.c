modded class Hologram
{
	override void EvaluateCollision(ItemBase action_item = null)
	{	
		// 1. OBRIGATÓRIO: Chamar o comportamento vanilla PRIMEIRO.
		// Isso garante que o jogo calcule colisões físicas reais (paredes, árvores, inclinação do terreno).
		super.EvaluateCollision(action_item);

		// 2. Proteções de Null Check para referências críticas do Holograma
		if (!m_Player || !m_Projection) return;

		EntityAI ent = action_item;
		if (!ent && m_Player.GetHumanInventory())
		{
			ent = m_Player.GetHumanInventory().GetEntityInHands();
		}
		
		if (ent && ent.IsItemBase()) 
		{
			// Verifica se está sobre a água
			bool is_surface_water = IsSurfaceWater(m_Projection.GetPosition());	
			
			// 3. Aplicação de Regras Restritivas (Território/Clã)
			// Se o jogador NÃO tem permissão OU está tentando colocar na água:
			if (is_surface_water || !m_Player.IsAuthorized(ItemBase.Cast(ent)))
			{
				// Forçamos a colisão para TRUE, impedindo o placement (bloqueia o holograma de ficar verde)
				SetIsColliding(true);
			}
			
			// NOTA TÉCNICA DE SEGURANÇA:
			// Se o jogador É autorizado, nós NÃO forçamos SetIsColliding(false). 
			// Nós deixamos a variável com o valor que o super.EvaluateCollision determinou. 
			// Assim, evitamos que o player construa itens dentro de pedras ou paredes.
		}
	}
}