#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen :protected clsScreen
{
	
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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

    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::ePermissions::pUpdateClient))
        {
            return;
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient With Account Number (" << AccountNumber << ") is not found, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nUpdate Client Info:";
        cout << "\n-------------------\n";

        _ReadClientInfo(Client1);

        clsBankClient::eSaveResults SaveResult;

        SaveResult = Client1.Save();

        switch (SaveResult)
        {

        case clsBankClient::eSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it is empty.";
            break;
        }

        case clsBankClient::eSaveResults::svSucceeded:
        {
            cout << "\nClient Updated Successfully :-)\n";
            _PrintClient(Client1);
            break;
        }



        }

    }


};

