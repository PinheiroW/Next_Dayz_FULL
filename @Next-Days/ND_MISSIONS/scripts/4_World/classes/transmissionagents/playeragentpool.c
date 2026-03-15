/**
 * playeragentpool.c
 * * GERENCIADOR DE AGENTES DE DOENÇA DO JOGADOR - Módulo ND_MISSIONS
 * Controla a injeção de agentes de radiação e químicos, aplicando resistências RPG naturais.
 */

modded class PlayerAgentPool
{
	override void AddAgent(int agent_id, float count)
	{
		int max_count = m_PluginTransmissionAgents.GetAgentMaxCount(agent_id);
		
		if (count > 0)
		{			
			float resistance;
			
			// OTIMIZAÇÃO E SEGURANÇA: Verificação em cascata para evitar Null Pointer Exception
			if (m_Player && m_Player.GetRP() && m_Player.GetRP().GetProtection())
			{
				switch (agent_id)
				{
					case alpeAgents.RADIATION:
					{
						resistance = m_Player.GetRP().GetProtection().GetNaturalResistanceAgainstRadiation();
						
						// Reduz a dose de radiação baseada na resistência RPG (Imunidade passiva)
						count = count - (count * resistance);
						
						if (count > 0)
						{
							// LÓGICA MANTIDA: Evolui progressivamente a habilidade de imunidade à radiação
							m_Player.GetRP().ImproveRadiationNaturalResistance(count);
						}
						break;
					}
					case eAgents.CHEMICAL_POISON:
					{
						resistance = m_Player.GetRP().GetProtection().GetNaturalResistanceAgainstChemical();
						
						// Reduz a dose do veneno químico baseada na resistência RPG
						count = count - (count * resistance);
						
						if (count > 0)
						{
							// LÓGICA MANTIDA: Evolui progressivamente a habilidade de resistência química
							m_Player.GetRP().ImproveToxicNaturalResistance(count);
						}					
						break;
					}		
				}
			}
		}
				
		// LÓGICA MANTIDA E OTIMIZADA: Processamento de inserção ou atualização de valores da doença
		if (!m_VirusPool.Contains(agent_id))
		{
			// Só insere um novo agente no sistema se após resistir ainda houver contaminação
			if (count > 0)
			{
				SetAgentCount(agent_id, count);
			}
		}
		else
		{
			// Se já possui a doença, soma a contaminação existente com a nova dose (mesmo que 0)
			float new_value = m_VirusPool.Get(agent_id) + count;
			SetAgentCount(agent_id, new_value);
		}
	}
}; // Adicionado ponto e vírgula obrigatório