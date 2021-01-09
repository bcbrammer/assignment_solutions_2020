// nerf gun manager v1.0 by Brad Brammer
// 11/1/2020 version 1
// this program lets you fire nerf darts from various blasters (guns)
// you can reload x darts, fire at random, and determine which blasters have darts still with 'c' command
// the menu is operated like a console with 3 arguments. this may be improved if we revisit this program.
// ideally it would parse like a real console "0 f 3" for example. I know how to do this but didn't design it this way.
// there is a 1/20 misfire chance when any gun is fired.
// there are some planned features, including adding, editing, deleting, and sorting guns
// also, firing accuracy based on range can be added since range is a gun member already
// some of the commands and methods are visible currently but do nothing

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>

#include "NerfGun.h"

using namespace std;

int parseArg3(string arg3);
void displayHelp();
bool isNumber(string str);
string inputStr(string prompt);
void compareGuns(vector<NerfGun> guns);
void goWild(vector<NerfGun> &guns);

int main()
{
    srand(time(0));

    vector<NerfGun> myGuns;

    cout << "Loading basic Nerf Guns..." << endl;

    string model = "Strongarm N-Strike Elite";
    int range = 90;
    int capacity = 6;
    myGuns.emplace_back(model, range, capacity);

    model = "Elite 2.0 Trio SD-3";
    range = 90;
    capacity = 3;
    myGuns.emplace_back(model, range, capacity);

    model = "Rampage N-Strike Elite";
    range = 90;
    capacity = 25;
    myGuns.emplace_back(model, range, capacity);

    model = "Mega Motostryke";
    range = 120;
    capacity = 10;
    myGuns.emplace_back(model, range, capacity);

    model = "Ultra One Motorized";
    range = 120;
    capacity = 25;
    myGuns.emplace_back(model, range, capacity);

    model = "A Real Gun";
    range = 600;
    capacity = 15;
    myGuns.emplace_back(model, range, capacity);

    // variables needed to run the menu loop and console
    bool exitFlag = false;
    string choice = "5f25";
    string arg1 = "";
    string arg2 = "";
    string arg3 = "";
    int validArg3 = 0;
    int activeGun = 0;
    int fireAmount = 2;
    int reloadAmount = 1;

    displayHelp();

    // this loop only ends if the user selects the option which sets exitFlag = true
    while (exitFlag == false)
    {
        cout << " " << endl;
        cout << "Blasters Available: " << 5 << endl;
        cout << "-Index#---Model---------" << endl;
        for (int i = 0; i < myGuns.size(); i++)
        {
            cout << " - " << i << " -    " << myGuns[i] << endl;
        }
        cout << "---------------------------" << endl;
        cout <<"(enter 'h' = help to see commands)" << endl;
        // highly recommend you use 'h' to see commands.

        choice = inputStr("Enter Index # + commands:");

        // flush all arg variables so that choice string/console parsing does not pass last iteration's values through
        arg1 = "";
        arg2 = "";
        arg3 = "";
        validArg3 = -1;
        // these parse the choice variable to determine what the user wants to do
        // only want to store data if there is data in the choice string to store...
        // so length must be long enough so that program doesn't store garbage to arg3 from memory
        if(choice.length() >= 1)
        {
            arg1 = choice.substr(0,1); // from char0, 1 char
        }
        if(choice.length() >= 2)
        {
            arg2 = choice.substr(1,1); // from char1, 1 char
        }
        if(choice.length() >=3)
        {
            arg3 = choice.substr(2);   // from char2, to the end of the string
            // parses arg3 to see if it is valid (positive integer number) since it exists
            validArg3 = parseArg3(arg3);
        }

        // if the first argument arg1 is a valid integer whole number in the gun index/vector we then...
        if(isNumber(arg1) == true && floor(stod(arg1))==stod(arg1) && stod(arg1) >= 0 && stod(arg1)<= (5))
        {
            // ... make it an actual number, which is the active gun in the vector/index ...
            activeGun = stoi(arg1);
            // ...fire it if arg2 is f
            if(arg2 == "f" || arg2 == "F")
            {
                fireAmount = validArg3;
                // fire it arg3 times if arg3 is a number zero or bigger
                // if arg3 is left blank, it defaults to -1, so this block is skipped
                if(fireAmount >= 1)
                {
                    cout << "Firing " << myGuns[activeGun].getModel() << "..." << endl;
                    for (int i = 0; i < fireAmount; i++)
                    {
                        myGuns[activeGun]--;
                    } 
                }
                // fire it just once otherwise using the overloaded -- operator
                else
                {
                    cout << "Firing " << myGuns[activeGun].getModel() << "..." << endl;
                    myGuns[activeGun]--;
                }
            }
            // ...reload it with arg3 number of darts
            else if(arg2 == "r" || arg2 == "R")
            {
                // set the reload amount to whatever number arg3 is
                // if arg3 is not a number, parseArg3 returns 0
                reloadAmount = validArg3;
                // if arg3 is 0 or not a number, this happens
                // if arg3 is left blank, e.g. for "2r" then arg3 is -1, which skips all these statements
                if(reloadAmount == 0)
                {
                    cout << "Invalid reload amount." << endl;
                }
                // otherwise it uses the overload += operator to reload the gun
                else if(reloadAmount >= 1)
                {
                    myGuns[activeGun] += reloadAmount;
                }
                else
                {
                    cout << "Provide an amount of darts to reload." << endl;
                }
            }
            // ... edit the active gun
            else if(arg2 == "e" || arg2 == "E")
            {
                cout << "You are not licensed to modify official Nerf blasters." << endl;
                // eventually the user can use the set methods and a submenu to modify gun private members
            }
            // ... display the active gun's info
            else if(arg2 == "?" || arg2 == "?")
            {
                myGuns[activeGun].dispInfo();
            }
            else
            {
                cout << "No valid command given for gun at index " << activeGun << "." << endl;
            }
        }
        // displays the help function (very important)
        else if (choice == "h" || choice == "H")
        {
            displayHelp();
        }
        // adds a new Nerf blaster
        else if (choice == "a" || choice == "A")
        {
            cout << "You are not licensed to create new Nerf blasters." << endl;
            // eventually the user can construct new gun objects here
        }
        // this fulfills the assignment requirement of "fire and reload random guns"
        else if (choice == "s" || choice == "S")
        {
            goWild(myGuns);
        }
        // this fulfills the assignment requiremnent to use the overloaded == and < operators
        else if (choice == "c" || choice == "C")
        {
            compareGuns(myGuns);
        }
        // exits the menu and quits the program
        else if (choice == "q" || choice == "Q")
        {
            exitFlag = true;
        }
        // if the choice string when parsed does not correspond to anything
        else
        {
            cout << "Invalid menu choice. Try again." << endl;
        }
    }

    return 0;
}

