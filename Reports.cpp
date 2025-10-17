#include "Reports.h"
#include <iostream>
using namespace std;
Reports::Reports(AddressBook *abPtr)
{
   this->abPtr = abPtr;
}
void Reports::showMissing()
{
   vector<Contact> contacts = abPtr->getBook(); // should call the getContacts from AddressBook
   bool missingInfo = false;
   cout << "=====================================" << endl;
   cout << "   REPORT: Contacts Missing Info" << endl;
   cout << "=====================================" << endl;
   for (const auto &c : contacts)
       {
           if (c.email.empty() || c.phoneNumber.empty())
           {
           	missingInfo = true;
               cout << "\n-------------------------------------\n";
               cout << "Name: " << c.name << endl;
               cout << "Email: " << (c.email.empty() ? "Missing" : c.email) << endl;
               cout << "Phone: " << (c.phoneNumber.empty() ? "Missing" : c.phoneNumber) << endl;
               cout << "City: " << c.city << endl;
               cout << "Type: ";
                          switch (c.type)
                          {
                          case Person:
                              cout << "Person";
                              break;
                          case Business:
                              cout << "Business";
                              break;
                          case Vendor:
                              cout << "Vendor";
                              break;
                          case Emergency:
                              cout << "Emergency";
                              break;
                          default:
                              cout << "Unknown";
                          }
                          cout << endl;
           }
       }
}
void Reports::listContactsByType()
{
	vector<Contact> contacts = abPtr->getBook();
   vector<Contact> persons;
   vector<Contact> businesses;
   vector<Contact> vendors;
   vector<Contact> emergencies;
   cout << "=====================================" << endl;
   cout << "        REPORT: Contacts by Type" << endl;
   cout << "=====================================" << endl;
   for (const auto &c : contacts)
   {
       switch (c.type)
       {
       case Person:
           persons.push_back(c);
           break;
       case Business:
           businesses.push_back(c);
           break;
       case Vendor:
           vendors.push_back(c);
           break;
       case Emergency:
           emergencies.push_back(c);
           break;
       default:
           break;
       }
   }
}

