#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

string months[12] = 
{
"January", 
"February", 
"March", 
"April", 
"May", 
"June", 
"July", 
"August", 
"September", 
"October", 
"November", 
"December"
};

Date::Date(int year, int month, int day)
{
    this->month = month;
    this->day = day;
    this->year = year;
}

void Date::setMonth(int m)
{
    month = m;
}

void Date::setDay(int d)
{
    day = d;
}

void Date::setYear(int y)
{
    year = y;
}

int Date::getMonth()
{
    return month;
}

int Date::getDay()
{
    return day;
}

int Date::getYear()
{
    return year;
}

string Date::outputString()
{
    string monthName = months[month-1];
    string str = monthName;
    str += " ";
    str += to_string(day);
    str += ", ";
    str += to_string(year);
    return str;
}