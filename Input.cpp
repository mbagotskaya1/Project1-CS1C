#include "Input.h"
using namespace std;


int Input::getIntegerChoice(int min, int max)
{
    int choice;
    while (true) {
        if (cin >> choice) {
            cin.ignore();
            return choice;
        } 
    }
}

/*
    else {
            cin.clear();
            cin.ignore();
        }
*/


string Input::getLine()
{
    string input;
    getline(cin, input);
    return input;
}


// probably not very useful since we have the graphics class.....
Contact Input::getContactInfo()
{
    Contact c;


    getline(cin, c.name);
    getline(cin, c.city);
    getline(cin, c.email);
    getline(cin, c.phoneNumber);


    int typeInt;
    cin >> typeInt;
    cin.ignore();
    c.type = static_cast<ContactType>(typeInt);


   
    string t;
    getline(cin, t);
    c.tag.push_back(t);


    string g;
    getline(cin, g);
    c.group.push_back(g);


    return c;
}




