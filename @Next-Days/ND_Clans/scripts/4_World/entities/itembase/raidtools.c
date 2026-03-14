modded class Hacksaw
{
	override void SetActions()
	{
		super.SetActions();
		
		// Registra a ação de desmontar/empacotar o Plot Pole na Hacksaw
		AddAction(alpActionDisassemblePlotPole);
	}
}