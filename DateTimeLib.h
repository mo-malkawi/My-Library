#pragma once
#pragma warning(disable:4996)
#include<iostream>
using namespace std;

enum enDateCompare { Before = -1, Equal = 0, After = 1 };

struct stDate
{
    short Day;
    short Month;
    short Year;

};

struct stPeriod
{
    stDate StartDate;
    stDate EndDate;
};

namespace Input
{
    short ReadYear()
    {
        short Year;

        cout << "Please enter a year. ";
        cin >> Year;

        return Year;
    }

    short ReadMonth()
    {
        short Month;
        do
        {
            cout << "Please enter a month. ";
            cin >> Month;
        } while (Month < 1 || Month > 12);

        return Month;
    }

    short ReadDay()
    {
        short Day;

        cout << "\nPlease enter a day. ";
        cin >> Day;

        return Day;
    }

    stDate ReadFullDate()
    {
        stDate Date;

        Date.Day = ReadDay();
        Date.Month = ReadMonth();
        Date.Year = ReadYear();

        return Date;
    }

    stPeriod ReadPeriod()
    {
        stPeriod Period;

        cout << "Enter start date:\n";
        Period.StartDate = ReadFullDate();

        cout << "\nEnter end date:\n";
        Period.EndDate = ReadFullDate();

        return Period;

    }
}

namespace IsDate
{
    bool IsLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    short DayOfWeekOrder(short Year, short Month, short Day)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder(stDate Date)
    {
        return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
    }

    short NumberOfDaysInAMonth(short Year, short Month)
    {
        int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }

    bool IsLastDayInMonth(stDate Date)
    {
        return Date.Day == NumberOfDaysInAMonth(Date.Year, Date.Month);
    }

    bool IsLastMonthInYear(short Month)
    {
        return Month == 12;
    }

    bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
    {

        return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
            ((Date1.Month < Date2.Month) ? true : ((Date1.Month == Date2.Month) ?
                Date1.Day < Date2.Day : false)) : false);

    }

    bool IsDate1EqualToDate2(stDate Date1, stDate Date2)
    {
        return ((Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day)) ? true : false;
    }

    bool IsDate1AfterDate2(stDate Date1, stDate Date2)
    {
        return (!IsDate::IsDate1BeforeDate2(Date1, Date2) && !IsDate::IsDate1EqualToDate2(Date1, Date2));
    }

    bool IsEndOfWeek(stDate Date)
    {
        return DayOfWeekOrder(Date) == 6;
    }

    bool IsWeekend(stDate Date)
    {
        short DayIndex = DayOfWeekOrder(Date);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWorkDay(stDate Date)
    {
        return !IsWeekend(Date);
    }

    enDateCompare CompareDates(stDate Date1, stDate Date2)
    {
        if (IsDate::IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate::IsDate1EqualToDate2(Date1, Date2))
            return enDateCompare::Equal;

        return enDateCompare::After;
    }
}

namespace FixDate
{
    

    short NumberOfDaysInAMonth(short Year, short Month)
    {
        int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (IsDate::IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }

    stDate IncreaseDateByOneDay(stDate Date)
    {

        if (IsDate::IsLastDayInMonth(Date))
        {
            if (IsDate::IsLastMonthInYear(Date.Month))
            {
                Date.Day = 1;
                Date.Month = 1;
                Date.Year++;
            }
            else
            {
                Date.Day = 1;
                Date.Month++;
            }
        }
        else
        {
            Date.Day++;
        }


        return Date;
    }

    void SwapDates(stDate& Date1, stDate& Date2)
    {
        stDate Temp;

        Temp.Year = Date1.Year;
        Temp.Month = Date1.Month;
        Temp.Day = Date1.Day;

        Date1.Year = Date2.Year;
        Date1.Month = Date2.Month;
        Date1.Day = Date2.Day;

        Date2.Year = Temp.Year;
        Date2.Month = Temp.Month;
        Date2.Day = Temp.Day;
    }


    int DifferenceBetweenDates(stDate Date1, stDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short SwapFlagValue = 1;

        if (!IsDate::IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }


        while (IsDate::IsDate1BeforeDate2(Date1, Date2))
        {
            Date1 = IncreaseDateByOneDay(Date1);
            Days++;
        }

        return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

    }

    stDate GetSystemDate()
    {
        stDate Date;

        time_t t = time(0);
        tm* now = localtime(&t);

        Date.Year = now->tm_year + 1900;
        Date.Month = now->tm_mon + 1;
        Date.Day = now->tm_mday;

        return Date;

    }

    short DayOfWeekOrder(short Year, short Month, short Day)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder(stDate Date)
    {
        return FixDate::DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
    }

    string DayShortName(short DayOrder)
    {
        string DayOfTheWeek[7] = { "Sunday", "Monday" ,"Tuesday" ,"Wednesday" ,"Thursday","Friday", "Saturday" };

        return DayOfTheWeek[DayOrder];
    }
    

}
namespace Periods
{
    bool DoPeriodsOverLap(stPeriod Period1, stPeriod Period2)
    {
        if (IsDate::CompareDates(Period2.EndDate, Period1.StartDate) == enDateCompare::Before
            || IsDate::CompareDates(Period2.StartDate, Period1.EndDate) == enDateCompare::After)
            return false;

        return true;
    }

    bool IsDateInPeriod(stPeriod Period, stDate DateToCheck)
    {
        return !(IsDate::CompareDates(DateToCheck, Period.StartDate) == enDateCompare::Before
            || IsDate::CompareDates(DateToCheck, Period.EndDate) == enDateCompare::After);
    }

    short PeriodLengthInDays(stPeriod Period, bool IncludeEndDate = false)
    {
        return FixDate::DifferenceBetweenDates(Period.StartDate, Period.EndDate, IncludeEndDate);
    }
}