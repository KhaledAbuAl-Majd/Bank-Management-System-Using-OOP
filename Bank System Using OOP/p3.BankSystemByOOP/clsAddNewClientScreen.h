#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen {

private:

    static void _ReadClientInfo(clsBankClient & Client) {


        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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

    static void ShowAddNewClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            return;

        _DrawScreenHeader("\t    Add New Client");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount Number Is already Used, Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();

        switch (SaveResult) {

        case clsBankClient::svSucceeded: {

            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::svFaildEmptyObject: {

            cout << "\nErorr account was not saved because it's Empty";
            break;
        }
        case clsBankClient::svFaildAccountNumberExists: {

            cout << "\nFaild Account Already in used.\n";
            break;
        }
        }

    }
};