void compareGuns(vector<NerfGun> guns)
{
    sort(guns.begin(), guns.end());
    cout << "Blasters with the most ammo: " << endl;
    cout << guns[5] << endl;
    for(int i = 0; i < guns.size() - 1; i++)
    {
        if(guns[5] == guns[i])
        {
            cout << guns[i] << endl;
        }
    }
}

// goWild does 1-10 actions
// each action has a 66% chance it fires a gun and a 34% chance it reloads
// each gun is equally likely to be chosen for an action
// the amount of shots fired or reloaded is 1-13
void goWild(vector<NerfGun> &myGuns)
{
    // sets the percentage chance above which a gun will not fire but instead be reloaded
    static int FIRE_CHANCE = 66;
    cout << "Firing and reloading guns at random..." << endl;
    // determines how many random actions will be taken
    int numActions = rand()%10 + 1;
    // what the current random action will be
    int currentAction;
    // how many times the current random action will happen
    int randomAmount;
    // the randomly determined active gun
    int randomActiveGun;
    for(int i = 0; i < numActions; i++)
    {
        randomActiveGun = rand()%5+1;
        randomAmount = rand()%13+1;
        currentAction = rand()%100+1;
        // if currentAction rolls over 66, the gun will be reloaded
        if(currentAction > FIRE_CHANCE)
        {
            myGuns[randomActiveGun] += randomAmount;
        }
        // if currentAction rolls 66 or below, the gun will be fired
        else
        {
            cout << "Firing " << myGuns[randomActiveGun].getModel() << "..." << endl;
            for(int j = 0; j < randomAmount; j++)
            {
                myGuns[randomActiveGun]--;
            }
        }
    }
    cout << "...finished!" << endl;
}

// tests 3rd console/choice argument to see if it is a positive integer and usable for fire/reload
int parseArg3(string arg3)
{
    int output = 0;
    double num = 1.2;
    if(isNumber(arg3) == true)
    {
        num = stod(arg3);
        if(num >= 0 && floor(num) == num)
        {
            output = num;
            return output;
        }
    }
    cout << "Invalid input for 3rd argument. Must be a positive integer." << endl;
    return 0;
}

void displayHelp()
{
    cout << endl;
    cout <<"# + f      = fire once (e.g. 0f)" << endl;
    cout <<"# + f + ## = fire ## darts (e.g. 0f3)" << endl;
    cout <<"# + r + ## = reload ## darts (e.g. 1r3)" << endl;
    cout <<"# + ?      = show blaster info" << endl;
    cout <<"# + e      = edit blaster attributes (e.g. 2e)" << endl;
    cout <<"    c      = compare ammunition levels (e.g. c)" << endl;
    cout <<"    s      = shoot and reload blasters randomly (e.g. s)" << endl;
    cout <<"    a      = add new blaster (e.g. a)" << endl;
    cout <<"    q      = quit program (e.g. q)" << endl;
    cout <<"    h      = display this menu" << endl;
}

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

// asks user a question and returns an inputted string (cannot be blank)
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