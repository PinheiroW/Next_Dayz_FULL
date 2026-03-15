/**
 * @class   alpNPC
 * @brief   Gerencia a interação moral e disponibilidade de serviços de NPCs no Next Days
 * Auditado em: 2026 - Foco em Correção de Bitmask e Lógica de Alinhamento
 */
modded class alpNPC : PlayerBase
{
	// 1. Verificação de Serviços (Erro de Tipagem Corrigido)
	bool CanMakeMedicalExamination()
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				// CRÍTICO: 'setting' DEVE ser int. Se for bool, o bitmask falha silenciosamente.
				int setting = stock.EnabledInteractions; 
				
				// Retorna true se a flag MEDICAL estiver presente no bitmask
				return (setting & alpNPC_AVAILABLE_MENU.MEDICAL) != 0;			
			}
		}
		return false;	
	}
	
	// 2. Sistema de Diálogo baseado em Reputação
	override bool CanSpeakWithMe(PlayerBase player)
	{
		// Failsafe de segurança: NPCs recebem muitos cliques, proteja os ponteiros.
		if (!player || !player.GetSyncData() || !player.GetRP()) return false;

		int role = 0; // 0 = Neutro (Padrão)

		// Avaliação direta e justa do papel do jogador
		if ( player.GetRP().IsHero() )
		{
			role = 1; // Herói
		}
		else if ( player.GetRP().IsBandit() )
		{
			role = 2; // Bandido
		}
		
		return CheckCharacterRole(role);
	}
	
	// 3. Validação de permissão do NPC
	bool CheckCharacterRole(int role)
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				int setting = stock.RequiredCharacterTraits;
				
				// Se setting for 0 (aceita todos) ou bater com o role do jogador, permite.
				return ( setting == 0 || setting == role );
			}
		}
		
		// Se não há configuração de estoque, assume que o NPC fala com qualquer um
		return true;			
	}		
}