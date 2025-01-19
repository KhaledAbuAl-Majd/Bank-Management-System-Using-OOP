#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen {

private:

	static void _PrintClient(clsBankClient  Client) {

		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFullName    : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static string _ReadAcountNumber() {

		cout << "\nPlease Enter Account Number? ";
		return clsInputValidate::ReadString();
	}

public:

	static void ShowWithdrawScreen() {

		_DrawScreenHeader("\t    Withdraw Screen");

		string AccountNumber = _ReadAcountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			printf("\nClient with [%s] does not exist.\n", AccountNumber.c_str());
			AccountNumber = _ReadAcountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		double Amount = clsInputValidate::ReadDbapositiveNumber("\nPlease enter Withdraw amount? ");

		cout << "\nAre you sure you want to peform this transactins? y/n ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			if (Client1.Withdraw(Amount)) {

				cout << "\nAmount Withdraw Successfully.\n";
				cout << "\nNew Balance Is : " << Client1.AccountBalance << endl;
			}
			else {

				cout << "\nCannot Withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance << endl;
			}
		}
		else {

			cout << "\nOperation was canselled.\n";
		}
	}
};

