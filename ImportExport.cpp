#include "ImportExport.h"
#include "Contact.h"
#include <iostream>
#include <sstream>


using namespace std;


vector<Contact> ImportExport::loadContactsFromFile(const string& file)
{
    vector<Contact> ab;
    ifstream inFile(file);


    while (!inFile.eof())
    {
        //Contact contact = ImportExport().getNextContact(inFile);
    }


    inFile.close();
    return ab;
}


void ImportExport::saveContactsToFile(const string& file, vector<Contact>* abPtr)
{
    ofstream outFile(file);


    for (const auto& contact : *abPtr)
    {
        // outFile << contact.contactToString() << "\n";
    }


    outFile.close();
}










