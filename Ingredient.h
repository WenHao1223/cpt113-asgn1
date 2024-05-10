#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>

using namespace std;

class Ingredient {
  private:
    string name;
    double cost;
    double weight = 0;
    int piece = 0;
    
  public:
    // Constructor
    // uncountable items
    Ingredient(string name, double cost, double weight);
    // countable items
    Ingredient(string name, double cost, int piece);

    // member functions
    void displayIngredientDetails() const;
};

#endif