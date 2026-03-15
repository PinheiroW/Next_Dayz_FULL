/**
 * @class   alpTirednessNotfr
 * @brief   Gerencia a exibição visual da fadiga (setas de tendência) na HUD
 * Auditado em: 2024 - Foco em Segurança de Inicialização e Dinâmica de Configuração
 */
enum alpeNotifiers : eNotifiers
{
	NTF_TIREDNESS,
}

class alpTirednessNotfr: NotifierBase
{
	private float m_ObservedValue;
	
	void alpTirednessNotfr(NotifiersManager manager)
	{
		// Notificadores não usam Init() como modificadores, o construtor é o lugar certo
		m_Active = true; 
	}

	override int GetNotifierType()
	{
		return alpeNotifiers.NTF_TIREDNESS;
	}

	// Helpers para obter thresholds com segurança
	protected float GetDecMed() 
	{
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetFatigue())
			return -0.01 * (GetND().GetRP().GetFatigue().FatigueWalk / 0.005);
		return -0.01;
	}

	protected float GetDecHigh() 
	{
		if (GetND() && GetND().GetRP() && GetND().GetRP().GetFatigue())
			return -0.018 * (GetND().GetRP().GetFatigue().FatigueJog / 0.008);
		return -0.018;
	}

	override void DisplayTendency(float delta)
	{
		int tendency = CalculateTendency(delta, 0, GetDecMed(), GetDecHigh(), 0.05, 0.2);
		
		// DS_TENDENCY_X são constantes nativas do DayZ para as setas da HUD
		// 1 seta, 2 setas, 3 setas, etc.
		DisplayElementTendency notifier_tendency = DisplayElementTendency.Cast(GetVirtualHud().GetElement(eDisplayElements.DELM_TENDENCY_FATIGUE));
		
		if (notifier_tendency)
		{
			notifier_tendency.SetTendency(tendency);
		}
	}

	override void OnTick(float deltaT)
	{
		if (!m_Player) return;

		// Obtém o valor atual da fadiga para comparar no próximo tick
		float current_value = m_Player.GetStatFatigue().Get();
		
		// A variação (delta) entre o valor antigo e o novo define a seta
		float delta = current_value - m_ObservedValue;
		
		DisplayTendency(delta);
		
		m_ObservedValue = current_value;
	}

	override void HideBadge()
	{
		// Implementação opcional para esconder o ícone se necessário
	}

	override void DisplayBadge()
	{
		// Implementação opcional para mostrar ícones especiais (ex: exclamação)
	}
};