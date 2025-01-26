#pragma once

#include<iostream>
#include<string>
#include<cstdlib>
#include"clsDate.h"
#include"clsInputValidate.h"

using namespace std;

class clsUtil
{

public:

    enum enCharType {
        SamallLetter = 1, CapitalLetter = 2,
        Digit = 3, MixChars = 4, SpecialCharacter = 5
    };

    static void  Srand()
    {
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    static  int GetRandomNumber(int From, int To)
    {
        //Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {

        //updated this method to accept mixchars
        if (CharType == MixChars)
        {
            //Capital/Samll/Digits only
            CharType = (enCharType)GetRandomNumber(1, 3);

        }

        switch (CharType)
        {

        case enCharType::SamallLetter:
        {
            return char(GetRandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(GetRandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(GetRandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(GetRandomNumber(48, 57));
            break;
        }
    defualt:
        {
            return char(GetRandomNumber(65, 90));
            break;
        }
        }
    }

    static  string GenerateWord(enCharType CharType, short Length)
    {
        string Word;

        for (int i = 1; i <= Length; i++)

        {

            Word = Word + GetRandomCharacter(CharType);

        }
        return Word;
    }

    static string  GenerateKey(enCharType CharType = CapitalLetter)
    {
        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {

        for (int i = 1; i <= NumberOfKeys; i++)

        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }

    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GetRandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);

    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    static  void Swap(int& A, int& B)
    {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(short& A, short& B)
    {
        short Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    
    static  void Swap(float& A, float& B)
    {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(double& A, double& B)
    {
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(bool& A, bool& B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(char& A, char& B)
    {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(string& A, string& B)
    {
        string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static  void Swap(clsDate& A, clsDate& B)
    {
        clsDate::SwapDates(A, B);

    }

    static  void ShuffleArray(int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[GetRandomNumber(1, arrLength) - 1], arr[GetRandomNumber(1, arrLength) - 1]);
        }

    }

    static  void ShuffleArray(string arr[100], int arrLength)
    {

        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[GetRandomNumber(1, arrLength) - 1], arr[GetRandomNumber(1, arrLength) - 1]);
        }

    }

    static string  Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;

    }

    static string  EncryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i < Text.length(); i++) {

            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string  DecryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i < Text.length(); i++) {

            Text[i] = char((int)Text[i] - EncryptionKey);
        }

        return Text;
    }

	static int GetReversedNumber(int Number) {

		int ReversedNumber = 0;
		int Remainder = 0;

		while (Number > 0) {

			Remainder = Number % 10;
			Number /= 10;
			ReversedNumber *= 10;
			ReversedNumber += Remainder;
			Remainder = 0;
		}

		return ReversedNumber;
	}

	static bool IsOdd(int Number)
	{
		return (Number % 2 != 0);
	}

	static bool IsAPrimeNumber(int Number)
	{
		int M = Number / 2;

		for (int i = 2; i <= M; i++)
		{
			if (Number % i == 0)
			{
				return false;
			}
		}

		return true;
	}

	static bool IsAPalindromeNumber(int Number) {

		int ReversedNumber = GetReversedNumber(Number);

		return (Number == ReversedNumber);
	}

	static int ToBit(int Number) {

		return pow(2, Number - 1);

	}

	static void ClearScreen() {

		system("cls");
	}

	static void AddArrayElement(int arr[100], int& arrLength, int Number)
	{
		arrLength++;
		arr[arrLength - 1] = Number;
	}

	static void FillArrayWith1toN(int arr[100], int N)
	{
		for (int i = 0; i < N; i++)
		{
			arr[i] = i + 1;
		}
	}

	static void ReverseOrderOfArrayElements(int arr[100], int Length)
	{
		for (int i = 0; i < Length / 2; i++)
		{
			swap(arr[i], arr[Length - i - 1]);
		}
	}

    static bool IsNumberBetween(short Number, short From, short To) {

        return clsInputValidate::IsNumberBetween(Number, From, To);
    }

    static bool IsNumberBetween(int Number, int From, int To) {

        return clsInputValidate::IsNumberBetween(Number, From, To);
    }

    static bool IsNumberBetween(float Number, float From, float To) {

        return clsInputValidate::IsNumberBetween(Number, From, To);
    }

    static bool IsNumberBetween(double Number, double From, double To) {

        return clsInputValidate::IsNumberBetween(Number, From, To);
    }

    char AskAddAgain()
    {
        char AddAgain = 'y';

        cout << "Do you want to add another element? Y/N ";
        cin >> AddAgain;

        return AddAgain;
    }

    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[Number] + " ";

        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return  "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return  "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return  "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return  "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }


    }
};

