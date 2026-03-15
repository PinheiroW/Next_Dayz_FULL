/**
 * @class   alpExpandedInteraction
 * @brief   Gerencia taxas de interações expandidas (Médico e Rumores)
 * Auditado em: 2024 - Foco em Performance e Segurança Econômica
 */

class alpSpreadRumoursFees 
{
	int NegativeGossipCost = 10000;
	int PositiveGossipCost = 10000;
	int NegativeGossipGain = 1000;
	int PositiveGossipGain = 1000;
}

class alpMedicalFees 
{
	bool EnabledBloodTest		= true;
	bool EnabledCloneDNA		= true;
	
	int Fee = 500;
	int Bleeding = 500;
	int BrainSick = 25000;
	int Commoncold = 5000;
	int Influenza = 10000;	
	int Cholera = 15000;
	int Salmonella = 10000;
	int WoundInfectionL1 = 5000;
	int WoundInfectionL2 = 10000;
	int FoodPoisoning = 5000;
	int ChemicalPoisoningL1 = 5000;
	int ChemicalPoisoningL2 = 10000;
	int ChemicalPoisoningL3 = 15000;		
	int BrokenArm = 10000;
	int BrokenLeg = 10000;
	int RadiationSick = 100000;
	int FrostbiteSick = 100000;
	
	int Decontamination = 2000;
	
	int SaveDNA = 100000;
	int RecoverDNA = 100000;
}

class alpExpandedInteraction 
{
	int ConfigVersion = 1; // Controle de versão
	bool EnableSales = true;
	
	ref alpMedicalFees MedicalFees = new alpMedicalFees;
	ref alpSpreadRumoursFees SpreadRumoursFees = new alpSpreadRumoursFees;
	
	alpMedicalFees GetMedicalFees(float rate, float coef, float sale)
	{
		alpMedicalFees fees = new alpMedicalFees;
		
		if (!EnableSales) sale = 0;
		
		// Segurança: Impede que o desconto seja superior a 100% ou menor que 0
		sale = Math.Clamp(sale, 0, 1);
		
		// Otimização: Pre-calculo do multiplicador final
		float finalMultiplier = rate * coef * (1.0 - sale);
		
		fees.EnabledBloodTest = MedicalFees.EnabledBloodTest;
		fees.EnabledCloneDNA = MedicalFees.EnabledCloneDNA;
		
		fees.Fee = MedicalFees.Fee * finalMultiplier;
		fees.Bleeding = MedicalFees.Bleeding * finalMultiplier;
		fees.BrainSick = MedicalFees.BrainSick * finalMultiplier;
		fees.Commoncold = MedicalFees.Commoncold * finalMultiplier;
		fees.Influenza = MedicalFees.Influenza * finalMultiplier;
		fees.Cholera = MedicalFees.Cholera * finalMultiplier;
		fees.Salmonella = MedicalFees.Salmonella * finalMultiplier;
		fees.WoundInfectionL1 = MedicalFees.WoundInfectionL1 * finalMultiplier;
		fees.WoundInfectionL2 = MedicalFees.WoundInfectionL2 * finalMultiplier;
		fees.FoodPoisoning = MedicalFees.FoodPoisoning * finalMultiplier;
		fees.ChemicalPoisoningL1 = MedicalFees.ChemicalPoisoningL1 * finalMultiplier;
		fees.ChemicalPoisoningL2 = MedicalFees.ChemicalPoisoningL2 * finalMultiplier;
		fees.ChemicalPoisoningL3 = MedicalFees.ChemicalPoisoningL3 * finalMultiplier;
		fees.BrokenArm = MedicalFees.BrokenArm * finalMultiplier;
		fees.BrokenLeg = MedicalFees.BrokenLeg * finalMultiplier;
		fees.RadiationSick = MedicalFees.RadiationSick * finalMultiplier;
		fees.FrostbiteSick = MedicalFees.FrostbiteSick * finalMultiplier;
		fees.Decontamination = MedicalFees.Decontamination * finalMultiplier;
		fees.SaveDNA = MedicalFees.SaveDNA * finalMultiplier;
		fees.RecoverDNA = MedicalFees.RecoverDNA * finalMultiplier;
				
		return fees;	
	}	
	
	alpSpreadRumoursFees GetRumoursFees(float rate, float coef, float sale)
	{
		alpSpreadRumoursFees fees = new alpSpreadRumoursFees;
		
		if (!EnableSales) sale = 0;

		sale = Math.Clamp(sale, 0, 1);
		float finalMultiplier = rate * coef * (1.0 - sale);
		
		fees.NegativeGossipCost = SpreadRumoursFees.NegativeGossipCost * finalMultiplier;
		fees.PositiveGossipCost = SpreadRumoursFees.PositiveGossipCost * finalMultiplier;
		fees.NegativeGossipGain = SpreadRumoursFees.NegativeGossipGain * finalMultiplier;
		fees.PositiveGossipGain = SpreadRumoursFees.PositiveGossipGain * finalMultiplier;
				
		return fees;	
	}	
}