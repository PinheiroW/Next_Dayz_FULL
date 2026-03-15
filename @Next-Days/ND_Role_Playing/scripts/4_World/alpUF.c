/**
 * @class   alpUF
 * @brief   Alpepino Useful Functions - Funções utilitárias globais do RPG
 * Auditado em: 2026 - Foco em Segurança de Ponteiro e Estabilidade de Config
 */
modded class alpUF
{
	/**
	 * @brief Calcula a velocidade metabólica de fadiga baseada no movimento
	 * @param movement_speed: 1 (Walk), 2 (Jog), 3 (Sprint), 0 (Idle)
	 */
	static float GetTirednessMetabolicSpeed(int movement_speed)
	{
		float speed = 0;

		// 1. BLINDAGEM: Verifica se toda a cadeia de plugins está pronta
		if (!GetND() || !GetND().GetRP()) return 0;

		auto fatigueOpts = GetND().GetRP().GetFatigue();
		if (!fatigueOpts) return 0;

		// 2. LÓGICA DE MOVIMENTO
		switch (movement_speed)
		{
			case 1: // Walk
				speed = fatigueOpts.FatigueWalk;
				break;
				
			case 2: // Jog
				speed = fatigueOpts.FatigueJog;
				break;
				
			case 3: // Sprint
				speed = fatigueOpts.FatigueSprint;
				break;
				
			default: // Idle ou outros
				speed = 0;
				break;
		}

		// 3. ADIÇÃO DA TAXA BASAL (Cansaço parado)
		speed += fatigueOpts.FatigueBasal;
		
		return speed;	
	}
};