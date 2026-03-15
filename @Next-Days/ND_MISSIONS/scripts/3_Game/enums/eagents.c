/**
 * eagents.c
 * * Define novos agentes de transmissão para o sistema de saúde.
 * ATENÇÃO: Todos os números devem ser potências de 2 (2^x).
 * Máximo de 32 agentes individuais para compatibilidade com bitmask da engine.
 */

/*
// Referência dos Agentes Vanilla (eAgents)
enum eAgents
{
	CHOLERA 		= 1,
	INFLUENZA 		= 2,
	SALMONELLA		= 4,
	BRAIN 			= 8,
	FOOD_POISON		= 16,
	CHEMICAL_POISON	= 32,
	WOUND_AGENT		= 64,
	NERVE_AGENT		= 128
};
*/

// Agentes personalizados do módulo Next Dayz
enum alpeAgents
{
	DRUNKENNESS		= 1024,
	RADIATION		= 2048
}; // Adicionado fechamento correto do enum