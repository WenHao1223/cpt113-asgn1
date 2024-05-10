#ifndef INGREDIENTINVENTORY_H
#define INGREDIENTINVENTORY_H

#include <iostream>
#include <string>

#include "Ingredient.h"

using namespace std;

class IngredientInventory : public Ingredient {
  private:
    int quantity;
    Ingredient ingredient;
    static int ingredientInventoryCount;
    static IngredientInventory * ingredientInventory;
  public:
    // constructor
    IngredientInventory();
    // uncountable items
    IngredientInventory(string name, double cost, double weight, int quantity);
    // countable items
    IngredientInventory(string name, double cost, int piece, int quantity);
    
    // member functions
    static IngredientInventory * getIngredientInventory();
    void displayIngredientInventoryDetails() const;
    void checkIngredientInventory() const;

    // mutator
    // void restockIngredientInventory(int quantity);

    // destructor
    ~IngredientInventory();
};

#endif