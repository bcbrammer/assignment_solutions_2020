#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <optional>

using namespace std;

// input validation function that checks if a string entered can be converted to a double, float, or truncated int safely with stod() or stoi()
// e.g. it won't accept 123abc and take 123, or 1.23abc as 1.23 if isNumber(myString) checks myString first
// reutrns true if a string is a number for stoi()/stod() so that the user cannot enter something like "1.1abc". they must enter "1.1" with no extra '.', '-' or 'aaa'
bool isNumber(string str);

// input validation function that returns false if the first char in passed string is ' ', or string is blank ""
// has optional parameter maxSpaces that can check if a string is "blanky" (like blank-ish or truthy) based on how many spaces are in it
// if no maxSpaces number is provided, it just doesn't check anything but the first two conditions
bool isBlanky(string str, optional<int> maxSpaces = nullopt);

// asks user a question and returns an inputted string (cannot be blank)
// optional parameter is maxLength of the string inputted. (defaults 255)
string inputStr(string prompt, optional<int> maxLength = 255, optional<int> maxSpaces = nullopt);

// this function will allow prompt the user for some kind of integer
// and optionally check if it is higher or lower than some min or max value if you pass them in
double inputDouble(string prompt, optional<double> min = nullopt, optional<double> max = nullopt);

// this function will allow prompt the user for some kind of integer,
// and optionally check if it is higher or lower than some min or max value if you pass them in
// will not check min or max if you don't pass one of those in.
int inputInt(string prompt, optional<double> min = nullopt, optional<double> max = nullopt);