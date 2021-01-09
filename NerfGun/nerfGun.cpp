#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "NerfGun.h"

NerfGun::NerfGun(string model, int range, int capacity)
{
    this->model = model;
    this->range = range;
    if (capacity <= 144)
    {
        this->capacity = capacity;
    }
    else
    {
        this->capacity = 144;
        cout << "New gun's maximum capacity cannot exceed 144: max capacity set to 144." << endl;
    }
    this->dartCount = this->capacity;
}

// setters
void NerfGun::setModel(string str)
{
    model = str;
}
void NerfGun::setRange(int x)
{
    range = x;
}
void NerfGun::setCapacity(int y)
{
    capacity = y;
}
void NerfGun::setDartCount(int z)
{
    dartCount = z;
}

// getters
string NerfGun::getModel()
{
    return model;
}
int NerfGun::getRange()
{
    return range;
}
int NerfGun::getCapacity()
{
    return capacity;
}
int NerfGun::getDartCount()
{
    return dartCount;
}

// special functions
void NerfGun::fire()
{
    dartCount--;
    try{
    if(dartCount < 0)
    {
        throw underflow_error("Out of ammo!");
    }
    else
    {
        int misfire = rand() % 20 + 1;
        // cout << "misfire=" << misfire << endl;
        if(misfire > 1)
        {
            cout << "BANG." << endl;
        }
        else
        {
            cout << "...gun misfired!" << endl;
        }
    }
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;
        dartCount++;
    }
}

void NerfGun::reload(int quantity)
{
    cout << "Reloading " << model << ": " << quantity << " darts..." << endl;
    try
    {
    this->dartCount += quantity;
    if(dartCount > capacity)
    {
        throw overflow_error("Excess ammo added!");
    }
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;
        dartCount = capacity;
    }
}

void NerfGun::dispInfo()
{
    cout << endl;
    cout << "Model: " << model << endl;
    cout << "Range: " << range << "ft" << endl;
    cout << "Capacity: " << capacity << " darts" << endl;
    cout << endl;
}

// overloads
// checks if two guns have same dartCount
// used to check for ties in the case of the most ammo
bool NerfGun::operator==(NerfGun rs)
{
    if(this->dartCount == rs.getDartCount())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

// checks to see if one gun has less ammunition than the other
// used for basic sort algorithm
bool NerfGun::operator<(NerfGun rs)
{
    if(dartCount < rs.getDartCount())
    {
        return true;
    }
    else
    {
        return false;
    }
    return false; 
}

// fires the gun, decreases amunition by 1
void NerfGun::operator--()
{
    fire();
}
void NerfGun::operator--(int)
{
    fire();
}

// reloads based on number of rounds, throws exception if > capacity
void NerfGun::operator+=(int rounds)
{
    reload(rounds);
}

NerfGun::~NerfGun()
{
    // statements
}

ostream& operator<<(ostream& out, NerfGun gun)
{
    out << gun.getModel() << " (" << gun.getDartCount() << "/" << gun.getCapacity() << " darts)";
    return out;
}