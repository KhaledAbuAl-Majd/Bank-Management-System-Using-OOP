#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen {

	static void _ReadUserInfo(clsUser& User) {

		User.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
		User.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
		User.Email = clsInputValidate::ReadString("\nEnter Email: ");
		User.Phone = clsInputValidate::ReadString("\nEnter Phone: ");
		User.Password = clsInputValidate::ReadString("\nEnter Password: ");
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static int _ReadPermissionsToSet() {

		int Permission = 0;
		char Answer = 'n';

		cout << "\nEnter Permission:";
		cout << "\nDo you want to give Full access y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			return clsUser::enPermissions::eAll;
		}
		else {

			cout << "\nDo you want to give access to:\n";
			short Counter = 0;

			Counter++;
			cout << "\nShow List Clients y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pListClients;
			}

			Counter++;
			cout << "\nAdd New Client y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pAddNewClient;
			}

			Counter++;
			cout << "\nDelete Client y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pDeleteClient;
			}

			Counter++;
			cout << "\nUpdate Client y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pUpdateClient;
			}

			Counter++;
			cout << "\nFind Client y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pFindClient;
			}

			Counter++;
			cout << "\nTransactions y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::Transactions;
			}

			Counter++;
			cout << "\nManage Users y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pManageUsers;
			}

			Counter++;
			cout << "\nShow Login Register y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pShowLoginRegister;
			}

			Counter++;
			cout << "\nCurrencyExchange y/n? ";
			cin >> Answer;

			if (toupper(Answer) == 'Y') {

				Counter--;
				Permission += clsUser::enPermissions::pCurrecnyExchange;
			}

			if (Counter == 0)
				Permission = clsUser::enPermissions::eAll;
		}

		return Permission;
	}

public:

	static void ShowAddNewUserScreen() {

		_DrawScreenHeader("\t    Add New User");

		string UserName = clsInputValidate::ReadString("\nPlease Enter User Name: ");

		while (clsUser::IsUserExist(UserName)) {

			UserName = clsInputValidate::ReadString("\nUser Name Is already Used, Enter another one: ");
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(NewUser);

		cout << "\nAre you sure you want to add this User y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y') {

			NewUser.Save();
			cout << "\nUser addedd Successfully:-)\n";
			_PrintUser(NewUser);
		}
		else {

			cout << "\nAdding this User was Canceled\n";
		}
	}

};

