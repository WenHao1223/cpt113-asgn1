#ifndef INGREDIENTINVENTORY_H
#define INGREDIENTINVENTORY_H

#include <iostream>
#include <string>

#include "Ingredient.h"

using namespace std;

class IngredientInventory : public Ingredient {
  private:
    Ingredient ingredient;
    static int ingredientInventoryCount;
    static IngredientInventory * ingredientInventory; // store here
  public:
    // constructor
    IngredientInventory();
    // uncountable items
    IngredientInventory(string name, double cost, double weight);
    // countable items
    IngredientInventory(string name, double cost, int piece);
    
    // member functions
    void displayIngredientInventoryList() const;
    void accessIngredientInventoryDetails() const;
    void checkIngredientInventory() const;

    // mutator
    void restockIngredientInventory(int chocie, int quantity);
    void changeIngredientCost(int index, double cost);
    void setIngredientInventory(IngredientInventory * ingredientInventory);

    // accessor
    static IngredientInventory * getIngredientInventory();
    int getIngredientInventoryCount() const;
    IngredientInventory * getIngredientInventory(int) const;
    string getIngredientInventoryName(int) const;
    double getIngredientInventoryCost(int) const;

    // destructor
    ~IngredientInventory();
};

#endif