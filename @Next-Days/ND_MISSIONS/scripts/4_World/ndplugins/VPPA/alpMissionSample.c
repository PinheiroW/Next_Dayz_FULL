/**
 * alpMissionSample.c
 * * MISSION TEMPLATE DEFINITION - Módulo ND_MISSIONS (VPPA/Core)
 * Define a estrutura de dados para templates de missões e configurações de IA.
 */

class alpMissionSample
{
	// --- Configurações Ativas e Probabilidade ---
	bool   active   = true;  // Define se o template pode ser selecionado pelo sistema
	float  chance   = 1.0;   // Probabilidade de spawn (0.0 a 1.0)
	
	// --- Ciclo de Vida e Limites ---
	int    nominal  = 1;     // Quantidade máxima desta missão ativa simultaneamente no mapa
	int    lifeTime = 0;     // Tempo de duração da missão em segundos (0 = infinito/manual)
	int    restock  = 0;     // Total de execuções permitidas por ciclo de servidor
	
	// --- Radios de Spawn e Segurança ---
	int    missionSafeSpawnRadius = 100; // Raio para evitar spawn próximo a jogadores
	int    distanceRadius         = 100; // Distância mínima para outras missões
	int    safeRadius             = 100; // Gatilho para spawn de IA dinâmica (proximidade)
	int    cleanRadius            = 150; // Raio de limpeza após a saída dos jogadores
	
	// --- Interface de Mapa (UI) ---
	bool   showInMap = true; // Define se um marcador será exibido no mapa
	string mapTitle;         // Nome que aparecerá no marcador do mapa

	// --- Conjuntos de Dados (Posicionamento e Entidades) ---
	ref array<ref array<float>>          position   = new array<ref array<float>>; // Coordenadas possíveis
	ref array<ref alpMissionAddSpawn>    structures = new array<ref alpMissionAddSpawn>; // Objetos estáticos
	ref array<ref alpMissionAddNPC>      NPC        = new array<ref alpMissionAddNPC>;   // NPCs e Traders
	ref array<ref alpMissionAddCargo>    loot       = new array<ref alpMissionAddCargo>; // Containers de loot
	ref array<ref alpMissionAddVehicle>  vehicles   = new array<ref alpMissionAddVehicle>; // Veículos da missão
}

/**
 * Define o comportamento e equipamentos de IAs vinculadas a uma missão.
 */
class alpMissionAIsample
{
	// --- Identidade e Comportamento ---
	string         className = "ZmbM_PrisonerSkinny"; // Tipo da entidade (Zumbi/Animal/Survivor)
	string         type      = "static";              // "static" ou "dynamic"
	ref array<int> nominal   = {1, 1};                // Range de quantidade [Min, Max]
	int            restock   = 0;                     // Reposição de IA se eliminada
	
	// --- Localização e Espalhamento ---
	vector         position;      // Posição relativa ao centro da missão
	int            radius      = 0; // Raio de patrulha/movimentação
	int            spawnRadius = 0; // Raio de dispersão no spawn
	
	// --- Equipamento Individual ---
	ref array<ref alpLootCargo> cargo = new array<ref alpLootCargo>; // Itens no inventário da IA
}