#include "Ingredient.h"

Ingredient::Ingredient(string name, double cost, double weight) {
  this->name = name;
  this->cost = cost;
  this->weight = weight;
  cout << "Ingredient " << name << " has been added." << endl;
}

Ingredient::Ingredient(string name, double cost, int piece) {
  this->name = name;
  this->cost = cost;
  this->piece = piece;
  cout << "Ingredient " << name << " has been added." << endl;
}

void Ingredient::displayIngredientDetails() const {
  cout << "Name: " << name << endl;
  cout << "Cost: " << cost << endl;
  cout << "Weight: " << weight << endl;
  cout << "Piece: " << piece << endl;
  cout << endl;
}