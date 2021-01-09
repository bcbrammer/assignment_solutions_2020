#include <iostream>
#include <string>
#include <optional>

#include "Computer.h"
#include "DataValidator.h"

using namespace std;

// section 1: initialize static and const variables and functions
// section 2: BadPart class custom exception methods
// section 3: Computer class primary object methods

// manufacturer codes and information on inventory
const string Computer::MANUF = "Factotum Computer Systems";
const string Computer::MANUF_CODE = "FACT";

string Computer::getMANUF()
{
    return MANUF;
}
string Computer::getMANUF_CODE()
{
    return MANUF_CODE;
}

int Computer::seq = 8800;

int Computer::inventory = 0;

int Computer::getSeq()
{
    return seq;
}

int Computer::getInventory()
{
    return inventory;
}

void Computer::decrementInventory()
{
    inventory--;
}

// HDD_SIZES

// all the valid int values for hddSize in gb
const int Computer::HDD_SIZES[7] = {250, 480, 1000, 2000, 4000, 8000, 12000};

// quickly outputs valid int values for hddSize based on HDD_SIZES constant array
void Computer::printHDD_SIZES()
{
    for (int j = 0; j < 7; j++)
    {
        cout << HDD_SIZES[j] << ", ";
    }
    cout << endl;
}

// checks if hddSize is one of the valid values in HDD_SIZES constant array
bool Computer::validHddSize(int hddSize)
{
    for(int i = 0; i < 7; i++)
    {
        if(hddSize == HDD_SIZES[i])
        {
            return true;
        }
    }
    return false;
}

// 2 BadPart

