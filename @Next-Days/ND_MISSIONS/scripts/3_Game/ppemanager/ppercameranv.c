/**
 * ppercameranv.c
 * * GERENCIADOR DE EFEITOS PÓS-PROCESSADOS (PPE) PARA VISÃO NOTURNA
 * Adiciona distorções visuais de radiação aos modos de Night Vision.
 */

modded class PPERequester_CameraNV extends PPERequester_GameplayBase
{
	// IDs de Modos Personalizados (Radiação + NV)
	static const int NV_DEFAULT_OPTICS_RAD_LOW 			= 11;
	static const int NV_DEFAULT_OPTICS_RAD_MEDIUM 		= 12;
	static const int NV_DEFAULT_OPTICS_RAD_HIGH 		= 13;
	static const int NV_DEFAULT_OPTICS_RAD_VERYHIGH 	= 14;

	static const int NV_DEFAULT_GLASSES_RAD_LOW 		= 21;
	static const int NV_DEFAULT_GLASSES_RAD_MEDIUM 		= 22;
	static const int NV_DEFAULT_GLASSES_RAD_HIGH 		= 23;
	static const int NV_DEFAULT_GLASSES_RAD_VERYHIGH 	= 24;	

	static const int NV_DAYTIME_RAD_LOW 				= 31;
	static const int NV_DAYTIME_RAD_MEDIUM 				= 32;
	static const int NV_DAYTIME_RAD_HIGH 				= 33;
	static const int NV_DAYTIME_RAD_VERYHIGH 			= 34;	

	override int SetNVMode(int mode)
	{
		switch (mode)
		{
			// --- MODOS VANILLA (Repassados para a classe base) ---
			case NV_NO_BATTERY:
			case NV_DEFAULT_OPTICS:
			case NV_DEFAULT_GLASSES:
			case NV_PUMPKIN:
			case NV_TRANSITIVE:
				return super.SetNVMode(mode);

			// --- MODOS DE RADIAÇÃO: ÓPTICAS ---
			case NV_DEFAULT_OPTICS_RAD_LOW:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 0.5, PPEExposureNative.L_0_NVG_OPTICS, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_LOW, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_LOW, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_LIGHT_MULT, false, 1.0, PPELightIntensityParamsNative.L_0_NVG, PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_NOISE_MULT, false, 1.0, PPELightIntensityParamsNative.L_1_NVG, PPOperators.HIGHEST);
				return 1;

			case NV_DEFAULT_OPTICS_RAD_MEDIUM:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 1.0, PPEExposureNative.L_0_NVG_OPTICS, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_MEDIUM, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_MEDIUM, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_LIGHT_MULT, false, 2.0, PPELightIntensityParamsNative.L_0_NVG, PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_NOISE_MULT, false, 1.0, PPELightIntensityParamsNative.L_1_NVG, PPOperators.HIGHEST);
				return 1;

			case NV_DEFAULT_OPTICS_RAD_HIGH:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 2.0, PPEExposureNative.L_0_NVG_OPTICS, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_HIGH, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_HIGH, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_LIGHT_MULT, false, 3.0, PPELightIntensityParamsNative.L_0_NVG, PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_NOISE_MULT, false, 1.0, PPELightIntensityParamsNative.L_1_NVG, PPOperators.HIGHEST);
				return 1;

			case NV_DEFAULT_OPTICS_RAD_VERYHIGH:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 3.0, PPEExposureNative.L_0_NVG_OPTICS, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_VERYHIGH, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_VERYHIGH, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_LIGHT_MULT, false, 4.0, PPELightIntensityParamsNative.L_0_NVG, PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS, PPELightIntensityParamsNative.PARAM_NOISE_MULT, false, 1.0, PPELightIntensityParamsNative.L_1_NVG, PPOperators.HIGHEST);
				return 1;

			// --- MODOS DE RADIAÇÃO: ÓCULOS ---
			case NV_DEFAULT_GLASSES_RAD_LOW:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 0.2, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_LOW, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_LOW, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			case NV_DEFAULT_GLASSES_RAD_MEDIUM:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 0.4, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_MEDIUM, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_MEDIUM, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			case NV_DEFAULT_GLASSES_RAD_HIGH:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 0.6, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_HIGH, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_HIGH, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			case NV_DEFAULT_GLASSES_RAD_VERYHIGH:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 0.8, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_VERYHIGH, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_VERYHIGH, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			// --- MODOS DE RADIAÇÃO: DIA (Luz do dia) ---
			case NV_DAYTIME_RAD_LOW:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 0.5, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_LOW, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_LOW, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			case NV_DAYTIME_RAD_MEDIUM:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 1.0, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_MEDIUM, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_MEDIUM, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			case NV_DAYTIME_RAD_HIGH:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 1.5, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_HIGH, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_HIGH, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;

			case NV_DAYTIME_RAD_VERYHIGH:
				SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {0.0, 1.0, 0.0, 0.0}, PPEGlow.L_23_NVG, PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE, PPEExposureNative.PARAM_INTENSITY, false, 2.0, PPEExposureNative.L_0_NVG_GOGGLES, PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_SHARPNESS, false, ALP_SHARPNESS_VERYHIGH, PPEFilmGrain.L_1_TOXIC_TINT, PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain, PPEFilmGrain.PARAM_GRAINSIZE, false, ALP_GRAINSIZE_VERYHIGH, PPEFilmGrain.L_2_TOXIC_TINT, PPOperators.SET);
				return 1;
		}

		// Fallback para qualquer outro modo não identificado
		return super.SetNVMode(mode);
	}
}