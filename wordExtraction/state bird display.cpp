// state bird display and database by Brad Brammer
// 10/19/2020 v1.0
// this program lets you input a state's postal code or 2-letter abbreviation and
// then displays the full state name and the state bird
// using a pair of maps it loads from a .txt file database
// variables are selfnamed and inline comments explain how database is created

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

void stringToupper(string *str);

string inputStr(string prompt)
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
        }
        catch (...)
        {
            cout << "ERROR: Input is invalid." << endl;
            isValid = false;
        }
    } while (isValid == false);
    return input;
}

int main()
{
    cout << "Loading data . . . " << endl;
    // declaring the two required maps, abbrev:longname and abbrev:bird
    map<string, string> longnames;
    map<string, string> birds;

    // placeholder strings to hold each relative value
    string line;     // hold entire line of data.txt
    string abbrev;   // will hold 1st value e.g. "IN"
    string longname; // will hold 2nd value e.g. "Indiana"
    string bird;     // will hold 3rd value e.g. "cardinal"

    // this value will allow parsing of the data file as I have it formatted
    char delimiter = ',';

    // the input stream we will use to open data.txt
    ifstream file;

    // reading info for each var from data.txt
    file.open("data.txt", ios::in);
    //while there is a new line to read from file, store in line. default delimiter for getline is the newline terminator
    while (getline(file, line))
    {
        // new stringstream to parse
        stringstream data(line);
        // delimiter is "," and reads from the stringstream we made from the line until it finds the ","
        // and then stores it in each variable
        getline(data, abbrev, delimiter);
        getline(data, longname, delimiter);
        getline(data, bird, delimiter);
        // inserts the values into the map for later lookup
        longnames.insert(pair<string, string>(abbrev, longname));
        birds.insert(pair<string, string>(abbrev, bird));
    }

    // declare variables for running the data viewer
    bool exitFlag = false;
    string state = "display quit message";
    bool validState = false;

    while (exitFlag == false)
    {
        validState = false;
        if (state != "display quit message")
        {
            cout << "(you can type \"quit\" or 'q' to exit)" << endl;
        }
        cout << "To see a US official state bird," << endl;
        state = inputStr("enter a 2-letter postal code (e.g. IN for Indiana): ");
        stringToupper(&state);
        if (state == "Q" || state == "QUIT")
        {
            exitFlag = true;
        }
        else
        {
            for (map<string, string>::iterator it = longnames.begin(); it != longnames.end(); it++)
            {
                if (state == it->first)
                {
                    cout << it->second << "'s state bird is: ";
                    validState = true;
                }
            }

            for (map<string, string>::iterator it = birds.begin(); it != birds.end(); it++)
            {
                if (state == it->first)
                {
                    cout << it->second << endl;
                }
            }
            if (validState == false)
            {
                cout << "ERROR: State \"" << state << "\" not found." << endl;
            }
        }
    }

    return 0;
}

// puts an entire string to uppercase
void stringToupper(string *str)
{
    string modStr = *str;
    for (int i = 0; i < modStr.size(); i++)
    {
        modStr[i] = toupper(modStr[i]);
    }
    *str = modStr;
}