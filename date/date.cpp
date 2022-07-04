#include "date.hpp"

void Date::validDate(int day, int month, int year)
{
    bool isA30DayMonth = (month == 4 || month == 6 || month == 9 || month == 11);
    bool isAFebruary = (month == 2);
    bool isA31DayMonth = !isA30DayMonth && !isAFebruary;

    if (month < 1 || month > 12)
    {
        throw invalid_argument("Invalid month");
    }

    if (day < 1 || day >= 31)
    {
        throw invalid_argument("Invalid day");
    }

    if (isAFebruary)
    {
        if (year % 4 == 0)
        {
            if (day > 29)
            {
                throw invalid_argument("Invalid day");
            }
        }
        else
        {
            if (day > 28)
            {
                throw invalid_argument("Invalid day");
            }
        }
    }
    else if (isA30DayMonth)
    {
        if (day > 30)
        {
            throw invalid_argument("Invalid day");
        }
    }
}

string Date::toString() const
{
    string dayString = to_string(day);
    string monthString = to_string(month);
    string yearString = to_string(year);

    if (day < 10)
    {
        dayString = "0" + dayString;
    }
    if (month < 10)
    {
        monthString = "0" + monthString;
    }
    if (year < 10)
    {
        yearString = "0" + yearString;
    }
    if (year < 100)
    {
        yearString = "0" + yearString;
    }
    if (year < 1000)
    {
        yearString = "0" + yearString;
    }

    string date = dayString + "/" + monthString + "/" + yearString;
    return date;
}

void Date::formatDate()
{
    bool isA30DayMonth = (month == 4 || month == 6 || month == 9 || month == 11);
    bool isAFebruary = (month == 2);
    bool isA31DayMonth = !isA30DayMonth && !isAFebruary;

    if (day > 28)
    {
        if (isAFebruary)
        {
            if (year % 4 == 0)
            {
                if (day > 29)
                {
                    while (day > 29)
                    {
                        month++;
                        day -= 29;
                    }
                }
            }
            else
            {
                if (day > 28)
                {
                    while (day > 28)
                    {
                        month++;
                        day -= 28;
                    }
                }
            }
        }
        else if (isA30DayMonth)
        {
            if (day > 30)
            {
                while (day > 30)
                {
                    month++;
                    day -= 30;
                }
            }
        }
        else
        {
            if (day > 31)
            {
                while (day > 31)
                {
                    month++;
                    day -= 31;
                }
            }
        }
    }

    if (month > 12)
    {
        while (month > 12)
        {
            year++;
            month -= 12;
        }
    }
}

void Date::validDateStringFormat(string date)
{
    if (date.length() != 10)
    {
        throw invalid_argument("Invalid date format");
    }
    if (date[2] != '/' || date[5] != '/')
    {
        throw invalid_argument("Invalid date format");
    }
    if (date[0] < '0' || date[0] > '9' || date[1] < '0' || date[1] > '9' || date[3] < '0' || date[3] > '9' || date[4] < '0' || date[4] > '9' || date[6] < '0' || date[6] > '9' || date[7] < '0' || date[7] > '9' || date[8] < '0' || date[8] > '9' || date[9] < '0' || date[9] > '9')
    {
        throw invalid_argument("Invalid date format");
    }
}

Date::Date(int _zero)
{
    day = 0;
    month = 0;
    year = 0;
}

Date::Date(int day, int month, int year)
{
    validDate(day, month, year);
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(string Date)
{
    validDateStringFormat(Date);
    this->day = stoi(Date.substr(0, 2));
    this->month = stoi(Date.substr(3, 2));
    this->year = stoi(Date.substr(6, 4));
}

void Date::setToday()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    this->year = now->tm_year + 1900;
    this->month = now->tm_mon + 1;
    this->day = now->tm_mday;
}

Date Date::getToday()
{

    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    int day = now->tm_mday;
    int month = now->tm_mon + 1;
    int year = now->tm_year + 1900;

    Date returnDate(day, month, year);
    return returnDate;
}

Date Date::operator+(int days)
{
    Date returnDate(day, month, year);
    returnDate.day += days;
    returnDate.formatDate();
    return returnDate;
}

void Date::operator+=(int days)
{
    this->day += days;
    this->formatDate();
}

int Date::operator-(Date date)
{
    int days = 0;
    if (this->year > date.year)
    {
        days += 365 * (this->year - date.year);
    }
    else if (this->year < date.year)
    {
        days -= 365 * (date.year - this->year);
    }
    else
    {
        if (this->month > date.month)
        {
            days += 30 * (this->month - date.month);
        }
        else if (this->month < date.month)
        {
            days -= 30 * (date.month - this->month);
        }
        else
        {
            days += this->day - date.day;
        }
    }
    return days;
}

bool operator>(const Date &d1, const Date &d2)
{
    if (d1.year > d2.year)
    {
        return true;
    }
    else if (d1.year < d2.year)
    {
        return false;
    }
    else
    {
        if (d1.month > d2.month)
        {
            return true;
        }
        else if (d1.month < d2.month)
        {
            return false;
        }
        else
        {
            return d1.day > d2.day;
        }
    }
}

bool operator<(const Date &d1, const Date &d2)
{
    return !(d1 > d2) && (d1 != d2);
}

bool operator==(const Date &d1, const Date &d2)
{
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool operator!=(const Date &d1, const Date &d2)
{
    return !(d1 == d2);
}