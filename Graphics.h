#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Contact.h"
#include "GraphicTypes.h"
#include "AddressBook.h"
#include <cmath>

using std::cout;
using std::vector;


// ansi codes to move cursor
#define MOVE_CURSOR(col, row) "\033[" << (row) << ";" << (col) << "H" // moves to col row
#define MOVE_DOWN(rows) "\033[" << rows << "B"                        // moves down rows number of rows
#define CLEAR_SCREEN "\033[2J"


class Graphics
{
public:
   Graphics(AddressBook *book);
   ~Graphics();


   void displayMenu(Menu menu);


   void displayContactSet(const vector<Contact> contactSet);
   void displayBook();
   void displayContact(int index);


   void pageUp();
   void pageDown();

   void outputMenuPrompt();

private:
   // Local book pointer
   AddressBook *book;


   // Screen delimeter rectangles
   Rectangle screenRec;
   Rectangle menuHeaderRec;
   Rectangle menuRec;
   Rectangle bookHeaderRec;
   Rectangle bookRec;


   // Holds named contact section recs
   Rectangle bookSectionHeaderRec[(int)ContactSection::NUM];


   // Start x coordinate for menu option printing
   int menuOptionsX;


   // Contact printing
   int contactHeight;
   int maxContactsShown;
   vector<Contact> contactBuffer;


   // Represents start of shown contacts in buffer | showing bufferPlace to maxContactsShown or bufferPlace to contactBuffer size
   int bufferPlace;


private:
   void printMainMenu();
   void printContactManagmentSubMenu();
   void printFilterSearchSubMenu();
   void printImportExportSubMenu();
   void printReportsSubMenu();


   void initBookSectionHeaderRecs();
   void printBookHeaders();


   void printContactBuffer();


   void printRec(Rectangle rec);
   void clearRec(Rectangle rec);


   void getRecCenterForString(int &x, int &y, Rectangle rec, string s);
};
