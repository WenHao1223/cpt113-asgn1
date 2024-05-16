#include <iomanip> // for input/output manipulation
#include <fstream> // for file handling
#include <cmath> // for mathematical functions

#include "Constant.h" // Include the header file that contains the declaration of the Constant class.
#include "IngredientInventory.h" // Include the header file that contains the declaration of the IngredientInventory class.

const int MAX_INGREDIENTS_INVENTORY = Constant::MAX_INGREDIENTS_INVENTORY; // The maximum number of ingredients in the inventory.

/**
 * @file IngredientInventory.cpp
 * @class IngredientInventory
 * @brief This class represents the inventory of ingredients.
 */

/**
 * @brief Default constructor for the IngredientInventory class.
 * 
 * @param None
 * @return None
 */
IngredientInventory::IngredientInventory() {}

/**
 * @brief Constructs an IngredientInventory object with the specified name, cost, and weight.
 * 
 * @param name The name of the ingredient.
 * @param cost The cost of the ingredient.
 * @param weight The weight of the ingredient.
 * 
 * @return None
 * 
 * This constructor checks if the name, cost, and weight are valid. If any of them are invalid,
 * an error message is displayed and the program exits. If the ingredient already exists in
 * the inventory, a message is displayed and the function returns. Otherwise, the ingredient
 * is added to the inventory file and the ingredient object is stored in the ingredientInventory
 * array. Finally, a success message is displayed.
 */
