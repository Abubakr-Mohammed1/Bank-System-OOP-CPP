#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient :public clsPerson
{

private:

	enum eMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	eMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;


	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "///")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(eMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "///")
	{
		string stClientRecord = "";

		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	string _prepareTransferRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "///")
	{
		string TransferRecord = "";

		TransferRecord += clsDate::GetSystemDateAndTime() + Seperator;
		TransferRecord += AccountNumber() + Seperator;
		TransferRecord += DestinationClient.AccountNumber() + Seperator;
		TransferRecord += to_string(Amount) + Seperator;
		TransferRecord += to_string(AccountBalance) + Seperator;
		TransferRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferRecord += UserName;

		return TransferRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
	{

		string DateLine = _prepareTransferRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("Transfer.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << endl;
			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(eMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> _LoadClientsDataFormFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;

	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string Line;

		if (MyFile.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					Line = _ConvertClientObjectToLine(C);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}

	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFormFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	struct sTransferRegisterRecord;
	static sTransferRegisterRecord _ConvertTransferRegisterToRecord(string Line, string Seperator = "///")
	{
		vector <string> vtransferRegisterData;
		vtransferRegisterData = clsString::Split(Line, Seperator);
		sTransferRegisterRecord TransferRegisterRecord;

		TransferRegisterRecord.DateTime = vtransferRegisterData[0];
		TransferRegisterRecord.SourceAccount = vtransferRegisterData[1];
		TransferRegisterRecord.DestinationAccount = vtransferRegisterData[2];
		TransferRegisterRecord.Amount = stof(vtransferRegisterData[3]);
		TransferRegisterRecord.SourceBalance = stof(vtransferRegisterData[4]);
		TransferRegisterRecord.DestinationBalance = stof(vtransferRegisterData[5]);
		TransferRegisterRecord.UserName = (vtransferRegisterData[6]);

		return TransferRegisterRecord;

	}





public:

	struct sTransferRegisterRecord
	{
		string DateTime;
		string SourceAccount;
		string DestinationAccount;
		float Amount;
		float SourceBalance;
		float DestinationBalance;
		string UserName;
	};

	clsBankClient(eMode Mode, string AccountNumber, string PinCode,
		string FirstName, string LastName, string Email, string Phone,
		float AccountBalance) :clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == eMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	//void Print()
	//{
	//	cout << "\nInfo:";
	//	cout << "\n----------------------------------";
	//	cout << "\nFirstName   : " << FirstName;
	//	cout << "\nLastName    : " << LastName;
	//	cout << "\nFullName    : " << FullName();
	//	cout << "\nAcc. Number : " << _AccountNumber;
	//	cout << "\nPassword    : " << _PinCode;
	//	cout << "\nEmail       : " << Email;
	//	cout << "\nPhone       : " << Phone;
	//	cout << "\nBalance     : " << _AccountBalance;
	//	cout << "\n----------------------------------\n";
	//}

	enum eSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

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
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return eSaveResults::svFaildAccountNumberExists;
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
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFormFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static clsBankClient Find(string AccountNumber)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyClientObject();

	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();
		}

		return _GetEmptyClientObject();

	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(eMode::AddNewMode, AccountNumber, "", "", "", "", "", 0);
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFormFile();
	}

	static double GetTotalBalance()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFormFile();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}

	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);

		return true;
	}

	static vector <sTransferRegisterRecord> GetTransferRegisterList()
	{
		vector <sTransferRegisterRecord> vTransferRegisterRecord;

		fstream MyFile;
		MyFile.open("Transfer.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			sTransferRegisterRecord TransferRegisterRecord;

			while (getline(MyFile, Line))
			{
				TransferRegisterRecord = _ConvertTransferRegisterToRecord(Line);

				vTransferRegisterRecord.push_back(TransferRegisterRecord);
			}

			MyFile.close();
		}

		return vTransferRegisterRecord;
	}











};

