#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen {

	static bool _Login() {

		string UserName = "";
		string Password = "";
		bool LoginFaild = false;
		short FaildLoginCount = 0;
		
		do {

			if (LoginFaild){

				FaildLoginCount++;
				cout << "\nInvalid UserName/Password!";
				cout << "\nYou have " << (3 - FaildLoginCount) << " Trial(s) to login.\n\n";

				if (FaildLoginCount == 3){

					cout << "\nYou are locked after 3 faild trails\n\n";
					return false;
				}
			}

			UserName = clsInputValidate::ReadString("Enter UserName? ");
			Password = clsInputValidate::ReadString("Enter Password? ");

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}
};

