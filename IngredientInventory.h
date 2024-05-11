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
    static IngredientInventory * getIngredientInventory();
    void displayIngredientInventoryList() const;
    void accessIngredientInventoryDetails() const;
    void checkIngredientInventory() const;

    // mutator
    void restockIngredientInventory(int chocie, int quantity);
    void changeIngredientCost(int choice, double cost);

    // accessor
    int getIngredientInventoryCount() const;

    // destructor
    ~IngredientInventory();
};

#endif