IngredientInventory::IngredientInventory(string name, double cost, double weight) {
  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the cost is negative.
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the weight is negative.
  if (weight < 0) {
    cout << "Weight cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Create a new ingredient object with the specified name, cost, and weight.
  this->ingredient = Ingredient(name, cost, weight);

  // Add the ingredient to the ingredient inventory array.
  ingredientInventory[ingredientInventoryCount] = *this;

  // Increment the ingredient inventory count.
  ingredientInventoryCount++;
}

/**
 * @brief Constructs an IngredientInventory object with the specified name, cost, and piece.
 * 
 * @param name The name of the ingredient.
 * @param cost The cost of the ingredient.
 * @param piece The number of pieces of the ingredient.
 * 
 * @return None
 * 
 * This constructor checks if the name, cost, and piece are valid. If any of them are invalid,
 * an error message is displayed and the program exits. If the ingredient already exists in
 * the inventory, a message is displayed and the function returns. Otherwise, the ingredient
 * is added to the inventory file and the ingredient object is stored in the ingredientInventory
 * array. Finally, a success message is displayed.
 */
IngredientInventory::IngredientInventory(string name, double cost, int piece) {
  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the cost is negative.
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the piece is negative.
  if (piece < 0) {
    cout << "Piece cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Create a new ingredient object with the specified name, cost, and piece.
  this->ingredient = Ingredient(name, cost, piece);
  
  // Add the ingredient to the ingredient inventory array.
  ingredientInventory[ingredientInventoryCount] = *this;

  // Increment the ingredient inventory count.
  ingredientInventoryCount++;
}

/**
 * @brief Displays the list of ingredients in the inventory.
 * 
 * @param None
 * @return None
 */
void IngredientInventory::displayIngredientInventoryList() const {
  cout << "+-----+---------------------------------------------+" << endl;
  cout << "| " << setw(3) << left << "No." << " | " << setw(43) << "Ingredient Name" << " |" << endl;
  cout << "+-----+---------------------------------------------+" << endl;

  for (int i = 0; i < ingredientInventoryCount; i++) {
    cout << "| " << setw(3) << left << to_string(i+1) + "." << " | " << setw(43) << ingredientInventory[i].ingredient.getName() << " |" << endl;
  }
  cout << "+-----+---------------------------------------------+" << endl;
}

/**
 * @brief Displays the details of the ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return None
 */
void IngredientInventory::accessIngredientInventoryDetails(int index) const {
  ingredientInventory[index].ingredient.displayIngredientDetails();
}

/**
 * @brief Displays the details of all ingredients in the inventory.
 * 
 * @param None
 * @return None
 */
void IngredientInventory::checkIngredientInventory() const {
  // check all ingredients in inventory
  cout << "+-----+--------------------+-------------------------+" << endl;
  cout << "| " << setw(3) << left << "No." << " | "
      << setw(18) << left << "Ingredient" << " | "
      << setw(12) << left << "Quantity"
      << setw(13) << right << " |" << endl;
  cout << "+-----+--------------------+-------------------------+" << endl;

  // Display the details of each ingredient in the inventory.
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

/**
 * @brief Adds a new ingredient to the inventory with the specified name, cost, and weight.
 * 
 * @param name The name of the ingredient.
 * @param cost The cost of the ingredient.
 * @param weight The weight of the ingredient.
 * 
 * @return None.
 * 
 * This function checks if the name, cost, and weight are valid. If any of them are invalid,
 * an error message is displayed and the program exits. If the ingredient already exists in
 * the inventory, a message is displayed and the function returns. Otherwise, the ingredient
 * is added to the inventory file and the ingredient object is stored in the ingredientInventory
 * array. Finally, a success message is displayed.
 */
void IngredientInventory::addNewInventoryIngredientWeight(string name, double cost, double weight) {
  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the cost is negative.
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the weight is negative.
  if (weight < 0) {
    cout << "Weight cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }
  
  // Check if ingredient already exists in inventory
  // Check ingredient inventory name from ingredientInventory
  for (int i = 0; i < ingredientInventoryCount; i++) {
    if (ingredientInventory[i].ingredient.getName() == name) {
      cout << "Ingredient " << name << " already exists in inventory." << endl;
      return;
    }
  }

  // file handling to add new ingredient into inventory
  ofstream addInventory;
  addInventory.open("files/IngredientInventory.csv", ios::app);
  addInventory << "\n" << name << "," << cost << "," << weight << ",0,false";
  addInventory.close();

  // Create a new ingredient object with the specified name, cost, and weight.
  ingredientInventory[ingredientInventoryCount] = IngredientInventory(name, cost, weight);

  // Increment the ingredient inventory count.
  cout << weight << " gram(s) of ingredient " << name << " has been added into inventory." << endl;
}

/**
 * @brief Adds a new ingredient to the inventory with the specified name, cost, and piece.
 * 
 * @param name The name of the ingredient.
 * @param cost The cost of the ingredient.
 * @param piece The number of pieces of the ingredient.
 * 
 * @return None.
 * 
 * This function checks if the name, cost, and piece are valid. If any of them are invalid,
 * an error message is displayed and the program exits. If the ingredient already exists in
 * the inventory, a message is displayed and the function returns. Otherwise, the ingredient
 * is added to the inventory file and the ingredient object is stored in the ingredientInventory
 * array. Finally, a success message is displayed.
 */
void IngredientInventory::addNewInventoryIngredientPiece(string name, double cost, int piece) {
  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the cost is negative.
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the piece is negative.
  if (piece < 0) {
    cout << "Piece cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if ingredient already exists in inventory
  // Check ingredient inventory name from ingredientInventory
  for (int i = 0; i < ingredientInventoryCount; i++) {
    if (ingredientInventory[i].ingredient.getName() == name) {
      cout << "Ingredient " << name << " already exists in inventory." << endl;
      return;
    }
  }

  // file handling to add new ingredient into inventory
  ofstream addInventory;
  addInventory.open("files/IngredientInventory.csv", ios::app);
  addInventory << "\n" << name << "," << cost << "," << piece << ",0,false";
  addInventory.close();

  // Create a new ingredient object with the specified name, cost, and piece.
  ingredientInventory[ingredientInventoryCount] = IngredientInventory(name, cost, piece);

  // Increment the ingredient inventory count.
  cout << piece << " piece(s) of ingredient " << name << " has been added into inventory." << endl;
}

/**
 * @brief Removes an ingredient from the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return None.
 * 
 * This function removes the ingredient from the inventory file and the ingredientInventory array.
 * Finally, a success message is displayed.
 */
double IngredientInventory::restockIngredientInventory(int index, double quantity) {
  // check if quantity is negative
  if (quantity < 0) {
    cout << "Restock weight cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return 0;
  }

  // restock ingredient
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
  // cost = cost per unit * quantity
  // round up to 2 decimal places
  double cost = ingredientInventory[index].ingredient.getCostPerUnit() * quantity;
  cost = ceil(cost * 100) / 100;

  // return the cost of restock
  return cost;
}

/**
 * @brief Changes the cost of an ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @param cost The new cost of the ingredient.
 * @return None.
 * 
 * This function changes the cost of the ingredient in the inventory file and the ingredientInventory array.
 * Finally, a success message is displayed.
 */
void IngredientInventory::changeIngredientCost(int index, double cost) {
  // Check if the cost is negative.
  if (cost < 0) {
    cout << "Cost cannot be negative." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // change the cost of ingredient
  ingredientInventory[index].ingredient.setCostPerUnit(cost);

  cout << "Cost of ingredient " << ingredientInventory[index].ingredient.getName() << " has been changed." << endl;
  cout << fixed;
  cout << "New cost: RM " << ingredientInventory[index].ingredient.getCostPerUnit();

  // Check if the ingredient is countable
  if (ingredientInventory[index].ingredient.getCountable()) {
    cout << " / piece(s)" << endl;
  } else {
    cout << " / gram(s)" << endl;
  }
}

/**
 * @brief Sets the ingredient inventory.
 * 
 * @param ingredientInventory The ingredient inventory to set.
 * @return None.
 */
void IngredientInventory::setIngredientInventory(IngredientInventory * ingredientInventory) {
  this->ingredientInventory = ingredientInventory;
}

/**
 * @brief Sets the number of pieces of a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @param piece The new number of pieces of the ingredient.
 * @return None.
 */
void IngredientInventory::setIngredientInventoryPiece(int index, int piece) {
  ingredientInventory[index].ingredient.setPiece(piece);
}

/**
 * @brief Sets the weight of a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @param weight The new weight of the ingredient.
 * @return None.
 */
void IngredientInventory::setIngredientInventoryWeight(int index, double weight) {
  ingredientInventory[index].ingredient.setWeight(weight);
}

/**
 * @brief Get the ingredient inventory.
 * 
 * @return A pointer to the ingredient inventory.
 */
IngredientInventory * IngredientInventory::getIngredientInventory() {
  return ingredientInventory;
}

/**
 * @brief Get the count of ingredients in the inventory.
 * 
 * @return The count of ingredients in the inventory.
 */
int IngredientInventory::getIngredientInventoryCount() const {
  return ingredientInventoryCount;
}

/**
 * @brief Get the ingredient.
 * 
 * @return The ingredient.
 */
Ingredient IngredientInventory::getIngredient() {
  return ingredient;
}

/**
 * @brief Get a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return A pointer to the specific ingredient in the inventory.
 */
IngredientInventory * IngredientInventory::getIngredientInventory(int index) const {
  return &ingredientInventory[index];
}

/**
 * @brief Get the name of a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return The name of the specific ingredient in the inventory.
 */
string IngredientInventory::getIngredientInventoryName (int index) const {
  return ingredientInventory[index].ingredient.getName();
}

/**
 * @brief Get the cost of a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return The cost of the specific ingredient in the inventory.
 */
double IngredientInventory::getIngredientInventoryCost (int index) const {
  return ingredientInventory[index].ingredient.getCostPerUnit();
}

/**
 * @brief Get the number of pieces of a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return The number of pieces of the specific ingredient in the inventory.
 */
int IngredientInventory::getIngredientInventoryPiece (int index) const {
  return ingredientInventory[index].ingredient.getPiece();
}

/**
 * @brief Get the weight of a specific ingredient in the inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @return The weight of the specific ingredient in the inventory.
 */
double IngredientInventory::getIngredientInventoryWeight (int index) const {
  return ingredientInventory[index].ingredient.getWeight();
}

/**
 * @brief Destructor for IngredientInventory.
 */
IngredientInventory::~IngredientInventory() {}

// Static member initialization
int IngredientInventory::ingredientInventoryCount = 0; // Initialize the static member variable ingredientInventoryCount.
IngredientInventory * IngredientInventory::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY]; // Initialize the static member variable ingredientInventory.