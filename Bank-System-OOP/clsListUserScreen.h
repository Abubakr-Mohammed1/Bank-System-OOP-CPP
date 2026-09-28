#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsListUserScreen :protected clsScreen
{

private:

	static void _PrintUsersRecord(clsUser User)
	{
		cout << setw(8) << left << "" << "| " << left << setw(15) << User.UserName;
		cout << "| " << left << setw(20) << User.FullName();
		cout << "| " << left << setw(20) << User.Email;
		cout << "| " << left << setw(10) << User.Phone;
		cout << "| " << left << setw(12) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
	}



public:

		static void ShowUsersList()
	{

		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\t  User List Screen";
		string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(15) << "UserName";
		cout << "| " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Phone";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;

		if (vUsers.size() == 0)
			cout << clsUtil::Tabs(5) << "No Users Available In The System!";
		else

			for (clsUser& User : vUsers)
			{
				_PrintUsersRecord(User);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________\n" << endl;

	}



};

