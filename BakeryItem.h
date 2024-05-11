#ifndef BAKERYITEM_H
#define BAKERYITEM_H

#include <iostream>
#include <string>

#include "Ingredient.h"

using namespace std;

const int MAX_INGREDIENTS = 10;

class BakeryItem {
  private:
    string name;
    string description;
    double pricePerUnit;
    Ingredient * ingredient = new Ingredient[MAX_INGREDIENTS];
    int ingredientCount = 0;
    string recipe;
    bool disabled = false;
    static int bakeryItemCount;
    static BakeryItem * bakeryItems; // pointer from Employee class
        
  public:
    // Constructor
    BakeryItem();
    BakeryItem(string name, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe);

    // member functions
    void displayBakeryItemDetails() const;

    // accessor
    int getBakeryItemCount() const;
    string getBakeryItemName() const;
    string getRecipe() const;

    // mutator
    void setBakeryItems(BakeryItem *);
    void setRecipe(string);

    // friend functions to be used by main.cpp
    friend void accessMenuDetails(BakeryItem &);

    // destructor
    ~BakeryItem();
};

#endif