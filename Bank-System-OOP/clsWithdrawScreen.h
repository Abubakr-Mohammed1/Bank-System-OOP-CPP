#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen :protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n-----------------------------";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n-----------------------------\n";
	}

	static string _ReadAccountNumer()
	{
		cout << "\nPlease Enter Account Number: ";
		string AccNumer = clsInputValidate::ReadString();
		return AccNumer;
	}



public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t   Withdraw Screen");

		string AccountNumber = _ReadAccountNumer();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient With Account Number [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumer();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		float Amount = 0;
		cout << "\nPlease enter withdraw amount? ";
		Amount = clsInputValidate::ReadPositiveNumber<float>("Invalid amount, Enter a valid one: ");

		cout << "\nAre you sure you want to perform this transactions? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client1.Withdraw(Amount))
			{
				cout << "\nAmount Withdrawed Successfully.\n";
				cout << "\nNew Balance is: " << Client1.AccountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insufficient Balance!\n";
				cout << "\nAmount to withdraw is " << Amount;
				cout << "\nYour Balance is " << Client1.AccountBalance;
			}

		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}


	}



};

