#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "AddressBook.h"

using std::string, std::vector;
// ImportExport includes functions to read an address book from a file,
// and to save an address book to a file.
class ImportExport
{  
public:


    static vector<Contact> loadContactsFromFile(const string& file);
   
    static void saveContactsToFile (const string& file, vector<Contact> *abPtr);

    
};




