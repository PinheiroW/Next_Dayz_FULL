/**
 * alpSync.c
 * * CENTRAL SYNCHRONIZATION MANAGER - Módulo ND_MISSIONS (Sync)
 * Coordena o tráfego de rede para estados bit-packed e valores delta-float.
 */

class alpSync 
{
	protected PlayerBase alp_Player;
	
	// --- Configuração Bit-Sync (Inteiros) ---
	protected ref array<int> alp_LastSentStats;
	protected const int      NUMBER_OF_ELEMENTS = alpRPelements.COUNT;	
	protected ref alpStatsBase alp_Elements[NUMBER_OF_ELEMENTS];	
	
	// --- Configuração Enhanced-Sync (Floats) ---
	protected bool           alp_IsRegisterToEnhancedStat;
	protected const int      NUMBER_OF_ELEMENTS_ENHANCED = alpRPelementsEnahnced.COUNT;
	protected ref alpStatsBaseEnhanced alp_ElementsEnhanced[NUMBER_OF_ELEMENTS_ENHANCED];		
	
	protected float          alp_TICK;

	// --- Inicialização e Registro ---

	void alpSync(PlayerBase player)
	{
		alp_Player = player;
		Init();
	}
	
	void Init()
	{
		// Registro de Estatísticas de Bits (Flags Binárias e Pequenos Inteiros)
		RegisterElement( new alpStatsIsAllowDamage( alp_Player ) );
		RegisterElement( new alpStatsIsInTradeZone( alp_Player ) );		
		RegisterElement( new alpStatsIsRained( alp_Player ) );		
		
		// Registro de Estatísticas Aprimoradas (Floats e Economia)
		RegisterElementEnhanced( new alpStatsEnhancedHealth(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedBlood(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedWater(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedFood(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedStomach(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedRadiationDoses( alp_Player ) );	
		RegisterElementEnhanced( new alpStatsEnhancedTraderBalance( alp_Player ) );	
		RegisterElementEnhanced( new alpStatsEnhancedPlayerBalance( alp_Player ) );
	}

	// --- Ciclo de Manutenção do Servidor ---

	/**
	 * Dispara a sincronização forçada baseada no intervalo de 1 segundo.
	 */
	void OnScheduledTick(float deltaTime)
	{
		if( GetGame() && GetGame().IsServer() )
		{
			alp_TICK += deltaTime;
			if( alp_TICK > 1 )
			{
				ForceSync();
				alp_TICK = 0;
			}
		}
	}	

	void ForceSync()
	{
		SendRPC_RP();          // Bits
		SendRPC_RP_ENHANCED(); // Floats
	}

	// --- Lógica Bit-Sync (Network Compression) ---

	/**
	 * Envia as estatísticas de bits apenas se houver mudança em relação ao último envio.
	 */
	void SendRPC_RP()
	{
		array<int> mask_array = new array<int>;
		SerializeStats(mask_array);
		
		if( !alp_LastSentStats || !AreArraysSame(alp_LastSentStats, mask_array) )
		{
			ScriptRPC rpc = new ScriptRPC();
			rpc.Write(mask_array);
			rpc.Send(alp_Player, ALP_RPC_PLAYER_SYNC_BIT, true, alp_Player.GetIdentity());
			alp_LastSentStats = mask_array;
		}
	}

	/**
	 * Processa o recebimento das estatísticas de bits no lado Cliente.
	 */
	void OnRPC_RP_STATS(ParamsReadContext ctx)
	{	
		array<int> mask_array = new array<int>;
		if ( ctx.Read(mask_array) )
		{
			DeserializeStats(mask_array);
		}
	}

	protected void SerializeStats(ref array<int> mask_array)
	{
		int offset = 0;
		int mask = 0;
		
		for(int i = 0; i < NUMBER_OF_ELEMENTS; i++)
		{
			alpStatsBase element = GetElement(i);
			if( element )
			{
				if( (element.GetNumberOfBits() + offset) > BIT_INT_SIZE )
				{
					mask_array.Insert(mask);
					offset = 0;
					mask = 0;
				}
				mask = mask | (element.GetValue() << offset);
				offset = offset + element.GetNumberOfBits();
			}
		}
		mask_array.Insert(mask);
	}

	protected void DeserializeStats(ref array<int> mask_array )
	{
		int maskArrayIndex = 0;
		int offset = 0;
		
		for(int i = 0; i < NUMBER_OF_ELEMENTS; i++)
		{
			alpStatsBase element = GetElement(i);
			if( element )
			{
				if( offset + element.GetNumberOfBits() > BIT_INT_SIZE )
				{
					maskArrayIndex++;
					offset = 0;
				}
				
				int mask = mask_array.Get(maskArrayIndex);
				int value = BitToDec( mask, offset, element.GetCompareMask() );
				offset = offset + element.GetNumberOfBits();
				element.SetValue( value );
				
				// Sincronização direta com a Identidade (Hotfix Progressão)
				if ( i == alpRPelements.REPUTATION && alp_Player.GetIdentity() ) {
					alp_Player.GetIdentity().SetPlayerLevel( value );	
				}
			}
		}		
	}

	// --- Lógica Enhanced-Sync (Delta Sync) ---

	/**
	 * Varre elementos flutuantes e envia apenas os que sofreram alteração.
	 */
	void SendRPC_RP_ENHANCED()
	{
		// Bloqueia sincronização se o jogador não tiver requisitos mínimos
		if ( !IsRegisteredToEnhanced() && !GetPlayer().GetRP().HasDosimeter() )
			return;

		for(int i = 0; i < NUMBER_OF_ELEMENTS_ENHANCED; i++)
		{
			alpStatsBaseEnhanced element = GetElementEnhanced(i);
			if( element )
			{
				// Verifica contexto: Trader, Player Vital ou Radiação
				if ( ( element.IsTraderStats() & IsRegisteredToEnhanced() ) || ( element.IsPlayerStats() & IsRegisteredToEnhanced() ) || ( element.IsRadiationStats() ) )
				{
					float value;											
					if ( element.GetValue( value ) ) // Verifica se houve alteração (Delta)
					{
						ScriptRPC rpc = new ScriptRPC();
						rpc.Write(i);
						rpc.Write(value);
						rpc.Send(alp_Player, ALP_RPC_PLAYER_SYNC_VALUE, false, alp_Player.GetIdentity());
					}
				}
			}
		}			
	}

	/**
	 * Recebe e aplica os valores flutuantes no lado Cliente.
	 */
	void OnRPC_RP_STATS_ENHANCED(ParamsReadContext ctx)
	{	
		int type;
		float value;					
		if ( ctx.Read(type) && ctx.Read(value) )
		{
			if ( GetElementEnhanced(type) )
			{
				GetElementEnhanced(type).SetValue( value );
			}
		}
	}	

	// --- Utilitários e Getters ---

	protected int BitToDec(int mask, int index, int compareMask)
	{
		int value = mask & (compareMask << index);
		value = value >> index;
		return value;
	}

	protected bool AreArraysSame( notnull array<int> array_a, notnull array<int> array_b )
	{
		if( array_a.Count() != array_b.Count() ) return false;
		for(int i = 0; i < array_a.Count(); i++)
		{
			if(	array_a.Get(i) != array_b.Get(i) ) return false;
		}
		return true;
	}

	PlayerBase GetPlayer() { return alp_Player; }
	
	bool IsRegisteredToEnhanced() { return alp_IsRegisterToEnhancedStat; }
	
	void RegisterToStats(bool state) { alp_IsRegisterToEnhancedStat = state; }

	protected void RegisterElement( alpStatsBase element) {
		alp_Elements[element.GetType()] = element;
	}

	protected void RegisterElementEnhanced( alpStatsBaseEnhanced element) {
		alp_ElementsEnhanced[element.GetType()] = element;
	}

	alpStatsBase GetElement(int element_id) {
		if( element_id < 0 || element_id >= NUMBER_OF_ELEMENTS ) return null;
		return alp_Elements[element_id];
	}

	alpStatsBaseEnhanced GetElementEnhanced(int element_id) {
		if( element_id < 0 || element_id >= NUMBER_OF_ELEMENTS_ENHANCED ) return null;
		return alp_ElementsEnhanced[element_id];
	}	
}