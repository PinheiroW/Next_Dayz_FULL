/**
 * contaminatedarea_dynamic.c
 * * MODDED CLASS (ZONAS CONTAMINADAS DINÂMICAS) - Módulo ND_MISSIONS
 * Gerencia o comportamento de ataques de artilharia química e zonas de gás dinâmicas.
 */

modded class EffectArea : House
{
	// Método gancho para extensões do mod Next-Days
	void OnCreateALP()
	{}
}

// Classe da área contaminada dinâmica (ataque de artilharia)
modded class ContaminatedArea_Dynamic : EffectArea
{
	const float ARTILLERY_SHELL_SPEED = 250;	
	
	override void EEInit()
	{
		super.EEInit();
		// Dispara a inicialização customizada
		OnCreateALP();		
	}	
	
	// Coordenadas fixas de onde os sons de artilharia podem originar (fora do mapa)
	ref array<vector> alp_ArtilleryPositions = {
		"-500.00 165.00 5231.69",
		"-500.00 300.00 9934.41",
		"10406.86 192.00 15860.00",
		"4811.75 370.00 15860.00",
		"-500.00 453.00 15860.00"
	};	
		
	override void OnCreateALP()
	{
		// Sincroniza com o sistema de efeitos visuais e pós-processamento (PPE)
		if ( m_PPERequesterType == "" )
		{
			m_PPERequesterType = "PPERequester_ContaminatedAreaL3";
		}
		
		// Lógica sonora de disparo de artilharia
		if ( GetGame().IsServer() )
		{
			int randIndex = Math.RandomInt(0, alp_ArtilleryPositions.Count());
			vector pos = alp_ArtilleryPositions.Get(randIndex);
			
			// Aqui poderia ser disparado um RemoteSync para som de ambiente
		}
	}

	// Carrega as configurações da zona vindas dos parâmetros de spawn
	override void SetupZoneData(  EffectAreaParams params )
	{
		super.SetupZoneData( params );
		
		if ( !params ) return;

		// Sincronização de dimensões e tipos de partículas
		if ( params.m_ParamRadius > 0 )
			m_Radius = params.m_ParamRadius;
			
		if ( params.m_ParamPosHeight > -1 )
			m_PositiveHeight = params.m_ParamPosHeight;
			
		if ( params.m_ParamNegHeight > -1 )
			m_NegativeHeight = params.m_ParamNegHeight;
		
		m_InnerRings = params.m_ParamInnerRings;
		
		if ( params.m_ParamInnerSpace > -1 )
			m_InnerSpacing = params.m_ParamInnerSpace;
		
		m_OuterRingToggle = params.m_ParamOuterToggle;
		
		if ( params.m_ParamOuterSpace > -1 )
			m_OuterSpacing = params.m_ParamOuterSpace;
			
		m_OuterRingOffset = params.m_ParamOuterOffset;
		
		if ( params.m_ParamVertLayers > 0 )
			m_VerticalLayers = params.m_ParamVertLayers;
			
		if ( params.m_ParamVerticalOffset > 0 )
			m_VerticalOffset = params.m_ParamVerticalOffset;
		
		// IDs de Partículas (Gás/Fumaça)
		m_ParticleID = params.m_ParamPartId;
		m_AroundParticleID = params.m_ParamAroundPartId;
		m_TinyParticleID = params.m_ParamTinyPartId;
		
		if ( params.m_ParamPpeRequesterType != "" )
		{
			m_PPERequesterType = params.m_ParamPpeRequesterType;
		}
	}
}