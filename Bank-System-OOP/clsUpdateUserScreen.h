#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen :protected clsScreen
{

private:

	static void _ReadUserInfo(clsUser& User)
	{

		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissions();
	}

	static int _ReadPermissions()
	{
		int Permissions = 0;
		char Access = 'n';

		cout << "\nDo you want to give full access? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to :\n";

		cout << "\nShow Clients List? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pShowClientsList;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pUpdateClient;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pTransactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pManageUsers;
		}

		cout << "\nShow Login Register List? y/n? ";
		cin >> Access;
		if (toupper(Access) == 'Y')
		{
			Permissions += clsUser::ePermissions::pLoginRegisterList;
		}

		return Permissions;
	}

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


	static void ShowUpdateUserScreen()
	{

		_DrawScreenHeader("\tUpdate User Screen");

		string UserName = "";

		cout << "\nPlease Enter User Name: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser With User Name (" << UserName << ") is not found, Enter another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

		cout << "\nUpdate User Info:";
		cout << "\n-------------------\n";

		_ReadUserInfo(User1);

		clsUser::eSaveResults SaveResult;

		SaveResult = User1.Save();

		switch (SaveResult)
		{

		case clsUser::eSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it is empty.";
			break;
		}

		case clsUser::eSaveResults::svSucceeded:
		{
			cout << "\nUser Updated Successfully :-)\n";
			_PrintUser(User1);
			break;
		}



		}

	}



};

