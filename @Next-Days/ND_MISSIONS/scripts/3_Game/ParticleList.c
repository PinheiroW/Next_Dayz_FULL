modded class ParticleList
{
	
  static const int ALP_SPAD        = RegisterParticle( "ND_MISSIONS/data/spad/", "spad" );
  static const int ALP_SPAD_BIG    = RegisterParticle( "ND_MISSIONS/data/spad/", "spad_big" );
  static const int ALP_SPAD_FAST   = RegisterParticle( "ND_MISSIONS/data/spad/", "spad_fast" );
  static const int ALP_SPARKS        = RegisterParticle( "ND_MISSIONS/data/sparks/", "alp_sparks" );
};

class alp_DynamiteExplosion : EffectParticle
{
	void alp_DynamiteExplosion()
	{
		SetParticleID(ParticleList.EXPLOSION_LANDMINE);
	}
}
