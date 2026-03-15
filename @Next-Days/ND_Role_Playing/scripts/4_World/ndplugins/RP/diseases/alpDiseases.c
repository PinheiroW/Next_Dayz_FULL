/**
 * @class   alpDisease
 * @brief   Classe base para todo o sistema de doenças e tratamentos do Next Days
 * Auditado em: 2026 - Foco em Blindagem de Herança e Otimização
 */
class alpDisease
{
	PlayerBase alp_Player;
	protected int alp_ID;
	protected bool alp_Enable;
	protected bool alp_CanBeCured;
	
	protected string alp_Name;
	protected string alp_Icon;
	
	void alpDisease(PlayerBase player, int id, string name, bool show, bool state, string icon)
	{
		alp_Player = player;
		alp_ID = id;
		alp_Name = name;
		alp_Enable = show;
		alp_CanBeCured = state;	
		alp_Icon = icon;
	}
	
	int GetID()
	{
		return alp_ID;
	}
	
	// Método a ser sobrescrito pelas filhas para aplicar a cura real
	void CureDisease()
	{
	}
	
	// Método base de verificação de infecção
	bool IsInfected()
	{
		// 1. Failsafe Massivo: Protege todas as doenças que não possuem override próprio
		if (!alp_Player || !alp_Player.GetRP()) 
		{
			return false; 
		}

		return alp_Player.GetRP().IsInfected(alp_ID);
	}
	
	bool IsEnable()
	{
		return alp_Enable;
	}
	
	bool CanBeCured()
	{
		return alp_CanBeCured;
	}	
	
	// Valor base padrão (Deve ser sobrescrito pelas filhas)
	float GetFee()
	{
		return 0;
	}
	
	// 2. Retorno simplificado (Mantém compatibilidade com multiplicadores das classes filhas)
	float GetPrice()
	{
		return GetFee();
	}
	
	string GetName()
	{
		return alp_Name;
	}
	
	string GetIcon()
	{
		return alp_Icon;
	}
}

// ---------------------------------------------------------
// Esqueleto da Doença de Febre (Placeholder para o futuro)
// ---------------------------------------------------------
class alpFever extends alpDisease
{
	/* override float GetFee()
	{
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees()) return 0.0; 
		return GetND().GetMS().GetTrader().GetFees().Fever;
	}
	*/

	override void CureDisease()
	{
		/* if (!alp_Player) return;
		if (GetGame().IsServer())
		{
			// Lógica de remoção de febre aqui (Ex: agente de influenza ou cholera secundário)
		}
		*/
	}
}