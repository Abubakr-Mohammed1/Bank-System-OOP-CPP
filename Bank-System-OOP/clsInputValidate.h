#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsString.h"
#include <string>

using namespace std;

class clsInputValidate
{

public:

    static bool IsNumberBetween(short Num, short From, short To)
    {
        if (Num >= From && Num <= To)
            return true;
        else
            return false;
    }

    static bool IsNumberBetween(int Num, int From, int To)
    {
        if (Num >= From && Num <= To)
            return true;
        else
            return false;
    }

    static bool IsNumberBetween(float Num, float From, float To)
    {
        if (Num >= From && Num <= To)
            return true;
        else
            return false;
    }

    static bool IsNumberBetween(double Num, double From, double To)
    {
        if (Num >= From && Num <= To)
            return true;
        else
            return false;
    }

    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
    {
        if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
            &&
            (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
            )
        {
            return true;
        }

        if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
            &&
            (clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
            )
        {
            return true;
        }

        return false;
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter a valid one : \n")
    {
        int Number;
       
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << ErrorMessage;

        }

        return Number;
    }

    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter a valid one : \n")
    {
        double Number;
       
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << ErrorMessage;

        }

        return Number;
    }

    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter a valid one : \n")
    {
        float Number;
       
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << ErrorMessage;

        }

        return Number;
    }

    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Invalid Number, Enter a valid one : ")
    {
        int Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }

        return Number;
    }

    static int ReadshortNumberBetween(short From, short To, string ErrorMessage = "Invalid Number, Enter a valid one : ")
    {
        short Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }

        return Number;
    }

    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Invalid Number, Enter a valid one : ")
    {
        double Number = ReadDblNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }

        return Number;
    }

    static bool IsValideDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }

    static string ReadString()
    {
        string  S1 = "";
        getline(cin >> ws, S1);
        return S1;
    }

    static int ReadPositiveintNumber(string ErrorMessage = "Invalid Number, Enter a valid one : \n")
    {
        int Number = 0;
        
        Number = ReadIntNumber();
		while (Number <= 0)
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }

        return Number;
    }

    static double ReadPositiveDblNumber(string ErrorMessage = "Invalid Number, Enter a valid one : \n")
    {
        double Number = 0;
        
        Number = ReadDblNumber();
		while (Number <= 0)
        {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }

        return Number;
    }

};

