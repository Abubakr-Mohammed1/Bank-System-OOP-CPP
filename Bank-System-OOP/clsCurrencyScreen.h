#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyScreen :protected clsScreen
{

private:

	enum eCurrencyMenueOptions { eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencuCalculator = 4, eMainMenue = 5 };

	static short _ReadCurrencyMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 5 ? ");
		return Choice;
	}

	static void _GoBackToCurrencyMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency menue...";

		system("pause>0");
		ShowCurrencyMenue();
	}

	static void _ShowListCurrenciesScreen()
	{
		//cout << "\nList Currencies Screen Will be here...\n";
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen Will be here...\n";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		//cout << "\nUpdate Rate Screen Will be here...\n";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen Will be here...\n";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}




	static void _ActivateCurrencyMenue(eCurrencyMenueOptions CurrencyMenueOption)
	{
		switch (CurrencyMenueOption)
		{
		case clsCurrencyScreen::eListCurrencies:
		{
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case clsCurrencyScreen::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case clsCurrencyScreen::eUpdateRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case clsCurrencyScreen::eCurrencuCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyMenue();
			break;
		}
		case clsCurrencyScreen::eMainMenue:
		{
			//nothing
		}

		}
	}


public:


	static void ShowCurrencyMenue()
	{
		system("cls");
		_DrawScreenHeader("    Currency Exchange Main Screen");

		cout << left;
		cout << setw(37) << "" << "==========================================\n";
		cout << setw(37) << "" << clsUtil::Tabs(1) << "Currency Exchange Menue\n";
		cout << setw(37) << "" << "==========================================\n";
		cout << setw(37) << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << "" << "==========================================\n\n";

		_ActivateCurrencyMenue((eCurrencyMenueOptions)_ReadCurrencyMenueOption());
	}

	

};

