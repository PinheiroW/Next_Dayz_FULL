/**
 * alpCreaturesPlugin
 * Gerenciador centralizado de criaturas.
 * OTIMIZAÇÃO: Cache de memória implementado para evitar I/O repetitivo.
 * FIX: Adicionada lógica de seleção de perfil GetZombieBehavior.
 */
class alpCreaturesPlugin extends alpPlugin
{
	ref alpCreaturesOptions alp_OptionsCreatures;

	// Cache de comportamentos (RAM)
	private ref array<ref alpZombieBehavior> m_CacheCivil;
	private ref array<ref alpZombieBehavior> m_CacheCivilNBC;
	private ref array<ref alpZombieBehavior> m_CacheMilitary;
	private ref array<ref alpZombieBehavior> m_CacheMilitaryNBC;
	private ref array<ref alpZombieBehavior> m_CacheMonster;

	override void Init() 
	{
		super.Init();
		alp_OptionsCreatures = new alpCreaturesOptions;

		if (GetGame().IsServer())
		{
			// Garante existência de diretório
			if (!FileExist(ALP_CREATURES_FOLDER))
				MakeDirectory(ALP_CREATURES_FOLDER);		
			
			// Carregamento das Opções
			if (!FileExist(ALP_CREATURES_FILE))
				JsonFileLoader<alpCreaturesOptions>.JsonSaveFile(ALP_CREATURES_FILE, alp_OptionsCreatures);
			else 
				JsonFileLoader<alpCreaturesOptions>.JsonLoadFile(ALP_CREATURES_FILE, alp_OptionsCreatures);	
			
			JsonFileLoader<alpCreaturesOptions>.JsonSaveFile(ALP_CREATURES_FILE, alp_OptionsCreatures);		

			// Pre-load de todos os perfis JSON para a memória
			LoadAllBehaviors();
		}
	}

	private void LoadAllBehaviors()
	{
		m_CacheCivil        = LoadBehavior(ALP_CREATURES_ZED_C_FILE, {0, 0.2, 3, 2, 0.25, 1});
		m_CacheCivilNBC     = LoadBehavior(ALP_CREATURES_ZED_C_NBC_FILE, {0, 0.2, 3, 2, 0.25, 2, 3, 3, 1});
		m_CacheMilitary     = LoadBehavior(ALP_CREATURES_ZED_M_FILE, {1, 0.1, 3, 2, 0.5, 2});
		m_CacheMilitaryNBC  = LoadBehavior(ALP_CREATURES_ZED_M_NBC_FILE, {1, 0.1, 3, 2, 0.5, 4, 6, 6, 1});
		m_CacheMonster      = LoadBehavior(ALP_CREATURES_ZED_MONSTER_FILE, {1, 0.025, 6, 4, 0.5, 10, 10, 10, 1});
	}

	private array<ref alpZombieBehavior> LoadBehavior(string path, array<float> defaults)
	{
		array<ref alpZombieBehavior> behavior = new array<ref alpZombieBehavior>;
		if (FileExist(path))
			JsonFileLoader<array<ref alpZombieBehavior>>.JsonLoadFile(path, behavior);
		
		if (!behavior || behavior.Count() == 0)
		{
			behavior = new array<ref alpZombieBehavior>;
			// Insere um padrão caso o arquivo seja novo
			behavior.Insert(new alpZombieBehavior(defaults[0], defaults[1], defaults[2], defaults[3], defaults[4], defaults[5], defaults[6], defaults[7], defaults[8]));
			JsonFileLoader<array<ref alpZombieBehavior>>.JsonSaveFile(path, behavior);
		}
		return behavior;
	}

	// FUNÇÃO PRINCIPAL: Seleciona o comportamento baseado na classe do zumbi
	alpZombieBehavior GetZombieBehavior(string type)
	{
		type.ToLower();
		array<ref alpZombieBehavior> list;

		// 1. Prioridade: Monstros Especiais
		if (IsZombieMonster(type))
			list = m_CacheMonster;
		// 2. Militares NBC (Áreas Contaminadas de Elite)
		else if (type.Contains("military") && type.Contains("nbc"))
			list = m_CacheMilitaryNBC;
		// 3. Militares Comuns
		else if (type.Contains("military"))
			list = m_CacheMilitary;
		// 4. Civis NBC
		else if (type.Contains("nbc"))
			list = m_CacheCivilNBC;
		// 5. Civis Comuns (Default)
		else
			list = m_CacheCivil;

		if (list && list.Count() > 0)
		{
			// Retorna o primeiro perfil ou você pode implementar uma lógica aleatória aqui
			return list.Get(0); 
		}

		return null;
	}

	alpCreaturesOptions GetOptions()
	{
		return alp_OptionsCreatures;
	}
	
	bool IsZombieMonster(string type)
	{	
		type.ToLower();	
		if (GetOptions() && GetOptions().ZombiesMonster)
		{
			foreach (string monster : GetOptions().ZombiesMonster)
			{
				string m = monster;
				m.ToLower();
				if (type == m) return true;
			}
		}		
		return false;	
	}
	
	// Getters auxiliares para acesso externo se necessário
	array<ref alpZombieBehavior> GetListCivil()    { return m_CacheCivil; }
	array<ref alpZombieBehavior> GetListMilitary() { return m_CacheMilitary; }
	array<ref alpZombieBehavior> GetListMonster()  { return m_CacheMonster; }
}