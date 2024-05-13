#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>

using namespace std;

class Ingredient {
  private:
    string name;
    double costPerUnit;
    double weight;
    int piece;
    bool countable;
    
  public:
    // Constructor
    Ingredient();
    // uncountable items
    Ingredient(string name, double costPerUnit, double weight);
    // countable items
    Ingredient(string name, double costPerUnit, int piece);

    // member functions
    void displayIngredientDetails() const;

    // accessor
    string getName() const;
    double getCostPerUnit() const;
    double getWeight() const;
    int getPiece() const;
    bool getCountable() const;

    // mutator
    void setCostPerUnit(double);
    void setWeight(double);
    void setPiece(int);
};

#endif