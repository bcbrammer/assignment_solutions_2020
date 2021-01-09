#ifndef COMPUTER_H_
#define COMPUTER_H_

#include <iostream>
#include <string>

using namespace std;

class Date
{
    private:
        int month;
        int day;
        int year;
    public:
        Date(int year, int month, int day);
        void setMonth(int month);
        void setDay(int day);
        void setYear(int year);
        int getMonth();
        int getDay();
        int getYear();
        string outputString();
};

#endif