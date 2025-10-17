#pragma once
#include "addressBook.h"
#include "Contact.h"
#include <string>
using std::string;


class Input {


    public:
        static int getIntegerChoice(int min, int max);
        static string getLine();
        static Contact getContactInfo();
 };






