#ifndef REPORTS_H
#define REPORTS_H
#include <string>
#include <vector>
#include "AddressBook.h"
using std::string, std::vector;


/*
* The Reports class
*  - Lists contacts by their type (Person, Business, Vendor, Emergency)
*  - Shows contacts missing essential information like email or phone
*/


class Reports
{
public:
   Reports(AddressBook *abPtr); // creates a Reports object that has a pointer to a variable in the AddressBook class


   /* Displays a report of contacts missing an email or phone number.
    *
    * This function scans all contacts in the AddressBook and lists those
    * missing either an email address or a phone number.
    */
   void showMissing();


   /* Lists contacts by type
    * This function categorizes contacts (Person, Business, Vendor, Emergency)
    * and displays each category along with the associated contacts.
    */
   void listContactsByType();


private:
   AddressBook *abPtr; ///< Pointer to the AddressBook used to generate reports.
};

#endif