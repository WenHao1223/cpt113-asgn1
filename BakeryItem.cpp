#include "Constant.h"
#include "BakeryItem.h"

const int MAX_BAKERY_ITEMS = Constant::MAX_BAKERY_ITEMS;

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

void BakeryItem::setIngredientCostToInventoryIngredientCost(IngredientInventory * inventoryIngredient) {
  for (int i = 0; i < ingredientCount; i++) {
    for (int j = 0; j < inventoryIngredient->getIngredientInventoryCount(); j++) {
      if (ingredient[i].getName() == inventoryIngredient[j].getName()) {
        cout << "Ingredient " << ingredient[i].getName() << " cost has been set to RM " << inventoryIngredient[j].getCostPerUnit() << endl;
        ingredient[i].setCostPerUnit(inventoryIngredient[j].getCostPerUnit());
      }
    }
  }
}

string BakeryItem::getBakeryItemName() const {
  return name;
}

string BakeryItem::getBakeryItemDescription() const {
  return description;
}

double BakeryItem::getPricePerUnit() const {
  return pricePerUnit;
}

Ingredient * BakeryItem::getIngredient(int index) const {
  return &ingredient[index];
}

int BakeryItem::getIngredientCount() const {
  return ingredientCount;
}

int BakeryItem::getBakeryItemQuantity() const {
  return quantity;
}

string BakeryItem::getRecipe() const {
  return recipe;
}

bool BakeryItem::getDisabled() const {
  return disabled;
}

int BakeryItem::getBakeryItemCount() const {
  return bakeryItemCount;
}

void BakeryItem::setBakeryItems(BakeryItem * bakeryItems) {
  // cout << "Bakery Item Address (from BakeryItem): " << bakeryItems << endl;
  this->bakeryItems = bakeryItems;
}

void BakeryItem::setPricePerUnit(double pricePerUnit) {
  this->pricePerUnit = pricePerUnit;
}

void BakeryItem::setBakeryItemQuantity(int quantity) {
  this->quantity = quantity;
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