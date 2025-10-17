#pragma once


enum class Menu
{
   MainMenu,
   ContactManagement,
   FilterSearch,
   ImportExport,
   Reports,
   Quit,
   NUM
};


enum class ContactSection
{
   Name,
   City,
   Email,
   Number,
   Type,
   Tag,
   Group,
   NUM
};


struct Rectangle
{
   int x, y, width, height;


   int getCenterX() { return x + width / 2; }
   int getCenterY() { return y + height / 2; }
};

