#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsUser :public clsPerson
{

private:

	enum eMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	eMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "///")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(eMode::UpdateMode, vUserData[0], vUserData[1], stoi(vUserData[2]), vUserData[3],
			vUserData[4], vUserData[5], vUserData[6]);

	}

	string _ConvertUserObjectToLogFile(string Seperator = "///")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateAndTime() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += Password + Seperator;
		LoginRecord += to_string(Permissions) + Seperator;
		LoginRecord += FirstName;

		return LoginRecord;
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "///")
	{
		string stUserRecord = "";

		stUserRecord += User.UserName + Seperator;
		stUserRecord += User.Password + Seperator;
		stUserRecord += to_string(User.Permissions) + Seperator;
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Email + Seperator;
		stUserRecord += User.Phone;

		return stUserRecord;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(eMode::EmptyMode, "", "", 0, "", "", "", "");
	}

	static vector <clsUser> _LoadUsersDataFormFile()
	{

		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;

	}

	static void _SaveUserDataToFile(vector <clsUser> vUser)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string Line;

		if (MyFile.is_open())
		{
			for (clsUser U : vUser)
			{
				if (U.MarkedForDelete() == false)
				{
					Line = _ConvertUserObjectToLine(U);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}

	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _Update()
	{
		vector <clsUser> _vUser;
		_vUser = _LoadUsersDataFormFile();

		for (clsUser& U : _vUser)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}

		_SaveUserDataToFile(_vUser);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}







public:

	enum ePermissions {
		pFullAccess = -1, pShowClientsList = 1, pAddNewClient = 2, pDeleteClient = 4
		, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
	};

	clsUser(eMode Mode, string UserName, string Password, int Permissions,
		string FirstName, string LastName, string Email, string Phone) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == eMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	enum eSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	eSaveResults Save()
	{
		switch (_Mode)
		{

		case eMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return eSaveResults::svFaildEmptyObject;
				break;
			}
		}

		case eMode::UpdateMode:
		{
			_Update();

			return eSaveResults::svSucceeded;
		}

		case eMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return eSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode = eMode::UpdateMode;
				return eSaveResults::svSucceeded;
			}
		}



		}
	}

	bool Delete()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFormFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkedForDelete = true;
				break;
			}
		}

		_SaveUserDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser Find(string UserName)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUserObject();

	}

	static clsUser Find(string UserName, string Password)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();
		}

		return _GetEmptyUserObject();

	}

	static bool IsUserExist(string UserName)
	{
		clsUser User1 = clsUser::Find(UserName);

		return (!User1.IsEmpty());
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(eMode::AddNewMode, UserName, "", 0, "", "", "", "");
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFormFile();
	}

	bool CheackAccessPermissions(ePermissions Permissions)
	{
		if (this->Permissions == ePermissions::pFullAccess)
			return true;

		if ((Permissions & this->Permissions) == Permissions)
			return true;
		else
			return false;
	}

	void RegisterLogin()
	{
		string Line = _ConvertUserObjectToLogFile();

		fstream MyFile;
		MyFile.open("log.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << Line << endl;
			MyFile.close();
		}
	}












};

