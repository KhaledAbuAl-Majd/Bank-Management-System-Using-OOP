#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsFindClientScreen : protected clsScreen{

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

public:

	static void ShowFindClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
            return;

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty()) {

            cout << "\nCilent Found:-)\n";

        }
        else {

            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client1);
	}

};

