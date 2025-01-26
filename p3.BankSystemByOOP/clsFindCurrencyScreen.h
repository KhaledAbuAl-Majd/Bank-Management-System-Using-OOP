#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen {

    enum enFindCurrencyBy { eFindByCode = 1, eFindByCountry = 2 };

    static short _ReadFindByOption() {

        cout << "\nFind By: [1] Code or [2] Country ? ";
        return clsInputValidate::ReadShortNumberBetween(1, 2, "\nPlease enter a number between 1 & 2? ");
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

    static void _ShowResult(clsCurrency Currency) {

        if (!Currency.IsEmpty()) {

            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else {

            cout << "\nCurrency Is Not Fount :-(\n";
        }
    }

    static clsCurrency _FindByCode() {

        return clsCurrency::FindByCode(clsInputValidate::ReadString("\nPlease Enter CurrencyCode: "));
    }

    static clsCurrency _FindByCountry() {

        return clsCurrency::FindByCountry(clsInputValidate::ReadString("\nPlease Enter Country: "));
    }

    static clsCurrency _PerfromFindByOption(enFindCurrencyBy FindBy) {

        switch (FindBy) {

        case enFindCurrencyBy::eFindByCode: {

            return _FindByCode();
        }
        case enFindCurrencyBy::eFindByCountry: {

            return _FindByCountry();
        }
        }
    }


public:

    static void ShowFindCurrencyScreen() {

        _DrawScreenHeader("\t  Find Currency Screen");

        clsCurrency Currency1 = _PerfromFindByOption((enFindCurrencyBy)_ReadFindByOption());
        _ShowResult(Currency1);
    }
};

