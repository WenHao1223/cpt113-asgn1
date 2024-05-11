#include <iomanip>

#include "Ingredient.h"

Ingredient::Ingredient() {
  name = "";
  cost = 0;
  weight = 0;
  piece = 0;
}

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
  this->countable = false;
  // cout << "Ingredient " << name << " has been added." << endl;
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
  this->countable = true;
  // cout << "Ingredient " << name << " has been added." << endl;
}

void Ingredient::displayIngredientDetails() const {
  cout << "Name: " << name << endl;
  cout << setprecision(2) << fixed << "Cost: RM" << cost << endl;
  cout << "Weight: " << weight << endl;
  cout << "Piece: " << piece << endl;
}

string Ingredient::getName() const {
  return name;
}

double Ingredient::getCost() const {
  return cost;
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

void Ingredient::setCost(double cost) {
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->cost = cost;
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