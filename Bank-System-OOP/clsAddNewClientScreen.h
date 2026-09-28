#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen :protected clsScreen
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
        cout << "\nFirstName   : " <<Client.FirstName;
        cout << "\nLastName    : " <<Client.LastName;
        cout << "\nFullName    : " <<Client.FullName();
        cout << "\nAcc. Number : " <<Client.AccountNumber();
        cout << "\nPassword    : " <<Client.PinCode;
        cout << "\nEmail       : " <<Client.Email;
        cout << "\nPhone       : " <<Client.Phone;
        cout << "\nBalance     : " <<Client.AccountBalance;
        cout << "\n-----------------------------\n";
    }



public:


    static void ShowAddNewClientScreen()
    {

        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number (" << AccountNumber << ") is already used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        ///*cout << "\nAdding New Client:";
        //cout << "\n-------------------\n";*/

        _ReadClientInfo(NewClient);

        clsBankClient::eSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {

        case clsBankClient::eSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it is empty.";
            break;
        }

        case clsBankClient::eSaveResults::svSucceeded:
        {
            cout << "\nAccount Added Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }

        case clsBankClient::eSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }



        }

    }


};

