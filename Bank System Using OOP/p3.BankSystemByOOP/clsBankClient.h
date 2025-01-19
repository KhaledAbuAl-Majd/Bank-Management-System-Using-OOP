#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
#include <iomanip>
#include "clsUtil.h"

//static short EncryptionKey = 2;

string FileName = "Clients.txt";

class clsBankClient : public clsPerson {

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode=2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelte = false;
	

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {

		vector<string>vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4],clsUtil::DecryptText(vClientData[5]) , stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client,string Seperator = "#//#") {

		return Client.FirstName + Seperator + Client.LastName + Seperator + Client.Email + Seperator + Client.Phone + Seperator + Client.AccountNumber()
			+ Seperator + clsUtil::EncryptText(Client.PinCode) + Seperator + to_string(Client.AccountBalance);
	}

	static vector<clsBankClient>_LoadClientsDataFromFile() {
		
		vector<clsBankClient>vClients;
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line = "";

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();
		}
		else {

			cout << "Erorr opening file!\n";
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient>vClients) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

			string DataLine = "";

		if (MyFile.is_open()) {


			for (clsBankClient C : vClients) {

				if (!C.MarkedForDelted()) {

					DataLine = _ConvertClientObjectToLine(C);

					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
		else {

			cout << "Eror Opening file!\n";
		}
	}

	void _Update() {

		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber()) {

				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static void _AddDataLineToFile(string DataLine) {

		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();
		}
		else {

			cout << "Error Opening file!\n";
		}
	}

	static clsBankClient _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,string UserName, string Seperator = "#//#") {

		return clsDate::GetSystemDateTimeString() + Seperator + _AccountNumber + Seperator + DestinationClient.AccountNumber()
			+ Seperator + to_string(Amount) + Seperator + to_string(AccountBalance) + Seperator
			+ to_string(DestinationClient.AccountBalance) + Seperator +UserName;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient,string UserName ) {

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << _PrepareTransferLogRecord(Amount, DestinationClient, UserName) << endl;

			MyFile.close();
		}
		else {

			cout << "\nError Opening File!\n";
		}
	}

	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string DataLine, string Seperator = "#//#") {

		vector <string> vString = clsString::Split(DataLine, Seperator);
		stTransferLogRecord TransferLog;

		TransferLog.DateTime = vString[0];
		TransferLog.SourceAccountNumber = vString[1];
		TransferLog.DestinationAccountNumber = vString[2];
		TransferLog.Amount = stof(vString[3]);
		TransferLog.srcBalanceAfter = stof(vString[4]);
		TransferLog.desBalanceAfter = stof(vString[5]);
		TransferLog.UserName = vString[6];

		return TransferLog;
	}

public:

	struct stTransferLogRecord {

		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float desBalanceAfter;
		string UserName;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName,LastName,Email,Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelted() {

		return _MarkedForDelte;
	}

	 string AccountNumber() {

		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {

		_PinCode = PinCode;
	}

	string GetPinCode() {

		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;

	void SetAccountBalance(float AccountBalance) {

		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {

		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	 static clsBankClient Find(string AccountNumber) {

		 vector<clsBankClient>vClient;

		 fstream MyFile;

		 MyFile.open("Clients.txt", ios::in);

		 if (MyFile.is_open()) {

			 string Line = "";
			 
			 while (getline(MyFile, Line)) {

				 clsBankClient Client = _ConvertLineToClientObject(Line);

				 if (Client.AccountNumber() == AccountNumber) {

					 MyFile.close();
					 return Client;
				 }

				 vClient.push_back(Client);
			 }

			 MyFile.close();

		 }
		 else {

			 cout << "Error Opening File!\n";
		 }

		 return _GetEmptyClientObject();
	 }

	 static clsBankClient Find(string AccountNumber,string PinCode) {

		 vector<clsBankClient>vClient;

		 fstream MyFile;

		 MyFile.open("Clients.txt", ios::in);

		 if (MyFile.is_open()) {

			 string Line = "";

			 while (getline(MyFile, Line)) {

				 clsBankClient Client = _ConvertLineToClientObject(Line);

				 if (Client._AccountNumber == AccountNumber && Client._PinCode==PinCode) {

					 MyFile.close();
					 return Client;
				 }
				 vClient.push_back(Client);
			 }

			 MyFile.close();
		 }
		 else {

			 cout << "Error Opening File!\n";
		 }

		 return _GetEmptyClientObject();
	 }

	 enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1,svFaildAccountNumberExists };

	 enSaveResults Save() {

		 switch (_Mode) {

		 case enMode::EmptyMode: {

			 return enSaveResults::svFaildEmptyObject;
		 }
		 case enMode::UpdateMode: {

			 _Update();

			 return enSaveResults::svSucceeded;
			
			 break;
		 }
		 case enMode::AddNewMode: {

			  if (IsClientExist(_AccountNumber))
			  {
				  return enSaveResults::svFaildAccountNumberExists;
			  }
			  else {

				  _AddNew();

				  _Mode = enMode::UpdateMode;
				  return enSaveResults::svSucceeded;
			  }
		 }

		 }	
	 }

	 static bool IsClientExist(string AccountNumber) {

		 clsBankClient Client = Find(AccountNumber);

		 return (!Client.IsEmpty());
	 }

	  bool Delete() {

		 vector<clsBankClient>vClients = _LoadClientsDataFromFile();

		 for (clsBankClient& C : vClients) {

			 if (C.AccountNumber() == AccountNumber()) {

				 C._MarkedForDelte = true;
				 break;
			 }
		 }

		 _SaveClientsDataToFile(vClients);

		 *this = _GetEmptyClientObject();
		 
		 return true;
	 }

	 static clsBankClient GetAddNewClientObject(string AccountNumber) {

		 return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	 }

	 static vector <clsBankClient> GetClientsList() {

		 return _LoadClientsDataFromFile();
	 }

	 static double GetTotalBalances() {

		 vector<clsBankClient>vClients = GetClientsList();
		 double TotalBalance = 0;

		 for (clsBankClient Client : vClients) {

			 TotalBalance += Client.AccountBalance;
		 }

		 return TotalBalance;
	 }

	 void Deposit(double Amount) {

		 _AccountBalance += Amount;
		 Save();
	 }

	 bool Withdraw(double Amount) {

		 if (Amount > _AccountBalance || Amount<=0) {

			 return false;
		 }
		 else {

			 _AccountBalance -= Amount;
			 Save();
		 }
	 }

	 bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName) {

		 if (Amount > _AccountBalance)
			 return false;

		 if (DestinationClient._AccountNumber == this->_AccountNumber) {

			 cout << "\nError You Cannot transre to the same Account!\n";
			 return false;
		 }
	
		 Withdraw(Amount);
		 DestinationClient.Deposit(Amount);

		 _RegisterTransferLog(Amount, DestinationClient,UserName);

		 return true;
	 }

	 static vector <stTransferLogRecord> GetTransferLogList() {

		 vector <stTransferLogRecord> vTransferLogRecord;

		 fstream MyFile;
		 MyFile.open("TransferLog.txt", ios::in);

		 if (MyFile.is_open()) {

			 string Line = "";

			 while (getline(MyFile, Line)) {

				 vTransferLogRecord.push_back(_ConvertTransferLogLineToRecord(Line));
			 }

			 MyFile.close();
		 }
		 else {

			 cout << "\nError Opening File!\n";
		 }

		 return vTransferLogRecord;
	 }
};