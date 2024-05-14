#include "Constant.h" // Include the Constant header file.
#include "BakeryItem.h" // Include the BakeryItem header file.

#include <fstream> // For file handling.

const int MAX_BAKERY_ITEMS = Constant::MAX_BAKERY_ITEMS; // Define the maximum number of bakery items.

/**
 * @file BakeryItem.cpp
 * @brief Implementation file for the BakeryItem class.
 */

/**
 * @class BakeryItem
 * @brief Represents a bakery item.
 */

BakeryItem::BakeryItem() {
  // cout << "BakeryItem object has been created." << endl;
}

BakeryItem::BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (category == "") {
    cout << "Category cannot be empty." << endl;
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

  if (bakeryItemCount == MAX_BAKERY_ITEMS) {
    cout << "Bakery Item has reached maximum capacity." << endl;
    return;
  }

  this->name = name;
  this->category = category;
  this->description = description;
  this->pricePerUnit = pricePerUnit;
  this->ingredient = ingredient;
  this->ingredientCount = ingredientCount;
  this->recipe = recipe;
  this->disabled = disabled;

  this->bakeryItems[bakeryItemCount] = *this;
  // cout << "bakeryItemCount: " << bakeryItemCount << endl;
  bakeryItemCount++;

  cout << category << " " << name << " has been added." << endl;
}

/**
 * @brief Constructs a new BakeryItem object.
 * 
 * @param name The name of the bakery item.
 * @param category The category of the bakery item.
 * @param description The description of the bakery item.
 * @param pricePerUnit The price per unit of the bakery item.
 * @param ingredient An array of ingredients used in the bakery item.
 * @param ingredientCount The number of ingredients in the bakery item.
 * @param recipe The recipe for making the bakery item.
 * @param disabled Indicates whether the bakery item is disabled or not.
 * @param totalWeight The total weight of the bakery item (only applicable for cakes).
 * 
 * @return None.
 */
BakeryItem::BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled, int totalWeight) {
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE);
    return;
  }

  if (category == "") {
    cout << "Category cannot be empty." << endl;
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

  if (bakeryItemCount == MAX_BAKERY_ITEMS) {
    cout << "Bakery Item has reached maximum capacity." << endl;
    return;
  }

  if (category == "Cake" && totalWeight <= 0) {
    cout << "Total weight cannot be zero or negative." << endl;
    cout << "Total weight: " << totalWeight << endl;
    exit(EXIT_FAILURE);
    return;
  }

  this->name = name;
  this->category = category;
  this->description = description;
  this->pricePerUnit = pricePerUnit;
  this->ingredient = ingredient;
  this->ingredientCount = ingredientCount;
  this->recipe = recipe;
  this->disabled = disabled;

  if (category == "Cake") {
    cake = new Cake(totalWeight);
  }

  this->bakeryItems[bakeryItemCount] = *this;
  // cout << "bakeryItemCount: " << bakeryItemCount << endl;
  bakeryItemCount++;

  cout << category << " " << name << " has been added." << endl;
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

string BakeryItem::getBakeryItemCategory() const {
  return category;
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

string BakeryItem::getIngredientName(int index) const {
  return ingredient[index].getName();
}

Cake * BakeryItem::getCake() const {
  return cake;
}

int BakeryItem::getIngredientCount() const {
  return ingredientCount;
}

double BakeryItem::getBakeryItemQuantity() const {
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

void BakeryItem::setBakeryItemQuantity(double quantity) {
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