#pragma once
#include <iostream>
#include "clsMainScreen.h"
#include "global.h"

class clsLoginScreen :protected clsScreen
{

private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCount = 0;
		string Username, Password;

		do
		{

			if (LoginFaild)
			{
				FaildLoginCount++;

				cout << "\nInvalid Username/Passwored!\n";
				cout << "You have " << (3 - FaildLoginCount) << " Trail(s) to login.\n\n";

			}

			if (FaildLoginCount == 3)
			{
				cout << "\nYou are locked after 3 faild trails.\n\n";
				return false;
			}

			cout << "Enter Username? ";
			getline(cin >> ws, Username);

			cout << "Enter Password? ";
			getline(cin >> ws, Password);

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenue();
		return true;
	}


public:


	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");

		return _Login();


	}


};

