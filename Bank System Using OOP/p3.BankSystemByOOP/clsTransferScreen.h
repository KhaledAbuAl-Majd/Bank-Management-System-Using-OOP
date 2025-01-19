#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen {

	static void _PrintClientCard(clsBankClient Client) {

		cout << "\nClient Card:";
		cout << "\n___________________\n";
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber(string AccountNumberFrom="") {

		string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number to Transfer To: ");

		while (!clsBankClient::IsClientExist(AccountNumber) || (AccountNumber == AccountNumberFrom)) {

			if ((AccountNumber == AccountNumberFrom)) {

				cout << "\nYou Cannot transfer to the same Account you transfer from!";
				AccountNumber = clsInputValidate::ReadString("\nEnter another one: ");
			}
			else
				AccountNumber = clsInputValidate::ReadString("\nClient Is Not Found, Enter another one: ");
		}
		return AccountNumber;
	}

	static float _ReadAmount(clsBankClient SourceClient) {

		cout << "\nEnter Transfer Amount? ";
		double Amount = clsInputValidate::ReadDblNumber();
		bool InValidAmount = false;

		do {
		
			if (Amount <= 0) {

				InValidAmount = true;
				cout << "\nEnter a Positive Amount? ";
				Amount = clsInputValidate::ReadDblNumber();
			}
			else if (Amount >SourceClient.AccountBalance) {

				InValidAmount = true;
				cout << "\nAmmount Exceeds the available Balance, Enter another Amount? ";
				Amount = clsInputValidate::ReadDblNumber();
			}
			else {

				InValidAmount = false;
			}

		} while (InValidAmount);
	
		return Amount;
	}

public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t   Transfer Screen");

		string AccountNumberFrom = _ReadAccountNumber();

		clsBankClient SourceCleint = clsBankClient::Find(AccountNumberFrom);
		_PrintClientCard(SourceCleint);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber(AccountNumberFrom));
		_PrintClientCard(DestinationClient);

		float Amount = _ReadAmount(SourceCleint);

		cout << "\nAre you sure you want to Perfrom this Operation y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			if (SourceCleint.Transfer(Amount,DestinationClient,CurrentUser.UserName)) {

				cout << "\nTransfer done Successfully\n";
			}
			else {

				cout << "\nTransfer Faild!\n";
			}

			_PrintClientCard(SourceCleint);
			_PrintClientCard(DestinationClient);
		}
		else {

			cout << "\nOperation Was Cancelled!\n";
		}
	}

};

