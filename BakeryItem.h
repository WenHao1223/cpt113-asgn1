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
    double quantity = 0; // double because user can choose to buy according to weight
    string recipe;
    bool disabled = false;
    Cake * cake;
    static int bakeryItemCount;
    static BakeryItem * bakeryItems; // pointer from Employee class
        
  public:
    // Constructor
    BakeryItem();
    BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled);
    BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled, int totalWeight);

    // member functions
    void displayBakeryItemDetails() const;
    double calculateCost() const;
    double calculateProfit() const;
    void setIngredientCostToInventoryIngredientCost(IngredientInventory *);

    // accessor
    string getBakeryItemName() const;
    string getBakeryItemCategory() const;
    string getBakeryItemDescription() const;
    double getPricePerUnit() const;
    Ingredient * getIngredient(int) const;
    string getIngredientName(int) const;
    Cake * getCake() const;
    int getIngredientCount() const;
    double getBakeryItemQuantity() const;
    string getRecipe() const;
    bool getDisabled() const;
    int getBakeryItemCount() const;

    // mutator
    void setBakeryItems(BakeryItem *);
    void setPricePerUnit(double);
    void setBakeryItemQuantity(double);
    void setRecipe(string);
    void setDisabled(bool);

    // friend functions to be used by main.cpp
    friend void accessMenuDetails(BakeryItem &);

    // destructor
    ~BakeryItem();
};

#endif