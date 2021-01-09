// computer object builder and editor by Bradley Brammer
// v1.3 09.29.2020
// makes a computer object with some parts, lets you edit or add to some of those parts
// contains strong data validation and exception handling both in class scope and in source scope

#include <iostream>
#include <string>
#include <cmath>
#include <optional>
#include <vector>

#include "Computer.h"
#include "DataValidator.h"

using namespace std;

// displays menu to modify the PC, some modifications available when it is on and others when off
void displayMenu(Computer *myComputer)
{
    cout << " " << endl;
    cout << "[Modifying: " << myComputer->getSerial() << "]" << endl;
    cout << "What would you like to do?" << endl;
    cout << " - 0 - View Computer Information" << endl;

    if (myComputer->getBootState() == 1)
    {
        cout << " - 1 - Shut Down PC " << endl;
        cout << " - 2 - Load new Operating System " << endl;
        cout << " - 3 - Return to Inventory" << endl;
        cout << " - 4 - Disassemble PC" << endl;
    }

    else if (myComputer->getBootState() == 0)
    {
        cout << " - 1 - Boot PC into " << myComputer->getOs() << endl;
        cout << " - 2 - Replace all RAM " << endl;
        cout << " - 3 - Add more RAM " << endl;
        cout << " - 4 - Replace HDD " << endl;
        if (myComputer->getDiskDrive() == false)
        {
            cout << " - 5 - Install Optical Disk Drive " << endl;
        }
        else if (myComputer->getDiskDrive() == true)
        {
            cout << " - 5 - Remove Optical Disk Drive " << endl;
        }
        if (myComputer->getGpu() == "N/A")
        {
            cout << " - 6 - Install Graphics Card " << endl;
        }
        else
        {
            cout << " - 6 - Change Graphics Card " << endl;
        }
        cout << " - 7 - Return to Inventory" << endl;
        cout << " - 8 - Disassemble PC" << endl;
    }
}

void executeMenu(Computer *myComputer, bool *quitFlag, bool *destroyFlag) // switch statements to execute menu options based on inputted menu choice
{
    int menuOp = 0; // because menuOp is an integer, you can enter "5.21" and will get menu option 5
    string tempStr = "0";
    int tempInt = 0;

    do
    {
        cout << "Input your operation # and press <ENTER>: " << endl;
        getline(cin, tempStr);
        if (isNumber(tempStr) == false)
        {
            cout << "Must input a number to select an operation." << endl;
        }
    } while (isNumber(tempStr) == false);
    menuOp = stoi(tempStr);

    if (myComputer->getBootState() == 1) // menu when PC is turned on (can't change parts)
    {
        switch (menuOp)
        {
        case 0:
            myComputer->displayInfo();
            break;
        case 1:
            myComputer->updateBootState(0);
            break;
        case 2:
            myComputer->updateOs(inputStr("What new OS will you install?"));
            cout << "Rebooting... " << endl;
            break;
        case 3:
            *quitFlag = true;
            break;
        case 4:
            *quitFlag = true;
            *destroyFlag = true;
            break;
        default:
            cout << "Invalid operation #." << endl;
            break;
        }
    }
    else if (myComputer->getBootState() == 0) // menu when PC is turned off (can change parts)
    {
        switch (menuOp)
        {
        case 0:
            myComputer->displayInfo();
            break;
        case 1:
            myComputer->updateBootState(1);
            break;
        case 2:
            cout << "Removed all RAM." << endl;
            myComputer->updateMemory(inputInt("How much RAM to install?", 2));
            break;
        case 3:
            cout << "Current RAM: " << myComputer->getMemory() << "gb" << endl;
            myComputer->addMemory(inputInt("How much RAM to add?", 2));
            break;
        case 4:
            cout << "Removed HDD. (You will be prompted to install a new OS after replacement.)" << endl;
            cout << "Available HDD sizes (in gb): ";
            Computer::printHDD_SIZES();
            myComputer->updateHdd
                (
                inputInt("New HDD size (in gb): ", 250, 12000),
                inputStr("New HDD type (SATA or SSD): ", 5),
                inputStr("New OS to install: ")
                );
            break;
        case 5:
            if (myComputer->getDiskDrive() == false)
            {
                myComputer->updateDiskDrive(1);
            }
            else if (myComputer->getDiskDrive() == true)
            {
                myComputer->updateDiskDrive(0);
            }
            break;
        case 6:
            myComputer->updateGpu(inputStr("What kind of graphics card to install?"));
            break;
        case 7:
            *quitFlag = true;
            break;
        case 8:
            *quitFlag = true;
            *destroyFlag = true;
            break;
        default:
            cout << "Invalid operation #." << endl;
            break;
        }
    }
}

