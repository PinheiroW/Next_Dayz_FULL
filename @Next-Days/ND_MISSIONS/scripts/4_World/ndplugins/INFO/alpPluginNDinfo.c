/**
 * alpPluginNDinfo.c
 * * INFO SYSTEM PLUGIN - Módulo ND_MISSIONS
 * Gerencia o carregamento de arquivos, leitura de textos e sincronização da Wiki interna.
 */

class alpPluginNDinfo extends alpPlugin
{
	ref alpInfoSitesTemplate alp_InfoSites;

	override void Init() 
	{
		if (GetGame().IsServer() && GetGame().IsMultiplayer())
		{
			// Garante a existência do diretório
			if (!FileExist(ALP_INFO_FOLDER)) 
				MakeDirectory(ALP_INFO_FOLDER);	

			// Carrega a estrutura de sites/menus via JSON
			JsonFileLoader<alpInfoSitesTemplate>.JsonLoadFile(ALP_INFO_FILE, alp_InfoSites);
			
			if (alp_InfoSites)			
			{
				ReadInfoContent(); // Popula os textos a partir dos arquivos .txt
			}
			else
			{
				// Se falhar (ex: primeiro boot), cria um template de exemplo
				InitInfoPagesTemplate();
			}
		}	
	}

	void ~alpPluginNDinfo()
	{
		if (alp_InfoSites)
			delete alp_InfoSites;				
	}	

	/**
	 * Sincroniza os dados de informação com o jogador no momento da conexão.
	 */
	override void OnConnectManaged(PlayerBase player)
	{					
		ScriptRPC rpc = GetND().GetInitRPC(GetID());					
		rpc.Write(alp_InfoSites);
							
		GetND().SendGameRPC(rpc, player);
	}	

	/**
	 * Recebe e processa os dados de informação no lado do cliente.
	 */
	override void ReadInitRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		ctx.Read(alp_InfoSites);		
	}	
	
	/**
	 * Lê os arquivos .txt referenciados no JSON e os converte em strings para a UI.
	 */
	protected void ReadInfoContent()
	{
		if (!alp_InfoSites || !alp_InfoSites.Items) return;

		for (int it = 0; it < alp_InfoSites.Items.Count(); it++)
		{
			alpISitem item = alp_InfoSites.Items.Get(it);
			if (!item || !item.Text) continue;

			for (int i = 0; i < item.Text.Count(); i++)
			{
				// O JSON deve conter o nome do arquivo (ex: "regras_ENG.txt")
				string fileName = item.Text.Get(i).Get(0);
				FileHandle file = OpenFile(ALP_INFO_FOLDER + fileName, FileMode.READ);
				
				if (file)
				{
					string line_content;
					item.Text.Get(i).Clear(); // Limpa a referência do nome do arquivo
					
					// Lê o conteúdo real do arquivo linha por linha
					while (FGets(file, line_content) > 0)
					{				
						item.Text.Get(i).Insert(line_content);
					}										
					CloseFile(file);
				}
			}	
		}	
	}	
	
	/**
	 * Cria uma estrutura inicial padrão para que o administrador saiba como configurar.
	 */
	protected void InitInfoPagesTemplate()
	{
		alpInfoSitesTemplateInput input = new alpInfoSitesTemplateInput();
		
		input.Language = {"English"};
		input.Button1 = {"Donate", "https://paypal.me/AlPepino"};
		input.Button5 = {"Discord", "https://discord.gg/nextdays"};
		
		// Inicializa 5 menus de exemplo
		for (int i = 0; i < 5; i++)
		{
			alpISitem item = new alpISitem();
			string menu = "Menu Exemplo " + i;							
			item.Menu = {menu};
			
			string textInput = "m" + i + "_ENG.txt";
			FileHandle file = OpenFile(ALP_INFO_FOLDER + textInput, FileMode.WRITE);		
			if (file)
			{
				FPrintln(file, "Este é o conteúdo do menu " + i);
				FPrintln(file, "Você pode editar este arquivo .txt no diretório INFO.");
				CloseFile(file);
			}
			
			item.Text.Insert({textInput});
			input.Items.Insert(item);
		}
		
		// Salva o template em disco
		JsonFileLoader<alpInfoSitesTemplateInput>.JsonSaveFile(ALP_INFO_FILE, input);
		
		// Recarrega para a memória
		JsonFileLoader<alpInfoSitesTemplate>.JsonLoadFile(ALP_INFO_FILE, alp_InfoSites);
		ReadInfoContent();
	}
}