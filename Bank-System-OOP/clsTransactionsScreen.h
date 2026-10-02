#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen :protected clsScreen
{

private:

	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eMainMenue = 6
	};

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 6 ? ");
		return Choice;
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << setw(37) << left << "" << "\n\n\tPress any key to go back to transactions menue...";

		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen()
	{
		//cout << "\nDeposit Screen Will be here...\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\nWithdraw Screen Will be here...\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		//cout << "\nBalances Screen Will be here...\n";
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		//cout << "\nTransfer Screen Will be here...\n";
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		//cout << "\nTransfer Log Screen Will be here...\n";
		clsTransferLogScreen::ShowTransferRegisterScreen();
	}

	static void _ActivateTransactionsMenue(enTransactionsMenueOptions TransactionsMenueOption)
	{
		switch (TransactionsMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case enTransactionsMenueOptions::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case enTransactionsMenueOptions::eTotalBalances:
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case enTransactionsMenueOptions::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
		}
		case enTransactionsMenueOptions::eTransferLog:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
		}
		case enTransactionsMenueOptions::eMainMenue:
		{
			//nothing;
		}
		}
	}




public:

	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::ePermissions::pTransactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << left;
		cout << setw(37) << "" << "==========================================\n";
		cout << setw(37) << "" << "\t\ttransactions Menue\n";
		cout << setw(37) << "" << "==========================================\n";
		cout << setw(37) << "" << "\t[1] Deposit.\n";
		cout << setw(37) << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << "" << "\t[4] Transfer.\n";
		cout << setw(37) << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << "" << "==========================================\n\n";

		_ActivateTransactionsMenue((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}


};

