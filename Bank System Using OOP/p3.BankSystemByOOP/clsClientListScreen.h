#pragma once

#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsClientListScreen : protected clsScreen {

    static void _PrintClientRecordLine(clsBankClient Client) {

        cout << setw(8) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(20) << Client.Email;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }

public:

    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
            return;

        vector<clsBankClient>vClients = clsBankClient::GetClientsList();

        string Title = "\t  Client List Screen";
        string SubTitle = "\t   (" + to_string(vClients.size()) + ") Clients(s)";

        _DrawScreenHeader(Title,SubTitle);
     
  
        cout << setw(8)<<left<<"\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8)<<left<<""<<"| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Eamil";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8)<<left<<""<<"\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0) {

            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else {

            for (clsBankClient Client : vClients) {

                _PrintClientRecordLine(Client);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

