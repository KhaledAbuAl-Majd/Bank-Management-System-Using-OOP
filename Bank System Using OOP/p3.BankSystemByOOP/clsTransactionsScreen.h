#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsUser.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen  {

private:

    enum enTransactionsOptions { eDeposit = 1, Withdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6 };

    static short _ReadTransactionsMenueOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowDepositScreen() {

       /* cout << "\nDeposit Screen Will be here...\n";*/
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen() {

       /* cout << "\nWithdraw Screen Will be here...\n";*/
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen() {

        /*cout << "\n Balances Screen Will be here...\n";*/
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen() {

        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {

        clsTransferLogScreen::ShowLogTransferScreen();
    }

    static void _GoBackToTransactionsMenue() {

        cout << setw(37) << left << "" << "\nPress any key to go back to Transactions Menue...\n";

        system("pause>0");
        ShowTranscationsMenue();
    }  

    static void _PerformTransactionsMenueOptions(enTransactionsOptions TransactionsOptions) {

        switch (TransactionsOptions) {

        case enTransactionsOptions::eDeposit: {

            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsOptions::Withdraw: {

            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsOptions::eTotalBalances: {

            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsOptions::eTransfer: {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsOptions::eTransferLog: {

            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsOptions::eShowMainMenue: {

        }

        }
    }

public:

	static void ShowTranscationsMenue() {

        if (!CheckAccessRights(clsUser::enPermissions::Transactions))
            return;

        system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOptions((enTransactionsOptions)_ReadTransactionsMenueOption());
	}
};

