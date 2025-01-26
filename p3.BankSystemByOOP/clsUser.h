#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

string UsersFileName = "Users.txt";

class clsUser : public clsPerson {

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDeleted = false;
	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvrtLoginRegisterLineToRecord(string DataLine, string Seperator = "#//#") {

		stLoginRegisterRecord LoginRegisterRcord;
		vector <string> vLoginRegisterDataLine = clsString::Split(DataLine, Seperator);

		LoginRegisterRcord.DateTime = vLoginRegisterDataLine[0];
		LoginRegisterRcord.UserName = vLoginRegisterDataLine[1];
		LoginRegisterRcord.Password = clsUtil::DecryptText(vLoginRegisterDataLine[2]);
		LoginRegisterRcord.Permissions = stoi(vLoginRegisterDataLine[3]);

		return LoginRegisterRcord;
	}

	string _PrepareLogInRecord(string Seperator = "#//#") {

		return clsDate::GetSystemDateTimeString() + Seperator+ UserName 
			+ Seperator + clsUtil::EncryptText(Password) + Seperator + to_string(Permissions);
	}

	static clsUser _ConvertLineToUserObject(string DataLine,string Seperator="#//#") {

		vector<string>vUserData = clsString::Split(DataLine,Seperator);

		if (vUserData.size() < 6) {

			cout << "\nErore in User Data Line!";
			system("pause>0");
		}

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4],
			clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {

		return User.FirstName + Seperator + User.LastName + Seperator + User.Email + Seperator
			+ User.Phone + Seperator + User.UserName + Seperator + clsUtil::EncryptText(User.Password) + Seperator + to_string(User.Permissions);
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				vUsers.push_back(_ConvertLineToUserObject(Line));
			}
			MyFile.close();
		}
		else {

			cout << "\nErro Opening file!\n";
		}

		return vUsers;
	}

	static void _SaveUserDataToFile(vector <clsUser> vUsers) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open()) {

			for (clsUser User : vUsers) {


				if (!User._MarkedForDeleted) {

					MyFile << _ConvertUserObjectToLine(User) << endl;
				}
			}

			MyFile.close();
		}
		else {

			cout << "\nError Opening file!\n";
		}
	}

	void _Update() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser & User : vUsers) {

			if (User.UserName == UserName) {

				User = *this;
				break;
			}
		}

		_SaveUserDataToFile(vUsers);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string DataLine) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();
		}
		else {

			cout << "\nError Opeining File!\n";
		}
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	enum enPermissions {

		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, Transactions = 32, pManageUsers = 64, pShowLoginRegister = 128, pCurrecnyExchange = 256
	};

	struct stLoginRegisterRecord {

		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode,string FirstName,string LastName,string Email,string Phone,string UserName,string Password,int Permissions) 
		: clsPerson(FirstName,LastName,Email,Phone) {

		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {

		return _Mode == enMode::EmptyMode;
	}

	bool MarkedForDeleted() {

		return _MarkedForDeleted;
	}

	void SetUserName(string UsrName) {

		_UserName = _UserName;
	}

	string GetUserName() {

		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName))string UserName;

	void SetPassword(string Password) {

		_Password = Password;
	}

	string GetPassword() {

		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	void SetPermissions(int Permissions) {

		_Permissions = Permissions;
	}

	int GetPermissions() {

		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;

	static clsUser Find(string UserName) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName) {

					MyFile.close();
					return User;
				}

			}

			MyFile.close();
			return _GetEmptyUserObject();
		}
		else {

			cout << "\nError Opening File!\n";
		}
	}

	static clsUser Find(string UserName,string Password) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password) {

					MyFile.close();
					return User;
				}

			}

			MyFile.close();
			return _GetEmptyUserObject();
		}
		else {

			cout << "\nError Opening File!\n";
		}
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save() {

		switch (_Mode) {

		case enMode::EmptyMode: {

			return enSaveResults::svFaildEmptyObject;
			break;
		}
		case enMode::UpdateMode: {

			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode: {

			if (IsUserExist(_UserName)) {

				return enSaveResults::svFaildUserExists;
			}
			else {

				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool IsUserExist(string UserName) {

		clsUser User = Find(UserName);

		return !User.IsEmpty();
	}

	bool Delete() {

		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers) {

			if (User.UserName == _UserName) {

				User._MarkedForDeleted = true;
				break;
			}
		}

		_SaveUserDataToFile(vUsers);
		*this= _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string UserName) {

		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList() {

		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission) {

		return ((Permission == enPermissions::eAll) || ((Permission & this->Permissions) == Permission));
	}

	/*void ClearRegisterHistory(string FileName = "LoginRegister.txt") {

		fstream MyFile;
		MyFile.open(FileName, ios::out);

		if (!MyFile.is_open()) {

			cout << "\nError Opening File!\n";
		}
	}*/

	void RegisterLogIn() {

		string DataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();
		}
		else {

			cout << "\nError Opening File!\n";
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {

		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				vLoginRegisterRecord.push_back(_ConvrtLoginRegisterLineToRecord(Line));
			}

			MyFile.close();
		}
		else {

			cout << "\nError Opening File!\n";
		}

		return vLoginRegisterRecord;
	}

};

