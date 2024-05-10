#ifndef BAKERYITEM_H
#define BAKERYITEM_H

#include <iostream>
#include <string>
#include "Ingredient.h"

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
        
  public:
    // Constructor
    BakeryItem(string name, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe);

    // member functions
    void displayBakeryItemDetails() const;

    // destructor
    ~BakeryItem();
};

#endif