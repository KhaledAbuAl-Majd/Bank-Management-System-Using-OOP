#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen	{

    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord Record) {

        cout << setw(8) << left << "" << "| " << left << setw(35) << Record.DateTime;
        cout << "| " << left << setw(20) << Record.UserName;
        cout << "| " << left << setw(20) << Record.Password;
        cout << "| " << left << setw(10) << Record.Permissions;
    }

public:

	static void ShowLoginRegisterScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pShowLoginRegister)) {

            return;
        }

		vector<clsUser::stLoginRegisterRecord> vRegisters = clsUser::GetLoginRegisterList();

		string Title = "\t Login Register Screen";
		string SubTitle = "\t    (" + to_string(vRegisters.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vRegisters.size() == 0) {

            cout << "\t\t\t\tNo Logins Available In the System!\n";
        }
 
        for (clsUser::stLoginRegisterRecord Record : vRegisters) {

            _PrintLoginRegisterRecordLine(Record);
            cout << endl;
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
	}
};

