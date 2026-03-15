/**
 * chemicalagent.c
 * * AGENTE DE TRANSMISSÃO QUÍMICA - Módulo ND_MISSIONS
 * Modifica a velocidade de cura (die-off) baseada na resistência RPG do jogador.
 */

modded class ChemicalAgent extends AgentBase
{
	override float GetDieOffSpeedEx(PlayerBase player)
	{
		// OTIMIZAÇÃO: Validação inicial de segurança para o objeto principal
		if (!player) 
		{
			return 0;
		}
		
		// SEGURANÇA: Verificação do ModifiersManager antes de buscar os modificadores ativos
		if (player.GetModifiersManager())
		{
			if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION2) || 
				player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION3))
			{
				return 0; // Contaminação severa paralisa a cura natural
			}
		}

		// Resgata o valor base calculado pela Enfusion Engine
		float doses = super.GetDieOffSpeedEx(player);
		
		// OTIMIZAÇÃO E SEGURANÇA: Verificação da árvore de atributos de RPG
		if (player.GetRP() && player.GetRP().GetProtection())
		{
			// Multiplica a taxa de decaimento pelo bônus de resistência química natural
			doses = doses * (1.0 + player.GetRP().GetProtection().GetNaturalResistanceAgainstChemical());
		}
		
		return doses;
	}
}; // Adicionado ponto e vírgula obrigatório