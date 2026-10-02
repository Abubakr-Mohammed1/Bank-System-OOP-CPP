#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsCurrency
{

private:

	enum eMode { EmptyMode = 0, UpdateMode = 1 };
	eMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "///")
	{
		vector <string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(eMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));

	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "///")
	{
		string sCurrencyRecord = "";

		sCurrencyRecord += Currency.Country() + Seperator;
		sCurrencyRecord += Currency.CurrencyCode() + Seperator;
		sCurrencyRecord += Currency.CurrencyName() + Seperator;
		sCurrencyRecord += to_string(Currency.Rate());

		return sCurrencyRecord;
	}

	static vector <clsCurrency> _LoadCurrenciesDataFormFile()
	{

		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;

	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string Line;

		if (MyFile.is_open())
		{
			for (clsCurrency& C : vCurrencies)
			{

				Line = _ConvertCurrencyObjectToLine(C);
				MyFile << Line << endl;

			}

			MyFile.close();
		}

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(eMode::EmptyMode, "", "", "", 0);
	}



	void _Update()
	{
		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurrenciesDataFormFile();

		for (clsCurrency& C : _vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrenciesDataToFile(_vCurrencies);
	}




public:

	clsCurrency(eMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == eMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();

	}

	static clsCurrency FindByCountry(string Country)
	{

		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);

		return (!C1.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFormFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency CurrencyTo)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * CurrencyTo.Rate());


	}









};

