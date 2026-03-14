modded class Construction
{
	//============================================
	// Collision check
	//============================================
	//Collisions (BBox and Trigger)
	override bool IsColliding( string part_name )
	{
		// 1. OBRIGATÓRIO: Retornar a checagem nativa da Enfusion Engine.
		// Retornar 'false' incondicionalmente criava exploits massivos de empilhamento de bases.
		return super.IsColliding( part_name );
	}
}