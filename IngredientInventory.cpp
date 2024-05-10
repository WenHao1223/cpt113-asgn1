#include "IngredientInventory.h"

const int MAX_INGREDIENTS_INVENTORY = 20;

IngredientInventory::IngredientInventory() {
  this->quantity = 0;
}

IngredientInventory::IngredientInventory(string name, double cost, double weight, int quantity) {
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

  if (quantity < 0) {
    cout << "Quantity cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->ingredient = Ingredient(name, cost, weight);
  this->quantity = quantity;

  ingredientInventory[ingredientInventoryCount] = *this;
  ingredientInventoryCount++;

  // cout << "Ingredient " << name << " has been added." << endl;
}

IngredientInventory::IngredientInventory(string name, double cost, int piece, int quantity) {
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

  if (quantity < 0) {
    cout << "Quantity cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->ingredient = Ingredient(name, cost, piece);
  this->quantity = quantity;
  
  ingredientInventory[ingredientInventoryCount] = *this;
  ingredientInventoryCount++;

  // cout << "Ingredient " << name << " has been added." << endl;
}

IngredientInventory * IngredientInventory::getIngredientInventory() {
  // cout << "address: " << ingredientInventory << endl;
  return ingredientInventory;
}

void IngredientInventory::displayIngredientInventoryDetails() const {
  ingredient.displayIngredientDetails();
  cout << "Quantity: " << quantity << endl;
}

void IngredientInventory::checkIngredientInventory() const {
  // check all ingredients in inventory
  cout << "Checking ingredient inventory..." << endl;
  displayIngredientInventoryDetails();
  cout << endl;
}

// void IngredientInventory::restockIngredientInventory(int quantity) {
//   if (quantity < 0) {
//     cout << "Restock quantity cannot be negative." << endl;
//     exit(EXIT_FAILURE);
//     return;
//   }
//
//   this->quantity += quantity;
//   cout << "Ingredient " << ingredient.getName() << " has been restocked." << endl;
// }

IngredientInventory::~IngredientInventory() {
  // cout << "Ingredient " << ingredient.getName() << " has been removed." << endl;
}

int IngredientInventory::ingredientInventoryCount = 0;
IngredientInventory * IngredientInventory::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY];