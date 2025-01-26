#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen{

	static float _ReadRate() {

		return clsInputValidate::ReadFloatapositiveNumber("\nEnter New Rate: ");
	}

	static void _PrintCurrency(clsCurrency Currency) {

		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_____________________________\n";
	}

public:

	static void ShowUpdateCurrencyRateScreen() {

		_DrawScreenHeader("\t Update Currency Screen");

		string CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			CurrencyCode = clsInputValidate::ReadString("\nCurrency is not found, choose another one: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		char Answer = clsInputValidate::ReadCharcter("\nAre you sure you want to update the rate of this Currency y/n? ");

		if (toupper(Answer) == 'Y') {

			cout << "\nUpdate Currency Rate:";
			cout << "\n_____________________________\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);
		}
		else {

			cout << "\nOperation Cancelled!\n";
		}
	
	}

};

