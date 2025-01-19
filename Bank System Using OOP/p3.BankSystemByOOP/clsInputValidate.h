#pragma once

#include<iostream>
#include<string>
#include"clsDate.h"

using namespace std;

class clsInputValidate
{

public:

	static bool IsNumberBetween(short Number, short From, short To) {

		if (From > To)
			swap(From, To);

		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To) {

		if (From > To)
			swap(From, To);

		return (Number >= From && Number <= To);
	}
	
	static bool IsNumberBetween(float Number, float From, float To) {

		if (From > To)
			swap(From, To);

		return (Number > From && Number < To);
	}
	
	static bool IsNumberBetween(double Number, double From, double To) {

		if (From > To)
			swap(From, To);

		return (Number >= From && Number <= To);
	}
	
	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo) {

		if (clsDate::IsDate1BeforeDate2(DateTo, DateFrom))
			clsDate::SwapDates(DateFrom, DateTo);

		return (!clsDate::IsDate1BeforeDate2(Date, DateFrom) && !clsDate::IsDate1BeforeDate2(DateTo, Date));
	}
	
	static int ReadIntNumber(string ErrorMessage="Invalid Number, Enter again: ")
	{
		int Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	/*static int ReadIntNumber(string Message,string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		int Number = 0;

		cout << Message;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}*/
	
	static short ReadShortNumber( string ErrorMessage = "Invalid Number, Enter again: ")
	{
		short Number = 0;


		while (!(cin>>Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	/*static short ReadShortNumber(string Message, string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		short Number = 0;

		cout << Message;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}*/
	
	static float ReadFloatNumber( string ErrorMessage = "Invalid Number, Enter again: ")
	{
		float Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	/*static float ReadFloatNumber(string Message, string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		float Number = 0;

		cout << Message;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}*/
	
	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again: ")
	{
		double Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}
	
	/*static double ReadDblNumber(string Message, string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		double Number = 0;

		cout << Message;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}*/
	
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage="Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To)) {

			cout << ErrorMessage;
			Number = ReadIntNumber();
		}

		return Number;
	}
	
	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To)) {

			cout << ErrorMessage;
			Number = ReadShortNumber();
		}

		return Number;
	}
	
	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To)) {

			cout << ErrorMessage;
			Number = ReadFloatNumber();
		}

		return Number;
	}
	
	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To)) {

			cout << ErrorMessage;
			Number = ReadDblNumber();
		}

		return Number;
	}
	
	static bool IsValidDate(clsDate Date) {

		return clsDate::IsValidDate(Date);
	}
	
	static int ReadIntpositiveNumber(string Message="Please enter a Positive Number: ")
	{
		int Number = 0;

		do
		{
			cout << Message;
			Number = ReadIntNumber();

		} while (Number <= 0);

		return Number;
	}

	static short ReadShortapositiveNumber(string Message="Please enter a Positive Number: ")
	{
		short Number = 0;

		do
		{
			cout << Message;
			Number = ReadShortNumber();

		} while (Number <= 0);

		return Number;
	}

	static float ReadFloatapositiveNumber(string Message="Please enter a Positive Number: ")
	{
		float Number = 0;

		do
		{
			cout << Message;
			Number = ReadFloatNumber();

		} while (Number <= 0);

		return Number;
	}

	static double ReadDbapositiveNumber(string Message="Please enter a Positive Number: ")
	{
		double Number = 0;

		do
		{
			cout << Message;
			Number = ReadDblNumber();

		} while (Number <= 0);

		return Number;
	}

	static int ReadIntpositiveNumberTo(int To,string Message = "Please enter a Positive Number: ")
	{
		int Number = 0;

		do
		{
			cout << Message;
			Number = ReadIntNumber();

		} while (Number <= 0 || Number > To);

		return Number;
	}

	static short ReadShortapositiveNumberTo(short To,string Message = "Please enter a Positive Number: ")
	{
		short Number = 0;

		do
		{
			cout << Message;
			Number = ReadShortNumber();

		} while (Number <= 0 || Number > To);

		return Number;
	}

	static float ReadFloatapositiveNumberTo(float To,string Message = "Please enter a Positive Number: ")
	{
		float Number = 0;

		do
		{
			cout << Message;
			Number = ReadFloatNumber();

		} while (Number <= 0 || Number > To);

		return Number;
	}

	static double ReadDblapositiveNumberTo(double To,string Message = "Please enter a Positive Number: ")
	{
		double Number = 0;

		do
		{
			cout << Message;
			Number = ReadDblNumber();

		} while (Number <= 0 || Number > To);

		return Number;
	}


	static string ReadString(string Message)
	{
		string S1 = "";

		cout << Message;
		getline(cin >> ws, S1);

		return S1;
	}

	static string ReadString()
	{
		string S1 = "";

		getline(cin >> ws, S1);

		return S1;
	}

	static char ReadCharcter(string Message) {

		char Charcter;

		cout << Message;
		cin >> Charcter;

		return Charcter;
	}
};

