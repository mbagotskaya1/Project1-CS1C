#include <iostream>
#include <string>
#include "AddressBook.h"
#include "Reports.h"
#include "Graphics.h"
#include "Input.h"
#include "ImportExport.h"
#include "GraphicTypes.h"

using namespace std;


int main() {
   AddressBook ab;
   Graphics graphics(&ab);
   Reports report(&ab);
   Input input;
   ImportExport io;
   Menu currentMenu = Menu::MainMenu;
    
   bool isRunning = true;

    do { 
        graphics.displayMenu(currentMenu);
        graphics.outputMenuPrompt();
        int choice = input.getIntegerChoice();
        
        if (choice > 1 && choice < 6) {

        }


        currentMenu = (Menu)choice;

        switch (currentMenu) {




        }


    } while (isRunning) ;



   return 0;
}



