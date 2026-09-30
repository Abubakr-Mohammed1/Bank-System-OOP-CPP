#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include <iomanip>

using namespace std;

class clsLoginRegisterScreen :protected clsScreen
{

private:

	static void _PrintUsersLoginRegisterLine(clsUser::sLoginRegisterRecord Record)
	{
		cout << setw(8) << left << "" << "| " << left << setw(35) << Record.DateTime;
		cout << "| " << left << setw(20) << Record.UserName;
		cout << "| " << left << setw(20) << Record.Password;
		cout << "| " << left << setw(10) << Record.Permissions;
	}



public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::ePermissions::pLoginRegisterList))
		{
			return;
		}

		vector <clsUser::sLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;

		if (vLoginRegisterRecord.size() == 0)
			cout << clsUtil::Tabs(5) << "No Logins Available In The System!";
		else
			for (clsUser::sLoginRegisterRecord& Record : vLoginRegisterRecord)
			{
				_PrintUsersLoginRegisterLine(Record);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;


	}


};

