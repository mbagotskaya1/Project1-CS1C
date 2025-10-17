#pragma once
#include <vector>
#include <string>


using std::string;
using std::vector;


enum ContactType
{
   Person,
   Business,
   Vendor,
   Emergency
};


struct Contact
{
   string name;
   string city;
   string email;
   string phoneNumber;


   ContactType type;
   vector<string> tag;
   vector<string> group;


   // Full contact equivalency check (excludes type tag group)
   bool operator==(const Contact &other)
   {
       if (name == other.name && city == other.city && email == other.email && phoneNumber == other.phoneNumber)
       {
           return true;
       }
       return false;
   }


   // Returns if given string is among base contact values
   bool containsBase(const string &b)
   {
       if (b == name || b == city || b == email || b == phoneNumber)
       {
           return true;
       }
       return false;
   }


   // Returns index of tag if found -1 if not
   int containsTag(const string &t)
   {
       for (int i = 0; i < tag.size(); i++)
       {
           if (tag[i] == t)
           {
               return i;
           }
       }
       return -1;
   }


   // Returns index of group if found -1 if not
   int containsGroup(const string &g)
   {
       for (int i = 0; i < group.size(); i++)
       {
           if (group[i] == g)
           {
               return i;
           }
       }
       return -1;
   }


   // Returns field num data as string (0 indexed)
   string numFieldToString(int numField)
   {
       string contactTypeStringArr[] = {"Person", "Business", "Vendor", "Emergency"};
       string tags, groups;


       switch (numField)
       {
       case 0:
           return name;
           break;


       case 1:
           return city;
           break;


       case 2:
           return email;
           break;


       case 3:
           return phoneNumber;
           break;


       case 4:
           return contactTypeStringArr[(int)type];
           break;


       case 5:
           for (int i = 0; i < tag.size(); i++)
           {
               tags += tag[i];
               if (i < tag.size())
               {
                   tags += ' ';
               }
           }
           return tags;
           break;


       case 6:
           for (int i = 0; i < group.size(); i++)
           {
               groups += group[i];
               groups += ' ';
           }
           return groups;
           break;


       default:
           return "Error | numFieldToString";
           exit(1);
       }
   }

};

