#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen :protected clsScreen
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



public:


    static void ShowDeleteClientScreen()
    {

        if (!CheckAccessRights(clsUser::ePermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\tDelete Client Screen");


        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number (" << AccountNumber << ") is not found, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        char Answer = 'n';
        cout << "\n\nDo you want to delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.Delete())
            {
                cout << "\n\nClient Deleted Successfully.\n";
                _PrintClient(Client1);
            }
            else
            {
                cout << "\nError Client Was Not Deleted\n";
            }

        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber << ") Not Deleted!";
        }



    }


};

