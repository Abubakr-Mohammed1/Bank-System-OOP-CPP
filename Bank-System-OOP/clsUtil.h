#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUtil
{

public:

	enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4, MixChars = 5 };

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		int RandNum = rand() % (To - From + 1) + From;

		return RandNum;
	}

	static char GetRandomCharacter(enCharType CharType)
	{

		if (CharType == enCharType::MixChars)
		{
			CharType = (enCharType)RandomNumber(1, 4);
		}

		switch (CharType)
		{

		case enCharType::SmallLetter:
		{
			return char(RandomNumber(97, 122));
			break;
		}
		case enCharType::CapitalLetter:
		{
			return char(RandomNumber(65, 90));
			break;
		}
		case enCharType::SpecialCharacter:
		{
			return char(RandomNumber(33, 47));
			break;
		}
		case enCharType::Digit:
		{
			return char(RandomNumber(48, 57));
			break;
		}

		}
	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word = "";

		for (int i = 1; i <= Length; i++)
		{
			Word = Word + GetRandomCharacter(CharType);
		}
		return Word;
	}

	static string GenerateKey(enCharType CharType = CapitalLetter)
	{
		string Key = "";

		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		cout << "\n";

		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
		}
	}

	static string EncryptText(string Text, short EncryptionKey = 4)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 4)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(From, To);
	}

	static void FillArrayWithKeys(string arr[100], int arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short WordLength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, WordLength);
	}

	static void FillArrayWith1toN(int arr[100], int arrLength)
	{

		for (int i = 0; i < arrLength; i++)
			arr[i] = i + 1;
	}

	static void CopyArray(int arrSource[100], int arrDestination[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			arrDestination[i] = arrSource[i];
		}
	}

	static void Swap(int& Num1, int& Num2)
	{
		int Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(double& Num1, double& Num2)
	{
		double Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& S1, string& S2)
	{
		string Temp;

		Temp = S1;
		S1 = S2;
		S2 = Temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate::SwapDates(Date1, Date2);
	}

	static void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static string  Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i <= NumberOfTabs; i++)
		{
			t = t + "        ";
			//cout << t;
		}
		return t;

	}

	static string Spaces(short NumberOfSpaces)
	{
		string Spaces = "";

		for (short i = 1; i <= NumberOfSpaces; i++)
		{
			Spaces += " ";
		}

		return Spaces;
	}

	static string NumberToText(int Number)
	{
		string OnesArr[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
	"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

		string TensArr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			return OnesArr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			return TensArr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + " Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + " Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + " Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return NumberToText(Number / 1000000000) + " Billion " + NumberToText(Number % 1000000000);
		}

	}

















};

