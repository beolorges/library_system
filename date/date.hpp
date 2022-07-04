#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>
#include <string>
#include <iostream>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

    void validDateStringFormat(string date);
    void validDate(int, int, int);
    void formatDate();

public:
    Date(){};
    Date(int);
    Date(string);
    Date(int, int, int);
    ~Date(){};

    Date getToday();
    void setToday();
    string toString() const;

    void operator+=(int);
    Date operator+(int);
    int operator-(Date);
    friend bool operator<(const Date &, const Date &);
    friend bool operator>(const Date &, const Date &);
    friend bool operator!=(const Date &, const Date &);
    friend bool operator==(const Date &, const Date &);
};

#endif