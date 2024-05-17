#include "Constant.h" // Include the Constant header file.
#include "BakeryItem.h" // Include the BakeryItem header file.

#include <fstream> // For file handling.
#include <iomanip> // For input/output manipulation.

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

/**
 * @file BakeryItem.cpp
 * @brief Implementation of the BakeryItem class.
 */

/**
 * @class BakeryItem
 * @brief Represents a bakery item.
 */

/**
 * @brief Constructs a new BakeryItem object.
 * 
 * @param name The name of the bakery item.
 * @param category The category of the bakery item.
 * @param description The description of the bakery item.
 * @param pricePerUnit The price per unit of the bakery item.
 * @param ingredient An array of ingredients used in the bakery item.
 * @param ingredientCount The number of ingredients in the bakery item.
 * @param recipe The recipe of the bakery item.
 * @param disabled Indicates whether the bakery item is disabled or not.
 * 
 * @return None.
 */
BakeryItem::BakeryItem(string name, string category, string description, double pricePerUnit, Ingredient * ingredient, int ingredientCount, string recipe, bool disabled) {
  // Check if the name is empty
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the category is empty
  if (category == "") {
    cout << "Category cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the price per unit is negative
  if (pricePerUnit < 0) {
    cout << "Price per unit cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the ingredient is empty
  if (ingredient == nullptr) {
    cout << "Ingredient cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the ingredient count is negative
  if (ingredientCount < 0) {
    cout << "Number of ingredients cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the bakery item has reached maximum capacity
  if (bakeryItemCount == MAX_BAKERY_ITEMS) {
    cout << "Bakery Item has reached maximum capacity." << endl;
    return;
  }

  // Set the member variables
  this->name = name;
  this->category = category;
  this->description = description;
  this->pricePerUnit = pricePerUnit;
  this->ingredient = ingredient;
  this->ingredientCount = ingredientCount;
  this->recipe = recipe;
  this->disabled = disabled;

  // Add the bakery item to the bakeryItems array
  this->bakeryItems[bakeryItemCount] = *this;
  bakeryItemCount++;

  // cout << category << " '" << name << "' has been added." << endl;
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
  // Check if the name is empty
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the category is empty
  if (category == "") {
    cout << "Category cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the price per unit is negative
  if (pricePerUnit < 0) {
    cout << "Price per unit cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the ingredient is empty
  if (ingredient == nullptr) {
    cout << "Ingredient cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the ingredient count is negative
  if (ingredientCount < 0) {
    cout << "Number of ingredients cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Check if the bakery item has reached maximum capacity
  if (bakeryItemCount == MAX_BAKERY_ITEMS) {
    cout << "Bakery Item has reached maximum capacity." << endl;
    return;
  }

  // Check if the total weight is zero or negative
  // Only applicable for cakes
  if (category == "Cake" && totalWeight <= 0) {
    cout << "Total weight cannot be zero or negative." << endl;
    cout << "Total weight: " << totalWeight << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code
    return;
  }

  // Set the member variables
  this->name = name;
  this->category = category;
  this->description = description;
  this->pricePerUnit = pricePerUnit;
  this->ingredient = ingredient;
  this->ingredientCount = ingredientCount;
  this->recipe = recipe;
  this->disabled = disabled;

  // Create a Cake object if the category is Cake
  if (category == "Cake") {
    cake = Cake(totalWeight);
  }

  // cout << category << " '" << name << "' has been added." << endl;

  // Add the bakery item to the bakeryItems array
  this->bakeryItems[bakeryItemCount] = *this;
  
  bakeryItemCount++;
}

/**
 * @brief Displays the details of the bakery item.
 * 
 * @param None
 * @return None
 */
void BakeryItem::displayBakeryItemDetails() const {
  // Display the bakery item details
  cout << "Name: " << name << endl;
  cout << "Category: " << category << endl;
  cout << "Description: " << description << endl;
  cout << "Price per unit: " << pricePerUnit << endl;
  cout << "Recipe: " << recipe << endl;

  // Display the total weight if the category is Cake
  if (category == "Cake") {
    cout << "Total weight: " << cake.getTotalWeight() << "g" << endl;
  }

  // Display the ingredients
  for (int i = 0; i < ingredientCount; i++) {
    cout << "Ingredient " << i + 1 << ":" << endl;
    ingredient[i].displayIngredientDetails();
  }

  // Display the disabled status
  cout << "Out of stock: " << disabled << endl;
  cout << endl;
}

/**
 * @class BakeryItem
 * @brief Represents a bakery item.
 */

/**
 * @brief Calculates the total cost of the bakery item.
 * 
 * This function calculates the total cost of the bakery item by iterating through
 * the ingredients and adding up the cost based on the quantity and unit price.
 * 
 * @return The total cost of the bakery item.
 */
double BakeryItem::calculateCost() const {
  double totalCost = 0; // Initialize the total cost to zero

  // Iterate through the ingredients
  // Calculate the total cost based on the quantity and unit price
  // Add the cost to the total cost
  for (int i = 0; i < ingredientCount; i++) {
    if (ingredient[i].getCountable()) {
      totalCost += ingredient[i].getCostPerUnit() * ingredient[i].getPiece();
    } else {
      totalCost += ingredient[i].getCostPerUnit() * ingredient[i].getWeight();
    }
  }

  // Return the total cost
  return totalCost;
}

/**
 * @brief Calculates the profit of the bakery item.
 * 
 * This function calculates the profit of the bakery item by subtracting the total cost
 * from the price per unit.
 * 
 * @return The profit of the bakery item.
 */
double BakeryItem::calculateProfit() const {
  return pricePerUnit - calculateCost();
}

/**
 * @brief Sets the ingredient cost of the bakery item to the cost of the corresponding ingredient in the inventory.
 * 
 * This function iterates through each ingredient of the bakery item and compares its name with the ingredients in the inventory.
 * If a match is found, the cost of the bakery item's ingredient is set to the cost per unit of the corresponding inventory ingredient.
 * 
 * @param inventoryIngredient A pointer to the IngredientInventory object containing the inventory of ingredients.
 */
void BakeryItem::setIngredientCostToInventoryIngredientCost(IngredientInventory * inventoryIngredient) {
  // Iterate through each ingredient of the bakery item
  for (int i = 0; i < ingredientCount; i++) {
    // Iterate through each ingredient in the inventory
    for (int j = 0; j < inventoryIngredient->getIngredientInventoryCount(); j++) {
      // Compare the name of the bakery item's ingredient with the name of the inventory ingredient
      if (ingredient[i].getName() == inventoryIngredient[j].getName()) {
        cout << "Ingredient " << ingredient[i].getName() << " cost has been set to RM " << inventoryIngredient[j].getCostPerUnit() << endl;

        // Set the cost per unit of the bakery item's ingredient to the cost per unit of the inventory ingredient
        ingredient[i].setCostPerUnit(inventoryIngredient[j].getCostPerUnit());
      }
    }
  }
}

/**
 * @brief Get the name of the bakery item.
 * 
 * @return The name of the bakery item.
 */
string BakeryItem::getBakeryItemName() const {
  return name;
}

/**
 * @brief Get the category of the bakery item.
 * 
 * Category - Cake / Cookie
 * 
 * @return The category of the bakery item.
 */
string BakeryItem::getBakeryItemCategory() const {
  return category;
}

/**
 * @brief Get the description of the bakery item.
 * 
 * @return The description of the bakery item.
 */
string BakeryItem::getBakeryItemDescription() const {
  return description;
}

/**
 * @brief Get the price per unit of the bakery item.
 * 
 * @return The price per unit of the bakery item.
 */
double BakeryItem::getPricePerUnit() const {
  return pricePerUnit;
}

/**
 * @brief Returns the ingredient at the specified index.
 * 
 * @param index The index of the ingredient to retrieve.
 * @return A pointer to the ingredient at the specified index.
 */
Ingredient * BakeryItem::getIngredient(int index) const {
  return &ingredient[index];
}

/**
 * @brief Get the name of the ingredient at the specified index.
 * 
 * @param index The index of the ingredient.
 * @return The name of the ingredient at the specified index.
 */
string BakeryItem::getIngredientName(int index) const {
  return ingredient[index].getName();
}

/**
 * @brief Get the cake object
 * @param None.
 * @return Cake object.
 */
Cake BakeryItem::getCake() const {
  return cake;
}

/**
 * @brief Get the number of ingredients in the bakery item.
 * 
 * @return The number of ingredients.
 */
int BakeryItem::getIngredientCount() const {
  return ingredientCount;
}

/**
 * @brief Get the quantity of the bakery item.
 * 
 * @return The quantity of the bakery item.
 */
double BakeryItem::getBakeryItemQuantity() const {
  return quantity;
}

/**
 * @brief Get the recipe of the bakery item.
 * 
 * @return The recipe of the bakery item as a string.
 */
string BakeryItem::getRecipe() const {
  return recipe;
}

/**
 * @brief Get the disabled status of the bakery item.
 * 
 * @return true if the bakery item is disabled, false otherwise.
 */
bool BakeryItem::getDisabled() const {
  return disabled;
}

/**
 * @brief Get the count of bakery items.
 * 
 * @return The count of bakery items.
 */
int BakeryItem::getBakeryItemCount() const {
  return bakeryItemCount;
}

/**
 * @brief Sets the bakery items for the BakeryItem object.
 * 
 * This function sets the bakery items for the BakeryItem object.
 * 
 * @param bakeryItems A pointer to an array of BakeryItem objects.
 * 
 * @return None.
 */
void BakeryItem::setBakeryItems(BakeryItem * bakeryItems) {
  this->bakeryItems = bakeryItems;
}

/**
 * @brief Sets the price per unit of the bakery item.
 * 
 * @param pricePerUnit The price per unit to be set.
 * 
 * @return None.
 */
void BakeryItem::setPricePerUnit(double pricePerUnit) {
  this->pricePerUnit = pricePerUnit;
}

/**
 * @brief Sets the quantity of the bakery item.
 * 
 * This function sets the quantity of the bakery item to the specified value.
 * 
 * @param quantity The quantity of the bakery item.
 */
void BakeryItem::setBakeryItemQuantity(double quantity) {
  this->quantity = quantity;
}

/**
 * @brief Sets the recipe for the bakery item.
 * 
 * @param recipe The recipe to set for the bakery item.
 */
void BakeryItem::setRecipe(string recipe) {
  this->recipe = recipe;
}

/**
 * @brief Sets the disabled status of the bakery item.
 * 
 * @param disabled The disabled status to set.
 * @return None.
 */
void BakeryItem::setDisabled(bool disabled) {
  this->disabled = disabled;
}

/**
 * @brief Destructor for the BakeryItem class.
 * 
 * This destructor is responsible for cleaning up the resources used by a BakeryItem object.
 * 
 * @param None.
 * @return None.
 */
BakeryItem::~BakeryItem() {
  // cout << "Bakery Item " << name << " has been removed." << endl;
}

int BakeryItem::bakeryItemCount = 0; // Initialize the bakery item count to zero
BakeryItem * BakeryItem::bakeryItems = new BakeryItem[MAX_BAKERY_ITEMS]; // Initialize the bakery items array with the maximum number of bakery items