void setParts(string *model, string *cpu, double *speed, int *memory, int *hddSize, string *hddType, string *os)
{
  cout << "Enter the following details of the model..." << endl;
  *model = inputStr("Model Name: ");
  *cpu = inputStr("Central Processing Unit: ");
  *speed = inputDouble("Processor Speed (in Ghz): ", 0.00);
  *memory = inputInt("Preinstalled RAM amount (in gb): ", 2);
  cout << "Available HDD sizes (in gb): ";
  Computer::printHDD_SIZES();
  *hddSize = inputInt("Preinstalled Hard Disk space (in gb): ", 250, 12000);
  *hddType = inputStr("Type of HDD (SATA or SSD): ", 5);
  *os = inputStr("Preinstalled Operating System: ");
}

void validateBuild(Computer *pc)
{
    bool validParts = true;
    BadPart myBadParts;
    do
    {
        try
        {
          validParts = pc->validateParts();
        }
        catch (BadPart partsThrown)
        {
            myBadParts = partsThrown;
            do
            {
                try
                { 
                    cout << myBadParts.getNumErrors() << " error(s) detected while building your PC." << endl;
                    pc->badPartHandler(&myBadParts);
                    cout << "Attempting to build your PC..." << endl;
                    validParts = pc->validateParts();
                    cout << myBadParts.getNumErrors() << " error(s) resolved. Successfully built PC." << endl;
                }
                catch(BadPart partsThrown)
                {
                    myBadParts = partsThrown;
                    validParts = false;
                }
            }while(validParts == false);
        }
        catch (...)
        {
            cout << "Fatal Error when building the PC. Restarting build process..." << endl;
            validParts = false;
        }
    } while (validParts == false);
}

void editComputer(Computer *pc, bool *destroyFlag)
{
    bool validParts = true;
    BadPart myBadParts;
    bool quitFlag = false;
    do
    {
        displayMenu(pc);
        try
        {
            executeMenu(pc, &quitFlag, destroyFlag);
        }
        catch (BadPart partsThrown)
        {
            myBadParts = partsThrown;
            do
            {
                try
                {
                    pc->badPartHandler(&myBadParts);
                    cout << "Checking new " << myBadParts.getPartName(0) << "..." << endl;
                    validParts = pc->validateParts();
                    cout << myBadParts.getPartName(0) << " error resolved. Part updated." << endl;
                }
                catch(BadPart partsThrown)
                {
                    myBadParts = partsThrown;
                    validParts = false;
                }
            }while(validParts == false);
        }
    } while (quitFlag == false);
}

int main()
{
    // something to organize and hold all the Computer objects
    vector<Computer> myComputers;

    // declare reusable user input vars for the parts
    string model = "Four";
    string cpu = "Intel Celeron";
    double speed = 2.5;
    int memory = 4;
    int hddSize = 250;
    string hddType = "5CHAR";
    string os = "Windows ME";

    cout << "Let's create an initial computer." << endl;

    // function call to set the variables
    setParts(&model, &cpu, &speed, &memory, &hddSize, &hddType, &os);

    // directly call the overload constructor and put an object in the back of the vector
    myComputers.emplace_back(model, cpu, speed, memory, hddSize, hddType, os);

    // validate the parts and the new Computer object in the vector
    validateBuild(&myComputers.back());

    // displays the built and validated Computer object
    myComputers.back().displayInfo();

    bool exitFlag = false;
    bool destroyFlag = false;
    string choice = "NaN";
    while (exitFlag == false)
    {
        destroyFlag = false;
        cout << " " << endl;
        cout << "Computers in inventory: " << Computer::getInventory() << endl;
        cout << "-Index#---Serial#---------" << endl;
        for (int i = 0; i < myComputers.size(); i++)
        {
            cout << " - " << i << " -    " << myComputers[i].getSerial() << endl;
        }
        cout << "---------------------------" << endl;
        choice = inputStr("Enter Index # to modify that computer, 'a' to add a new one, or 'q' to quit.");
        if(isNumber(choice) == true && floor(stod(choice))==stod(choice) && stod(choice) >= 0 && stod(choice)<= (Computer::getInventory() - 1))
        {
            editComputer(&myComputers[stoi(choice)], &destroyFlag);
            if(destroyFlag == true)
            {
                cout << "Dissassembling " << myComputers[stoi(choice)].getSerial() << " . . . " << endl;
                Computer::decrementInventory();
                myComputers.erase(myComputers.begin() + stoi(choice));
            }

            // something here to clean the vector if the user destroys a computer
        }
        else if (choice == "a" || choice == "A")
        {
            setParts(&model, &cpu, &speed, &memory, &hddSize, &hddType, &os);
            myComputers.emplace_back(model, cpu, speed, memory, hddSize, hddType, os);
            validateBuild(&myComputers.back());
        }
        else if (choice == "q" || choice == "Q")
        {
            exitFlag = true;
        }
        else
        {
            cout << "Invalid menu choice. Try again." << endl;
        }
    }

    // pause console
    cin.ignore();
    cin.get();

    return 0;
}