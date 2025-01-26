#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsDepositScreen : protected clsScreen {

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

	static void ShowDepositScreen() {

		_DrawScreenHeader("\t    Deposit Screen");

		string AccountNumber = _ReadAcountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			printf("\nClient with [%s] does not exist.\n", AccountNumber.c_str());
			AccountNumber = _ReadAcountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		double Amount = clsInputValidate::ReadDbapositiveNumber("\nPlease enter deposite amount? ");

		cout << "\nAre you sure you want to peform this transactins? y/n ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			Client1.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is : " << Client1.AccountBalance << endl;
		}
		else {

			cout << "\nOperation was canselled.\n";
		}

	}
};

