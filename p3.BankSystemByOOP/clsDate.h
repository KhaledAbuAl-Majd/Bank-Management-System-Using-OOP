#pragma once
#pragma warning (disable : 4996);

#include<iostream>
#include<string>
#include<vector>
#include"clsString.h";

using namespace std;

class clsDate 
{
	short _Day = 0;
	short _Month = 0;
	short _Year = 0;

public:

	clsDate() {

		SystemDate();
	}

	clsDate(string DateString) {

		StringToDate(DateString);
	}

	clsDate(short Day, short Month, short Year) {

		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrder, short Year) {

		_Year = Year;
		GetDateFromDayOrderInyear(DayOrder);
	}

	void SetDay(short Day) {

		_Day = Day;
	}

	short GetDay() {

		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay))short Day;

	void SetMonth(short Month) {

		_Month = Month;
	}

	short GetMonth() {

		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth))short Month;

	void SetYear(short Year) {

		_Year = Year;
	}

	short GetYear() {

		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear))short Year;

	void Print() {

		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		clsDate DateNow;
		DateNow.Day = now->tm_mday;
		DateNow.Month = now->tm_mon + 1;
		DateNow._Year = now->tm_year + 1900;

		return DateNow;
	}

	void SystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	static bool IsValidDate(clsDate Date) {

		return (Date._Year < 1) ? false : (Date._Month < 1 || Date._Month>12) ? false :
			(Date._Day<1 || Date._Day>NumberOfDaysInMonth(Date._Month, Date._Year) ? false : true);
	}

	bool IsValid() {

		return IsValidDate(*this);
	}

	static string DateToString(short Day, short Month, short Year) {

		clsDate Date;
		Date.Day = Day;
		Date.Month = Month;
		Date.Year = Year;

		return DateToString(Date);
	}

	static string DateToString(clsDate Date) {

		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date._Year);
	}

	string DateToString() {

		return DateToString(*this);
	}

	static bool IsLeapYear(short Year) {

		return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
	}

	bool IsLeapYear() {

		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInYear(short Year) {

		return(IsLeapYear(Year)) ? 366 : 365;
	}

	short NumberOfDaysInYear() {

		return NumberOfDaysInYear(_Year);
	}

	static short NumberOfHoursInYear(short Year) {

		return NumberOfDaysInYear(Year) * 24;
	}

	short NumberOfHoursInYear() {

		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short Year) {

		return NumberOfHoursInYear(Year) * 60;
	}

	int NumberOfMinutesInYear() {

		return NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short Year) {

		return NumberOfMinutesInYear(Year) * 60;
	}

	int NumberOfSecondsInYear() {

		return NumberOfSecondsInYear(_Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year) {

		if (Month < 1 || Month>12) {
			return 0;
		}

		short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}

	short NumberOfDaysInMonth() {

		return NumberOfDaysInMonth(_Month, _Year);
	}

	static short NumberOfHoursInMonth(short Year, short Month) {

		return NumberOfDaysInMonth(Year, Month) * 24;
	}

	short NumberOfHoursInMonth() {

		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInMonth(short Year, short Month) {

		return NumberOfHoursInMonth(Year, Month) * 60;
	}

	int NumberOfMinutesInMonth() {

		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month) {

		return NumberOfMinutesInMonth(Year, Month) * 60;
	}

	int NumberOfSecondsInMonth() {

		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year) {

		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + (12 * a) - 2;
		//Gregorian
		//0:sun,1:Mon,2:Tue..etc
		return(Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date) {

		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	short DayOfWeekOrder() {

		return DayOfWeekOrder(*this);
	}

	static string DayShortName(short DayOfWeekOrder) {

		string arrDayName[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDayName[DayOfWeekOrder];
	}

	static string DayShortName(short Day, short Month, short Year) {

		return DayShortName(DayOfWeekOrder(Day, Month, Year));
	}

	static string DayShortName(clsDate Date) {

		return DayShortName(DayOfWeekOrder(Date));
	}

	string DayShortName() {

		return DayShortName(*this);
	}

	static string MonthShortName(short Month) {

		string arrMonthName[12] = { "Jan","Feb","Mar","Apr","May","Jun","July","Aug","Sep","Oct","Nov","Dec" };

		return arrMonthName[Month - 1];
	}

	string MonthShortName() {

		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year) {

		short NumberOfDaysInaMonth =NumberOfDaysInMonth(Month, Year);
		int Current = DayOfWeekOrder(1, Month, Year);

		printf("\n _______________%s_________________\n\n", MonthShortName(Month).c_str());

		printf("  Sun  Mon  Tue   Wed Thu  Fri  Sat\n");

		short i = 0;

		for (i = 0; i < Current; i++) {

			printf("     ");
		}

		for (short j = 1; j <= NumberOfDaysInaMonth; j++) {

			printf("%5d", j);

			if (++i == 7 && j != NumberOfDaysInaMonth) {
				i = 0;
				printf("\n");
			}
		}

		printf("\n ___________________________________");
	}

	void PrintMonthCalendar() {

		PrintMonthCalendar(this->Month, this->Year);
	}

	static void PrintYearCalendar(short Year) {

		printf("\n ___________________________________\n\n");
		printf("\t  Calendar - %d", Year);
		printf("\n ___________________________________\n\n");

		for (short i = 1; i <= 12; i++) {

			PrintMonthCalendar(i, Year);
			cout << endl;
		}
	}

	void PrintYearCalendar() {

		PrintYearCalendar(this->Year);
	}

	static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year) {

		short TotalDays = 0;

		for (short i = 1; i < Month; i++) {

			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	static short DaysFromTheBeginingOfTheYear(clsDate Date) {

		return DaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);
	}

	short DaysFromTheBeginingOfTheYear() {

		return DaysFromTheBeginingOfTheYear(*this);
	}

	static clsDate GetDateFromDayOrderInyear(short DateOrderInYear, short Year) {

		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date._Year = Year;
		Date._Month = 1;

		while (true) {

			MonthDays = NumberOfDaysInMonth(Date._Month, Year);

			if (RemainingDays > MonthDays) {

				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else {

				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	void GetDateFromDayOrderInyear(short DateOrderInYear) {

		*this = GetDateFromDayOrderInyear(DateOrderInYear, _Year);
	}

	static clsDate AddDays(short NumberOfDaysToAdd, clsDate & Date) {

		short RemainingDays = NumberOfDaysToAdd + DaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date._Year);
		short MonthsDays = 0;
		Date.Month = 1;


		while (true) {

			MonthsDays = NumberOfDaysInMonth(Date.Month, Date._Year);

			if (RemainingDays > MonthsDays) {

				RemainingDays -= MonthsDays;
				Date.Month++;

				if (Date.Month > 12) {

					Date.Month = 1;
					Date._Year++;
				}
			}
			else {
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	void AddDays(short NumberOfDaysToAdd) {

		 AddDays(NumberOfDaysToAdd, *this);
	}//

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2) {

		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1IsEqualToData2(clsDate Date1, clsDate Date2) {

		return ((Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false) : false);
	}

	bool IsDateEqualToDate2(clsDate Date2) {

		return IsDate1IsEqualToData2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return(!IsDate1BeforeDate2(Date1, Date2) && !IsDate1IsEqualToData2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2) {

		IsDate1AfterDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date) {

		return(Date._Day == NumberOfDaysInMonth(Date._Month, Date._Year));
	}

	bool IsLastDayInMonth() {

		return IsLastDayInMonth(*this);
	}

	static bool IsFirstDayInMonth(clsDate Date) {

		return(Date._Day == 1);
	}

	bool IsFirstDayInMonth() {

		return IsFirstDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {

		return (Month == 12);
	}

	bool IsLastMonthInYear() {

		return IsLastMonthInYear(_Month);
	}

	static bool IsEndOfWeek(clsDate Date) {

		return DayOfWeekOrder(Date) == 6;
	}

	bool IsEndOfWeek() {

		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {

		//weekends are Fri and Sat
		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd() {

		return IsWeekEnd(*this);
	}

	static bool isBusinessDay(clsDate Date) {

		return(!IsWeekEnd(Date));
	}

	bool isBusinessDay() {

		return isBusinessDay(*this);
	}

	void StringToDate(string DateString) {

		vector<string>vDate = clsString::Split(DateString, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy") {

		string FormattedDateString = "";

		FormattedDateString = clsString::ReplaceWordIgnoreSpace(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = clsString::ReplaceWordIgnoreSpace(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = clsString::ReplaceWordIgnoreSpace(FormattedDateString, "yyyy", to_string(Date._Year));

		return FormattedDateString;
	}

	string FormatDate(string DateFormat = "dd/mm/yyyy") {

		return FormatDate(*this, DateFormat);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare GetCompareDates(clsDate Date1, clsDate Date2) {

		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1IsEqualToData2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}
	
	enDateCompare GetCompareDates(clsDate Date2) {

		return GetCompareDates(*this, Date2);
	}

	static clsDate AddOneDay(clsDate & Date) {

		IsLastDayInMonth(Date) ? (Date._Day = 1, (IsLastMonthInYear(Date._Month) ? (Date._Month = 1, Date._Year++) : Date._Month++)) : (Date._Day++);

		return Date;
	}

	void AddOneDay() {

		 AddOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {

		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludingEndDay = false) {

		int Days = 0;
		short SwapFlagvalue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {

			SwapDates(Date1, Date2);
			SwapFlagvalue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2)) {

			Days++;
			Date1 = AddOneDay(Date1);
		}

		return (IncludingEndDay) ? (++Days * SwapFlagvalue) : (Days * SwapFlagvalue);
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludingEndDay = false) {

		return GetDifferenceInDays(*this, Date2, IncludingEndDay);
	}

	static short CalculateMyAgeInDay(clsDate DateOfBirth) {

		return GetDifferenceInDays(DateOfBirth, GetSystemDate());
	}

	static clsDate SetLastDayInMonth(clsDate & Date) {

		short NumberOfDaysInaMonth = NumberOfDaysInMonth(Date._Month, Date._Year);

		if (Date._Day > NumberOfDaysInaMonth) {

			Date._Day = NumberOfDaysInaMonth;
		}
		return Date;
	}

	void SetLastDayInMonth() {

		SetLastDayInMonth(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate & Date, int DaysToAdd) {

		for (int i = 0; i < DaysToAdd; i++) {

			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(int DaysToAdd) {

		 IncreaseDateByXDays(*this, DaysToAdd);
	}

	static clsDate IncreaseDateByOneWeek(clsDate & Date) {

		return(IncreaseDateByXDays(Date, 7));
	}

	void IncreaseDateByOneWeek() {

		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreasDateByXWeeks(clsDate & Date, int WeeksToAdd) {

		for (int i = 0; i < WeeksToAdd; i++) {

			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreasDateByXWeeks(int WeeksToAdd) {

		IncreasDateByXWeeks(*this, WeeksToAdd);
	}

	static clsDate IncreaseDateByOneMonth(clsDate & Date) {

		if (Date._Month == 12) {

			Date._Month = 1;
			Date._Year++;
		}
		else {

			Date._Month++;
		}

		Date = SetLastDayInMonth(Date);

		return Date;
	}

	void IncreaseDateByOneMonth() {

		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate & Date, short MonthsToAdd) {

		for (short i = 0; i < MonthsToAdd; i++) {

			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short MonthsToAdd) {

		 IncreaseDateByXMonths(*this, MonthsToAdd);
	}

	static clsDate IncreaseDateByOneyear(clsDate & Date) {

		Date._Year++;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void IncreaseDateByOneyear() {

		 IncreaseDateByOneyear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short YearsToAdd) {

		Date._Year += YearsToAdd;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void IncreaseDateByXYears(short YearsToAdd) {

		 IncreaseDateByXYears(*this, YearsToAdd);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {

		Date._Year += 10;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void IncreaseDateByOneDecade() {

		 IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short DecadesToAdd) {

		Date._Year += (10 * DecadesToAdd);
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void IncreaseDateByXDecades(short DecadesToAdd) {

		 IncreaseDateByXDecades(*this, DecadesToAdd);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {

		Date._Year += 100;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void IncreaseDateByOneCentury() {

	 IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreseDateByOneMillennium(clsDate& Date) {

		Date._Year += 1000;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void IncreseDateByOneMillennium() {

		IncreseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date) {

		if (Date.Day == 1) {

			if (Date.Month == 1) {

				Date.Month = 12;
				Date.Day = 31;
				Date._Year--;
			}
			else {

				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date._Year);
			}
		}
		else {

			Date.Day--;
		}
		return Date;
	}

	void DecreaseDateByOneDay() {

		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, int DaysToDecrease) {

		for (int i = 0; i < DaysToDecrease; i++) {

			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(int DaysToDecrease) {

		 DecreaseDateByXDays(*this, DaysToDecrease);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {

		for (short i = 0; i < 7; i++) {

			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek() {

	 DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, int WeekToDecrease) {

		for (int i = 0; i < WeekToDecrease; i++) {

			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(int WeeksToDecrease) {

		DecreaseDateByXWeeks(*this, WeeksToDecrease);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {

		(Date.Month == 1) ? (Date._Year--, Date._Month = 12) : (Date._Month--);
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DecreaseDateByOneMonth() {

		 DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short MonthsToDecrease) {

		for (short i = 0; i < MonthsToDecrease; i++) {

			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short MonthsToDecrease) {

		DecreaseDateByXMonths(*this, MonthsToDecrease);
	}

	static clsDate DecreasaDateByOneYear(clsDate& Date) {

		Date._Year--;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DecreasaDateByOneYear() {

		DecreasaDateByOneYear(*this);
	}

	static clsDate DeceaseDateByXYears(clsDate& Date, short YearsToDecrease) {

		Date._Year -= YearsToDecrease;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DeceaseDateByXYears(short YearsToDecrease) {

		DeceaseDateByXYears(*this, YearsToDecrease);
	}

	static clsDate DeceaseDatByOneDecade(clsDate& Date) {

		Date._Year -= 10;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DeceaseDatByOneDecade() {

		DeceaseDatByOneDecade(*this);
	}

	static clsDate DecraseDateByXDecades(clsDate& Date, short DecadesToDecrease) {

		Date._Year -= (10 * DecadesToDecrease);
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DecraseDateByXDecades(short DecadesToDecrease) {

		DecraseDateByXDecades(*this, DecadesToDecrease);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {

		Date._Year -= 100;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DecreaseDateByOneCentury() {

		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecraseDateByOneMellennium(clsDate& Date) {

		Date._Year -= 1000;
		Date = SetLastDayInMonth(Date);
		return Date;
	}

	void DecraseDateByOneMellennium() {

		 DecraseDateByOneMellennium(*this);
	}

	static short GetDaysUntilEndOfWeek(clsDate Date) {

		return (6 - DayOfWeekOrder(Date));
	}

	short GetDaysUntilEndOfWeek() {

		return GetDaysUntilEndOfWeek(*this);
	}

	static short GetDaysUntilEndOfMonths(clsDate Date, bool IncludingEndDay = false) {

		return(NumberOfDaysInMonth(Date._Month, Date._Year) - Date._Day + IncludingEndDay);
	}

	short GetDaysUntilEndOfMonths() {

		return GetDaysUntilEndOfMonths(*this);
	}

	static short GetDaysUntilEndOfYear(clsDate Date) {

		short Days = 0;

		for (short i = Date._Month + 1; i <= 12; i++) {

			Days += NumberOfDaysInMonth(i, Date._Year);
		}
		return GetDaysUntilEndOfMonths(Date,true) + Days;
	}

	short GetDaysUntilEndOfYear() {

		return GetDaysUntilEndOfYear(*this);
	}

	static short CalculateBussinessDays(clsDate DateFrom, clsDate DateTo) {

		short DaysCount = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo)) {

			if (isBusinessDay(DateFrom))
				DaysCount++;

			DateFrom = AddOneDay(DateFrom);
		}
		return DaysCount;
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {

		return GetDifferenceInDays(DateFrom, DateTo) - CalculateBussinessDays(DateFrom, DateTo);
	}

	static clsDate CalculateVacationReturndDate(clsDate DateFrom, short VacationDays) {

		while (VacationDays > 0) {

			if (isBusinessDay(DateFrom)) {

				VacationDays--;
			}

			DateFrom = AddOneDay(DateFrom);
		}

		//in case the return date is week end keep adding until you reach business day
		if (IsWeekEnd(DateFrom)) {

			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}

	static string GetSystemDateTimeString() {

		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return DateToString(clsDate(Day, Month, Year)) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
	}
};

