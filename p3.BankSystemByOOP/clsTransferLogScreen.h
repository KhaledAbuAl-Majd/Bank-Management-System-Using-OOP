#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen {
    
    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLog) {

        cout << setw(8) << left << "" << "| " << left << setw(23) << TransferLog.DateTime;
        cout << "| " << left << setw(8) << TransferLog.SourceAccountNumber;
        cout << "| " << left << setw(8) << TransferLog.DestinationAccountNumber;
        cout << "| " << left << setw(8) << TransferLog.Amount;
        cout << "| " << left << setw(10) << TransferLog.srcBalanceAfter;
        cout << "| " << left << setw(10) << TransferLog.desBalanceAfter;
        cout << "| " << left << setw(8) << TransferLog.UserName;
    }

public:

	static void ShowLogTransferScreen() {

		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogList();

		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t     (" + to_string(vTransferLogRecord.size()) + ") Record(s)";

		_DrawScreenHeader(Title,SubTitle);

        cout << setw(8) << left << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0) {

            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else {

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord) {

                _PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}
};

