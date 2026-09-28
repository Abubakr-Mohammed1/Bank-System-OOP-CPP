#pragma once
#include <iostream>
#include "clsMainScreen.h"
#include "global.h"

class clsLoginScreen :protected clsScreen
{

private:

	static void _Login()
	{
		bool LoginFaild = false;
		string Username, Password;

		do
		{

			if (LoginFaild)
			{
				cout << "\nInvalid Username/Passwored!\n";
			}

			cout << "Enter Username? ";
			getline(cin >> ws, Username);

			cout << "Enter Password? ";
			getline(cin >> ws, Password);

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenue();
	}


public:


	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");

		_Login();


	}


};

