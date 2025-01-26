#pragma once

#include <iostream>
#include <vector>
#include "fstream"
#include <string>
#include "clsString.h"

using namespace std;

string CurrencyFileName = "Currencies.txt";

class clsCurrency {

	enum enMode { EmptyMode = 0, UpdateMode = 2 };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string DataLine, string Seperator = "#//#") {

		vector <string> vCurrencyData = clsString::Split(DataLine, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {

		return Currency._Country + Seperator + Currency._CurrencyCode + Seperator + Currency._CurrencyName + Seperator + to_string(Currency._Rate);
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile() {

		vector <clsCurrency> vCurrencys;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				vCurrencys.push_back(_ConvertLineToCurrencyObject(Line));
			}

			MyFile.close();
		}
		else {

			cout << "\nError Opening File!\n";
		}

		return vCurrencys;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open()) {

			for (clsCurrency Currency : vCurrencys) {

				MyFile << _ConvertCurrencyObjectToLine(Currency) << endl;
			}

			MyFile.close();
		}
		else {

			cout << "\nError Opening File!\n";
		}
	}

	void _Update() {

		vector <clsCurrency> vCurrencys = _LoadCurrencyDataFromFile();

		for (clsCurrency & Currency : vCurrencys) {

			if (Currency.CurrencyCode() == CurrencyCode()) {

				Currency = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject() {

		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode,string Country,string CurrencyCode,string CurrencyName,float Rate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector <clsCurrency> GetAllUSDRates() {

		return _LoadCurrencyDataFromFile();
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	string Country() {

		return _Country;
	}

	string CurrencyCode() {

		return _CurrencyCode;
	}

	string CurrencyName() {

		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {

		_Rate = NewRate;
		_Update();
	}

	float Rate() {

		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllLString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == CurrencyCode) {

					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();
		}
		else {

			cout << "\nError Opning File!\n";
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllLString(Currency.Country()) == clsString::UpperAllLString(Country)) {

					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();
		}
		else {

			cout << "\nError Opning File!\n";
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {

		return (!clsCurrency::FindByCode(CurrencyCode).IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList() {

		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount) {

		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {

		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD") {

			return AmountInUSD;
		}

		return AmountInUSD * Currency2.Rate();
	}
};

