/**
 * alpMessagesSymbols.c
 * * LOCATION LABELS - Módulo ND_MISSIONS (NOTF)
 * Traduz coordenadas vetoriais em nomes de cidades conhecidas para notificações.
 */

class alpMessagesLocationLabel 
{
	ref map<string, ref vector> alp_Location = new map<string, ref vector>;
	
	void alpMessagesLocationLabel()
	{
		string mise;
		
		// Identifica o nome do mapa atual
		if ( GetGame() && GetGame().IsServer() )
		{
			GetDayZGame().GetWorldName(mise);			
		}
		else
		{
			mise = GetDayZGame().GetMissionPath();		
		}
		
		mise.ToLower();
		
		// --- Suporte Exclusivo: CHERNARUS ---
		if (mise.Contains("cherna") || mise.Contains("Cherna"))
		{
			alp_Location.Insert("Balota", "4390 0 2410");
			alp_Location.Insert("Balota Airstrip", "5030 0 2360");
			alp_Location.Insert("Bashnya", "4160 0 11750");
			alp_Location.Insert("Bay Mutnaya", "5630 0 1950");
			alp_Location.Insert("Bay Tikhaya", "1190 0 2190");
			alp_Location.Insert("Bay Zelenaya", "11140 0 3090");
			alp_Location.Insert("Belaya Polana", "14150 0 15000");
			alp_Location.Insert("Berezhki", "15150 0 13820");
			alp_Location.Insert("Berezino", "11860 0 8990");
			alp_Location.Insert("Black Forest", "9080 0 7560");
			alp_Location.Insert("Black Lake", "13360 0 11900");
			alp_Location.Insert("Black Mtn", "10250 0 11980");
			alp_Location.Insert("Bogatyrka", "1500 0 8940");
			alp_Location.Insert("Bor", "3320 0 4010");
			alp_Location.Insert("Cap Golova", "8350 0 2440");
			alp_Location.Insert("Cernaya Polana", "12200 0 13670");
			alp_Location.Insert("Chernogorsk", "6570 0 2450");
			alp_Location.Insert("Chernogorsk Factory", "6410 0 2710");
			alp_Location.Insert("Chyornaya Bay", "7710 0 3090");
			alp_Location.Insert("Crown Castle", "1430 0 9220");
			alp_Location.Insert("Deep Lake", "1850 0 14860");
			alp_Location.Insert("Devil's Castle", "6910 0 11370");
			alp_Location.Insert("Dichina Military", "4620 0 8280");
			alp_Location.Insert("Dobroe", "13100 0 14950");
			alp_Location.Insert("Dolina", "11330 0 6650");
			alp_Location.Insert("Drakon Island", "11190 0 2490");
			alp_Location.Insert("Drozhino", "3450 0 4930");
			alp_Location.Insert("Dubky", "6650 0 3670");
			alp_Location.Insert("Dubrovka", "10400 0 9800");
			alp_Location.Insert("Dubrovka Vyshnaya", "9950 0 10390");
			alp_Location.Insert("Electrozavodsk", "10500 0 2340");
			alp_Location.Insert("Gnome Castle", "7410 0 9110");
			alp_Location.Insert("Gorka", "9650 0 8810");
			alp_Location.Insert("Green Mtn", "3740 0 6010");
			alp_Location.Insert("Grishino", "6020 0 10260");
			alp_Location.Insert("Grozovoy Pass", "3240 0 15290");
			alp_Location.Insert("Guba", "14610 0 13280");
			alp_Location.Insert("Guglovo", "8410 0 6690");
			alp_Location.Insert("Gvozdno", "8710 0 11900");
			alp_Location.Insert("Kabanino", "5300 0 8560");
			alp_Location.Insert("Kamenka", "1890 0 2160");
			alp_Location.Insert("Kamensk", "6630 0 14470");
			alp_Location.Insert("Kamyshovo", "12170 0 3450");
			alp_Location.Insert("Karmanovka", "12520 0 14680");
			alp_Location.Insert("Khelm", "12290 0 10790");
			alp_Location.Insert("Klen Mtn", "11490 0 11330");
			alp_Location.Insert("Komarovo", "3620 0 2340");
			alp_Location.Insert("Kozlova Mtn", "8830 0 2860");
			alp_Location.Insert("Kozlovka", "4450 0 4580");
			alp_Location.Insert("Krasnoe", "6490 0 14980");
			alp_Location.Insert("Krasnostav", "11230 0 12220");
			alp_Location.Insert("Krasnostav Airstrip", "12020 0 12490");
			alp_Location.Insert("Krutoy Cap", "13620 0 3890");
			alp_Location.Insert("Kumyrna", "8400 0 6030");
			alp_Location.Insert("Lopatino", "2750 0 9990");
			alp_Location.Insert("Mamino", "7980 0 13060");
			alp_Location.Insert("Mogilevka", "7500 0 5240");
			alp_Location.Insert("Msta", "11260 0 5510");
			alp_Location.Insert("Myshkino", "2060 0 7430");
			alp_Location.Insert("Myshkino Military", "1270 0 7230");
			alp_Location.Insert("Nadezhdino", "5820 0 4760");
			alp_Location.Insert("Nagornoe", "9330 0 14670");
			alp_Location.Insert("Nizhnoye", "12900 0 8040");
			alp_Location.Insert("Novaya Petrovka", "3470 0 12990");
			alp_Location.Insert("Novaya Trainyard", "3530 0 12580");
			alp_Location.Insert("Novodmitrovsk", "11600 0 14700");
			alp_Location.Insert("Novoselky", "6050 0 3290");
			alp_Location.Insert("Novy Sobor", "7160 0 7690");
			alp_Location.Insert("NWA", "4644 0 10104");
			alp_Location.Insert("Olha", "13320 0 12890");
			alp_Location.Insert("Oreshka Pass", "9880 0 6010");
			alp_Location.Insert("Orlovets", "12140 0 7280");
			alp_Location.Insert("Orlovets Factory", "11490 0 7590");
			alp_Location.Insert("Otmel Island", "11640 0 3100");
			alp_Location.Insert("Pavlovo", "1630 0 3850");
			alp_Location.Insert("Pavlovo Military", "2100 0 3290");
			alp_Location.Insert("Pogorevka", "4380 0 6410");
			alp_Location.Insert("Polana", "10680 0 8090");
			alp_Location.Insert("Polesovo", "5820 0 13490");
			alp_Location.Insert("Prigorodki", "7980 0 3300");
			alp_Location.Insert("Prud Lake", "6630 0 9290");
			alp_Location.Insert("Pulkovo", "4900 0 5650");
			alp_Location.Insert("Pusta", "9180 0 3860");
			alp_Location.Insert("Pustoshka", "2990 0 7810");
			alp_Location.Insert("Ratnoe", "6310 0 12710");
			alp_Location.Insert("Rify", "13780 0 11230");
			alp_Location.Insert("Rog Castle", "11260 0 4290");
			alp_Location.Insert("Rogovo", "4730 0 6780");
			alp_Location.Insert("Romashka", "8150 0 11020");
			alp_Location.Insert("Severograd", "7890 0 12580");
			alp_Location.Insert("Shakhovka", "9670 0 6500");
			alp_Location.Insert("Silence Lake", "1200 0 6510");
			alp_Location.Insert("Sinystok", "1450 0 11920");
			alp_Location.Insert("Skalisty Island", "13660 0 2960");
			alp_Location.Insert("Smirnovo", "11630 0 15020");
			alp_Location.Insert("Solnichniy", "13470 0 6240");
			alp_Location.Insert("Solnichniy Factory", "13070 0 7160");
			alp_Location.Insert("Sosnovka", "2510 0 6370");
			alp_Location.Insert("Sosnovy Pass", "2740 0 6760");
			alp_Location.Insert("Staroye", "10160 0 5460");
			alp_Location.Insert("Stary Sobor", "6070 0 7750");
			alp_Location.Insert("Stary Yar", "4940 0 15070");
			alp_Location.Insert("Prison Island", "2610 0 1310");
			alp_Location.Insert("Svergino", "9530 0 13730");
			alp_Location.Insert("Svetlojarsk", "13930 0 13230");
			alp_Location.Insert("Three Valleys", "12840 0 5500");
			alp_Location.Insert("Tisy", "3410 0 14810");
			alp_Location.Insert("Tisy Military", "1680 0 14120");
			alp_Location.Insert("Topolniki", "2820 0 12370");
			alp_Location.Insert("Troitskoe", "7560 0 13520");
			alp_Location.Insert("Troitskoe Military", "7870 0 14680");
			alp_Location.Insert("Tulga", "12810 0 4460");
			alp_Location.Insert("Turovo", "13580 0 14130");
			alp_Location.Insert("Vavilovo", "2210 0 11020");
			alp_Location.Insert("Veresnik Mtn", "4440 0 8080");
			alp_Location.Insert("Vybor", "3800 0 8840");
			alp_Location.Insert("Vyshnoye", "6530 0 6090");
			alp_Location.Insert("Vysotovo", "5620 0 2560");
			alp_Location.Insert("Willow Lake", "13250 0 11610");
			alp_Location.Insert("Zabolotye", "1160 0 10010");
			alp_Location.Insert("Zaprudnoe", "4930 0 13030");
			alp_Location.Insert("Zelenogorsk", "2710 0 5390");
			alp_Location.Insert("Zub Castle", "6540 0 5590");
			alp_Location.Insert("Zvir", "480 0 5200");
		}
	}
	
	/**
	 * Retorna o nome da localização mais próxima de um vetor.
	 */
	string GetLocation(vector pos)
	{
		float distance = 50000;
		float measure;
		string location = pos.ToString();
		pos[1] = 0; // Ignora altura no cálculo
		
		if (alp_Location.Count() > 0)
		{
			foreach (vector v : alp_Location)
			{
				measure = alpUF.VectorDistance(v, pos);
				if (measure < distance)
				{
					distance = measure;
					location = alp_Location.GetKeyByValue(v);
				}
			}
		}		
		return location;
	}

	/**
	 * Retorna o nome e ajusta o vetor de saída para a coordenada exata da cidade.
	 */
	string GetLocation2(out vector pos)
	{
		float distance = 50000;
		float measure;
		string location = pos.ToString();
		pos[1] = 0;
		vector posAdjusted = pos;

		if (alp_Location.Count() > 0)
		{
			foreach (vector v : alp_Location)
			{
				measure = alpUF.VectorDistance(v, pos);
				if (measure < distance)
				{
					distance = measure;
					location = alp_Location.GetKeyByValue(v);
					posAdjusted = v;					
				}
			}
		}		
		pos = posAdjusted;
		return location;
	}
}