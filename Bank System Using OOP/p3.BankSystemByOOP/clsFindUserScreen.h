#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsFindUserScreen : protected clsScreen {

	static void _PrintUser(clsUser User) {

		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFullName    : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}

public:

	static void ShowFindUserScreen() {

		_DrawScreenHeader("\t   Find User Screen");

		string UserName = clsInputValidate::ReadString("\nPlease Enter User Name: ");

		while (!clsUser::IsUserExist(UserName)) {

			UserName = clsInputValidate::ReadString("\nUser Name is not found, Choose another one: ");
		}

		clsUser User1 = clsUser::Find(UserName);

		if (!User1.IsEmpty()) {

			cout << "\nUser Found:-)\n";
		}
		else {

			cout << "\nUser was not Found :-(\n";
		}

		_PrintUser(User1);
	}
};

