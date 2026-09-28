#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsTotalBalancesScreen :protected clsScreen
{

private:

	static void _PrintClientBalanceLine(clsBankClient Client)
	{
		cout << setw(25) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(40) << Client.FullName();
		cout << "| " << left << setw(12) << Client.AccountBalance;
	}



public:

	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t Balances List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, SubTitle);

		double TotalBalances = 0;
		TotalBalances = clsBankClient::GetTotalBalance();

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________________________________________\n" << endl;

		cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << clsUtil::Tabs(5) << "No Clients Available In The System!";
		else

			for (clsBankClient& Client : vClients)
			{
				_PrintClientBalanceLine(Client);
				cout << endl;
			}

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________________________________________\n" << endl;
		cout << "\n" << clsUtil::Tabs(6) << "Total Balances = " << TotalBalances;
		cout << "\n" << clsUtil::Tabs(6) << "( " << clsUtil::NumberToText(TotalBalances) << " )";

	}



};

