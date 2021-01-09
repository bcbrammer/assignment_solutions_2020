// .txt file word extractor by Brad Brammer
// 10/17/2020 v1.0
// this program lets you analyze a words.txt file and will display every word
// in the .txt file delimited by a space
// words with a space in them are not recognized
// it trims punctuation from the entire document, so words like string.length() would become stringlength
// it does not use any NLP pkg or dictionary database to know if something is a word

#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

bool containsPunctuation(string str);
void removePunctuation(string * str);
void stringTolower(string * str);

set<string> generateWordList()
{
    cout << "Parsing words.txt . . . " << endl;
    // declare needed variables
    set<string> wordList; // the set we will return and display
    ifstream file; // the input stream we will use to open words.txt
    string word; // a string to put words in as we read them, then insert and store them to the list after cleaning
    file.open("words.txt", ios::in);
    while(file >> word)
    {
        // cout << word << endl; uncomment to preview words before cleaning
        // although it is slower, using a while() instead of if() here will make sure that removePunctuation()
        // will erase ALL leading and ending punctuation from a word for example "..." and " '''. . alkjwl;.ll<>?/"/?"  will be clipped.
        while(containsPunctuation(word) == true) 
        {
            removePunctuation(&word);
        }
        stringTolower(&word);
        // cout << word << endl; uncomment to preview words after cleaning before list
        wordList.insert(word);
    }
    file.close();
    return wordList;
}

int main()
{
    set<string> wordList = generateWordList();
    for(string it : wordList)
    {
        cout << it << endl;
    }
}

bool containsPunctuation(string str)
{
    for(int i = 0; i < str.size(); i++)
    {   
        if(str.front() == '\'') // this will find leading single quotes
        {
            return true;
        }
        if(str.back() == '\'') // this will find ending single quotes
        {
            return true;
        }
        if(str[i] == '\'') // we don't want to count apostrophes or single quotes WITHIN words
        {
            i++; // so we skip to the next index when we see one inside a word
        }
        if(ispunct(str[i]))
        {
            return true;
        }
    }
    return false;
}

void removePunctuation(string * str)
{
    string modStr = *str; // modStr is a string to modify before altering the final string pointer
    int length = modStr.size(); // this is the length of the string, which changes as we erase punctuation
    if(modStr.front() == '\'') // this will find leading single quotes
    {
        modStr.erase(modStr.begin()+0);
        length = modStr.size();
    }
    if(modStr.back() == '\'') // this will find ending single quotes
    {
        modStr.pop_back();
        length = modStr.size();
    }
    for(int i = 0; i < length; i++)
    {
        if(modStr[i] == '\'') // we don't want to remove apostrophes or single quotes inside of words
        {
            i++;
        }
        if(ispunct(modStr[i]))
        {
            modStr.erase(i--, 1);
            length = modStr.size();
        }
    }
    *str = modStr;
}

// puts an entire string to lowercase
void stringTolower(string * str)
{
    string modStr = *str;
    for(int i = 0; i < modStr.size(); i++)
    {
        modStr[i] = tolower(modStr[i]);
    }
    *str = modStr;
}