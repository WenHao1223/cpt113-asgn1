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
    static BakeryItem * bakeryItems;
        
  public:
    // Constructor
    BakeryItem();
    BakeryItem(string name, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe);

    // member functions
    void displayBakeryItemDetails() const;
    int getBakeryItemCount() const;
    string getBakeryItemName() const;

    // friend functions to be used by Employee class
    // friend void Employee::accessMenuList(BakeryItem * item) const;
    // friend void accessMenuDetails() const;
    friend void accessBakeryName(BakeryItem * item);

    // destructor
    ~BakeryItem();
};

#endif