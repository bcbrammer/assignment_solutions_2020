#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class NerfGun
{
private:
    string model;
    int range;
    int capacity;
    int dartCount;
public:
    // constructors
    NerfGun();
    NerfGun(string model, int range, int capacity);
    ~NerfGun();
    // setters
    void setModel(string str);
    void setRange(int x);
    void setCapacity(int y);
    void setDartCount(int z);
    // getters
    string getModel();
    int getRange();
    int getCapacity();
    int getDartCount();
    // special functions
    void fire();
    void reload(int quantity);
    void dispInfo();
    // operator overloads
    // checks if two guns have same dartCount
    bool operator==(NerfGun rs);
    // checks to see if one gun has less ammunition than the other
    bool operator<(NerfGun rs);
    // fires the gun, decreases amunition by 1
    void operator--();
    void operator--(int);
    // reloads based on number of rounds, throws exception if > capacity
    void operator+=(int rounds);
    // overloads insertion operator to allow gun info to be printed to console
    ostream& operator<<(ostream & out);
};

ostream& operator<<(ostream & out, NerfGun gun);
