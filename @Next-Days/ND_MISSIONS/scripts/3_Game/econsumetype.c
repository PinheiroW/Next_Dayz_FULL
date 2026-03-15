/**
 * econsumetype.c
 * * DEFINE TIPOS DE CONSUMO PARA O AMBIENTE - Módulo ND_MISSIONS
 * Define identificadores para fontes de água contaminada (poços e lagoas).
 */

/*
// Referência original para Namalsk (Preservado conforme lógica do mod)
enum alpeConsumeType
{
	ENVIRO_POND_CONTAMINED,
	ENVIRO_WELL_CONTAMINED,
	ENVIRO_POND_CONTAMINED_FREEZING,
	ENVIRO_SNOW_CONTAMINED_FROZEN,	
};
*/

// CORREÇÃO: Removida herança inválida ': EConsumeType' e adicionado ';' no fechamento
enum alpeConsumeType
{
	ENVIRO_POND_CONTAMINED,
	ENVIRO_WELL_CONTAMINED,
};