/**
 * ParticleList.c
 * * REGISTRO DE EFEITOS VISUAIS (PARTÍCULAS) - Módulo ND_MISSIONS
 * Define novas partículas customizadas e ganchos de explosões para itens do mod.
 */

modded class ParticleList
{
	// Registro de partículas customizadas localizadas nos dados do mod
	static const int ALP_SPAD      = RegisterParticle("ND_MISSIONS/data/spad/", "spad");
	static const int ALP_SPAD_BIG  = RegisterParticle("ND_MISSIONS/data/spad/", "spad_big");
	static const int ALP_SPAD_FAST = RegisterParticle("ND_MISSIONS/data/spad/", "spad_fast");
	static const int ALP_SPARKS    = RegisterParticle("ND_MISSIONS/data/sparks/", "alp_sparks");
};

class alp_DynamiteExplosion : EffectParticle
{
	void alp_DynamiteExplosion()
	{
		// Vincula o efeito visual à explosão de mina terrestre padrão do jogo
		SetParticleID(ParticleList.EXPLOSION_LANDMINE);
	}
}; // Adicionado ponto e vírgula obrigatório