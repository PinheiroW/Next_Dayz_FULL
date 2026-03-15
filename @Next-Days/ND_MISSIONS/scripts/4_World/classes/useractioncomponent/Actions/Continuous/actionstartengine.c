/**
 * actionstartengine.c
 * * AÇÃO CONTÍNUA (LIGAR MOTOR DO VEÍCULO) - Módulo ND_MISSIONS
 * Exige que o jogador segure a chave correta (ou chave de admin) nas mãos para ligar o carro.
 */

modded class ActionStartEngine: ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		// OTIMIZAÇÃO (Early Exit): Se a condição base do jogo não for atendida 
		// (ex: carro sem bateria, sem combustível, ou motor arruinado), aborta instantaneamente.
		if (!super.ActionCondition(player, target, item))
		{
			return false;
		}
		
		// OTIMIZAÇÃO: Segurança primária para garantir que a entidade existe
		if (!player) 
		{
			return false;
		}
		
		// OTIMIZAÇÃO E SEGURANÇA: Leitura protegida das opções globais de veículos
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetVehicleOptions())
		{
			// LÓGICA MANTIDA: Se a opção de exigir chave estiver DESLIGADA no JSON, permite ligar direto
			if (!GetND().GetRP().GetVehicleOptions().RequiredKeyToStartEngine) 
			{
				return true;
			}
		}
		else
		{
			// Fallback de Segurança: Se os módulos de configuração falharem por desync, 
			// permite a partida para evitar travamentos ou perda de veículos do jogador.
			return true; 
		}
		
		CarScript car;
		alp_CarKey_Base key;
		
		// LÓGICA MANTIDA E OTIMIZADA: Verifica se o jogador está dentro do carro e segurando uma chave
		// Class.CastTo já atua como uma validação segura para GetParent() e GetItemInHands()
		if (Class.CastTo(car, player.GetParent()) && Class.CastTo(key, player.GetItemInHands()))
		{
			// Verifica se o ID da chave corresponde ao carro OU se é uma chave de Admin (Curinga)
			if (car.GetAlpCarID() == key.GetAlpKeyID() || key.IsAdminKey())				
			{
				return true;
			}
		}
		
		// Se chegou aqui, a opção de chave é obrigatória, mas o jogador não a possui nas mãos ou tem a chave errada
		return false;
	}
}; // Fechamento de classe padronizado