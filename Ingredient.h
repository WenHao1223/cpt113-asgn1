#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>

using namespace std;

class Ingredient {
  private:
    string name;
    double costPerPiece;
    double weight;
    int piece;
    bool countable;
    
  public:
    // Constructor
    Ingredient();
    // uncountable items
    Ingredient(string name, double costPerPiece, double weight);
    // countable items
    Ingredient(string name, double costPerPiece, int piece);

    // member functions
    void displayIngredientDetails() const;

    // accessor
    string getName() const;
    double getCostPerPiece() const;
    double getWeight() const;
    int getPiece() const;
    bool getCountable() const;

    // mutator
    void setCostPerPiece(double);
    void setWeight(double);
    void setPiece(int);
};

#endif