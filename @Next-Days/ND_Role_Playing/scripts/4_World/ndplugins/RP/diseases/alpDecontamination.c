/**
 * @class   alpDecontaminationDisease
 * @brief   Gerencia a cobrança e o processo de Descontaminação Química/Radioativa no Next Days
 * Auditado em: 2026 - Foco em Failsafes e Performance de UI
 */
class alpDecontaminationDisease extends alpDisease
{
	override float GetFee()
	{
		// 1. Failsafe contra falhas na cadeia do Trader ou Configs
		if (!GetND() || !GetND().GetMS() || !GetND().GetMS().GetTrader() || !GetND().GetMS().GetTrader().GetFees())
		{
			return 0.0; 
		}

		return GetND().GetMS().GetTrader().GetFees().Decontamination;
	}

	override bool IsInfected()
	{
		// 2. Failsafe Duplo: Garante que o jogador e o módulo RP existem
		if (!alp_Player || !alp_Player.GetRP()) 
		{
			return false; // Se os dados não carregaram, previne que o menu mostre a opção
		}
		
		return !alp_Player.GetRP().WasDecontamined();
	}
	
	override void CureDisease()
	{
		// 3. Segurança: Tratamentos profundos devem ser estritamente no Servidor
		if (!alp_Player || !alp_Player.GetRP()) return;

		if (GetGame().IsServer())
		{
			alp_Player.GetRP().Decontamination(true);
		}
	}
}