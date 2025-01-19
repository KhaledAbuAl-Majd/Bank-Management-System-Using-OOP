#pragma once

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class clsString
{  
	string _Value;

public:

	clsString() {

		_Value = "";
	}

	clsString(string Value) {

		_Value = Value;
	}

	void SetValue(string Value) {

		this->_Value = Value;
	}

	string GetValue() {

		return this->_Value;
	}

	__declspec(property(get = GetValue, put = SetValue))string Value;

	static short Length(string S1) {

		return S1.length();
	}

	short Length() {

		return Length(_Value);
	}

	static short CountWords(string Text) {

		string Delim = " ";
		short Counter = 0;
		short Pos = 0;
		string sWord = "";

		while ((Pos = Text.find(Delim)) != std::string::npos) {

			sWord = Text.substr(0, Pos);

			if (sWord != "") {

				Counter++;
			}

			Text.erase(0, (Pos + Delim.length()));
		}

		if (Text != "") {

			Counter++;
		}

		return Counter;
	}

	short CountWords() {

		return CountWords(_Value);
	}

	static void PrintFirstLetterOfEachWordInString(string Text) {

		bool IsFirstLetter = true;

		cout << "\nFirst Letter of this string:\n";

		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && IsFirstLetter) {

				cout << Text[i] << "\n";
			}

			IsFirstLetter = (Text[i] == ' ') ? true : false;
		}

	}

	void PrintFirstLetterOfEachWordInString() {

		PrintFirstLetterOfEachWordInString(_Value);
	}

	static string UpperFirstLetterOfEachWord(string Text) {

		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && IsFirstLetter) {

				Text[i] = toupper(Text[i]);
			}

			IsFirstLetter = (Text[i] == ' ') ? true : false;
		}

		return Text;
	}

	void UpperFirstLetterOfEachWord() {

		_Value= UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string Text){

		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && IsFirstLetter) {

				Text[i] = tolower(Text[i]);
			}

			IsFirstLetter = (Text[i] == ' ') ? true : false;
		}

		return Text;
	}

	void LowerFirstLetterOfEachWord() {

		_Value= LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllLString(string Text) {

		for (short i = 0; i < Text.length(); i++) {

			Text[i] = toupper(Text[i]);
		}

		return Text;
	}

	void UpperAllLString() {

		_Value= UpperAllLString(_Value);
	}

	static string LowerAllString(string Text) {

		for (short i = 0; i < Text.length(); i++) {

			Text[i] = tolower(Text[i]);
		}

		return Text;
	}

	void LowerAllString() {

		_Value= LowerAllString(_Value);
	}

	static char InvertLetterCase(char Character) {

		return (isupper(Character)) ? tolower(Character) : toupper(Character);
	}

	static string InvertAllLettersCase(string Text) {

		for (short i = 0; i < Text.length(); i++) {

			Text[i] = InvertLetterCase(Text[i]);
		}

		return Text;
	}

	void InvertAllLettersCase() {

		_Value= InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { CapitalLetters = 0, SmallLetters = 1, Punctuatoin = 2, Digits = 3, All = 4 };

	static short CountLetters(string Text, enWhatToCount WhatToCount = enWhatToCount::All) {

		short Counter = 0;

		switch (WhatToCount) {

		case enWhatToCount::All:
		{
			return Text.length();
			break;
		}
		case enWhatToCount::SmallLetters:
		{
			return CountSmallLetters(Text);
			break;
		}
		case enWhatToCount::CapitalLetters:
		{
			return CountCapitalLetters(Text);
			break;
		}
		case enWhatToCount::Punctuatoin:
		{
			return CountPunctuatoin(Text);
			break;
		}
		case enWhatToCount::Digits:
		{
			return CountDigits(Text);
			break;
		}
		default:
			return Text.length();

		}

	}

	short CountLetters( enWhatToCount WhatToCount = enWhatToCount::All) {

		return CountLetters(_Value, WhatToCount);
	}

	static short CountCapitalLetters(string Text) {

		short Counter = 0;

		for (short i = 0; i < Text.length(); i++) {

			if (isupper(Text[i])) {

				Counter++;
			}
		}

		return Counter;
	}

	short CountCapitalLetters() {

		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string Text) {

		short Counter = 0;

		for (short i = 0; i < Text.length(); i++) {

			if (islower(Text[i])) {

				Counter++;
			}
		}

		return Counter;
	}

	short CountSmallLetters() {

		return CountSmallLetters(_Value);
	}

	static short CountPunctuatoin(string Text) {

		short Counter = 0;

		for (short i = 0; i < Text.length(); i++) {

			if (ispunct(Text[i])) {

				Counter++;
			}

		}

		return Counter;
	}

	short CountPunctuatoin() {

		return CountPunctuatoin(_Value);
	}

	static short CountDigits(string Text) {

		short Counter = 0;

		for (short i = 0; i < Text.length(); i++) {

			if (isdigit(Text[i])) {

				Counter++;
			}
		}

		return Counter;
	}

	short CountDigits() {

		return CountDigits(_Value);
	}

	static short CountSepecificLetter(string Text, char Letter, bool MatchCase = true) {

		//ignore case 

		short Counter = 0;

		for (short i = 0; i < Text.length(); i++) {


			if (MatchCase) {

				if (Text[i] == Letter)
					Counter++;
			}
			else {

				if (tolower(Text[i]) == tolower(Letter))
					Counter++;
			}

		}

		return Counter;
	}

	short CountSpecificLetter(char Letter, bool MatchCase = true) {

		return CountSepecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Character) {

		Character = tolower(Character);

		return ((Character == 'a') || (Character == 'e') || (Character == 'i') || (Character == 'o') || (Character == 'u'));
	}

	static short CountVowels(string Text) {

		short Counter = 0;

		for (short i = 0; i < Text.length(); i++) {

			if (IsVowel(Text[i])) {

				Counter++;
			}
		}

		return Counter;
	}

	short CountVowels() {

		return CountVowels(_Value);
	}

	static void printVowels(string Text) {

		cout << "\nVowels in string are: ";

		for (short i = 0; i < Text.length(); i++) {

			if (IsVowel(Text[i])) {

				cout << Text[i] << "    ";
			}
		}
		cout << endl;
	}

	void printVowels() {

		printVowels(_Value);
	}

	static vector<string> Split(string Text, string Delim) {

		vector <string> vString;

		short Pos = 0;
		string sWord = "";

		while ((Pos = Text.find(Delim)) != std::string::npos) {

			sWord = Text.substr(0, Pos);

			if (sWord != "") {

				vString.push_back(sWord);
			}

			Text.erase(0, (Pos + Delim.length()));
		}

		if (Text != "") {

			vString.push_back(Text);
		}

		return vString;
	}

	vector<string> Split(string Delim) {

		return  Split(_Value,Delim);
	}

	static string TrimLeft(string Text) {

		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ') {

				return Text.substr(i, Text.length() - i);
			}
		}

		return "";
	}

	string TrimLeft() {

		return TrimLeft(_Value);
	}

	static string TrimRight(string Text) {

		for (short i = Text.length() - 1; i >= 0; i--) {

			if (Text[i] != ' ') {

				return Text.substr(0, i + 1);
			}
		}

		return "";
	}

	string TrimRight() {

		return TrimRight(_Value);
	}

	static string Trim(string Text) {

		return (TrimLeft(TrimRight(Text)));
	}

	string Trim() {

		return Trim(_Value);
	}

	static string JoinString(vector<string>& vString, string Delim=" ") {

		string sWord = "";

		for (const string& Token : vString) {

			sWord += Token + Delim;
		}

		return sWord.substr(0, (sWord.length() - Delim.length()));
	}

	static string JoinString(string arrString[], short Length, string Delim=" ") {

		string sWord = "";

		for (short i = 0; i < Length; i++) {

			sWord += arrString[i] + Delim;
		}

		return sWord.substr(0, (sWord.length() - Delim.length()));
	}

	static string ReverseWordsInString(string Text) {

		vector<string>vString;
		vString = Split(Text, " ");

		string ReversedString = "";

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin()) {

			--iter;

			ReversedString += *iter + " ";

		}


		return ReversedString.substr(0, ReversedString.length() - 1);
	}

	void ReverseWordsInString() {

		_Value= ReverseWordsInString(_Value);
	}

	static string ReplaceWordIgnoreSpace(string Text, string StringToReplace, string StringReplaceTo) {

		//يستبدل اي مقطع يحتوي هذه الكلمه

		short Pos = Text.find(StringToReplace);

		while (Pos != std::string::npos) {

			Text = Text.replace(Pos, StringToReplace.length(), StringReplaceTo);
			Pos = Text.find(StringToReplace);
		}

		return Text;
	}

	string ReplaceWordIgnoreSpace(string StringToReplace, string StringReplaceTo) {

		return ReplaceWordIgnoreSpace(_Value, StringToReplace, StringReplaceTo);
	}

	static string ReplaceWord(string Text, string StringToReplace, string StringReplaceTo, bool MatchCase = true) {

		//يستبدل الكلمة لو كانت كلمة منفرده حسب delimeter

		vector<string>vString;
		vString = Split(Text, " ");

		for (string& Token : vString) {

			if (MatchCase) {

				if (Token == StringToReplace) {

					Token = StringReplaceTo;
				}
			}
			else
			{

				if (LowerAllString(Token) == LowerAllString(StringToReplace)) {

					Token = StringReplaceTo;
				}
			}
		}

		return JoinString(vString, " ");
	}

	string ReplaceWord(string StringToReplace, string StringReplaceTo, bool MatchCase = true) {

		return  ReplaceWord( _Value, StringToReplace, StringReplaceTo,  MatchCase );
	}

	static string RemovenPauncuationsFromString(string Text) {

		string S2 = "";

		for (short i = 0; i < Text.length(); i++) {

			if (!ispunct(Text[i])) {

				S2 += Text[i];
			}
		}

		return S2;
	}

	void RemovenPauncuationsFromString() {

		_Value= RemovenPauncuationsFromString(_Value);
	}

};

