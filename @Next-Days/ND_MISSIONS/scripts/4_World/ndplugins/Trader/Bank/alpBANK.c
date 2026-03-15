/**
 * alpBANK.c
 * * CENTRAL BANKING SYSTEM - Módulo ND_MISSIONS (Trader)
 * Gerencia economia, contas, câmbio e sistema de empréstimos/dívidas.
 */

class alpBANK 
{
	// --- Memória e Mapeamento ---
	static ref alpBankAccount alp_ClientAccount;
	static ref map<int, PlayerBase> alp_Debtors = new map<int, PlayerBase>;
	
	static ref map<int, int> alp_BankBalance;       // Saldo Global do Banco
	static ref map<int, int> alp_PlayerBankBalance; // Saldo Total de Jogadores
	static ref map<int, int> alp_TraderBankBalance = new map<int, int>;
	
	static ref map<int, ref alpBankAccount> alp_AccountsMapped = new map<int, ref alpBankAccount>;
	static ref alpCurrencies alp_Currencies = new alpCurrencies();

	// --- Câmbio e Moedas ---

	static float GetCurrencyRate(int currency)
	{
		return alp_Currencies.GetCurrencyRate(currency);	
	}

	/**
	 * Realiza a troca de moedas entre contas, atualizando o lastro do banco.
	 */
	static void Exchange(int accountid, int fromCurrency, int toCurrency, int fromAmmount, int toAmmount, PlayerBase player)
	{
		int back = AddBalanceToAccount(accountid, fromCurrency, -fromAmmount, player);
		
		if (!back)
		{
			AddBankBalance(fromCurrency, fromAmmount);
			AddBankBalance(toCurrency, -toAmmount);
			AddBalanceToAccount(accountid, toCurrency, toAmmount, player);
		}
		else
		{
			back = fromAmmount - back;
			AddBalanceToAccount(accountid, fromCurrency, back, player);
		}
	}

	/**
	 * Calcula a taxa de câmbio baseada no balanço das moedas.
	 * Fórmula Matemática:
	 */
	static float GetExchangeRate(int from, int to)
	{
		int balanceFrom = GetBankBalance(from);
		int balanceTo = GetBankBalance(to);
		
		alpCurrency currencyFrom = alp_Currencies.GetCurrency(from);
		alpCurrency currencyTo = alp_Currencies.GetCurrency(to);
		
		float rateFrom = currencyFrom.GetRate();
		float rateTo = currencyTo.GetRate();
		float offset = currencyTo.GetOffset();
		
		float total = (balanceFrom / rateFrom + balanceTo / rateTo) + 0.001; 
		
		float rate = (balanceTo / rateTo) / total;
		rate = (rate - 0.5) / -0.5;
		rate = offset * rate * (rateFrom / rateTo);

		return (rateFrom / rateTo) + rate;
	}

	// --- Sistema de Empréstimos (Loans) ---

	static void TakeLoan(PlayerBase player, Param6<int, int, int, int, float, int> takeLoan)
	{
		alpLoans loan = new alpLoans(takeLoan);
		alpBankAccount account = alpBANK.GetBankAccount(takeLoan.param1);			
		account.AddLoan(loan);
		
		AddBalanceToAccount(takeLoan.param1, takeLoan.param2, takeLoan.param3, player);
	}

	static void PartialLoanRepayment(int accountid, int currency, int pay, PlayerBase player)
	{
		alpBankAccount account = alpBANK.GetBankAccount(accountid);		
		if (!account) return;

		alpLoans loan = account.GetLoan(currency);
		if (loan)
		{
			int total = loan.Principal + loan.Interest;
			total -= pay;
			
			if (total <= 0)
			{
				AddBankBalance(currency, loan.Interest);					
				account.RemoveLoanRecord(loan);
				AddBalanceToAccount(accountid, currency, -pay, player);
				
				// Reavalia status de devedor após quitação
				PlayerBase p;
				if (alp_Debtors.Find(accountid, p) && p) CheckDebts(p, account);
			}
			else
			{
				// Abate primeiro os juros, depois o principal
				if (loan.Interest - pay < 0)
				{
					AddBankBalance(currency, loan.Interest);	
					loan.Principal += (loan.Interest - pay);
					loan.Interest = 0;
				}
				else
				{
					AddBankBalance(currency, pay);	
					loan.Interest -= pay;				
				}
				AddBalanceToAccount(accountid, currency, -pay, player);
			}
		}
	}

	// --- Gestão de Contas e Persistência ---

	static void SetBankAccountOnConnect(PlayerBase player, int pID = -1)
	{
		int playerID = (pID > 0) ? pID : player.GetPlayerHive().GetPlayerID();
		string guid = player.GetIdentity().GetPlainId();
		alpBankAccount account;	
		
		if (!alp_AccountsMapped.Find(playerID, account))
		{
			string path = ALP_MISSIONS_BANK_FOLDER + playerID + ".json";
			JsonFileLoader<alpBankAccount>.JsonLoadFile(path, account);	
			
			if (!account)
			{
				account = new alpBankAccount(playerID, guid, player.GetIdentity().GetName());
				JsonFileLoader<alpBankAccount>.JsonSaveFile(path, account);	
			}	
			alp_AccountsMapped.Set(playerID, account);
		}
		CheckDebts(player, account);
	}

	/**
	 * Verifica se o jogador possui dívidas vencidas e aplica status de Debtor no RP.
	 */
	static void CheckDebts(PlayerBase player, alpBankAccount account)
	{
		if (account)
		{
			if (IsDebtor(account.Loans, account.PlayerID, player))
			{
				alp_Debtors.Set(player.GetPlayerHive().GetPlayerID(), player);
				player.GetRP().SetDebtor(true);
			}
			else
			{
				player.GetRP().SetDebtor(false);
			}			
		}	
	}

