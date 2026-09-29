#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include "clsString.h"

class clsDate
{

private:

	short _Day = 2;
	short _Month = 9;
	short _Year = 2005;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string sDate)
	{
		vector <string> vDate;
		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrderInYear, short Year)
	{
		clsDate Date1 = GetDateFromDayOrderInYear(DayOrderInYear, Year);

		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static bool IsLeapYear(int Year)
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static clsDate StringToDate(string DateString)
	{
		clsDate Date;
		vector <string> vDate;

		vDate = clsString::Split(DateString, "/");

		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Day < 1 || Date.Day>31)
			return false;

		if (Date.Month < 1 || Date.Month>12)
			return false;

		short DaysInMonth = NumberOfDaysInAMonth(Date.Year, Date.Month);

		if (Date.Day > DaysInMonth)
			return false;

		return true;
	}

	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static short NumberOfDaysInAYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Year, short Month)
	{
		if (Month >= 1 && Month <= 12)
		{
			int NumberOfDays[13] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
		}
		else
		{
			return 0;
		}
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Year, _Month);
	}

	static short NumberOfHoursInAMonth(short Year, short Month)
	{
		return NumberOfDaysInAMonth(Year, Month) * 24;
	}

	short NumberOfHoursInAMonth()
	{
		return NumberOfHoursInAMonth(_Year, _Month);
	}

	static int NumberOfMinutesInAMonth(short Year, short Month)
	{
		return NumberOfHoursInAMonth(Year, Month) * 60;
	}

	int NumberOfMinutesInAMonth()
	{
		return NumberOfMinutesInAMonth(_Year, _Month);
	}

	static int NumberOfSecondsInAMonth(short Year, short Month)
	{
		return NumberOfMinutesInAMonth(Year, Month) * 60;
	}

	int NumberOfSecondsInAMonth()
	{
		return NumberOfSecondsInAMonth(_Year, _Month);
	}

	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;


		short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;

		return d;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Year, _Month, _Day);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDayOrder[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayOrder[DayOfWeekOrder];

	}

	static string DayShortName(short Day, short Month, short Year)
	{

		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder(Year, Month, Year)];

	}

	string DayShortName()
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder(_Year, _Month, _Day)];

	}

	static string MonthShortName(short Month)
	{
		string Months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug" ,"Sep","Oct","Nov","Dec" };

		return Months[Month - 1];
	}

	string MonthShortName()
	{
		string Months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug" ,"Sep","Oct","Nov","Dec" };

		return Months[_Month - 1];
	}

	static void PrintMonthCalendar(short Year, short Month)
	{
		printf("\n _______________%s_______________\n\n",
			MonthShortName(Month).c_str());

		printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short Current = DayOfWeekOrder(Year, Month, 1);

		short i;
		for (i = 0; i < Current; i++)
			printf("     ");

		short NumberOfDays = NumberOfDaysInAMonth(Year, Month);

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n _________________________________\n\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year)
	{
		printf("\n  __________________________________________________\n\n");
		printf("\t\tCalendar - %d\n", Year);
		printf("  __________________________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(Year, i);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short TotalDaysFromTheBeginningOfYear(short Year, short Month, short Day)
	{
		short TotalDaysCount = 0;

		for (short i = 1; i < Month; i++)
		{
			TotalDaysCount += NumberOfDaysInAMonth(Year, i);
		}

		return TotalDaysCount + Day;
	}

	short TotalDaysFromTheBeginningOfYear()
	{
		return TotalDaysFromTheBeginningOfYear(_Year, _Month, _Day);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DayOrderInYear;
		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			short MonthDays = NumberOfDaysInAMonth(Year, Date.Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	clsDate GetDateFromDayOrderInYear(short DayOrderInYear)
	{
		return GetDateFromDayOrderInYear(DayOrderInYear, _Year);
	}

	static clsDate AddDays(clsDate Date, short Days)
	{
		short RemainingDays = Days + TotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);
		Date.Month = 1;

		while (true)
		{
			short MonthDays = NumberOfDaysInAMonth(Date.Year, Date.Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	void AddDays(short Days)
	{
		short RemainingDays = Days + TotalDaysFromTheBeginningOfYear(_Year, _Month, _Day);
		_Month = 1;

		while (true)
		{
			short MonthDays = NumberOfDaysInAMonth(_Year, _Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;

				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true :
			((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true :
				(Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return ((Date1.Year == Date2.Year) ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day) : false) : false);
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInAMonth(Date.Year, Date.Month));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Year++;
				Date.Day = 1;
				Date.Month = 1;
			}
			else
			{
				Date.Month++;
				Date.Day = 1;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}

	static int GetDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDays = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDays ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	int GetDiffrenceInDays(clsDate Date2, bool IncludeEndDays = false)
	{
		return GetDiffrenceInDays(*this, Date2, IncludeEndDays);
	}

	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Day = now->tm_mday;
		Date.Month = now->tm_mon + 1;
		Date.Year = now->tm_year + 1900;

		return Date;
	}

	static string GetSystemTime()
	{

		time_t t = time(0);
		tm* td = localtime(&t);

		string Time = "";
		Time += to_string(td->tm_hour);
		Time += ":" + to_string(td->tm_hour);
		Time += ":" + to_string(td->tm_hour);

		return Time;
	}

	static string GetSystemDateAndTime()
	{
		return DateToString(GetSystemDate()) + " - " + GetSystemTime();
	}

	static clsDate IncreaseDateByXDays(clsDate Date, short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, short Months)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		Date.Year += Years;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByXYearsFaster(short Years)
	{
		IncreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		Date.Year += 10;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, short Decades)
	{
		Date.Year += Decades * 10;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decades)
	{
		IncreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		Date.Year += 100;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year += 1000;

		if (NumberOfDaysInAMonth(Date.Year, Date.Month) < Date.Day)
		{
			Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate AdjustDayToMonthEnd(clsDate Date)
	{
		short MonthDays = NumberOfDaysInAMonth(Date.Year, Date.Month);

		if (Date.Day > MonthDays)
		{
			Date.Day = MonthDays;
		}

		return Date;
	}

	void AdjustDayToMonthEnd()
	{
		AdjustDayToMonthEnd(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{

		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Year--;
				Date.Day = 31;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short Months)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		Date.Year -= Years;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByXYearsFaster(short Years)
	{
		DecreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		Date.Year -= 10;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, short Decades)
	{
		Date.Year -= Decades * 10;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByXDecadesFaster(short Decades)
	{
		DecreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		Date.Year -= 100;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year -= 1000;

		Date = AdjustDayToMonthEnd(Date);

		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DayOrder = DayOfWeekOrder(Date.Year, Date.Month, Date.Day);

		return (DayOrder == 5 || DayOrder == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;

		EndOfMonthDate.Day = NumberOfDaysInAMonth(Date.Year, Date.Month);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDiffrenceInDays(Date, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		clsDate EndOfYearDate;

		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDiffrenceInDays(Date, EndOfYearDate, true);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum eDateCompare { Beforfe = -1, Equal = 0, After = 1 };

	static eDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return eDateCompare::Beforfe;

		if (IsDate1EqualDate2(Date1, Date2))
			return eDateCompare::Equal;

		return eDateCompare::After;
	}

	eDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}























};