// default constructor, contains 0 errors, all 0 error codes, and no part names
BadPart::BadPart()
{
    int errorCodes[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string partNames[10] = {"1","2","3","4","5","6","7","8","9","10"};
    numErrors = 0;
}

// this constructor can loop through and load up to 10 error codes and associated part names, and stores the total number of errors
BadPart::BadPart(int errorCodes[], int numErrors, string partNames[])
{
    for(int i = 0; i < 10; i++)
    {
        this->errorCodes[i] = errorCodes[i];
        this->partNames[i] = partNames[i];
    }
    this->numErrors = numErrors;
}
// accessor functions, the arrays must be looped through
int BadPart::getNumErrors()
{
    return numErrors;
}
int BadPart::getErrorCode(int i)
{
    return errorCodes[i];
}
string BadPart::getPartName(int i)
{
    return partNames[i];
}

// this function will validate each part a given computer object
// it does not check that the datatypes match, but that the data provided fits within the ranges or values
// error code 1 is for blank or "blanky" data (see: DataValidator's isBlanky() function)
// error code 2 is for less than 0 clock speed
// error code 3 is for memory not being a valid power of 2
// error code 4 is for HDD size not being one of the options in HDD_SIZES
// error code 5 is for HDD type not being one of the two options
// error code 9, invalid datatype (e.g. int value for string) may be added later
// if any error is encountered, it throws a BadPart object to be caught in the main function.
// if no errors are found, it returns TRUE, e.g. all parts are valid. 
// this is not how I would write this program, but I am complying with assignment requirements
// (class must throw exception, main must handle exception)
bool Computer::validateParts()
{
    int i = 0;
    int errorCodes[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string partNames[10] = {"1","2","3","4","5","6","7","8","9","10"};

    if(isBlanky(model)==true || model.length() < 4)
    {
        errorCodes[i] = 1;
        partNames[i] = "Model";
        i++;
    }
    if(isBlanky(cpu)==true)
    {
        errorCodes[i] = 1;
        partNames[i] = "CPU";
        i++;
    }
    if(speed <= 0.00)
    {
        errorCodes[i] = 2;
        partNames[i] = "CPU";
        i++;
    }
    if(memory >= 2 && (memory & (memory - 1)) == 0000) { } 
    // so this checks if the binary of this variable memory has only a single 1 bit checked and all others 0. 
    // e.g. memory = 8, so memory = x1000 and 8-1 = 7 so memory-1 = x0111. thus using bitwise & (AND) to compare each bit will create 0000
    // if memory = 9, memory bits are 1001 and 9-1 = 8 so memory-1 = x1000. adding bitwise gives 1000, which is not zero.
    // powers of 2 added bitwise to their value minus 1 should always equal zero, because each place in binary is a power of two.
    else
    {
        errorCodes[i] = 3;
        partNames[i] = "RAM";
        i++;
    }
    if(validHddSize(hddSize) == false)
    {
        errorCodes[i] = 4;
        partNames[i] = "HDD";
        i++;
    }
    if(hddType != "SATA" && hddType != "SSD")
    {
        errorCodes[i] = 5;
        partNames[i] = "HDD";
        i++;
    }
    if(isBlanky(os)==true)
    {
        errorCodes[i] = 1;
        partNames[i] = "OS";
        i++;
    }
    if(isBlanky(gpu)==true)
    {
        errorCodes[i] = 1;
        partNames[i] = "GPU";
        i++;
    }
    if (i > 0)
    {
        throw BadPart(errorCodes, i, partNames);
    }

    return true;
}


// this method can be called in the main to handle a given Computer object's BadParts object thrown
// it handles the error codes as listed in validateParts() method
void Computer::badPartHandler(BadPart *myBadParts)
{
    for(int i = 0; i < myBadParts->getNumErrors(); i++)
    {
        if(myBadParts->getErrorCode(i) == 1)
        {
            cout << "ERROR - " << myBadParts->getPartName(i) << ": Must provide a valid name." << endl;
            if (myBadParts->getPartName(i) == "Model")
            {
                if(model.length() < 4)
                {
                    cout << "Model name must be 4 characters or longer." << endl;
                }
                model = (inputStr("Enter valid Model Name: "));
                serial.replace(5,3,model.substr(0,3));
            }
            if (myBadParts->getPartName(i) == "CPU")
            {
                cpu = (inputStr("Enter valid CPU: "));
            }
            if (myBadParts->getPartName(i) == "OS")
            {
                os = (inputStr("Enter valid OS: "));
            }
            if (myBadParts->getPartName(i) == "GPU")
            {
                gpu = (inputStr("Enter valid GPU: "));
            }
        }
        if(myBadParts->getErrorCode(i) == 2)
        {
            cout << "ERROR - " << myBadParts->getPartName(i) << ": Must provide a Clock Speed greater than 0." << endl;
            speed = (inputDouble("Enter a valid CPU Clock Speed", 0));
        }
        if(myBadParts->getErrorCode(i) == 3)
        {
            cout << "ERROR - " << myBadParts->getPartName(i) << ": Memory must be a power of 2." << endl;
            memory = (inputInt("Enter a valid amount of total memory: ", 2));
        }
        if(myBadParts->getErrorCode(i) == 4)
        {
            cout << "ERROR - " << myBadParts->getPartName(i) << ": Invalid disk size. Valid sizes are:" << endl;
            printHDD_SIZES();
            hddSize = (inputInt("Enter valid HDD size (in gb): ", 250, 12000));
        }
        if(myBadParts->getErrorCode(i) == 5)
        {
            cout << "ERROR - " << myBadParts->getPartName(i) << ": Invalid type. Valid HDD types are SATA and SSD." << endl;
            hddType = (inputStr("Enter valid HDD type: ", 5));
        }
        if(myBadParts->getErrorCode(i) == 0)
        {
            break;
        }
    }
}

Computer::Computer()
{
    model = "Four";
    cpu = "Intel Celeron";
    speed = 2.5;
    memory = 4;
    hddSize = 250;
    hddType = "5CHAR";
    os = "Windows ME";
}

// overload constructor
// this overload constructor has the validateParts() method built into it
Computer::Computer(string model,
                string cpu,
                double speed,
                int memory,
                int hddSize,
                string hddType,
                string os,
                bool bootState,
                bool diskDrive,
                string gpu)
{
    this->model = model;
    this->cpu = cpu;
    this->speed = speed;
    this->memory = memory;
    this->os = os;
    this->hddSize = hddSize;
    this->hddType = hddType;
    this->bootState = bootState;
    this->diskDrive = diskDrive;
    this->gpu = gpu;

    // code that makes the serial number
    this->serial = MANUF_CODE + "-" + model.substr(0,4) + to_string(seq);

    seq++;
    inventory++;

    cout << "Building computer... " << endl;
}

// accessor methods
string Computer::getModel()
{
    return model;
}
string Computer::getSerial()
{
    return serial;
}
string Computer::getCpu()
{
    return cpu;
}
int Computer::getMemory()
{
    return memory;
}
double Computer::getSpeed()
{
    return speed;
}
string Computer::getOs()
{
    return os;
}
int Computer::getHddSize()
{
    return hddSize;
}
string Computer::getHddType()
{
    return hddType;
}
bool Computer::getBootState()
{
    return bootState;
}
bool Computer::getDiskDrive()
{
    return diskDrive;
}
string Computer::getGpu()
{
    return gpu;
}

//mutator methods
void Computer::setModel(string str)
{
    model = str;
}
// not yet implemented, also updates serial number
void Computer::updateModel(string str)
{
    model = str;
    seq++;
    serial = MANUF_CODE + "-" + model.substr(0,4) + to_string(seq);
    cout << "New Model Name: " << model << endl;
    cout << "Issued Updated Serial #: " << serial << endl;
}
void Computer::setCpu(string str)
{
    cpu = str;
}
void Computer::setSpeed(double x)
{
    speed = x;
}
// not yet implemented
void Computer::updateCpu(string str, double x)
{
    cpu = str;
    speed = x;
    validateParts();
    cout << "Updated CPU: " << cpu << " @ " << speed << "Ghz" << endl;
}
void Computer::setMemory(int x)
{
    memory = x;
}
void Computer::updateMemory(int x)
{
    memory = x;
    validateParts();
    cout << "Installed RAM: " << memory << "gb" << endl;
}
void Computer::addMemory(int x)
{
    memory +=x;
    validateParts();
    cout << "Added " << x << "gb of addtional RAM." << endl;
    cout << "New total RAM available: " << memory << "gb" << endl;
}
void Computer::setOs(string str)
{
    os = str;
}
void Computer::updateOs(string str)
{
    os = str;
    validateParts();
    cout << "Finished installing new OS: " << os << endl;
}
void Computer::setHddSize(int x)
{
    hddSize = x;
}
void Computer::setHddType(string str)
{
    hddType = str;
}
// this is for the menu option to replace HDD (requires setting type and OS again)
void Computer::updateHdd(int x, string str1, string str2)
{
    hddSize = x;
    hddType = str1;
    os = str2;
    validateParts();
    cout << "Installed new HDD: " << hddSize << "gb " << hddType << endl;
    cout << "Booting computer into new OS: " << os << "..." << endl;
    setBootState(1);
}
void Computer::setBootState(bool p)
{
    bootState = p;
}
void Computer::updateBootState(bool p)
{
    bootState = p;
    if(bootState == true)
    {
        cout << "Booting computer into " << os << "..." << endl;
    }
    if(bootState == false)
    {
        cout << "Shutting down..." << endl;
    }
}
void Computer::setDiskDrive(bool p)
{
  diskDrive = p;
}
void Computer::updateDiskDrive(bool p)
{
    diskDrive = p;
    if(diskDrive == true)
    {
        cout << "Installed optical disk drive." << endl;
    }
    if (diskDrive == false)
    {
        cout << "Removed optical disk drive." << endl;
    }
}
void Computer::setGpu(string str)
{
    gpu = str;
}
void Computer::updateGpu(string str)
{
    gpu = str;
    validateParts();
    cout << "Installed new GPU: " << gpu << endl;
}

// other methods

void Computer::displayInfo()
{   
    cout << " " << endl;
    cout << "Power: ";
    if(bootState == 1)
    {
        cout << "[ON] (booted into " << os << ")" << endl;
    }
    else
    {
        cout << "[OFF]" << endl;
    }

    cout << "|---" << serial << "----------------------------X|" << endl;
    cout << "| Manufacturer: " << MANUF << endl;
    cout << "| Model: " << model << endl;
    cout << "| Serial #: " << serial << endl; 
    cout << "| CPU: " << cpu << endl;
    cout << "| Clock Speed: " << speed << "Ghz" << endl;
    cout << "| RAM: " << memory << "gb" << endl;
    cout << "| HDD: " << hddSize << "gb " << hddType << endl;
    cout << "| GPU: " << gpu << endl;
    cout << "| Default OS: " << os << endl;
    cout << "| ODD: ";
    if(diskDrive == true)
    {
        cout << "Installed" << endl;
    }
    else
    {
        cout << "N/A" << endl;
    }
    cout << "|---------------------------------------------|" << endl;
}

// default deconstructor
Computer::~Computer()
{
  //does not do inventory--; because of dynamic data allocation in the vector when new computers are added.
}