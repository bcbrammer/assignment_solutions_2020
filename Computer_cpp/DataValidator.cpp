#include <iostream>
#include <string>
#include <cmath>
#include <optional>

#include "DataValidator.h"

using namespace std;

// input validation function that checks if a string entered can be converted to a double, float, or truncated int safely with stod() or stoi()
// e.g. it won't accept 123abc and take 123, or 1.23abc as 1.23 if isNumber(myString) checks myString first
// reutrns true if a string is a number for stoi()/stod() so that the user cannot enter something like "1.1abc". they must enter "1.1" with no extra '.', '-' or 'aaa'
bool isNumber(string str)
{
    bool isDecimal = false;
    if (str.length() == 0)
    {
        return false;
    }
    if (str ==".")
    {
        return false;
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (i == 0)
        {
            if (str[0] == '-')
            {
                i += 1;
            }
        }
        if (isdigit(str[i]) || str[i] == '.')
        {
            if (str[i] == '.')
            {
                if (isDecimal == true)
                {
                    return false;
                }
                else
                {
                    isDecimal = true;
                }
            }
            else
            {
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

// input validation function that returns false if the first char in passed string is ' ', or string is blank ""
// has optional parameter maxSpaces that can check if a string is "blanky" (like blank-ish or truthy) based on how many spaces are in it
// if no maxSpaces number is provided, it just doesn't check anything but the first two conditions
bool isBlanky(string input, optional<int> maxSpaces)
{
    int i = 0;
    int numSpaces = 0;
    if (input == "")
    {
        return true;
    }
    if (input[0] == ' ')
    {
        return true;
    }
    if (maxSpaces.has_value() == true)
    {
        for (int i = 0; i <= input.length(); i++)
        {
            if (input[i] == ' ')
            {
                numSpaces++;
            }
        }
        if (numSpaces > maxSpaces)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// asks user a question and returns an inputted string (cannot be blank)
// optional parameter is maxLength of the string inputted. (defaults 255)
string inputStr(string prompt, optional<int> maxLength, optional<int> maxSpaces)
{
    string input = "input";
    bool isValid = true;
    do
    {
        try
        {
            isValid = true;
            cout << prompt << endl;
            getline(cin, input);
            if (isBlanky(input, maxSpaces) == true)
            {
                cout << "ERROR: This field cannot be blank, or contains too many (greater than " << *maxSpaces << ") spaces." << endl;
                isValid = false;
            }
            if (input.length() > maxLength.value_or(255))
            {
                cout << "ERROR: Exceeded maximum character length. (" << input.length() << "/" << *maxLength << ")" << endl;
                isValid = false;
            }
        }
        catch (...)
        {
            cout << "ERROR: Input is invalid." << endl;
            isValid = false;
        }
    } while (isValid == false);
    return input;
}

// this function will allow prompt the user for some kind of integer
// and optionally check if it is higher or lower than some min or max value if you pass them in
double inputDouble(string prompt, optional<double> min, optional<double> max)
{
    string input = "NaN"; // hold temporary string that will become double number
    double number = 1.1; // holds temporary number that will be validated and returned
    bool isValid = true; // flag variable for invalid data of any kind
    do
    {
        isValid = true;
        cout << prompt << endl;
        try
        {
            getline(cin, input);
            if(isNumber(input)==false)
            {
                throw invalid_argument(input);
            }
            number = stod(input);
            // exception: invalid_argument will be thrown here if input cannot be converted by stod()
            if (min.has_value() == true && number < min)
            {
                cout << "ERROR: Value must be greater than " << *min << "." << endl;
                isValid = false;
            }
            if (max.has_value() == true && number > max)
            {
                cout << "ERROR: Value must be less than " << *max << "." << endl;
                isValid = false;
            }
        }
        catch (invalid_argument ia)
        {
            cout << "ERROR: " + input + " is not a numeric value." << endl;
            isValid = false;
        }
        catch (...)
        {
            cout << "ERROR: " + input + " is not valid." << endl;
            isValid = false;
        }
    } while (isValid == false);

    return number;
}

// this function will allow prompt the user for some kind of integer,
// and optionally check if it is higher or lower than some min or max value if you pass them in
// will not check min or max if you don't pass one of those in.
int inputInt(string prompt, optional<double> min, optional<double> max)
{
    string input = "NaN"; // hold temporary string that will become double number
    double number = 1.1; // holds temporary number that will be validated to int integer
    int integer = -1; // the integer itself after conversion from string to double to int
    bool isValid = true; // flag variable for invalid data of any kind
    do
    {
        isValid = true;
        cout << prompt << endl;
        try
        {
            getline(cin, input);
            if(isNumber(input)==false)
            {
                throw invalid_argument(input);
            }
            number = stod(input);
            // exception: invalid_argument will be thrown here if input cannot be converted by stod()
            if(floor(number) != number)
            {
                cout << "ERROR: " << number << " is not an integer value." << endl;
                isValid = false;
            }
            if (min.has_value() == true && number < min)
            {
                cout << "ERROR: Value must be greater than " << *min << "." << endl;
                isValid = false;
            }
            if (max.has_value() == true && number > max)
            {
                cout << "ERROR: Value must be less than " << *max << "." << endl;
                isValid = false;
            }
        }
        catch (invalid_argument ia)
        {
            cout << "ERROR: " + input + " is not a numeric value." << endl;
            isValid = false;
        }
        catch (...)
        {
            cout << "ERROR: " + input + " is not valid." << endl;
            isValid = false;
        }
        if (isValid == true)
        {
            integer = stoi(input);
        }
    } while (isValid == false);

    return integer;
}