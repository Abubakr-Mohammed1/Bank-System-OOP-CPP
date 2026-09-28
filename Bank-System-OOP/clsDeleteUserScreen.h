#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserscreen:protected clsScreen
{

private:

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n-----------------------------";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFullName    : " << User.FullName();
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n-----------------------------\n";
	}



public:

    static void ShowDeleteUsercreen()
    {

        _DrawScreenHeader("\tDelete User Screen");


        string UserName = "";

        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name (" << UserName << ") is not found, Enter another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        char Answer = 'n';
        cout << "\n\nDo you want to delete this User? y/n ? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (User1.Delete())
            {
                cout << "\n\nUser Deleted Successfully.\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was Not Deleted\n";
            }

        }
        else
        {
            cout << "\nUser with User Name (" << UserName << ") Not Deleted!";
        }



    }



};

