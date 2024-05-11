#include <iomanip>

#include "IngredientInventory.h"

const int MAX_INGREDIENTS_INVENTORY = 20;

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

void IngredientInventory::accessIngredientInventoryDetails() const {
  ingredient.displayIngredientDetails();
}

void IngredientInventory::checkIngredientInventory() const {
  // check all ingredients in inventory
  cout << setw(5) << left << "No." << setw(20) << left << "Ingredient" << "Quantity" << endl;

  for (int i = 0; i < ingredientInventoryCount; i++) {
    cout << setw(5) << left << (i+1) << setw(20) << left << ingredientInventory[i].ingredient.getName();
    // Check if the ingredient is 0 in quantity
    if (ingredientInventory[i].ingredient.getCountable()) {
      if (ingredientInventory[i].ingredient.getPiece() == 0) {
        cout << "Out of stock" << endl;
      } else {
        cout << ingredientInventory[i].ingredient.getPiece() << " piece(s)" << endl;
      }
    } else {
      if (ingredientInventory[i].ingredient.getWeight() == 0) {
        cout << 0 << endl;
      } else {
        cout << ingredientInventory[i].ingredient.getWeight() << " gram(s)" << endl;
      }
    }
  }
}

void IngredientInventory::restockIngredientInventory(int choice, int quantity) {
  if (quantity < 0) {
    cout << "Restock weight cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (ingredientInventory[choice].ingredient.getCountable()) {
    ingredientInventory[choice].ingredient.setPiece(ingredientInventory[choice].ingredient.getPiece() + quantity);
  } else {
    ingredientInventory[choice].ingredient.setWeight(ingredientInventory[choice].ingredient.getWeight() + quantity);
  }

  cout << "Ingredient " << ingredientInventory[choice].ingredient.getName() << " has been restocked." << endl;
  if (ingredientInventory[choice].ingredient.getCountable()) {
    cout << "New quantity: " << ingredientInventory[choice].ingredient.getPiece() << " piece(s)" << endl;
  } else {
    cout << "New quantity: " << ingredientInventory[choice].ingredient.getWeight() << " gram(s)" << endl;
  }
}

void IngredientInventory::changeIngredientCost(int choice, double cost) {
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  ingredientInventory[choice].ingredient.setCost(cost);

  cout << "Cost of ingredient " << ingredientInventory[choice].ingredient.getName() << " has been changed." << endl;
  cout << setprecision(2) << fixed;
  cout << "New cost: RM" << ingredientInventory[choice].ingredient.getCost() << endl;
}

void IngredientInventory::setIngredientInventory(IngredientInventory * ingredientInventory) {
  this->ingredientInventory = ingredientInventory;
}

IngredientInventory * IngredientInventory::getIngredientInventory() {
  cout << "address: " << ingredientInventory << endl;
  return ingredientInventory;
}

int IngredientInventory::getIngredientInventoryCount() const {
  return ingredientInventoryCount;
}

IngredientInventory * IngredientInventory::getIngredientInventory(int index) const {
  return &ingredientInventory[index];
}

string IngredientInventory::getIngredientInventoryName (int index) const {
  return ingredientInventory[index].ingredient.getName();
}

IngredientInventory::~IngredientInventory() {
  // cout << "Ingredient " << ingredient.getName() << " has been removed." << endl;
}

int IngredientInventory::ingredientInventoryCount = 0;
IngredientInventory * IngredientInventory::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY];