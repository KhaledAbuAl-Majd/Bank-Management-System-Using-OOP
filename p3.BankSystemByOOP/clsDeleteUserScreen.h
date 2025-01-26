#pragma once

#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen{

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

	static void ShowDeleteUserScreen() {

		_DrawScreenHeader("\tDelete User Screen");

		string userName = clsInputValidate::ReadString("\nPlease enter User Name: ");

		while (!clsUser::IsUserExist(userName)) {

			userName = clsInputValidate::ReadString("\nUser is not found, Choose another one: ");
		}

		clsUser User1 = clsUser::Find(userName);
		_PrintUser(User1);

		cout << "\nAre you sure you want to delete this User y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			if (User1.Delete()) {

				cout << "\nUser Deleted Successfully\n";
				_PrintUser(User1);
			}
			else {

				cout << "\nError User Was not Deleted\n";
			}
		}
		else {

			cout << "\nDelete User Was Cancelled\n";
		}
	}
};

