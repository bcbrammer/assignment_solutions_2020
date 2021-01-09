// date inputter and formatter by Bradley Brammer v1.0
// this program lets the user input numerical values for a validated date and then formats and outputs it as a string
//09/21/2020
// variable names are self-identifying or explained via inline comments

#include <iostream>
#include <string> 

#include "Date.h"
#include "Date.cpp"

using namespace std;

// otherParamA and otherParamB are for the day error message calculation, where A is int month number and B is int year
// I named these parameters generically so I can use this new function in other projects as needed
// they default to 0 so that you don't need to fill them in for integer inputs where it wouldn't make sense
int inputInteger(const string &prompt, int low, int high, string inputName, int otherParamA = 0, int otherParamB = 0)
{
    string input = "NaN";
    int integer = -1;
    bool isInt = true;
    do
    {
        isInt = true;
        cout << prompt << endl;
        try
        {
            getline(cin, input);
            integer = stoi(input);

            if (integer < low || integer > high)
            {
                if(inputName == "year")
                {
                    throw range_error("ERROR: The year must be between 1900 and 2020.");
                }
                if(inputName == "month")
                {
                    throw range_error("ERROR: The month must be a valid month (1-12).");
                }
                if(inputName == "day")
                {
                    throw range_error("ERROR: The day must be in the appropriate range for this month.");
                }
                else
                {
                printf("ERROR: Value must be between %d and %d.", low, high);
                cout << "" << endl;
                }
            }
        }
        catch (invalid_argument &ia)
        {
            cout << "ERROR: " + input + " is not a valid integer." << endl;
            isInt = false;
        }
        catch (range_error &re)
        {
            cout << re.what() << endl;
            if(inputName == "day")
            {
                cout << "There are only " << high << " days in " << months[otherParamA-1] << " of " << otherParamB << "." << endl;
            }
        }
        catch (...)
        {
            cout << "ERROR: " + input + " is not valid." << endl;
            isInt = false;
        }
    } while (isInt == false || (integer < low || integer > high));

    return integer;
}

// sets the number of days in a month based on the month and year combination (to identify leap years)

int setMaxDays(int month, int year)
{
    if (month == 2)
    {
        if(year%400 == 0)
        {
            return 29;
        }
        else if (year%100 == 0)
        {
            return 28;
        }
        else if (year%4 == 0)
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else if(month < 8 && month % 2 == 0)
    {
        return 30;
    }
    else if(month < 8 && month % 2 == 1)
    {
        return 31;
    }
    else if(month > 7 && month % 2 == 0)
    {
        return 31;
    }
    else
    {
        return 30;
    }
}

void displayMenu(Date *myDate)
{       
        cout << " " << endl;
        cout << "Current Date: " << myDate->getMonth() << "/" << myDate->getDay() << "/" << myDate->getYear() << endl;
        cout << " " << endl;
        cout << " - 1 - Print Date "<< endl;
        cout << " - 2 - Edit Year " << endl;
        cout << " - 3 - Edit Month " << endl;
        cout << " - 4 - Edit Day " << endl;
        cout << " - 5 - Quit " << endl;
        cout << " " << endl;
}

int setMenuOption(int *menuOption)
{
    string str;
    bool menuOptionValid = true;
    do
    {
        menuOptionValid = true;
        try
        {
            cout << "Enter menu option: ";
            getline(cin, str);
            *menuOption = stoi(str);
            if(*menuOption > 5 || *menuOption < 1)
            {
                throw range_error("ERROR: Invalid menu selection.");
            }
        }
        catch(range_error &re)
        {
            cout << re.what() << endl;
        }
        catch(invalid_argument &ia)
        {
            cout << "ERROR: Choose a menu option by entering a number." << endl;
            menuOptionValid = false;
        }
        catch(...)
        {
            cout << "ERROR: Choose a menu option by entering a number." << endl;
            menuOptionValid = false;
        }
    } while (menuOptionValid == false || (*menuOption > 5 || *menuOption < 1));
    return *menuOption;
}

void executeMenu(Date * myDate, int * menuOption, bool * menuRun)
{
    int maxDays = setMaxDays(myDate->getMonth(), myDate->getYear());
    switch (*menuOption)
    {
    case 1:
        {
        cout << " " << endl;
        cout << myDate->outputString() << endl;
        cout << " " << endl;
        break;
        }
    case 2:
        {
        myDate->setYear(inputInteger("Enter new year:", 1900, 2020, "year"));
        maxDays = setMaxDays(myDate->getMonth(), myDate->getYear());
        if(myDate->getDay() > maxDays)
        {
            do
            {
                cout << "Your current day # is invalid for the new year." << endl;
                myDate->setDay(inputInteger("Please set new day:", 1, maxDays, "day", myDate->getMonth(), myDate->getYear()));
            } while (myDate->getDay() > maxDays);
        }
        break;
        }
    case 3: 
        {
        myDate->setMonth(inputInteger("Enter new month:", 1, 12, "month"));
        maxDays = setMaxDays(myDate->getMonth(), myDate->getYear());
        if(myDate->getDay() > maxDays)
        {
            do
            {
                cout << "Your current day # is invalid for the new month." << endl;
                myDate->setDay(inputInteger("Please set new day:", 1, maxDays, "day", myDate->getMonth(), myDate->getYear()));
            } while (myDate->getDay() > maxDays);
        }
        break;
        }
    case 4:
        {
        myDate->setDay(inputInteger("Enter new day:", 1, maxDays, "day", myDate->getMonth(), myDate->getYear()));
        break;
        }
    case 5:
        {
        *menuRun = false;
        break;
        }
    default:
        {
        *menuRun = true;
        break;
        }
    }
}

int main()
{
    int year = inputInteger("What year is the date?", 1900, 2020, "year");
    int month = inputInteger("What month is it? (enter the number)", 1, 12, "month");
    int maxDays = setMaxDays(month, year);
    int day = inputInteger("What day is it?", 1, maxDays, "day", month, year);

    Date myDate(year, month, day);

    bool menuRun = true;
    int menuOption = 1;
    do
    {
        displayMenu(&myDate);
        setMenuOption(&menuOption);
        executeMenu(&myDate, &menuOption, &menuRun);
    } while (menuRun == true);
    
    cin.ignore(); // just to pause the console after program is done
    cin.get();
}