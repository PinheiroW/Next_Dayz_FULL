/**
 * @class   MorphineMdfr
 * @brief   Modificador de Morfina (Next Days) - Aumenta a duração e integra ao RPG
 * Auditado em: 2024 - Foco em Compatibilidade Vanilla e Feedback Visual
 */
modded class MorphineMdfr: ModifierBase
{
	// Redefinição do tempo de vida para 5 minutos (300s)
	const int ND_MORPHINE_LIFETIME = 300;

	override void Init()
	{
		super.Init();
		
		m_TrackActivatedTime    = true;
		m_IsPersistent          = true;
		m_ID                    = eModifiers.MDF_MORPHINE;
		
		// Sobrescreve o tempo definido na classe base
		// No DayZ vanilla, o lifetime é controlado pelo m_Lifetime
		// m_Lifetime é uma variável da ModifierBase
	}

	override protected void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		// Ativa o ícone de pílulas no HUD para indicar efeito ativo
		if (player && player.GetNotifiersManager())
		{
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
		}
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		// Desativa o ícone de pílulas
		if (player && player.GetNotifiersManager())
		{
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
		}
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		// Garante que o efeito dure os 300 segundos definidos
		return (GetAttachedTime() >= ND_MORPHINE_LIFETIME);
	}
};