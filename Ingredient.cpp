#include <iomanip>

#include "Ingredient.h"

Ingredient::Ingredient() {
  name = "";
  costPerUnit = 0;
  weight = 0;
  piece = 0;
}

Ingredient::Ingredient(string name, double costPerUnit, double weight) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (costPerUnit < 0) {
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
  this->costPerUnit = costPerUnit;
  this->weight = weight;
  this->piece = 0;
  this->countable = false;
  // cout << "Ingredient " << name << " has been added." << endl;
}

Ingredient::Ingredient(string name, double costPerUnit, int piece) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (costPerUnit < 0) {
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
  this->costPerUnit = costPerUnit;
  this->weight = 0;
  this->piece = piece;
  this->countable = true;
  // cout << "Ingredient " << name << " has been added." << endl;
}

void Ingredient::displayIngredientDetails() const {
  cout << "Name: " << name << endl;
  cout << setprecision(2) << fixed << "Cost: RM " << costPerUnit;
  if (countable) {
    cout << " / gram(s)" << endl;
    cout << "Piece: " << piece << " piece(s)" << endl;
  } else {
    cout << " / piece(s)" << endl;
    cout << "Weight: " << weight << " gram(s)" << endl;
  }
}

string Ingredient::getName() const {
  return name;
}

double Ingredient::getCostPerUnit() const {
  return costPerUnit;
}

double Ingredient::getWeight() const {
  return weight;
}

int Ingredient::getPiece() const {
  return piece;
}

bool Ingredient::getCountable() const {
  return countable;
}

void Ingredient::setCostPerPiece(double costPerUnit) {
  if (costPerUnit < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->costPerUnit = costPerUnit;
}

void Ingredient::setWeight(double weight) {
  if (weight < 0) {
    cout << "Weight cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->weight = weight;
}

void Ingredient::setPiece(int piece) {
  if (piece < 0) {
    cout << "Piece cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->piece = piece;
}