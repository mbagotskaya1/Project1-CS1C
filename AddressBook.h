#pragma once
#include <iostream>
#include <iostream>
#include <algorithm>
#include "Contact.h"

using std::vector;


class AddressBook
{


public:
   AddressBook();
   AddressBook(vector<Contact> &contactSet);


   ~AddressBook();


   void addContact(Contact contact);
   void addContact(vector<Contact> &contactSet);


   bool deleteContact(Contact contact);
   bool deleteContact(vector<Contact> &contactSet);
   bool deleteContact(int index);


   void editBaseContact(string baseField, string newVal, int index = -1, Contact contact = {});


   void addGroup(int contactIndex, string group);
   bool removeGroup(int contactIndex, string group);


   void addTag(int contactIndex, string tag);
   bool removeTag(int contactIndex, string tag);


   vector<Contact> filterByBase(const string &baseField);
   vector<Contact> filterByType(const ContactType &type);
   vector<Contact> filterByGroup(const string &group);
   vector<Contact> filterByTag(const string &tag);

   inline vector<Contact> getBook () { return contacts; }

private:
   vector<Contact> contacts;


private:
   int findContactByContact(Contact contact);
};


