#ifndef BAKERYITEM_H
#define BAKERYITEM_H

#include <iostream>
#include <string>

#include "Constant.h"
#include "Cake.h"
#include "Ingredient.h"
#include "IngredientInventory.h"

using namespace std;

const int MAX_INGREDIENTS = Constant::MAX_BAKERY_ITEMS;

class BakeryItem {
  private:
    string name;
    string category;
    string description;
    double pricePerUnit;
    Ingredient * ingredient = new Ingredient[MAX_INGREDIENTS];
    int ingredientCount = 0;
    int quantity = 0;
    string recipe;
    bool disabled = false;
    Cake * cake;
    static int bakeryItemCount;
    static BakeryItem * bakeryItems; // pointer from Employee class
        
  public:
    // Constructor
    BakeryItem();
    BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, int totalWeight = 0);

    // member functions
    void displayBakeryItemDetails() const;
    double calculateCost() const;
    double calculateProfit() const;
    void setIngredientCostToInventoryIngredientCost(IngredientInventory *);

    // accessor
    string getBakeryItemName() const;
    string getBakeryItemDescription() const;
    double getPricePerUnit() const;
    Ingredient * getIngredient(int) const;
    string getIngredientName(int) const;
    int getIngredientCount() const;
    int getBakeryItemQuantity() const;
    string getRecipe() const;
    bool getDisabled() const;
    int getBakeryItemCount() const;

    // mutator
    void setBakeryItems(BakeryItem *);
    void setPricePerUnit(double);
    void setBakeryItemQuantity(int);
    void setRecipe(string);
    void setDisabled(bool);

    // friend functions to be used by main.cpp
    friend void accessMenuDetails(BakeryItem &);

    // destructor
    ~BakeryItem();
};

#endif