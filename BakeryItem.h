#ifndef BAKERYITEM_H
#define BAKERYITEM_H

#include <iostream>
#include <string>
#include "Ingredient.h"
#include "Employee.h"

using namespace std;

class BakeryItem {
  private:
    string name;
    string description;
    double pricePerUnit;
    Ingredient * ingredient = nullptr;
    int ingredientCount = 0;
    string recipe;
    bool disabled = false;
    static int bakeryItemCount;
        
  public:
    // Constructor
    BakeryItem();
    BakeryItem(string name, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe);

    // member functions
    void displayBakeryItemDetails() const;

    // friend functions to be used by main.cpp
    // friend void accessMenuDetails() const;
    friend void accessMenuList(BakeryItem []);
    friend void accessMenuDetails(BakeryItem &);

    // destructor
    ~BakeryItem();
};

#endif