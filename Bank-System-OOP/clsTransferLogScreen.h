#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen :protected clsScreen
{

private:


	static void _PrintTransferRegisterLine(clsBankClient::sTransferRegisterRecord Record)
	{
		cout << setw(8) << left << "" << "| " << left << setw(23) << Record.DateTime;
		cout << "| " << left << setw(8) << Record.SourceAccount;
		cout << "| " << left << setw(8) << Record.DestinationAccount;
		cout << "| " << left << setw(8) << Record.Amount;
		cout << "| " << left << setw(10) << Record.SourceBalance;
		cout << "| " << left << setw(10) << Record.DestinationBalance;
		cout << "| " << left << setw(8) << Record.UserName;
	}




public:

	static void ShowTransferRegisterScreen()
	{

		vector <clsBankClient::sTransferRegisterRecord> vTransferRegisterRecord = clsBankClient::GetTransferRegisterList();

		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t\t(" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acc";
		cout << "| " << left << setw(8) << "d.Acc";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;

		if (vTransferRegisterRecord.size() == 0)
			cout << clsUtil::Tabs(5) << "No Transfers founded In The System!";
		else
			for (clsBankClient::sTransferRegisterRecord& Record : vTransferRegisterRecord)
			{
				_PrintTransferRegisterLine(Record);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;


	}



};

