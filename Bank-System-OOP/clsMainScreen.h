#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"

using namespace std;

class clsMainScreen :protected clsScreen
{

private:

	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLogout
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
		short Choice = clsInputValidate::ReadshortNumberBetween(1, 8, "Enter Number between 1 to 8 ? ");
		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to main menue...";

		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		//cout << "\nClient List Screen Will be here...\n";
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		//cout << "\nAdd New Client Screen Will be here...\n";
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientsScreen()
	{
		//cout << "\nDelete Client Screen Will be here...\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientsScreen()
	{
		//cout << "\nUpdate Client Screen Will be here...\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientsScreen()
	{
		//cout << "\nFind Client Screen Will be here...\n";
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		//cout << "\nTransactions Menue Will be here...\n";
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		//cout << "\nUsers Menue Will be here...\n";
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will be here...\n";

	}

	static void _ActivateMainMenue(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eDeleteClient:
		{
			system("cls");
			_ShowDeleteClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eFindClient:
		{
			system("cls");
			_ShowFindClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eTransactions:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eManageUsers:
		{
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eLogout:
		{
			system("cls");
			_ShowEndScreen();
			break;
		}
		default:
		{
			cout << "\n\nInvalid Input )-:";
			_GoBackToMainMenue();
		}

		}
	}




public:

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t     Main Screen");

		cout << left;
		cout << setw(37) << "" << "==========================================\n";
		cout << setw(37) << "" << "\t\t" << clsUtil::Spaces(5) << " Main Menue\n";
		cout << setw(37) << "" << "==========================================\n";
		cout << setw(37) << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << "" << "\t[5] Find Client.\n";
		cout << setw(37) << "" << "\t[6] Transactins.\n";
		cout << setw(37) << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << "" << "\t[8] Logout.\n";
		cout << setw(37) << "" << "==========================================\n\n";

		_ActivateMainMenue((enMainMenueOptions)_ReadMainMenueOption());
	}

};

