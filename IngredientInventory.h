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
    void accessIngredientInventoryDetails(int index) const;
    void checkIngredientInventory() const;
    void addNewInventoryIngredientWeight(string name, double cost, double weight);
    void addNewInventoryIngredientPiece(string name, double cost, int piece);

    // mutator
    void restockIngredientInventory(int index, int quantity);
    void changeIngredientCost(int index, double cost);
    void setIngredientInventory(IngredientInventory * ingredientInventory);
    void setIngredientInventoryPiece(int index, int piece);
    void setIngredientInventoryWeight(int index, double weight);

    // accessor
    static IngredientInventory * getIngredientInventory();
    int getIngredientInventoryCount() const;
    Ingredient getIngredient();
    double getIngredientCost(int) const;
    IngredientInventory * getIngredientInventory(int) const;
    string getIngredientInventoryName(int) const;
    double getIngredientInventoryCost(int) const;
    int getIngredientInventoryPiece(int) const;
    double getIngredientInventoryWeight(int) const;

    // destructor
    ~IngredientInventory();
};

#endif