#include "BakeryItem.h"

BakeryItem::BakeryItem(string name, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (pricePerUnit < 0) {
    cout << "Price per unit cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (ingredient == nullptr) {
    cout << "Ingredient cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (ingredientCount < 0) {
    cout << "Number of ingredients cannot be negative." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->name = name;
  this->description = description;
  this->pricePerUnit = pricePerUnit;
  this->ingredient = ingredient;
  this->ingredientCount = ingredientCount;
  this->recipe = recipe;
  // cout << "Bakery Item " << name << " has been added." << endl;
}

void BakeryItem::displayBakeryItemDetails() const {
  cout << "Name: " << name << endl;
  cout << "Description: " << description << endl;
  cout << "Price per unit: " << pricePerUnit << endl;
  cout << "Recipe: " << recipe << endl;

  for (int i = 0; i < ingredientCount; i++) {
    cout << "Ingredient " << i + 1 << ":" << endl;
    ingredient[i].displayIngredientDetails();
  }

  cout << "Out of stock: " << disabled << endl;
  cout << endl;
}

BakeryItem::~BakeryItem() {
  delete[] ingredient;
  // cout << "Bakery Item " << name << " has been removed." << endl;
}