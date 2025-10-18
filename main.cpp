#include <iostream>
#include <string>
#include <vector>

#include "AddressBook.h"
#include "Reports.h"
#include "Graphics.h"
#include "Input.h"
#include "ImportExport.h"
#include "GraphicTypes.h"

using namespace std;

static Contact makeContact(Input& input) {
    Contact c;
    cout << "Name: ";        c.name = input.getLine();
    cout << "City: ";        c.city = input.getLine();
    cout << "Email: ";       c.email = input.getLine();
    cout << "Phone: ";       c.phoneNumber = input.getLine();
    cout << "Type (0 = Person, 1 = Business, 2 = Vendor, 3 = Emergency): ";
    c.type = static_cast<ContactType>( input.getIntegerChoice(0, 3) );
    return c;
}

int main() {
    AddressBook  ab;
    Graphics     graphics(&ab);
    Reports      report(&ab);
    Input        input;

    Menu currentMenu = Menu::MainMenu;
    bool isRunning   = true;

    do {
        graphics.displayMenu(currentMenu);
        graphics.outputMenuPrompt();

        int choice = 0;
        switch (currentMenu) {
            case Menu::MainMenu:          choice = input.getIntegerChoice(1, 5); break;
            case Menu::ContactManagement: choice = input.getIntegerChoice(1, 6); break;
            case Menu::FilterSearch:      choice = input.getIntegerChoice(1, 2); break;
            case Menu::ImportExport:      choice = input.getIntegerChoice(1, 2); break;
            case Menu::Reports:           choice = input.getIntegerChoice(1, 3); break;
            default:                      choice = 1; break;
        }

        switch (currentMenu) {
            // ===== MAIN =====
            case Menu::MainMenu: {
                if      (choice == 1) currentMenu = Menu::ContactManagement;
                else if (choice == 2) currentMenu = Menu::FilterSearch;
                else if (choice == 3) currentMenu = Menu::ImportExport;
                else if (choice == 4) currentMenu = Menu::Reports;
                else if (choice == 5) currentMenu = Menu::Quit;
            } break;

            // ===== CONTACT MANAGEMENT =====
            // 1 Add (uses addContact(Contact))
            // 2 Edit base (uses editBaseContact(field, newVal, index))
            // 3 Delete (choose overload: by index or by Contact)
            // 4 View one (by index, show with Graphics)
            // 5 List all (Graphics)
            // 6 Back
            case Menu::ContactManagement: {
                if (choice == 1) {
                    Contact c = makeContact(input);
                    ab.addContact(c);                 // overload: addContact(Contact)
                    graphics.displayBook();
                }
                else if (choice == 2) {
                    vector<Contact> book = ab.getBook();
                    if (book.empty()) { cout << "(No contacts)\n"; break; }

                    cout << "Index to edit (0.." << (int)book.size()-1 << "): ";
                    int idx = input.getIntegerChoice(0, (int)book.size()-1);

                    cout << "Field (name/city/email/phoneNumber): ";
                    string field = input.getLine();

                    cout << "New value: ";
                    string val = input.getLine();

                    ab.editBaseContact(field, val, idx);
                    graphics.displayBook();
                }
                else if (choice == 3) {
                    cout << "Delete by: 1) Index  2) Exact Contact\n> ";
                    int how = input.getIntegerChoice(1, 2);

                    if (how == 1) {
                        vector<Contact> book = ab.getBook();
                        if (book.empty()) { cout << "(No contacts)\n"; break; }
                        cout << "Index to delete (0.." << (int)book.size()-1 << "): ";
                        int idx = input.getIntegerChoice(0, (int)book.size()-1);
                        ab.deleteContact(idx);          // overload: deleteContact(int)
                    } else {
                        cout << "Enter the exact contact to delete:\n";
                        Contact c = makeContact(input);
                        ab.deleteContact(c);            // overload: deleteContact(Contact)
                    }
                    graphics.displayBook();
                }
                else if (choice == 4) {
                    vector<Contact> book = ab.getBook();
                    if (book.empty()) { cout << "(No contacts)\n"; break; }

                    cout << "Index to view (0.." << (int)book.size()-1 << "): ";
                    int idx = input.getIntegerChoice(0, (int)book.size()-1);

                    vector<Contact> one{ book[idx] };
                    graphics.displayContactSet(one);
                    graphics.displayContact(0);
                }
                else if (choice == 5) {
                    graphics.displayBook();
                }
                else if (choice == 6) {
                    currentMenu = Menu::MainMenu;
                }
            } break;

            // ===== SEARCH / FILTER =====
            // 1 Search base (uses filterByBase(value))
            // 2 Filter (type/city/tag/group)
            case Menu::FilterSearch: {
                if (choice == 1) {
                    cout << "Search value (matches name/city/email/phoneNumber exactly): ";
                    string val = input.getLine();
                    vector<Contact> matches = ab.filterByBase(val); // overload provided
                    graphics.displayContactSet(matches);
                }
                else if (choice == 2) {
                    cout << "Filter by: 1) Type  2) City  3) Tag  4) Group\n> ";
                    int by = input.getIntegerChoice(1, 4);

                    if (by == 1) {
                        cout << "Type (0=Person,1=Business,2=Vendor,3=Emergency): ";
                        int t = input.getIntegerChoice(0, 3);
                        graphics.displayContactSet( ab.filterByType(static_cast<ContactType>(t)) );
                    } else if (by == 2) {
                        cout << "City: ";
                        string city = input.getLine();
                        graphics.displayContactSet( ab.filterByBase(city) ); // containsBase handles city
                    } else if (by == 3) {
                        cout << "Tag: ";
                        string tag = input.getLine();
                        graphics.displayContactSet( ab.filterByTag(tag) );
                    } else { // 4
                        cout << "Group: ";
                        string group = input.getLine();
                        graphics.displayContactSet( ab.filterByGroup(group) );
                    }
                }
            } break;

            // ===== IMPORT / EXPORT =====
            // 1 Import (vector<Contact> -> addContact(vector&))
            // 2 Export (saveContactsToFile)
            case Menu::ImportExport: {
                if (choice == 1) {
                    cout << "Import file name: ";
                    string path = input.getLine();
                    vector<Contact> loaded = ImportExport::loadContactsFromFile(path);
                    if (!loaded.empty()) {
                        ab.addContact(loaded);          // overload: addContact(vector<Contact>&)
                        graphics.displayBook();
                    }
                }
                else if (choice == 2) {
                    cout << "Export file name: ";
                    string path = input.getLine();
                    vector<Contact> copy = ab.getBook();
                    ImportExport::saveContactsToFile(path, &copy);
                }
            } break;

            // ===== REPORTS =====
            // 1 List by Type
            // 2 Show Missing
            //3 Display Group Summaries;
            case Menu::Reports: {
                if (choice == 1)      report.listContactsByType();
                else if (choice == 2) report.showMissing();
                else if (choice == 3) /* did not find */ ;
            } break;

            case Menu::Quit:
                isRunning = false;
                break;

            default:
                currentMenu = Menu::MainMenu;
                break;
        }

    } while (isRunning);

    return 0;
}
