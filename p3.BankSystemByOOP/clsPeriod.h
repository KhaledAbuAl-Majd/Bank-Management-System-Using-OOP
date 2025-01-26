#pragma once

#include<iostream>
#include"clsDate.h";

using namespace std;

class clsPeriod 
{
	clsDate _StartDate;
	clsDate _EndDate;

public:

	clsPeriod(clsDate StartDate, clsDate EndDate) {

		_StartDate = StartDate;
		_EndDate = EndDate;
	}

	static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2) {

		if (clsDate::GetCompareDates(Period2._EndDate, Period1._StartDate) == clsDate::enDateCompare::Before ||
			clsDate::GetCompareDates(Period2._StartDate, Period1._EndDate) == clsDate::enDateCompare::After)
			return false;
		else;
		return true;
	}

	bool IsOverlapWith(clsPeriod Period2) {

		return IsOverlapPeriods(*this, Period2);
	}

	static bool IsDateInPeriod(clsDate Date, clsPeriod Period) {

		return  !(clsDate::GetCompareDates(Date, Period._StartDate) == clsDate::enDateCompare::Before ||
			clsDate::GetCompareDates(Date, Period._EndDate) == clsDate::enDateCompare::After);
	}

	bool IsDateInPeriod(clsDate Date) {

		return IsDateInPeriod(Date, *this);
	}

	static int GetPeriodLengthInDays(clsPeriod Period, bool IncludeEndDate = false) {

		return clsDate::GetDifferenceInDays(Period._StartDate, Period._EndDate, IncludeEndDate);
	}

	int GetPeriodLengthInDays(bool IncludingEndDate = false) {

		return GetPeriodLengthInDays(*this, IncludingEndDate);
	}

	static short CountOverlapDays(clsPeriod Period1, clsPeriod Period2) {

		short OverlapDays = 0;
		short Period1Length = GetPeriodLengthInDays(Period1, true);
		short Period2Length = GetPeriodLengthInDays(Period2, true);

		if (!IsOverlapPeriods(Period1, Period2))
			return 0;

		if (Period1Length < Period2Length) {

			while (clsDate::IsDate1BeforeDate2(Period1._StartDate, Period1._EndDate)) {

				if (IsDateInPeriod(Period1._StartDate, Period2)) {

					OverlapDays++;
				}
				Period1._StartDate = clsDate::AddOneDay(Period1._StartDate);
			}
		}
		else {

			while (clsDate::IsDate1BeforeDate2(Period2._StartDate, Period2._EndDate)) {

				if (IsDateInPeriod(Period2._StartDate, Period1)) {

					OverlapDays++;
				}
				Period2._StartDate = clsDate::AddOneDay(Period2._StartDate);
			}
		}

		return OverlapDays;
	}

	short CountOverlapDays(clsPeriod Period2) {

		return CountOverlapDays(*this, Period2);
	}

	void Print() {

		cout << "Period Start: ";
		_StartDate.Print();

		cout << "Period End: ";
		_EndDate.Print();
	}
};