	static bool IsDebtor(array<autoptr alpLoans> loans, int accountID, PlayerBase player)
	{
		if (loans && loans.Count() > 0)
		{
			int year, month, day, today;
			GetYearMonthDayUTC(year, month, day);
			today = year + month * 30 + day; // Simplificação de data ND

			for (int i = 0; i < loans.Count(); )
			{
				alpLoans loan = loans.Get(i);
				int terminated = loan.Terminated[0] + loan.Terminated[1] * 30 + loan.Terminated[2];
				
				if (terminated < today)
				{
					int debt = loan.Principal + loan.Interest;
					int available = GetBalanceInCurrency(accountID, loan.CurrencyID);
					
					if (available >= debt) // Pagamento Automático
					{
						AddBankBalance(loan.CurrencyID, loan.Interest);	
						loans.Remove(i);						
						AddBalanceToAccount(accountID, loan.CurrencyID, -debt, player);						
						continue;
					}
					else // Torna-se devedor
					{
						player.GetRP().SetDebt(loan.CurrencyID, debt);
						return true;
					}
				}
				i++;
			}			
		}	
		return false;
	}

	// --- Capital e Balanço Global ---

	static void AddBankBalance(int currency, int ammount)
	{
		int balance;
		if (alp_BankBalance.Find(currency, balance))
		{				
			int max = int.MAX - Math.AbsInt(ammount);
			if (balance < max) balance += ammount;					
			if (balance < 0) balance = 0;						
		}
		alp_BankBalance.Set(currency, balance);		
		JsonFileLoader<map<int, int>>.JsonSaveFile(ALP_MISSIONS_BANK_BALANCE, alp_BankBalance);		
	}

	static int AddBalanceToAccount(int name, int currency, int balance, PlayerBase player)
	{
		int back = Math.AbsInt(balance);
		alpBankAccount account;		
		if (alp_AccountsMapped.Find(name, account))
		{
			back = account.AddBalance(currency, balance, player);
		}			
		
		AddBankCapital(currency, (balance - back));	
		return back;	
	}

	static alpCurrencies GetCurencies() { return alp_Currencies; }
	static int GetBankBalance(int currency) { return alp_BankBalance.Get(currency); }
	static int GetDepositLimit(PlayerBase player) { return GetND().GetMS().GetOptoinsTrader().PlayerDepositLimit; }
}

/**
 * Representação de um empréstimo individual.
 */
class alpLoans 
{
	int CurrencyID;
	int Start[3];
	int Terminated[3];
	int Principal;
	int Interest;
	float InterestRate;
	
	void alpLoans(Param6<int, int, int, int, float, int> takeLoan)
	{
		CurrencyID = takeLoan.param2;
		Principal = takeLoan.param3;
		Interest = takeLoan.param4;	
		InterestRate = takeLoan.param5;	
		
		int y, m, d;
		GetYearMonthDayUTC(y, m, d);
		Start = {y, m, d};
		
		// Cálculo de expiração
		int length = takeLoan.param6;	
		int months[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		
		int dayEnd = d + length;
		int monthEnd = m;
		int yearEnd = y;

		if (dayEnd > months[m])
		{
			dayEnd -= months[m];
			monthEnd++;
			if (monthEnd > 12) { monthEnd = 1; yearEnd++; }
		}
		Terminated = {yearEnd, monthEnd, dayEnd};
	}	
}

/**
 * Objeto de persistência da conta bancária do jogador.
 */
class alpBankAccount 
{
	int PlayerID;
	string GUID;
	string Name;
	ref array<ref alpLoans> Loans;
	ref array<int> RegisteredCards;
	ref map<int, int> Currencies;
			
	void alpBankAccount(int playerid, string id, string name)
	{
		PlayerID = playerid;
		GUID = id;
		Name = name;
		RegisteredCards = new array<int>;
		Currencies = new map<int, int>;
		Loans = new array<ref alpLoans>;
		
		alpCurrencies currs = alpBANK.GetCurencies();
		for (int i = 0; i < currs.alp_Currencies.Count(); i++)
		{
			Currencies.Set(currs.alp_Currencies.GetKey(i), 0);
		}						
	}

	int AddBalance(int currency, int change, PlayerBase player)
	{
		int balance = GetBalance(currency);
		int back = Math.AbsInt(change);
		int limit = alpBANK.GetDepositLimit(player);

		if (change > 0) // Depósito
		{
			if (balance + change <= limit)
			{
				balance += change;
				back = 0;
			}
			else
			{
				back = (balance + change) - limit;
				balance = limit;
			}
		}
		else // Saque / Débito
		{
			balance += change;
			if (balance < 0) { back = Math.AbsInt(balance); balance = 0; }
			else back = 0;
		}

		Currencies.Set(currency, balance);
		Save();
		return back;
	}

	int GetBalance(int currency) { 
		int val; 
		return (Currencies.Find(currency, val)) ? val : 0; 
	}
	
	void AddLoan(alpLoans loan) { Loans.Insert(loan); Save(); }
	void RemoveLoanRecord(alpLoans loan) { Loans.RemoveItem(loan); Save(); }
	void Save() { if (GetGame().IsServer()) JsonFileLoader<alpBankAccount>.JsonSaveFile(ALP_MISSIONS_BANK_FOLDER + PlayerID + ".json", this); }
}