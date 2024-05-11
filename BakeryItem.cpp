#include "BakeryItem.h"

const int MAX_BAKERY_ITEMS = 10;

BakeryItem::BakeryItem() {
  // name = "";
  // description = "";
  // pricePerUnit = 0;
  // ingredient = nullptr;
  // ingredientCount = 0;
  // recipe = "";
  // disabled = false;

  // cout << "BakeryItem object has been created." << endl;
}

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

  this->bakeryItems[bakeryItemCount] = *this;
  // cout << "bakeryItemCount: " << bakeryItemCount << endl;
  bakeryItemCount++;

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

double BakeryItem::calculateCost() const {
  double totalCost = 0;

  for (int i = 0; i < ingredientCount; i++) {
    if (ingredient[i].getCountable()) {
      totalCost += ingredient[i].getCostPerUnit() * ingredient[i].getPiece();
    } else {
      totalCost += ingredient[i].getCostPerUnit() * ingredient[i].getWeight();
    }
  }

  return totalCost;
}

double BakeryItem::calculateProfit() const {
  return pricePerUnit - calculateCost();
}

int BakeryItem::getBakeryItemCount() const {
  return bakeryItemCount;
}

string BakeryItem::getBakeryItemName() const {
  return name;
}

double BakeryItem::getPricePerUnit() const {
  return pricePerUnit;
}

string BakeryItem::getRecipe() const {
  return recipe;
}

void BakeryItem::setBakeryItems(BakeryItem * bakeryItems) {
  // cout << "Bakery Item Address (from BakeryItem): " << bakeryItems << endl;
  this->bakeryItems = bakeryItems;
}

void BakeryItem::setPricePerUnit(double pricePerUnit) {
  this->pricePerUnit = pricePerUnit;
}

void BakeryItem::setRecipe(string recipe) {
  this->recipe = recipe;
}

void BakeryItem::setDisabled(bool disabled) {
  this->disabled = disabled;
}

BakeryItem::~BakeryItem() {
  // cout << "Bakery Item " << name << " has been removed." << endl;
}

int BakeryItem::bakeryItemCount = 0;
BakeryItem * BakeryItem::bakeryItems = new BakeryItem[MAX_BAKERY_ITEMS];