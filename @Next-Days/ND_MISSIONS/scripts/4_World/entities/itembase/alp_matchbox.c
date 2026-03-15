/**
 * alp_matchbox.c
 * * MODDED ENTITIES (ITENS DE IGNIÇÃO) - Módulo ND_MISSIONS
 * Injeta a capacidade de detonar dinamites em diversos itens de fogo do jogo.
 */

// --- FÓSFOROS ---
modded class Matchbox 
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionIgniteDynamite);
	}	
}

// --- ISQUEIRO ---
modded class PetrolLighter 
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionIgniteDynamite);
	}	
}

// --- SINALIZADOR DE ESTRADA ---
modded class Roadflare
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionIgniteDynamite);
	}	
}

// --- KIT DE FRICÇÃO (HAND DRILL) ---
modded class HandDrillKit
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionIgniteDynamite);
	}	
}

// --- FOGÃO PORTÁTIL ---
modded class PortableGasStove
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionIgniteDynamite);
	}	
}

// --- TOCHA ---
modded class Torch
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(alpActionIgniteDynamite);
	}	
}