#pragma once

#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen {

	static float _ReadAmount() {

		return clsInputValidate::ReadFloatapositiveNumber("\nEnter Amount To Exchange: ");
	}

	static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
	{

		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_____________________________\n\n";

	}

	static clsCurrency _GetCurrency(string Message) {

		string CurrencyCode = clsInputValidate::ReadString(Message);

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			CurrencyCode = clsInputValidate::ReadString("\nCurrency Code is not found, Choose another one: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static void _PrintCalaculationResult(float Amount, clsCurrency Currency1, clsCurrency Currency2) {

		_PrintCurrencyCard(Currency1, "Convert From:");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD") {

			return;
		}

		cout << "\nConverting from USD to:\n";
		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode();
	}

public:

	static void ShowCurrencyCalculatorScreen() {

		char Continue = 'y';

		while (toupper(Continue) == 'Y') {

			system("cls");
			_DrawScreenHeader("\t   Currency Calculator");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalaculationResult(Amount, CurrencyFrom, CurrencyTo);

			Continue = clsInputValidate::ReadCharcter("\n\nDo you want to perform another Calculation? y/n? ");
		}	
	}

};

