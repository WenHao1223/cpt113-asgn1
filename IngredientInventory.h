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
    static IngredientInventory * ingredientInventory;
  public:
    // constructor
    IngredientInventory();
    // uncountable items
    IngredientInventory(string name, double cost, double weight);
    // countable items
    IngredientInventory(string name, double cost, int piece);
    
    // member functions
    static IngredientInventory * getIngredientInventory();
    void displayIngredientInventoryDetails() const;
    void checkIngredientInventory() const;

    // mutator
    // void restockIngredientInventory(int quantity);

    // accessor
    int getIngredientInventoryCount() const;

    // destructor
    ~IngredientInventory();
};

#endif