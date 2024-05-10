#include "Ingredient.h"

Ingredient::Ingredient(string name, double cost, double weight) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (weight < 0) {
    cout << "Weight cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->name = name;
  this->cost = cost;
  this->weight = weight;
  cout << "Ingredient " << name << " has been added." << endl;
}

Ingredient::Ingredient(string name, double cost, int piece) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (piece < 0) {
    cout << "Piece cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

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