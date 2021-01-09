#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <optional>

#include "DataValidator.h"

using namespace std;

class Cipher
{
    public:
        Cipher(string str, int n)
        {
            message = str;
            shift = n;
        }
        void encrypt()
        {
            cout << "Encrypting with shift of " << shift << "..." << endl;
            string cipherText = "";
            for(int i = 0; i < message.length(); i++)
            {
                cipherText += doShift(message[i]);
            }
            message = cipherText;
        }
        void decrypt()
        {
            cout << "Decrypting for shift of " << shift << "..." << endl;
            string clearText = "";
            for(int i = 0; i < message.length(); i++)
            {
                clearText += undoShift(message[i]);
            }
            message = clearText;
        }
        void printMessage()
        {
            cout << "Current secret message: " << endl;
            cout << message << endl;
        }
        void setShift(int n)
        {
            shift = n;
            cout << "Shift set to: " << n << endl;
        }
        void setMessage(string str)
        {
            message = str;
        }
    private:
        string message;
        int shift;
        char doShift(char letter)
        {
            if(letter == ' ')
            {
                  return ' ';
            }
            else if(letter == '.')
            {
                  return '.';
            }
            else if(letter == ',')
            {
                  return ',';
            }
            else if(isupper(letter))
            {
                return (char)(((letter + shift - 'A' + 26) % 26) + 'A');
            }
            else
            {
                return (char)(((letter + shift - 'a' + 26) % 26) + 'a');
            }
        }
        char undoShift(char letter)
        {
            char argument;
            if(letter == ' ')
            {
                  return ' ';
            }
            else if(letter == '.')
            {
                  return '.';
            }
            else if(letter == ',')
            {
                  return ',';
            }
            else if(isupper(letter))
            {
                argument = (letter - shift - 'A' + 26);
                if(argument < 0)
                {
                  argument += 26;
                }
                return (char)(((letter - shift - 'A' + 26) % 26) + 'A');
            }
            else
            {   
                argument = (letter - shift - 'a' + 26);
                if(argument < 0)
                {
                  argument += 26;
                }
                return (char)(((letter - shift - 'a' + 26) % 26) + 'a');
            }
        }
};

bool isNumber(string str);

int main()
{
    // string to hold initial message to pass to Cipher object
    string str = "This is a secret message.";
    // integer to hold initial shift to pass to Cipher object
    int n = 1; 
    str = inputStr("Enter a secret message: ");
    n = inputInt("Enter the amount to shift the letters: ", 0, 26);
    Cipher myCode(str, n);
    myCode.printMessage();
    myCode.encrypt();
    myCode.printMessage();
    myCode.decrypt();
    myCode.printMessage();

    cin.ignore(); // just to pause the console after program is done so it doesn't quit out
    cin.get();
}

