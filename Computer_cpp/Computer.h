#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <optional>

#include "DataValidator.h"

using namespace std;

// custom exception object to throw and handle exceptions for data validation
class BadPart
{
    public:
        BadPart();
        BadPart(int errorCodes[10], int numErrors, string partNames[]);
        int getNumErrors();
        int getErrorCode(int i);
        string getPartName(int i);
    private:
        int errorCodes[10];
        int numErrors;
        string partNames[10];
};

class Computer 
{
    private:
        static const string MANUF;
        static const string MANUF_CODE;
        static int seq;
        static int inventory;
        string model;
        string serial;
        string cpu;
        int memory;
        double speed;
        string os;
        int hddSize;
        string hddType;
        bool bootState;
        bool diskDrive;
        string gpu;
        static const int HDD_SIZES[7];
    public:
        //default constructor
        Computer();
        //overload constructors
        Computer(
                string model,
                string cpu,
                double speed,
                int memory,
                int hddSize,
                string hddType,
                string os,
                bool bootState = false,
                bool diskDrive = false,
                string gpu = "N/A");
        //check if computer's data is valid and throw a BadPart object if not
        bool validateParts();
        void badPartHandler(BadPart *parts);
        //accessor methods
        static string getMANUF();
        static string getMANUF_CODE();
        static int getSeq();
        static int getInventory();
        static void decrementInventory();
        string getModel();
        string getSerial();
        string getCpu();
        double getSpeed();
        int getMemory();
        string getOs();
        int getHddSize();
        string getHddType();
        bool getBootState();
        bool getDiskDrive();
        string getGpu();
        //mutator methods
        void setModel(string str);
        void updateModel(string str);
        void setCpu(string str);
        void updateCpu(string str, double x);
        void setSpeed(double x);
        void setMemory(int x);
        void updateMemory(int x);
        void addMemory(int x);
        void setOs(string str);
        void updateOs(string str);
        void setHddSize(int x); 
        void setHddType(string str); 
        void updateHdd(int x, string str1, string str2);
        void setBootState(bool p);
        void updateBootState(bool p);
        void setDiskDrive(bool p);
        void updateDiskDrive(bool p);
        void setGpu(string str);
        void updateGpu(string str);
        // other methods and HDD_SIZES methods
        void displayInfo();
        static bool validHddSize(int hddSize);
        static void printHDD_SIZES();
        // default deconstructor
        ~Computer();
};