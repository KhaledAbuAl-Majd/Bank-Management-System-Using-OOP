#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "Global.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen{

    enum enCurrenciesMainMenueOptions { eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3, eCurrencyCalaculator = 4, MainMenue = 5 };

    static short _ReadCurrencyExchangeMenueOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        return clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
    }

    static void _GoBackToCurrenciesMenue() {

        cout << "\n\tPress any key to go back to Main Menue...\n";
        system("pause>0");
        ShowCurrenciesMenue();
    }

    static void _ShowCurrenciesListScreen() {

       /* cout << "\nList Currencies Screen Will be here...\n";*/
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen() {

       /* cout << "\nFind Currency Screen Will be here...\n";*/
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen() {

        /*cout << "\nUpdate Rate Screen Will be here...\n";*/
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalcualtorScreen() {

       /* cout << "\nCurrency Calaculator Screen Will be here...\n";*/
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrenciesMainMenueOption(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions) {

        switch (CurrenciesMainMenueOptions) {

        case enCurrenciesMainMenueOptions::eListCurrencies: {

            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenue();
            break;
        }
        case enCurrenciesMainMenueOptions::eFindCurrency: {

            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;
        }
        case enCurrenciesMainMenueOptions::eUpdateCurrencyRate: {

            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenue();
            break;
        }
        case enCurrenciesMainMenueOptions::eCurrencyCalaculator: {

            system("cls");
            _ShowCurrencyCalcualtorScreen();
            _GoBackToCurrenciesMenue();
            break;
        }
        case enCurrenciesMainMenueOptions::MainMenue: {


        }
        }
    }

public:

	static void ShowCurrenciesMenue() {

		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pCurrecnyExchange))
			return;

        system("cls");
		_DrawScreenHeader("   Currency Exhange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calaculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrenciesMainMenueOption((enCurrenciesMainMenueOptions)_ReadCurrencyExchangeMenueOption());
	}
};

