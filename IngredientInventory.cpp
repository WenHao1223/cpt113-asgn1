#include <iomanip>
#include <fstream>
#include <cmath>

#include "Constant.h"
#include "IngredientInventory.h"

const int MAX_INGREDIENTS_INVENTORY = Constant::MAX_INGREDIENTS_INVENTORY;

IngredientInventory::IngredientInventory() {
  // cout << "IngredientInventory object has been created." << endl;
}

IngredientInventory::IngredientInventory(string name, double cost, double weight) {
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

  this->ingredient = Ingredient(name, cost, weight);

  ingredientInventory[ingredientInventoryCount] = *this;
  ingredientInventoryCount++;

  // cout << "Ingredient " << name << " has been added." << endl;
}

IngredientInventory::IngredientInventory(string name, double cost, int piece) {
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

  this->ingredient = Ingredient(name, cost, piece);
  
  ingredientInventory[ingredientInventoryCount] = *this;
  ingredientInventoryCount++;

  // cout << "Ingredient " << name << " has been added." << endl;
}

void IngredientInventory::displayIngredientInventoryList() const {
  cout << setw(5) << left << "No." << setw(20) << "Ingredient Name" << endl;

  for (int i = 0; i < ingredientInventoryCount; i++) {
    cout << setw(5) << left << to_string(i+1) + "." << ingredientInventory[i].ingredient.getName() << endl;
  }
}

void IngredientInventory::accessIngredientInventoryDetails(int index) const {
  // cout << "address accessing ingredient inventory: " << &ingredient << endl;
  ingredientInventory[index].ingredient.displayIngredientDetails();
}

void IngredientInventory::checkIngredientInventory() const {
  // check all ingredients in inventory
  cout << "+-----+--------------------+-------------------------+" << endl;
  cout << "| " << setw(3) << left << "No." << " | "
      << setw(18) << left << "Ingredient" << " | "
      << setw(12) << left << "Quantity"
      << setw(13) << right << " |" << endl;
  cout << "+-----+--------------------+-------------------------+" << endl;

  for (int i = 0; i < ingredientInventoryCount; i++) {
    cout << "| " << setw(3) << left << (i+1) << " | "
         << setw(18) << left << ingredientInventory[i].ingredient.getName() << " | ";

    // Check if the ingredient is 0 in quantity
    if (ingredientInventory[i].ingredient.getCountable()) {
      cout << setw(12) << right << ingredientInventory[i].ingredient.getPiece();
      cout << setw(13) << right << "piece(s) |" << endl;
    } else {
      cout << setw(12) << right << fixed << setprecision(2) << ingredientInventory[i].ingredient.getWeight();
      cout << setw(13) << right << "gram(s) |" << endl;
    }
  }
  cout << "+-----+--------------------+-------------------------+" << endl;
}

// @TjeEwe require file handling
// update inventory.csv
void IngredientInventory::addNewInventoryIngredientWeight(string name, double cost, double weight) {
  ofstream addInventory;
  addInventory.open("files/IngredientInventory.csv", ios::app);
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

  addInventory << name << "," << cost << "," << weight << ",0\n";
  addInventory.close();
  ingredientInventory[ingredientInventoryCount] = IngredientInventory(name, cost, weight);

  cout << weight << " gram(s) of ingredient " << name << " has been added into inventory." << endl;
}

// @TjeEwe require file handling
// update inventory.csv
void IngredientInventory::addNewInventoryIngredientPiece(string name, double cost, int piece) {
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

  ingredientInventory[ingredientInventoryCount] = IngredientInventory(name, cost, piece);

  cout << piece << " piece(s) of ingredient " << name << " has been added into inventory." << endl;
}

double IngredientInventory::restockIngredientInventory(int index, double quantity) {
  if (quantity < 0) {
    cout << "Restock weight cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return 0;
  }

  if (ingredientInventory[index].ingredient.getCountable()) {
    ingredientInventory[index].ingredient.setPiece(ingredientInventory[index].ingredient.getPiece() + quantity);
    cout << quantity << " piece(s)";
  } else {
    ingredientInventory[index].ingredient.setWeight(ingredientInventory[index].ingredient.getWeight() + quantity);
    cout << quantity << " gram(s)";
  }

  cout << " of " << ingredientInventory[index].ingredient.getName() << " has been restocked." << endl;
  if (ingredientInventory[index].ingredient.getCountable()) {
    cout << "New quantity: " << ingredientInventory[index].ingredient.getPiece() << " piece(s)" << endl;
  } else {
    cout << "New quantity: " << ingredientInventory[index].ingredient.getWeight() << " gram(s)" << endl;
  }

  // calculate the cost of restock
  double cost = ingredientInventory[index].ingredient.getCostPerUnit() * quantity;
  cost = ceil(cost * 100) / 100;

  return cost;
}

void IngredientInventory::changeIngredientCost(int index, double cost) {
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  ingredientInventory[index].ingredient.setCostPerUnit(cost);

  cout << "Cost of ingredient " << ingredientInventory[index].ingredient.getName() << " has been changed." << endl;
  cout << setprecision(2) << fixed;
  cout << "New cost: RM " << ingredientInventory[index].ingredient.getCostPerUnit();
  if (ingredientInventory[index].ingredient.getCountable()) {
    cout << " / piece(s)" << endl;
  } else {
    cout << " / gram(s)" << endl;
  }

  // cout << "address from ingredient inventory ingredient: " << &ingredientInventory[index].ingredient << endl;
}

void IngredientInventory::setIngredientInventory(IngredientInventory * ingredientInventory) {
  this->ingredientInventory = ingredientInventory;
}

void IngredientInventory::setIngredientInventoryPiece(int index, int piece) {
  ingredientInventory[index].ingredient.setPiece(piece);
}

void IngredientInventory::setIngredientInventoryWeight(int index, double weight) {
  ingredientInventory[index].ingredient.setWeight(weight);
}

IngredientInventory * IngredientInventory::getIngredientInventory() {
  // cout << "address: " << ingredientInventory << endl;
  return ingredientInventory;
}

int IngredientInventory::getIngredientInventoryCount() const {
  return ingredientInventoryCount;
}

Ingredient IngredientInventory::getIngredient() {
  // cout << "address: " << &ingredient << endl;
  return ingredient;
}

IngredientInventory * IngredientInventory::getIngredientInventory(int index) const {
  return &ingredientInventory[index];
}

string IngredientInventory::getIngredientInventoryName (int index) const {
  return ingredientInventory[index].ingredient.getName();
}

double IngredientInventory::getIngredientInventoryCost (int index) const {
  return ingredientInventory[index].ingredient.getCostPerUnit();
}

int IngredientInventory::getIngredientInventoryPiece (int index) const {
  return ingredientInventory[index].ingredient.getPiece();
}

double IngredientInventory::getIngredientInventoryWeight (int index) const {
  return ingredientInventory[index].ingredient.getWeight();
}

IngredientInventory::~IngredientInventory() {
  // cout << "Ingredient " << ingredient.getName() << " has been removed." << endl;
}

int IngredientInventory::ingredientInventoryCount = 0;
IngredientInventory * IngredientInventory::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY];