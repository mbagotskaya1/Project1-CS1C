#include "AddressBook.h"

AddressBook::AddressBook() {}
AddressBook::AddressBook(vector<Contact>& contactSet) {
    for (int i = 0; i < contactSet.size(); ++i) {
        contacts.push_back(contactSet[i]);
    }
}
AddressBook::~AddressBook() {}


void AddressBook::addContact(Contact contact) {
    contacts.push_back(contact);
}


void AddressBook::addContact(vector<Contact>& contactSet) {
    for (int i = 0; i < contactSet.size(); ++i) {
        contacts.push_back(contactSet[i]);
    }
}


bool AddressBook::deleteContact(Contact contact) {
    int index = findContactByContact(contact);
    if (index == -1) {

        return false;
    }
    contacts.erase(contacts.begin() + index);
   
    return true;
}


bool AddressBook::deleteContact(vector<Contact>& contactSet) {
    for (int i = 0; i < contactSet.size(); ++i) {
        bool deleted = deleteContact(contactSet[i]);
        if (!deleted) {
            return false;
        }
    }
    return true;
}


bool AddressBook::deleteContact(int index) {
    if (index < 0 || index >= contacts.size()) {
        return false;
    }
    contacts.erase(contacts.begin() + index);
    return true;
}


void AddressBook::editBaseContact(string baseField, string newVal, int index, Contact contact) {
    if (index == -1) {
        index = findContactByContact(contact);
    }
    if (index < 0 || index >= contacts.size()) {
        return;
    }
    if (baseField == "name") {
        contacts[index].name = newVal;
    } else if (baseField == "city") {
        contacts[index].city = newVal;
    } else if (baseField == "email") {
        contacts[index].email = newVal;
    } else if (baseField == "phoneNumber") {
        contacts[index].phoneNumber = newVal;
    } else {
        return;
    }
}


void AddressBook::addGroup(int contactIndex, string group) {
    if (contactIndex < 0 || contactIndex >= contacts.size()) {
        return;
    }
    contacts[contactIndex].group.push_back(group);
}


bool AddressBook::removeGroup(int contactIndex, string group) {
    if (contactIndex < 0 || contactIndex >= contacts.size()) {
        return false;
    }
    vector<string>* groupPtr = &contacts[contactIndex].group;
    int groupIndex = contacts[contactIndex].containsGroup(group);
    if (groupIndex == -1) {
        return false;
    }
    groupPtr->erase(groupPtr->begin() + groupIndex);
    return true;
}


void AddressBook::addTag(int contactIndex, string tag) {
    if (contactIndex < 0 || contactIndex >= contacts.size()) {
        return;
    }
    contacts[contactIndex].tag.push_back(tag);
}


bool AddressBook::removeTag(int contactIndex, string tag) {
    if (contactIndex < 0 || contactIndex >= contacts.size()) {
        return false;
    }
    vector<string>* tagPtr = &contacts[contactIndex].tag;
    int tagIndex = contacts[contactIndex].containsTag(tag);
    if (tagIndex == -1) {
        return false;
    }
    tagPtr->erase(tagPtr->begin() + tagIndex);
    return true;
}


vector<Contact> AddressBook::filterByBase(const string& baseField) {
    vector<Contact> filtered;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].containsBase(baseField)) {
            filtered.push_back(contacts[i]);
        }
    }

    return filtered;
}


vector<Contact> AddressBook::filterByType(const ContactType& type) {
    vector<Contact> filtered;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].type == type) {
            filtered.push_back(contacts[i]);
        }
    }

    return filtered;
}


vector<Contact> AddressBook::filterByGroup(const string& group) {
    vector<Contact> filtered;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].containsGroup(group)) {
            filtered.push_back(contacts[i]);
        }
    }

    return filtered;
}


vector<Contact> AddressBook::filterByTag(const string& tag) {
    vector<Contact> filtered;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].containsTag(tag)) {
            filtered.push_back(contacts[i]);
        }
    }

    return filtered;
}


int AddressBook::findContactByContact(Contact contact) {
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i] == contact) {
            return i;
        }
    }
    return -1;
}
