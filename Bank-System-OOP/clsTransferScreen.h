#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsTransferScreen :protected clsScreen
{

private:

	static string _ReadAccountNumer(string Message = "\nPlease Enter Account Number: ")
	{
		string AccountNumber;
		cout << Message;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient With Account Number [" << AccountNumber << "] does not exist, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n-----------------------------";
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n-----------------------------\n";
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		cout << "\nEnter Transfer Amount? ";
		double Amount = 0;
		Amount = clsInputValidate::ReadPositiveDblNumber("Invalid amount, Enter a valid one: ");

		while (SourceClient.AccountBalance < Amount)
		{
			cout << "\nAmount Exceeds the available balance, Enter another amount: ";
			Amount = clsInputValidate::ReadPositiveDblNumber("Invalid amount, Enter a valid one: ");
		}

		return Amount;
	}


public:

	static void ShowTransferScreen()
	{

		_DrawScreenHeader("\t    Transfer Screen");


		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumer("\nPlease Enter Account Number to transfer from: "));
		_PrintClient(SourceClient);


		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumer("\nPlease Enter Account Number to transfer To: "));
		_PrintClient(DestinationClient);


		float Amount = _ReadAmount(SourceClient);


		cout << "\nAre you sure you want to perform this Operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully.\n";
			}
			else
			{
				cout << "\nTransfer Faild.\n";
			}

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);

	}


};

