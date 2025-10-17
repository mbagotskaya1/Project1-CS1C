#include "Graphics.h"


Graphics::Graphics(AddressBook *book)
{
   // Store local pointer to book
   this->book = book;
   // Set screen width and height
   screenRec = {1, 1, 154, 40};


   // Set screen split recs (menuRec 1/4 screenRec width)
   int headerHeight = 5;
   menuHeaderRec = {screenRec.x, screenRec.y, screenRec.width / 4, headerHeight};
   menuRec = {menuHeaderRec.x, menuHeaderRec.y + menuHeaderRec.height - 1, menuHeaderRec.width, screenRec.height - menuHeaderRec.height + 1};


   bookHeaderRec = {menuHeaderRec.x + menuHeaderRec.width - 1, screenRec.y, screenRec.width - menuHeaderRec.width + 1, headerHeight};
   bookRec = {bookHeaderRec.x, bookHeaderRec.y + bookHeaderRec.height - 1, bookHeaderRec.width, screenRec.height - bookHeaderRec.height + 1};


   // Initiallize named book section header rectangles
   initBookSectionHeaderRecs();


   // Set start x coordinate for menu option printing
   menuOptionsX = menuRec.x + menuRec.width / 4;


   // Clear screen
   cout << CLEAR_SCREEN;


   // Display initial book column headers
   printBookHeaders();


   // Init contact printing
   contactHeight = 3;
   maxContactsShown = bookRec.height / (contactHeight - 1) - 1;
   bufferPlace = 0;


   // Display initial screen borders
   printRec(menuHeaderRec);
   printRec(menuRec);
   printRec(bookHeaderRec);
   printRec(bookRec);
   printRec(screenRec);
}


Graphics::~Graphics() {}


void Graphics::displayMenu(Menu menu)
{
   // Reset menu rec and header
   clearRec(menuRec);
   clearRec(menuHeaderRec);


   // Call print function based on menu
   switch (menu)
   {
   case Menu::MainMenu:
       printMainMenu();
       break;


   case Menu::ContactManagement:
       printContactManagmentSubMenu();
       break;


   case Menu::FilterSearch:
       printFilterSearchSubMenu();
       break;


   case Menu::ImportExport:
       printImportExportSubMenu();
       break;


   case Menu::Reports:
       printReportsSubMenu();
       break;


   default:
       cout << "ERROR | Graphcis displayMenu";
       exit(1);
   }
}


// Replaces current contact buffer with vec of contacts
void Graphics::displayContactSet(const vector<Contact> contactSet)
{
   contactBuffer.clear();


   clearRec(bookRec);


   for (int i = 0; i < contactSet.size(); i++)
   {
       contactBuffer.push_back(contactSet[i]);
   }


   printContactBuffer();
}


void Graphics::displayBook()
{
   displayContactSet(book->getBook());
}


// Prints one contact on screen
void Graphics::displayContact(int index)
{
   int numSections = (int)ContactSection::NUM;
   int vertSpacing = bookRec.height / (numSections + 1);


   // Check if index is within bufferSize
   if (index > contactBuffer.size())
   {
       cout << "Error | displayContact index size";
   }


   // Clears contact box
   clearRec(bookRec);


   for (int i = 0; i < numSections; i++)
   {
       // Get field data
       string field = contactBuffer[index].numFieldToString(i);


       // Get x for centered text
       int x, y;
       getRecCenterForString(x, y, bookRec, field);


       // Ignore function y and print at multiple of vert spacing
       cout << MOVE_CURSOR(x, bookRec.y + vertSpacing * (i + 1)) << field;
   }
}


void Graphics::pageUp()
{
   // Increment buffer by one page of contacts
   bufferPlace += maxContactsShown;


   // Bounds check top
   if (bufferPlace > contactBuffer.size())
   {
       bufferPlace = contactBuffer.size() - 1;
   }
}
void Graphics::pageDown()
{
   // Decrement buffer
   bufferPlace -= maxContactsShown;


   // Bounds check bottom
   if (bufferPlace < 0)
   {
       bufferPlace = 0;
   }
}


// Private
void Graphics::printMainMenu()
{
   // Caclulate start y coordinate for menu option printing (center minus num lines)
   int optionsY = menuRec.getCenterY() - 5;


   // Get center minus half size string offset for header and print
   int x, y;
   getRecCenterForString(x, y, menuHeaderRec, "Main_Menu");
   cout << MOVE_CURSOR(x, y) << "Main Menu";


   // Print menu options (y is manually incremented each new line)
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "1. Contact Managment";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "2. Search or Filter";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "3. Import or Export";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "4. Reports";
   cout << MOVE_CURSOR(menuOptionsX, optionsY) << "5. Quit";
}


void Graphics::printContactManagmentSubMenu()
{
   int optionsY = menuRec.getCenterY() - 6;


   // Print header
   int x, y;
   getRecCenterForString(x, y, menuHeaderRec, "Contact_Management");
   cout << MOVE_CURSOR(x, y) << "Contact Management";


   // Print options
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "1. Add New Contact";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "2. Edit Contact";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "3. Delete Contact";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "4. View Contact";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "5. List All Contacts";
   cout << MOVE_CURSOR(menuOptionsX, optionsY) << "6. Back";
}


void Graphics::printFilterSearchSubMenu()
{
   int optionsY = menuRec.getCenterY() - 2;


   // Print header
   int x, y;
   getRecCenterForString(x, y, menuHeaderRec, "Search_or_Filter");
   cout << MOVE_CURSOR(x, y) << "Search or Filter";


   // Print options
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "1. Search for Contact";
   cout << MOVE_CURSOR(menuOptionsX, optionsY) << "2. Filter Contacts";
}


void Graphics::printImportExportSubMenu()
{
   int optionsY = menuRec.getCenterY() - 2;


   // Print header
   int x, y;
   getRecCenterForString(x, y, menuHeaderRec, "Import_or_Export");
   cout << MOVE_CURSOR(x, y) << "Import or Export";


   // Print options
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "1. Import";
   cout << MOVE_CURSOR(menuOptionsX, optionsY) << "2. Export";
}


void Graphics::printReportsSubMenu()
{
   int optionsY = menuRec.getCenterY() - 3;


   // Print header
   int x, y;
   getRecCenterForString(x, y, menuHeaderRec, "Reports");
   cout << MOVE_CURSOR(x, y) << "Reports";


   // Print options
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "1. List by Type";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "2. Show Missing";
   cout << MOVE_CURSOR(menuOptionsX, optionsY++) << "3. Display Group Summaries";
}


void Graphics::initBookSectionHeaderRecs()
{
   int numSections = (int)ContactSection::NUM;
   int bookHeaderColumnWidth = bookHeaderRec.width / numSections;


   int remainder;


   if (bookHeaderRec.width / (float)bookHeaderColumnWidth != numSections)
   {
       remainder = bookHeaderRec.width % numSections;
   }


   int width, x = bookHeaderRec.x;
   for (int i = 0; i < numSections; i++)
   {
       width = bookHeaderColumnWidth;


       if (remainder)
       {
           width++;
           remainder--;
       }


       bookSectionHeaderRec[i] = {x, bookHeaderRec.y, width, bookHeaderRec.height};


       x += width;
   }
}


void Graphics::printBookHeaders()
{
   string headerNames[] = {"Name", "City", "Email", "Number", "Type", "Tags", "Groups"};


   for (int x = 0; x < (int)ContactSection::NUM; x++)
   {
       int centerX, centerY;
       getRecCenterForString(centerX, centerY, bookSectionHeaderRec[x], headerNames[x]);


       printRec(bookSectionHeaderRec[x]);
       cout << MOVE_CURSOR(centerX, centerY) << headerNames[x];
   }
}


void Graphics::printContactBuffer()
{
   for (int i = bufferPlace; i < bufferPlace + maxContactsShown && i < contactBuffer.size(); i++)
   {
       Rectangle contactRec = {bookRec.x, bookRec.y + (i - bufferPlace) * (contactHeight - 1), bookRec.width, contactHeight};
       printRec(contactRec);


       for (int n = 0; n < (int)ContactSection::NUM; n++)
       {
           Rectangle contactSectionRec = {bookSectionHeaderRec[n].x, contactRec.y, bookSectionHeaderRec[n].width, contactHeight};
           printRec(contactSectionRec);


           // Get field data
           string field = contactBuffer[i].numFieldToString(n);


           // Concatonate field data to space available
           int maxStringSize = contactSectionRec.width - 4;
           if (field.size() > maxStringSize)
           {
               field = field.substr(0, maxStringSize);
           }


           // Center printing
           int x, y;
           getRecCenterForString(x, y, contactSectionRec, field);


           cout << MOVE_CURSOR(x, y) << field;
       }
   }


   printRec(bookRec);
}


void Graphics::printRec(Rectangle rec)
{
   int left = rec.x;
   int right = rec.x + rec.width - 1;
   int top = rec.y;
   int bottom = rec.y + rec.height - 1;


   // Top line
   cout << MOVE_CURSOR(left, top);
   for (int x = left; x <= right; x++)
   {
       cout << "-";
   }


   // Sides
   for (int y = top + 1; y < bottom; y++)
   {
       cout << MOVE_CURSOR(left, y) << "|";
       cout << MOVE_CURSOR(right, y) << "|";
   }


   // Bottom line
   cout << MOVE_CURSOR(left, bottom);
   for (int x = left; x <= right; x++)
   {
       cout << "-";
   }
}


void Graphics::clearRec(Rectangle rec)
{
   // For every space inside the rectangle write an empty space
   for (int y = rec.y + 1; y <= rec.y + rec.height - 2; y++)
   {
       for (int x = rec.x + 1; x <= rec.x + rec.width - 2; x++)
       {
           cout << MOVE_CURSOR(x, y) << ' ';
       }
   }
}


void Graphics::getRecCenterForString(int &x, int &y, Rectangle rec, string s)
{
   // Set y to centerline
   y = rec.y + rec.height / 2;


   // Set x to centerline minus half of text length
   x = rec.x + round((rec.width - s.length()) / 2.0);
}
